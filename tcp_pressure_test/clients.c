#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

const int max_size = 10000;
const int port_size = 65535;

bool b[port_size] = {false};
int count = 0;
int existc = 0;
inline bool is_exists(int fd){
	if (b[fd-1]){
		++existc;
		return true; }
	b[fd-1] = 1;
	++count;
	return false;
}
/*
inline int get_count(){
	int count = 0;
	for (int i=0; i<port_size; ++i){
		if (b[i]) ++count;
	}
	return count;
}*/

int main()
{
	int fd,ret,len,port;
	sockaddr_in addr,addrmy;
	time_t t0 = time(0);
	int start=0,end=0;
	for (int i=0; i<max_size; ++i){
		fd = socket(AF_INET, SOCK_STREAM, 0);
		if (fd < 0)
			printf("error: %s \n",strerror(errno));
		bzero(&addr, sizeof(addr));
		addr.sin_family=AF_INET;
		addr.sin_port=htons(61021);
		addr.sin_addr.s_addr=inet_addr("127.0.0.1");
		ret = connect(fd, (sockaddr*)&addr, sizeof(sockaddr_in));
		if (ret != 0)
			printf("error: %s \n",strerror(errno));
		memset(&addrmy, 0, sizeof(addrmy));
		len = sizeof(addrmy);
		ret = getsockname(fd, (sockaddr*)&addrmy, (socklen_t*)&len);
		port = ntohs(addrmy.sin_port);
		if (i == 0)
			start = port;
		else if (i == max_size-1)
			end = port;
		if (ret != 0)
			printf("get sockname failed .\n");
		if ( is_exists(port) )
			;//printf("port exist: %d \n",port);
		//printf("port : %d \n",port);
		close(fd);
	}
	printf("time0:%ld time1:%ld start:%d end:%d count:%d existc:%d \n",t0, time(0), start, end, count, existc);
	return 0;
}

