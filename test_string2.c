#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void test_MYString();


int main()
{
    test_MYString();
    return 0;
}

class MYString
{
    public:
        char *m_buf; //buf char *buf is not correct
        MYString():m_buf( (char*)malloc(sizeof(char)*1) ){
            m_buf[0] = '\0';
        }
        MYString(const char* _buf){
            int len = 1;
            if (_buf != NULL)
                len = strlen(_buf);
            m_buf = (char*)malloc(sizeof(char)*len+1);
            if (1 == len)
                m_buf[len] = '\0';
            strcpy(m_buf, _buf);
        }
        ~MYString(){
            if (m_buf != NULL) 
                delete m_buf;
        }
        MYString(const MYString& mystr){
            //free(buf); --> bug
            int len = strlen(mystr.m_buf);
            m_buf = (char*)malloc(sizeof(char)*len+1);
            strcpy(m_buf, mystr.m_buf);
            // \0 ?
        }
        MYString& operator=(const char* _buf){
            assert(_buf!=NULL);
            free(m_buf);
            int len = strlen(_buf);
            m_buf = (char*)malloc(sizeof(char)*len+1);
            strcpy(m_buf, _buf);
            return *this; //bug must return
        }
        MYString& operator=(const MYString& mystr){
            if (this == &mystr)  //>>> >>>  remember this
                return *this;
            free(m_buf);
            int len = strlen(mystr.m_buf);
            m_buf = (char*)malloc(sizeof(char)*len+1);
            strcpy(m_buf, mystr.m_buf);
            return *this; //bug must return
        }
        void PrintMe()
        {
            printf("MYString: %s \n",m_buf);
        }
};


void test_MYString()
{
    MYString mystr;
    mystr = "hello";
    mystr.PrintMe();
    MYString mystr2(mystr);
    mystr2.PrintMe();
    MYString mystr3("world");
    mystr3.PrintMe();
    mystr3 = mystr2;
    mystr3.PrintMe();
}
