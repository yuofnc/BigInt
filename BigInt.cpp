// BigInt.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "BigInt.h"
#include "BigNumber.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO:  ���Ĵ�������Է���������Ҫ
			_tprintf(_T("����:  MFC ��ʼ��ʧ��\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO:  �ڴ˴�ΪӦ�ó������Ϊ��д���롣
			long iIN = 0;
			
			do
			{
				printf("1.����7!\r\n");
				printf("2.����600!\r\n");
				printf("3.����n!\r\n");
				scanf_s("%d", &iIN);
				printf("��¼����ǣ�%d\r\n", iIN);

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
					printf("1.����n!,��¼��n\r\n");
					scanf_s("%ld", &iIN);
					printf("��¼����ǣ�%ld\r\n", iIN);

				} while ((iIN < 1) || (iIN > 1000000));
				iCal = iIN;
				break;
			}
			CBigNumber bResu;
			bResu.Add(1);
			for (long i = 1; i <= iCal;i++)
				bResu.Mul(i);	
			printf("\r\n�����Ϊ1��\r\n");
			
			bResu.printResu();		
			
			
			CBigNumber bResu2;
			bResu2.Add(1);
			for (long i = iCal + 1; i <= iCal + 12; i++)
				bResu2.Mul(i);
						
			printf("\r\n�����Ϊ2��\r\n");
			bResu2.printResu();			
			
			printf("\r\n�����Ϊ2_Resu��\r\n");
			bResu2.printResu();			

			CBigNumber bResu3;
			bResu3.Add(1);
			for (long i =  1; i <= iCal + 12; i++)
				bResu3.Mul(i);

			printf("\r\n�����Ϊ3��\r\n");
			bResu3.printResu();
			
			
			CBigNumber bResu5;
			CBigNumber bResu6;
			CBigNumber bTemp;
			long lMul = 1159;
			bool bTest = true;
			/*
			for (int k = 1; k < 300; k++)
			{
			lMul = rand() % 10000;
			if (lMul < 1000)
			lMul += 1000;
			bResu5.setNumber(lMul);
			bResu5.Mul(1000);
			bResu5.Mul(1000);
			bResu5.Mul(1059);
			bResu5.Mul(1033);
			bTest = true;
			for (int i = 33; i < 36 + (rand() % 10); i++)
			bResu5.Mul(i + (rand() % 100));

			bResu5.Mul(97);
			bResu5.Mul(196);
			bResu5.Add(lMul);

			printf("\r\n����Ϊ��\r\n");
			bResu5.printResu();
			bTemp.setNumber(bResu5);
			bResu6.setNumber(bResu5);

			bResu5.Div(lMul);
			printf("\r\n���Ϊ��\r\n");
			bResu5.printResu();

			bResu5.Mul(lMul);
			if (bResu6.Sub(bResu5) == 0)
			{
			if (bResu6.getValidCount() > 0)
			{
			printf("\r\n%�����ˣ�\r\n");
			bResu6.printResu();
			bTest = false;
			break;
			}
			if (bResu6.pUsed[0] > 0)
			{
			printf("\r\n%�����ˣ�\r\n");
			bResu6.printResu();
			bTest = false;
			break;
			}
			}
			else
			{
			printf("\r\n%�����ˣ�\r\n");
			bResu6.printResu();
			bTest = false;
			break;
			}

			printf("\r\n%���Ϊ��\r\n");
			bResu5.printResu();
			}
			if (!bTest)
			{
			bResu5.setNumber(bTemp);
			printf("\r\n%������Ϊ��\r\n");
			bResu5.printResu();

			bResu5.Div(lMul);
			printf("\r\n����%d���Ϊ��\r\n",lMul);
			bResu5.printResu();
			bResu5.Mul(lMul);

			printf("\r\n%��ԭ���Ϊ��\r\n");
			bResu5.printResu();


			}
			*/
			
			//
			//bResu.Mul(1000);
			//bResu.printResu();	
			bResu.setNumber(111793);
			int i = 101;
			
			for (i = 1010; i < 3000; i++)
			{
			printf("\r\n%d\r\n", i);
			bTemp.setNumber(bResu);
			bTemp.printResu();
			bResu.setNumber(bTemp);
			bResu.Mul(i);
			if (i == 1039)
			{
			int icheck = 1;
			}
			bResu.Div(i);
			if (bResu.Sub(bTemp) == 0)
			{
			if ((bResu5.getValidCount() == 0) && (bResu5.pUsed[0] == 0))
			{
			printf("\r\n�����ȷ��\r\n");
			bResu.setNumber(bTemp);
			bResu.Mul(i);
			}
			else
			{
			printf("\r\n�������\r\n");
			break;
			}

			}
			else
			{
			printf("\r\n�������\r\n");
			break;
			}

			}
			
			
			
			for (int i = 1; i < 300; i++)
			{
				bTest = true;
				bResu6.setNumber(11571 + i);

				for (int i = 1; i < 531; i++)
					bResu6.Mul(i + rand() % 10);
				for (int i = 1; i < 531; i++)
					bResu6.Mul(i + rand() % 10);
				for (int i = 1; i < 531; i++)
					bResu6.Mul(i + rand() % 10);
				bResu6.Mul(519);
				bResu6.Add(135);
				bResu6.Add(133191);
				bResu5.setNumber(bResu6);

				bTemp.setNumber(379);
				for (int k = 1; k < 300; k++)
					bTemp.Mul(379 + rand() % 100);
				for (int k = 1; k < 300; k++)
					bTemp.Mul(531 + rand() % 100);
				for (int k = 1; k < 300; k++)
					bTemp.Mul(679 + rand() % 100);
				for (int k = 1; k < 200; k++)
					bTemp.Add(rand() % 1000);
				//for (int i = 0; i < 100; i++)
				//	bTemp.Mul(i);
				bResu2.setNumber(bResu5);

				bTest = true;
				bResu5.setNumber(bResu2);
				bResu5.Mul(bTemp);

				bResu5.Div(bTemp);
				if (bResu5.Sub(bResu2) == 0)
				{
					if ((bResu5.getValidCount() == 0) && (bResu5.pUsed[0] == 0))
						printf("\r\n�����ȷ��\r\n");
					else
					{
						bResu5.setNumber(bResu2);
						bResu5.Mul(bTemp);

						bResu5.Div(bTemp);
						bTest = false;
						break;
					}

				}
				else
				{
					bResu5.setNumber(bResu2);
					bResu5.Mul(bTemp);

					bResu5.Div(bTemp);
					bTest = false;
					break;
				}
			}


			if (!bTest)
			{
				printf("\r\n�������\r\n");
			}

			
		}
	}
	else
	{
		// TODO:  ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����:  GetModuleHandle ʧ��\n"));
		nRetCode = 1;
	}

	return nRetCode;
}

void testCase1()
{
	long iIN = 0;

	do
	{
		printf("1.����7!\r\n");
		printf("2.����600!\r\n");
		printf("3.����n!\r\n");
		scanf_s("%d", &iIN);
		printf("��¼����ǣ�%d\r\n", iIN);

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
			printf("1.����n!,��¼��n\r\n");
			scanf_s("%ld", &iIN);
			printf("��¼����ǣ�%ld\r\n", iIN);

		} while ((iIN < 1) || (iIN > 1000000));
		iCal = iIN;
		break;
	}
	CBigNumber bResu;
	bResu.Add(1);
	for (long i = 1; i <= iCal; i++)
		bResu.Mul(i);
	printf("�����Ϊ��\r\n");
	bResu.printResu();
	CBigNumber bResu2;
	bResu2.Add(1);
	for (long i = 1; i <= iCal; i++)
		bResu2.Mul(i);
	printf("�����Ϊ��\r\n");
	bResu2.printResu();
	bResu.Add(bResu2);
	printf("�����Ϊ��\r\n");
	bResu.printResu();
}