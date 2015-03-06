#include <stdio.h>  
#include <iostream>  
#include <fcntl.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <unistd.h>  
using namespace std;  

void test_file1(char **pargv);
void test_file2(char **pargv);


int main(int argc, char *argv[])  
{  
    //test_file1(argv);
    test_file2(argv);
    return 0;  
}  


//---- ---- rel ---- ---->
void test_file1(char **argv)
{
    if(access(argv[1], F_OK) != 0){  
        cout << "file not found......" << endl;  
        _exit(0);  
    }  
    else if(access(argv[1], R_OK) != 0){  
        cout << "you have no permission to read ......" << endl;  
        _exit(0);  
    }

    int fin = open(argv[1], O_RDONLY, 0777);  
    int fout = open(argv[2], O_WRONLY|O_CREAT, 0777);  

    char buff[1024] = {'\0'};  
    int len = 0;  
    while((len = read(fin, buff, sizeof(buff))) > 0)  
    {  
        printf(">>> read len:%d buff:%s \n",len,buff);
        write(fout, buff, len);  
    }  

    close(fin);  
    close(fout); 
}
void test_file2(char **argv)
{
    FILE *fp1;  
    fp1 = fopen(argv[1], "r");  
    if (fp1 == NULL){
        printf("file not exist. \n");
        _exit(0);
    }
    FILE *fp2;  
    fp2 = fopen("output", "w+"); //argv[2]

    char buff[1024] = {'\0'};   //buf 1024 why ?
/*
    while(fgets(buff, sizeof(buff), fp1) != NULL) {  
        fputs(buff, fp2);  
    }  
*/
    int count = 0;
    while((count = fread(buff, 1, 1024, fp1)) != 0) {  
        fwrite(buff, 1, count, fp2);  
    }

    fclose(fp1);  
    fclose(fp2); 
}

