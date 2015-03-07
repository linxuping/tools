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
        if (NULL == m_pInstance)
	     delete m_pInstance;
	m_pInstance = NULL;
    }
public:
    static Singleton* m_pInstance;//err. static Singleton* ms_instance;
    static Singleton* GetInstance(){
        //Lock()
        if (NULL == m_pInstance){
	    m_pInstance = new Singleton();
	    atexit(Singleton::Destroy);
	}
        //UnLock()
	return m_pInstance;
    }
    void display(){ printf("i am singleton \n"); }
};
Singleton* Singleton::m_pInstance = NULL; //err. if miss, will (.text._ZN9Singleton11GetInstanceEv[_ZN9Singleton11GetInstanceEv]+0x8): undefined reference to `Singleton::m_pInstance'
void test_singleton()
{
    Singleton::GetInstance()->display();
}

static void before(void) __attribute__ ((constructor));
static void after(void) __attribute__ ((destructor));
static void before(){ printf("-- before main -->\n"); }
static void after(){ printf("-- after main -->\n"); }
