// WinQemuImage.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

extern "C"
{
	int __declspec(dllexport) qemu_image_main(int argc, char **argv);
};


int _tmain(int argc, _TCHAR* argv[])
{
	return qemu_image_main(argc, argv);
}

