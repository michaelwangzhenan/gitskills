#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <utility>
#include <stdint.h>
#include <assert.h>
using namespace std;

void showVersion(char* v)
{
	cout << v << endl;
}


void back ()
{
	cout << "!!!Hello World!!!" << endl;

	char version[10] = "v1.0";
	char * pVersion = NULL;

	pVersion = (char *)malloc(10);
	showVersion(version);

	memcpy(pVersion,version,10);
	strcat(pVersion,".1");
	showVersion(pVersion);

	free(pVersion);

	string str="0123456789";
	cout <<"str.length()="<<str.length()<<endl;

	int a,b;
	char s[20]="0123456789";
	a=strlen(s);
	b=sizeof(s);
	cout <<"a=" <<a <<", b=" <<b <<endl;

	char s2[]="0123456789";
	a=strlen(s2);
	b=sizeof(s2);
	cout <<"a=" <<a <<", b=" <<b <<endl;

}

namespace S1{
	struct s1
	{
	char a;
	double b;
	int c;
	char d;
	};

	struct s2
	{
	char a;
	char b;
	int c;
	double d;
	};
}

namespace S2{
	struct s1
	{
	char a[8];
	};

	struct s2
	{
	double d;
	};

	struct s3
	{
	s1 s;
	char a;
	};

	struct s4
	{
	s2 s;
	char a;
	};

	int where = 1;
}

int where = 2;

namespace // only used in this file
{
	int xy = 4;
}

void test1()
{
	using namespace S1;
	cout<<sizeof(s1)<<endl; // 24
	cout<<sizeof(s2)<<endl; // 16

	using S2::s1;
	using S2::s2;
	using namespace S2;
	cout<<sizeof(s1)<<endl; // 8
	cout<<sizeof(s2)<<endl; // 8
	cout<<sizeof(S1::s1)<<endl; // 24
	cout<<sizeof(S1::s2)<<endl; // 16
	cout<<sizeof(s3)<<endl; // 9
	cout<<sizeof(s4)<<endl; // 16;

	int where = 3;

	cout << xy <<endl;
	cout << where << endl;  // local
	cout << ::where << endl; // global
	cout << S2::where << endl; // namespace
}

void test2()
{
	float f1 = 1.23f, f2=1.23;
	cout <<f1 <<" , " <<f2 <<endl;

	int i=0;
	cout<<i  <<endl;
 }


class CBase
{
private:
	int m_private;
protected:
	int m_protected;
    int m_data;
public:
    int m_public;
    static int base;
    CBase()
    {
    	m_data=1;
    	m_public=2;
    	m_protected=3;
    	m_private=4;
    };
    virtual void fun(){ cout<<"base:" << m_data<<endl;}
    virtual ~CBase(){cout<<"~base"<<endl;}
};

int CBase::base=1;

class CSub1 : public CBase
{
public:
    static int base;
    CSub1(){m_data_a=0;};
    virtual void fun()
    {
    	cout <<"m_data_a:" << m_data<<endl;
    	cout <<"m_public:" << m_public <<endl;
    	cout <<"m_protected:" << m_protected <<endl;
    	//cout <<"m_private:" << m_private <<endl;
    }
    ~CSub1(){cout<<"~Csub1"<<endl;}
protected:
    int m_data_a;

};

int CSub1::base=2;

class CSub2 : public CBase
{
protected:
    long m_data_b;
};

void testg()
{
	CBase base;
	//cout<<base.m_protected <<endl;

	CSub1 sub1;
	sub1.fun();
	cout << sub1.m_public <<endl;
	//cout << sub1.m_protected <<endl;
}

void testf()
{
	double a = 1.2;
	double* pd = &a;
	int* pi = reinterpret_cast<int*>(pd);
	//int* pi2 = static_cast<int*>(pd);
	cout << a << endl;
	cout << *pd <<endl;
	cout <<static_cast<int>(a) << endl;
	cout << *pi <<endl;
}

