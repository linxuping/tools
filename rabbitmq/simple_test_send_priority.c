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
 * ***** END LICENSE BLOCK *****
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <amqp_tcp_socket.h>
#include <amqp.h>
#include <amqp_framing.h>
#include "utils.h"

int main(/*int argc, char const *const *argv*/)
{
	char const *hostname;
	int port, status;
	char const *exchange;
	//char const *routingkey;
	//char const *messagebody;
	amqp_socket_t *socket = NULL;
	amqp_connection_state_t conn;
	amqp_bytes_t queuename1;
	amqp_bytes_t queuename2;
	amqp_basic_properties_t props;
	int i = 0;

	/*
	   if (argc < 6) {
	   fprintf(stderr, "Usage: amqp_sendstring host port exchange routingkey messagebody\n");
	   return 1;
	   }*/

	hostname = "192.168.29.131";
	port = 5672;
	exchange = "topic_logs";
	//routingkey = "linxpq1";
	//messagebody = "hello,world";

	conn = amqp_new_connection();

	socket = amqp_tcp_socket_new(conn);
	if (!socket) {
		die("creating TCP socket");
	}

	status = amqp_socket_open(socket, hostname, port);
	if (status) {
		die("opening TCP socket");
	}

	die_on_amqp_error(amqp_login(conn, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, "test_user", "test_user"), "Logging in");
	amqp_channel_open(conn, 1);
	die_on_amqp_error(amqp_get_rpc_reply(conn), "Opening channel");

	amqp_exchange_declare(conn, 1, amqp_cstring_bytes(exchange), amqp_cstring_bytes("topic"),
			0, 0, 0, 0, amqp_empty_table);
	die_on_amqp_error(amqp_get_rpc_reply(conn), "Declaring exchange");

	queuename1 = amqp_cstring_bytes("linxpq1");
	queuename2 = amqp_cstring_bytes("linxpq2");

	{
		amqp_table_entry_t inner_entries[1];
		amqp_table_t inner_table;
		inner_entries[0].key = amqp_cstring_bytes("x-max-priority");
		inner_entries[0].value.kind = AMQP_FIELD_KIND_I32;
		inner_entries[0].value.value.i32 = 10;
		inner_table.num_entries = 1;
		inner_table.entries = inner_entries;

		{
			amqp_queue_declare_ok_t *r = amqp_queue_declare(conn, 1, queuename1, 0, 1, 0, 0, inner_table);
			die_on_amqp_error(amqp_get_rpc_reply(conn), "Declaring queue");
			queuename1 = amqp_bytes_malloc_dup(r->queue);
			if (queuename1.bytes == NULL) {
				fprintf(stderr, "Out of memory while copying queue name");
				return 1;
			}
			amqp_queue_bind(conn, 1, queuename1, amqp_cstring_bytes(exchange), amqp_cstring_bytes("zb.*"),amqp_empty_table);
		}
		{
			amqp_queue_declare_ok_t *r = amqp_queue_declare(conn, 1, queuename2, 0, 1, 0, 0, inner_table);
			die_on_amqp_error(amqp_get_rpc_reply(conn), "Declaring queue");
			queuename2 = amqp_bytes_malloc_dup(r->queue);
			if (queuename2.bytes == NULL) {
				fprintf(stderr, "Out of memory while copying queue name");
				return 1;
			}
			amqp_queue_bind(conn, 1, queuename2, amqp_cstring_bytes(exchange), amqp_cstring_bytes("zb"),amqp_empty_table);
		}


		props._flags = AMQP_BASIC_PRIORITY_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG;
		//props.content_type = amqp_cstring_bytes("text/plain");
		props.delivery_mode = 2; /* persistent delivery mode */
		props.priority = 10; /* persistent delivery mode */
		for (i=0; i<2; ++i)
		{
			die_on_error(amqp_basic_publish(conn,
						1,
						amqp_cstring_bytes(exchange),
						amqp_cstring_bytes("zb.yy"),
						0,
						0,
						&props,
						amqp_cstring_bytes("it is zb.yy, high priority=10")),
					"Publishing");
			printf("send to zb.yy \n");
		}
		for (i=0; i<3; ++i)
		{
			die_on_error(amqp_basic_publish(conn,
						1,
						amqp_cstring_bytes(exchange),
						amqp_cstring_bytes("zb"),
						0,
						0,
						&props,
						amqp_cstring_bytes("it is zb, high priority = 10")),
					"Publishing");
			printf("send to zb \n");
		}

		printf("++ send finish.\n");
		fflush(stdout);
	}

	die_on_amqp_error(amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS), "Closing channel");
	die_on_amqp_error(amqp_connection_close(conn, AMQP_REPLY_SUCCESS), "Closing connection");
	die_on_error(amqp_destroy_connection(conn), "Ending connection");
	while(1);
	return 0;
}

