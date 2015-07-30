#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define nsize 16


void multi(const char* left, const char* right)
{
	int *tmp1 = new int(strlen(left)+strlen(right));
	memset(tmp1, 0, nsize*sizeof(int));

	int a[nsize],b[nsize];
	memset(a, 0, nsize*sizeof(int)); //not only nsize
	memset(b, 0, nsize*sizeof(int));
	int len1 = strlen(left);
	int len2 = strlen(right);
	for (int i=len1-1; i>=0; --i){
		a[len1-i-1] = left[i]-'0';
	}
	for (int i=len2-1; i>=0; --i){
		b[len2-i-1] = right[i]-'0';
	}

	for (int i=0; i<nsize; ++i)
		printf("%d ",a[i]);
	printf("\n");
	for (int i=0; i<nsize; ++i)
		printf("%d ",b[i]);
	printf("\n");

	int m=0, n=0, count=0;
	for (int i=0; i<nsize; ++i){
		m = a[i];
		for (int j=0; j<nsize; ++j){
			tmp1[j+count] += m*b[j];
		}
		++count;
		if (count > len2-1)
			break;
	}
	for (int i=0; i<nsize; ++i){
		if (tmp1[i] == 0) break;
		tmp1[i+1] += tmp1[i]/10;
		tmp1[i] = tmp1[i]%10;
		//printf("%d ",tmp1[i]);
	}
	//printf("\n");
	bool flag = true;
	for (int i=nsize-1; i>=0; --i){
		if (flag && tmp1[i]!=0)
			flag = false;
		if (!flag)
			printf("%d",tmp1[i]);
	}
	printf("\n");

}

int main()
{
	char left[] = "16";
	char right[] = "16";

	//multi("16", "16");
	multi("12345", "3345");
	return 0;
}

