
#ifdef MYDLL_EXPORTS
	#define MYDLL_API _declspec(dllexport)
#else
	#define MYDLL_API _declspec(dllimport)
#endif

// 声明自定义导出函数
MYDLL_API void helloDLL(void);
