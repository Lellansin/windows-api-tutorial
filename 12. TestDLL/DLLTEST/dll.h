
#ifdef MYDLL_EXPORTS
	#define MYDLL_API _declspec(dllexport)
#else
	#define MYDLL_API _declspec(dllimport)
#endif

// �����Զ��嵼������
MYDLL_API void helloDLL(void);
