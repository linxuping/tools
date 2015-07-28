/*
 * doc: http://blog.csdn.net/jackyvan/article/details/5349724
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	int a, b, c, d;
	char cc;
	char buf[16];
	sscanf("2006:03:18:a", "%d:%d:%d:%c", &a, &b, &c, &cc); 
	printf("%d %d %d %c\n",a,b,c,cc);

	a = -1;
	sscanf("123abc456", "%d", &a);
	printf("%d\n",a);

	a = -1;
	sscanf("123abc456", "%s%d", buf,&a);
	printf("%s %d\n",buf,a);

	a = -1;
	sscanf("123abc456", "%2d", &a);
	printf("%d\n",a);

	sscanf("123^^^abc456", "%[12^34]", buf); //'^'作为字符匹配
	printf("%s\n",buf);

	sscanf("123:abc:456", "%*d:%*[^:]:%s", buf);  //error: "%*d:%*s:%s"
	printf("%s\n",buf);

	memset(buf, 0, 16);
	sscanf("hello, world", "%*s%s", buf);  //" "
	printf("%s\n",buf);
	memset(buf, 0, 16);
	sscanf("hello,world", "%*s%s", buf);  
	printf("%s\n",buf);
	memset(buf, 0, 16);
	sscanf("hello world", "%*s%s", buf);  
	printf("%s\n",buf);

	memset(buf, 0, 16);
	sscanf("123#linxp@126.com&", "%*[^#]#%[^&]", buf);  
	printf("%s\n",buf);

	//字符串"127.0.0.2"转成atol的结果
	sscanf("127.0.0.2", "%d.%d.%d.%d",&a,&b,&c,&d);  
	printf("%d.%d.%d.%d\n", a,b,c,d);
	printf("%02x %02x %02x %02x\n", a,b,c,d);  //not %2x %2x %2x %2x
	sprintf(buf, "%02x%02x%02x%02x", a,b,c,d);
	printf("%s \n",buf);
	int ll = -1;
	sscanf(buf, "%x", &ll);
	printf("%d\n", ll);

	memset(buf, 0, 16);
	sscanf("linxp@126.com", "%[l.n]", buf);  
	printf("%s\n",buf);






	sscanf("12+3/5-32*8", "%d%[(+|-)]%s", &a, &cc, buf); 
	printf("%d %c %s\n",a,cc,buf);

	return 0;
}


