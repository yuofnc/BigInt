// BigInt.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "BigInt.h"
#include "BigNumber.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// 初始化 MFC 并在失败时显示错误
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO:  更改错误代码以符合您的需要
			_tprintf(_T("错误:  MFC 初始化失败\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO:  在此处为应用程序的行为编写代码。
			long iIN = 0;
			
			do
			{
				printf("1.计算7!\r\n");
				printf("2.计算600!\r\n");
				printf("3.计算n!\r\n");
				scanf_s("%d", &iIN);
				printf("你录入的是：%d\r\n", iIN);

			} while ((iIN > 3) || (iIN < 1));
			int iCal = 0;
			switch (iIN)
			{
			case 1:
				iCal = 7;
				break;
			case 2:
				iCal = 600;
				break;
			case 3:
				do
				{
					printf("1.计算n!,请录入n\r\n");
					scanf_s("%ld", &iIN);
					printf("你录入的是：%ld\r\n", iIN);

				} while ((iIN < 1) || (iIN > 1000000));
				iCal = iIN;
				break;
			}
			CBigNumber bResu;
			bResu.Add(1);
			for (long i = 1; i <= iCal;i++)
				bResu.Mul(i);
			bResu.printResu();			
		}
	}
	else
	{
		// TODO:  更改错误代码以符合您的需要
		_tprintf(_T("错误:  GetModuleHandle 失败\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
