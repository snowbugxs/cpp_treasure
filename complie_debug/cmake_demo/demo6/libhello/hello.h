#ifndef _HELLO_
#define _HELLO_
#if defined _WIN32
	#if LIBHELLO_BUILD
		#define LIBHELLO_API __declspec(dllexport)
	#else
		#define LIBHELLO_API __declspec(dllimport)
	#endif
#else
	#define LIBHELLO_API
#endif
//终于发现函数前面宏的意义: 在不同的系统平台的时候定义了一个公用的编译条件宏
LIBHELLO_API void printHello(char *);

#endif //_HELLO_
