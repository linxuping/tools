/* vim:set ft=c ts=2 sw=2 sts=2 et cindent: */
/*
 * ***** BEGIN LICENSE BLOCK *****
 * Version: MIT
 *
 * Portions created by Alan Antonuk are Copyright (c) 2012-2013
 * Alan Antonuk. All Rights Reserved.
 *
 * Portions created by VMware are Copyright (c) 2007-2012 VMware, Inc.
 * All Rights Reserved.
 *
 * Portions created by Tony Garnock-Jones are Copyright (c) 2009-2010
 * VMware, Inc. and Tony Garnock-Jones. All Rights Reserved.  *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * ***** END LICENSE BLOCK ***** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <errno.h>
#include <amqp_tcp_socket.h>
#include <amqp.h>
#include <amqp_framing.h>
#include <assert.h>
#include "utils.h"

#define SUMMARY_EVERY_US 1000000

#ifdef WIN32
#define snprintf _snprintf
#endif

static void run(amqp_connection_state_t conn)
{
	uint64_t start_time = now_microseconds();
	int received = 0;
	int previous_received = 0;
	uint64_t previous_report_time = start_time;
	uint64_t next_summary_time = start_time + SUMMARY_EVERY_US;

	amqp_frame_t frame;

	uint64_t now;
	int i=0;
	while (1) {
		amqp_rpc_reply_t ret;
		amqp_envelope_t envelope;

		now = now_microseconds();
		if (now > next_summary_time) {
			int countOverInterval = received - previous_received;
			double intervalRate = countOverInterval / ((now - previous_report_time) / 1000000.0);
			//printf("%d ms: Received %d - %d since last report (%d Hz)\n",
			//		(int)(now - start_time) / 1000, received, countOverInterval, (int) intervalRate);

			previous_received = received;
			previous_report_time = now;
			next_summary_time += SUMMARY_EVERY_US;
		}

		amqp_maybe_release_buffers(conn);
		ret = amqp_consume_message(conn, &envelope, NULL, 0);
		//printf("recv: %s \n",(char*)envelope.message.body.bytes);

		for(i=0; i<10000000; ++i);

		if (AMQP_RESPONSE_NORMAL != ret.reply_type) {
			printf("--1----------------------------->>>>\n");
			if (AMQP_RESPONSE_LIBRARY_EXCEPTION == ret.reply_type &&
					AMQP_STATUS_UNEXPECTED_STATE == ret.library_error) {
				if (AMQP_STATUS_OK != amqp_simple_wait_frame(conn, &frame)) {
					return;
				}

				if (AMQP_FRAME_METHOD == frame.frame_type) {
					switch (frame.payload.method.id) {
						case AMQP_BASIC_ACK_METHOD:
							/* if we've turned publisher confirms on, and we've published a message
							 * here is a message being confirmed
							 */

							break;
						case AMQP_BASIC_RETURN_METHOD:
							/* if a published message couldn't be routed and the mandatory flag was set
							 * this is what would be returned. The message then needs to be read.
							 */
							{
								amqp_message_t message;
								ret = amqp_read_message(conn, frame.channel, &message, 0);
								if (AMQP_RESPONSE_NORMAL != ret.reply_type) {
									return;
								}

								amqp_destroy_message(&message);
							}

							break;

						case AMQP_CHANNEL_CLOSE_METHOD:
							/* a channel.close method happens when a channel exception occurs, this
							 * can happen by publishing to an exchange that doesn't exist for example
							 *
							 * In this case you would need to open another channel redeclare any queues
							 * that were declared auto-delete, and restart any consumers that were attached
							 * to the previous channel
							 */
							return;

						case AMQP_CONNECTION_CLOSE_METHOD:
							/* a connection.close method happens when a connection exception occurs,
							 * this can happen by trying to use a channel that isn't open for example.
							 *
							 * In this case the whole connection must be restarted.
							 */
							return;

						default:
							fprintf(stderr ,"An unexpected method was received %d\n", frame.payload.method.id);
							return;
					}
				}
			}

		} else {
			amqp_destroy_envelope(&envelope);
		}

		received++;
	}
}
const char *amqp_server_exception_string(amqp_rpc_reply_t r)
{
	int res;
	static char s[512];

	switch (r.reply.id) {
		case AMQP_CONNECTION_CLOSE_METHOD: {
							amqp_connection_close_t *m
								 = (amqp_connection_close_t *)r.reply.decoded;
							res = snprintf(s, sizeof(s), "server connection error %d, message: %.*s",
									m->reply_code,
									(int)m->reply_text.len,
									(char *)m->reply_text.bytes);
							break;
						}

		case AMQP_CHANNEL_CLOSE_METHOD: {
							amqp_channel_close_t *m
								= (amqp_channel_close_t *)r.reply.decoded;
							res = snprintf(s, sizeof(s), "server channel error %d, message: %.*s",
									m->reply_code,
									(int)m->reply_text.len,
									(char *)m->reply_text.bytes);
							break;
						}

		default:
						res = snprintf(s, sizeof(s), "unknown server error, method id 0x%08X",
								r.reply.id);
						break;
	}

	return res >= 0 ? s : NULL;
}

