#include <cstdlib>
#include <iostream>
#include <typeinfo>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <syslog.h>
#include "TutorialConfig.h"

#ifdef USE_MYMATH
#include "mysqrt.h"
#endif

using namespace std;
class NullType;

namespace TL{  
	template<class T,class U>  
	struct TypeList  {    
		typedef T head;    
		typedef U tail;  
	};
}

using namespace TL;

#define TYPELIST_1(T1) TypeList<T1,NullType>
#define TYPELIST_2(T1,T2) TypeList<T1,TYPELIST_1(T2)>
#define TYPELIST_3(T1,T2,T3) TypeList<T1,TYPELIST_2(T2,T3)>

typedef TypeList<char,TypeList<signed char,unsigned char> > CharList;
template<class Tlist>
struct Length;

template<>
struct Length<NullType>
{  
	enum{value = 0};
};

template<class T,class U>
struct Length<TypeList<T,U> >
{
	enum{value = 1 + Length<U>::value};
};//-----------//利用索引查找对象

template<class T,int U>
struct TypeAt;

template<class head,class tail>
struct TypeAt<TypeList<head,tail>,0>{  
	typedef head Result;
};

template<class head,class tail,int i>
struct TypeAt<TypeList<head,tail>,i>{  
	typedef typename TypeAt<tail,i - 1>::Result Result;
};

int main(int argc, char *argv[])
{    
	cout<<"Index-----------------------------------------"<<endl;    
	typedef TYPELIST_3(char,int,string) MyTypeList;
	
	TypeAt<MyTypeList,0>::Result gg[] = "char";    
	cout<<"(0) is char:"<<gg<<endl;  
	
	TypeAt<MyTypeList,1>::Result h = 11;    
	cout<<"(1) is int:"<<h<<endl;
	
	TypeAt<MyTypeList,2>::Result ii = "string";    
	cout<<"(2) is char:"<<ii<<endl;
	
	printf("Version:%d.%d\n", Tutorial_VERSION_MAJOR, Tutorial_VERSION_MINOR);
	
#ifdef USE_MYMATH
	printf("my math Version:%d.%d\n", Tutorial_VERSION_MAJOR, Tutorial_VERSION_MINOR);
#else
	printf("other Version:%d.%d\n", Tutorial_VERSION_MAJOR, Tutorial_VERSION_MINOR);
#endif

	syslog(LOG_MAKEPRI(LOG_USER, LOG_DEBUG), "%s", "trace_output1");
	syslog(LOG_MAKEPRI(LOG_USER, LOG_INFO), "%s", "trace_output2");
	syslog(LOG_MAKEPRI(LOG_USER, LOG_NOTICE), "%s", "trace_output3");
	syslog(LOG_MAKEPRI(LOG_USER, LOG_WARNING), "%s", "trace_output4");
	syslog(LOG_MAKEPRI(LOG_USER, LOG_ERR), "%s", "trace_output5");
	syslog(LOG_MAKEPRI(LOG_USER, LOG_CRIT), "%s", "trace_output6");
	syslog(LOG_MAKEPRI(LOG_USER, LOG_ALERT), "%s", "trace_output7");
	syslog(LOG_MAKEPRI(LOG_USER, LOG_EMERG), "%s", "trace_output8");
	
	return EXIT_SUCCESS;
}