void testc()
{

	//CBase base;
	CSub1 sub1;
	//base.fun();
	sub1.fun();

	cout <<"----"<<endl;
/*
	CBase * pb = new CSub1();
	pb->fun();
	delete pb;
*/
}


void test3()
{
	//CBase * pb = new CBase();
	//CSub1 * p1 = new CSub1();
	CBase b = CBase();
	CSub1 s = CSub1();

	CBase& pb = b;
	CSub1& p1 = s;

	//cast a class to its base class
	CBase& p = dynamic_cast<CBase&>(p1);
	p.fun();
	//cout<<"dynamic_cast<CBase *>(p1); is ok? "<< ((p != NULL) ? "true" : "false")<<endl;
	//cast a class to its derived class

	CSub1 &pSub1 = static_cast<CSub1&>(pb);
	pSub1.fun();
	//CSub1 &pSub2 = dynamic_cast<CSub1&>(pb);
	//cout<<"dynamic_cast<CSub1 *>(pb); is ok? "<< ((pSub1 != NULL)? "true" : "false") <<endl;

	//delete pb;
	//delete p1;
}

void ConstTest1(){
	int a1 = 5;
	int *p1;
	p1=&a1;
	(*p1)++;
	cout << "normal:" <<endl;
    cout<<a1<<endl;
    cout<<*p1<<endl;

    const int a2 = 5;
    int *p2;
    p2 = const_cast<int*>(&a2);
    (*p2)++;
    cout<< "const:" << endl;
    cout<<a2<<endl;
    cout<<*p2<<endl;

    int b = 5;
    const int a3 = b;
    int *p3;
    p3 = const_cast<int*>(&a3);
    (*p3)++;
    cout<< "const2:" << endl;
    cout<<a3<<endl;
    cout<<*p3<<endl;
}

void ConstTest2(){
	int a1 = 5;
	int &p1=a1;
	p1++;
	cout << "normal:" <<endl;
    cout<<&a1<<":"<<a1<<endl;
    cout<<&p1<<":"<<p1<<endl;

    const int a2 = 5;
    int &p2 = const_cast<int&>(a2);
    p2++;
    cout<< "const:" << endl;
    cout<<&a2<<":"<<a2<<endl; // strange: same address, different value
    cout<<&p2<<":"<<p2<<endl;
    int c2 = a2;
    cout<<&c2<<":"<<c2<<endl;

    int b = 5;
    const int a3 = b;
    int &p3 = const_cast<int&>(a3);
    p3++;
    cout<< "const2:" << endl;
    cout<<&a3<<":"<<a3<<endl;
    cout<<&p3<<":"<<p3<<endl;
    cout<<&b<<":"<<b<<endl;
    int c3 = a3;
    cout<<&c3<<":"<<c3<<endl;
}

void test4()
{
	int a1=3;   ///non-const data

	const int a2=a1;    ///const data
	int const a21=a1;   ///const data, same as up

	int * a3 = &a1;   ///non-const data,non-const pointer

	const int * a4 = &a1;   ///const data,non-const pointer
	int const * a41 = &a1;   ///const data,non-const pointer, sanme a up

	int * const a5 = &a1;   ///non-const data,const pointer

	int const * const a6 = &a1;   ///const data,const pointer
	const int * const a7 = &a1;   ///const data,const pointer, same as up
}

void test5()
{
	cout << CBase::base <<endl;
	cout << CSub1::base <<endl;
}


void swap_int(int *a,int *b)
{
	//cout <<pb a << " ... "<< b <<endl;
    int *temp=a;
    a=b;
    b=temp;
    cout << a << " ... "<< b <<endl;
}

void test(int *p)
{
    int a=1;
    p=&a;
    cout<<p<<" "<<*p<<endl<<endl;;
}

void test6()
{
	int a=1,b=2;
	cout<<&a<<" "<<&b<<endl;
	swap_int(&a,&b);
	cout<<&a<<" "<<&b<<endl;

	//cout<<a<<" "<<b<<endl<<endl;
}

