import struct
def queue_in(qname, weight, data) :
	data = str(data)
	print data
	data_len = len(data) + 20
	print data_len
	bin_str = struct.pack("4I", data_len, 0, int(qname), int(weight))
	print len(bin_str)
	char_ords = map(ord, data)
	print char_ords
	for v in char_ords:
		bin_str += struct.pack("B", v)
	bin_str += struct.pack("4B", 0XFF, 0XFF, 0XFF, 0XFF)
	print bin_str,len(bin_str)
		#self.__client.send(bin_str)

queue_in(8, 0, "hello")