const char *amqp_rpc_reply_string(amqp_rpc_reply_t r)
{
	switch (r.reply_type) {
		case AMQP_RESPONSE_NORMAL:
			return "normal response";

		case AMQP_RESPONSE_NONE:
			return "missing RPC reply type";

		case AMQP_RESPONSE_LIBRARY_EXCEPTION:
			return amqp_error_string2(r.library_error);

		case AMQP_RESPONSE_SERVER_EXCEPTION:
			return amqp_server_exception_string(r);

		default:
			abort();
	}
}

void die_rpc(amqp_rpc_reply_t r, const char *fmt, ...)
{
	va_list ap;

	if (r.reply_type == AMQP_RESPONSE_NORMAL) {
		return;
	}

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fprintf(stderr, ": %s\n", amqp_rpc_reply_string(r));
	exit(1);
} 
void die_errno(int err, const char *fmt, ...)
{
	va_list ap;

	if (err == 0) {
		return;
	}

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fprintf(stderr, ": %s\n", strerror(err));
	exit(1);
}

void die_amqp_error(int err, const char *fmt, ...)
{
	va_list ap;

	if (err >= 0) {
		return;
	}

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fprintf(stderr, ": %s\n", amqp_error_string2(err));
	exit(1);
}


void write_all(int fd, amqp_bytes_t data)
{ 
	while (data.len > 0) {
		ssize_t res = write(fd, data.bytes, data.len);
		if (res < 0) {
			die_errno(errno, "write");
		}

		data.len -= res;  
		data.bytes = (char *)data.bytes + res;
		printf("buf:%s \n",(char*)data.bytes);
	}
}   

void copy_body(amqp_connection_state_t conn, int fd)
{
	size_t body_remaining;
	amqp_frame_t frame;

	int res = amqp_simple_wait_frame(conn, &frame);
	die_amqp_error(res, "waiting for header frame");
	if (frame.frame_type != AMQP_FRAME_HEADER) {
		die("expected header, got frame type 0x%X",
				frame.frame_type);
	}

	body_remaining = frame.payload.properties.body_size;
	while (body_remaining) {
		res = amqp_simple_wait_frame(conn, &frame);
		die_amqp_error(res, "waiting for body frame");
		if (frame.frame_type != AMQP_FRAME_BODY) {
			die("expected body, got frame type 0x%X", frame.frame_type);
		}

		write_all(fd, frame.payload.body_fragment);
		body_remaining -= frame.payload.body_fragment.len;
	}
}



int main(/*int argc, char const *const *argv*/)
{
	char const *hostname;
	int port, status;
	char const *exchange;
	char const *routingkey;
	char const *messagebody;
	amqp_socket_t *socket = NULL;
	amqp_connection_state_t conn;
	amqp_rpc_reply_t t;
	int i = 0;

	/*
	   if (argc < 6) {
	   fprintf(stderr, "Usage: amqp_sendstring host port exchange routingkey messagebody\n");
	   return 1;
	   }*/

	hostname = "192.168.29.131";
	port = 5672;
	exchange = "topic_logs";
	routingkey = "linxpq1";
	messagebody = "hello,world";

	conn = amqp_new_connection();
	socket = amqp_tcp_socket_new(conn); if (!socket) {
		die("creating TCP socket");
	}

	status = amqp_socket_open(socket, hostname, port);
	if (status) {
		die("opening TCP socket");
	}

	die_on_amqp_error(amqp_login(conn, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, "test_user", "test_user"), "Logging in");
	amqp_channel_open(conn, 1);
	die_on_amqp_error(amqp_get_rpc_reply(conn), "Opening channel");
	printf("body: %s \n",messagebody);

	//amqp_exchange_declare(conn, 1, amqp_cstring_bytes(exchange), amqp_cstring_bytes("topic"),
	//		0, 0, 0, 0, amqp_empty_table);
	//die_on_amqp_error(amqp_get_rpc_reply(conn), "Declaring exchange");
	//amqp_bytes_t queuename = amqp_cstring_bytes("linxpq1");
	//amqp_basic_consume(conn, 1, amqp_cstring_bytes("linxpq2"), amqp_empty_bytes, 0, 1, 0, amqp_empty_table);
	//die_on_amqp_error(amqp_get_rpc_reply(conn), "Consuming");
	//run(conn);

	while (1){
		t = amqp_basic_get(conn, 1, amqp_cstring_bytes("linxpq1"), 1);
		//die_rpc(t, "basic.get");
		copy_body(conn, 1);	
		for(i=0; i<1000000000; ++i);
	}

	die_on_amqp_error(amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS), "Closing channel");
	die_on_amqp_error(amqp_connection_close(conn, AMQP_REPLY_SUCCESS), "Closing connection");
	die_on_error(amqp_destroy_connection(conn), "Ending connection");
	return 0;
}

