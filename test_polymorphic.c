#include <iostream>      
using namespace std;    

class Vehicle  
{    
	public:    
		Vehicle(float speed,int total)  
		{  
			Vehicle::speed=speed;  
			Vehicle::total=total;  
		}  
		//virtual void ShowMember()  //1
		void ShowMember()            //2 
		{  
			cout<<"Base: "<<speed<<"|"<<total<<endl;  
		}  
	protected:    
		float speed;  
		int total;  
};    
class Car:public Vehicle    
{    
	public:    
		Car(int aird,float speed,int total):Vehicle(speed,total)    
	{    
		Car::aird=aird;    
	}  
		void ShowMember()  
		{  
			cout<<"Derived: "<<speed<<"|"<<total<<"|"<<aird<<endl;  
		}  
	protected:    
		int aird;  
};    

void test(Vehicle &temp)  
{  
	temp.ShowMember();  
}  

int main()    
{  
	Vehicle a(120,4);  
	Car b(180,110,4);  
	test(a);  
	test(b);  
    cout << "[ts=4 here]you can tell me why not run with polymorpyic ?\n" << endl;
	//cin.get();  
    return 0;
}
