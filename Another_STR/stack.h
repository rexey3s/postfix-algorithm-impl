#include <iostream>
using namespace std;
#ifndef stack_h
#define stack_h
template <class T>
class stack
{
	public: T *a;
			int cmax;
			int top;
		
public:        
stack()
{
     cmax=50;			
     top=-1;
     a =new T[cmax];
}
stack(const stack &s)
{
     cmax=s.cmax;
     top=s.top;
     a = new T[cmax];
     for (int i=0; i <= top;i++)
     a[i]=s.a[i];
};
 stack(int max)
 {
    cmax=max;
    top=-1;
    a=new T[cmax];
};
~stack(){
	if (a!= NULL)
		delete[] a;
};
//--------------------//
bool push(T &x){
	if (isfull())
		return false;
	a[++top]=x;
	return true;
}
;
T pop(){
	return a[top--];
	
};
bool isempty() const
                {
	if (top==-1) return true;
	else return false;
};
bool isfull() const{
	if (top == cmax-1) return true;
	else return false;
}; 
T topstack()
{
	if(!isempty()) return a[top];
	else return NULL;
};
void OUTPUT()
{
	for(int i=0;i<=top;i++) {cout<<a[i]<<"\t";};
}
void R_OUTPUT()
{
	for(int i=top;i>=0;i--)	cout<<a[i];
}

};
#endif