void test7()
{
	int v1 = 30;
	int v2 = 300;
	int v3 = 1024;
	cout <<v1<<" "<<v2<<" "<<v3<<" "<<endl;
	cout <<dec<<v1<<" "<<v2<<" "<<v3<<" "<<endl;
	cout <<oct<<v1<<" "<<v2<<" "<<v3<<" "<<endl;
	cout <<dec<<v1<<" "<<v2<<" "<<v3<<" "<<endl;
	cout <<hex<<v1<<" "<<v2<<" "<<v3<<" "<<endl;
	cout <<setiosflags(ios::uppercase)<<v1<<" "<<v2<<" "<<v3<<" "<<endl;

	cout <<hex<<v1<<" "<<v2<<" "<<v3<<" "<<endl;
	cout <<resetiosflags(ios::uppercase)<<v1<<" "<<v2<<" "<<v3<<" "<<endl;

	 cout <<setw(20)<<v1<<" "<<v2<<" " <<setw(20)<<v3<<" "<<endl;
	 cout <<setw(20)<<setiosflags(ios::left)<<v1<<" "<<v2<<" "<<v3<<" "<<endl;

}

class A
{
};

class B
{
    int a,b;
    char c;
    virtual void func0()  {  }
};

class C
{
    char a;
    virtual void func()  {  }
    virtual void func1()  {  }
};

class D: public A, public C
{
    int d;
    virtual void func()  {  }
    virtual void func1()  {  }
};
class E: public B, public C
{
    char e;
    //virtual void func0()  {  }
    //virtual void func1()  {  }
};

void test8()
{

	cout << sizeof(A) <<endl;
	cout << sizeof(B) <<endl;
	cout << sizeof(C) <<endl;
	cout << sizeof(D) <<endl;
	cout << sizeof(E) <<endl;

}

void test9()
{
	unsigned short s = 0xB3; //0000 0000 1011 0011
	cout <<hex << s <<  endl;
	cout <<hex << (s<<1) <<  endl; //0000 0001 0110 0110
	cout <<hex << (s>>1) <<  endl; //0000 0000 0101 1001

	signed short s1 = 0x70B3;//0111 0000 1011 0011
	signed short s2 = 0xF0B3;//1111 0000 1011 0011
	cout <<hex << (s1<<1) <<endl; //1110 0001 0110 0110
	cout <<hex << (s1>>1) <<endl; //0011 1000 0101 1001
	cout <<hex << (signed short)(s2<<1) <<endl; //1110 0001 0110 0110
	cout <<hex << (signed short)(s2>>1) <<endl; //1111 1000 0101 1001
}

void testa(int i, char c){ cout << "a" <<endl;}
void testb(char a, int i){ cout << "b" <<endl;}

#define T(x) cout<<#x <<"=" <<x <<endl;
#define T2(x) cout<<"a" <<#x <<"=" <<a##x<<endl;
void testd()
{
	int a1=0;
	T(a1);
	T2(1);
}

void teste()
{
	int i = 0;
	cout << sizeof i << endl;
	cout << sizeof (double) << endl;
	cout << sizeof(++i)<<endl;
	cout << sizeof(i++)<<endl;
}

void show (int i)
{
	cout << i <<" ";
}

#if 0
void vector_test(void)
{
	set<int> s;
	set<int>::iterator i;
	for (int i=1;i<=5;++i)
		s.insert(i*10);
	i = s.begin();

	s.insert(i,25);
	s.insert(i,20);
	s.insert(i,35);

	for (i= s.begin(); i!=s.end(); ++i)
		cout << " " <<*i;
}

string d(string s)
{
	for(string::size_type i=0; i<s.size();++i)
		if(s[i]=='.' && isdigit(s[i-1]) && isdigit(s[i+1]))
			s[i]=',';
	return s;
}
#endif
