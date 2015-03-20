#include<stdio.h>
#include<stdlib.h> //atexit
void test_singleton();


int main()
{
    test_singleton();
    return 0;
}

//---- ---- rel ---- ---->
class Singleton  //optimize using template T
{
private:
    Singleton(){}
    Singleton(const Singleton& s){} //err. Singleton(Singleton& s){}
    Singleton& operator=(const Singleton& s){}//err. Singleton& operator=(const Singleton* sp){}

    //err. how to destruct ?
    static void Destroy(){
        printf("Singleton::Destroy() \n");
        if (NULL == m_pInstance)
            delete m_pInstance;
        m_pInstance = NULL;
    }
public:
    //static volatile Singleton* m_pInstance;//err. static Singleton* ms_instance;
    static Singleton* volatile m_pInstance;//err. static Singleton* ms_instance;
    static Singleton* GetInstance(){
        if (NULL == m_pInstance){
            //Lock()
            if (NULL == m_pInstance){
                m_pInstance = new Singleton();
                atexit(Singleton::Destroy);
            }
            //UnLock()
        }
        return m_pInstance;
    }
    void display(){ printf("i am singleton \n"); }
};
Singleton* volatile Singleton::m_pInstance = NULL; //err. if miss, will (.text._ZN9Singleton11GetInstanceEv[_ZN9Singleton11GetInstanceEv]+0x8): undefined reference to `Singleton::m_pInstance'
/*if no add volatile:
test_designpattern.c:43:23: error: conflicting declaration ‘Singleton* Singleton::m_pInstance’
 Singleton* Singleton::m_pInstance = NULL; //err. if miss, will (.text._ZN9Singleton11GetInstanceEv[_ZN9Singleton11GetInstanceEv]+0x8): undefined reference to `Singleton::m_pInstance'
                       ^
test_designpattern.c:29:32: error: ‘Singleton::m_pInstance’ has a previous declaration as ‘Singleton* volatile Singleton::m_pInstance’
     static Singleton* volatile m_pInstance;//err. static Singleton* ms_instance;
                                ^
test_designpattern.c:43:23: error: declaration of ‘Singleton* volatile Singleton::m_pInstance’ outside of class is not definition [-fpermissive]
 Singleton* Singleton::m_pInstance = NULL; //err. if miss, will (.text._ZN9Singleton11GetInstanceEv[_ZN9Singleton11GetInstanceEv]+0x8): undefined reference to `Singleton::m_pInstance'
*/
void test_singleton()
{
    Singleton::GetInstance()->display();
}

static void before(void) __attribute__ ((constructor));
static void after(void) __attribute__ ((destructor));
static void before(){ printf("-- before main -->\n"); }
static void after(){ printf("-- after main -->\n"); }
