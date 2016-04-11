// WinQemuTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

extern "C"
{
	int __declspec(dllexport) qemu_main(int argc, char **argv, char **envp);
};

extern "C"
{
	void test1 (int a, __int8 b)
	{
		a += b;
	}

	void test2 (int a, __int16 b)
	{
		a += b;
	}

	void test3 (int a, __int32 b)
	{
		a += b;
	}
};
int _tmain(int argc, _TCHAR* argv[])
{
	//test1 (0, 1);
	//test2 (0, 2);
	//test3 (0, 3);

	qemu_main(argc, argv, NULL);

	return 0;
}

