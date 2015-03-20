#include <stdio.h>  
#include <stdlib.h>
#include <iostream>  
#include <fcntl.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <unistd.h>  
using namespace std;  

void test_file1(char **pargv);
void test_file2(char **pargv);
void test_semaphore();
void test_parent_pid();
void test_deamon();

int main(int argc, char *argv[])  
{  
    //test_file1(argv);
    //test_file2(argv);
    test_semaphore();
    test_parent_pid();
    test_deamon();
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

#include <semaphore.h>
#include <pthread.h>
sem_t sem_a;
void *task1(void*);
void test_semaphore()
{
    int ret=0;
    pthread_t thrd1;
    pthread_t thrd2;
    sem_init(&sem_a,0,10);
    ret=pthread_create(&thrd1,NULL,task1,NULL); //创建子线程
    ret=pthread_create(&thrd2,NULL,task1,NULL); //创建子线程
    pthread_join(thrd1,NULL); //等待子线程结束
    pthread_join(thrd2,NULL); //等待子线程结束
}
void *task1(void*)
{
    int sval = 0;
    sem_wait(&sem_a); //持有信号量
    //sleep(5); //do_nothing
    sem_getvalue(&sem_a,&sval);
    printf("sem value = %d\n",sval);
    sem_post(&sem_a); //释放信号量
} 

void test_parent_pid()
{
    for (int i=0; i<1; ++i){
        pid_t pid = fork();
        printf("ret pid:%d(return child pid if not 0) getpid:%d getppid:%d \n",pid,getpid(),getppid());
    }
}

void test_deamon()
{
    //http://baike.baidu.com/link?url=hbDWuKM0brP-OvhK7uoFEwsP6_9cTnOeagZJlQ47cuwPPomSGTTqvyvAfPWMw60gQ3AAiFHh3Uy-ZUmzUoV5sK
    printf("%s think think... ... \n", __FUNCTION__);
}

