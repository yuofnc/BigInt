#include "stdafx.h"
#include "BigNumber.h"
#include <stdexcept>

CBigNumber::CBigNumber()
{
	pUsedCount = MAXLENGTH;
	pUsed = new unsigned long[pUsedCount];
	ZeroMemory(pUsed, sizeof(unsigned long)*pUsedCount);
	pValidCount = 0;

}

CBigNumber::CBigNumber(long lSize)
{
	if (lSize < MAXLENGTH)
	{
		pUsedCount = MAXLENGTH;
		pUsed = new unsigned long[pUsedCount];
		ZeroMemory(pUsed, sizeof(unsigned long)*pUsedCount);
		pValidCount = 0;
		return;
	}	
	pUsedCount = lSize;
	pUsed = new unsigned long[lSize];
	ZeroMemory(pUsed, sizeof(unsigned long)*lSize);
	pValidCount = 0;

}


CBigNumber::~CBigNumber()
{
	delete[]pUsed;
}

void CBigNumber::setNumber(unsigned long lset)
{
	int i = lset / SINGLEITEM;
	if (i*SINGLEITEM < lset)
		i++;
	ZeroMemory(pUsed, sizeof(unsigned long)*pUsedCount);
	unsigned long * pCurr;
	for (int k = 0; k < i; k++)
	{
		//pCurr = pUsed+k;
		pUsed[k] = lset % MAXITEM;
		lset = lset / MAXITEM;
	}
	pValidCount = i;
	return;
}

void CBigNumber::reNew(long lSize)
{
	pUsedCount = lSize;
	delete[]pUsed;
	pUsed = new unsigned long[pUsedCount];
}
/*
CBigNumber CBigNumber::Add(CBigNumber ba, CBigNumber bb)
{
CBigNumber Resu;
return Resu;
}
CBigNumber CBigNumber::Mul(CBigNumber ba, CBigNumber bb)
{
CBigNumber Resu;
return Resu;
}
*/

void CBigNumber::Add( unsigned long lAdd)
{
	//低位加lAdd
	long iCurr;
	iCurr = 0;
	pUsed[iCurr] += lAdd;
	if (pUsed[iCurr] < MAXITEM)
		return;
	long iNext = 0;
	iNext = pUsed[iCurr] / MAXITEM;
	pUsed[iCurr] = pUsed[iCurr] % MAXITEM;
	
	while (true)
	{
		iCurr++;
		if (iCurr > (pUsedCount - 1))
		{
			reNewAndSet();
		}
		pUsed[iCurr] += iNext;
		if (pUsed[iCurr] < MAXITEM)
		{
			if (iCurr > pValidCount)
				pValidCount = iCurr;
			return;
		}
			
		iNext = pUsed[iCurr] / MAXITEM;
		
		
		pUsed[iCurr] = pUsed[iCurr] % MAXITEM;
	}
}

void  CBigNumber::Mul(unsigned long lMul)
{	
	//计算偏移位
	int imul = 0;
	unsigned long llMul = lMul;
			
	long iCurr;
	iCurr = 0;
	pUsed[iCurr] *= lMul;
	if ((pUsed[iCurr] < MAXITEM) && (iCurr == pValidCount))
		return;
	long iNext = 0;
	iNext = pUsed[iCurr] / MAXITEM;
	pUsed[iCurr] = pUsed[iCurr] % MAXITEM;
	bool bNotMull = false;
	while (true)
	{
		iCurr++;
		if (iCurr > (pUsedCount - 1))
		{
			reNewAndSet();
		}
		if (iCurr > pValidCount)
		{
			bNotMull = true;
			pValidCount = iCurr;
		}
		if (!bNotMull)
			pUsed[iCurr] *= lMul;
		pUsed[iCurr] += iNext;	
		
			
		if ((pUsed[iCurr] < MAXITEM) && (iCurr == pValidCount))
		{			
			return;
		}

		iNext = pUsed[iCurr] / MAXITEM;

		pUsed[iCurr] = pUsed[iCurr] % MAXITEM;
	}
}

void CBigNumber::MulMAXITEM(unsigned int iTimes)
{	
	if ((pValidCount + iTimes)>(pUsedCount - 1))
		reNewAndSet();
	pValidCount = pValidCount + iTimes;
	for (int k =0, i = pValidCount; i >= iTimes; i--)
	{
		pUsed[pValidCount-k] = pUsed[pValidCount - iTimes-k];
		k++;
	}
	for (int i = iTimes-1; i >= 0; i--)
	{
		pUsed[i] = 0;
	}
}

void CBigNumber::printResu()
{
	CString str1 ;
	str1 = "";
	for (int i = 0; i < SINGLEITEM; i++)
		str1 += "0";


	for (int i = pValidCount; i >= 0; i--)
		if (pUsed[i] == 0)
		{
			switch (SINGLEITEM)
			{
			case 3:
				printf("%03d", pUsed[i]);
				break;
			case 4:
				printf("%04d", pUsed[i]);
				break;
			case 5:
				printf("%05d", pUsed[i]);
				break;
			case 6:
				printf("%06d", pUsed[i]);
				break;
			case 7:
				printf("%07d", pUsed[i]);
				break;
			}
		}			
		else
			if (i == pValidCount)
				printf("%d", pUsed[i]);
			else
				switch (SINGLEITEM)
				{
				case 3:
					printf("%03d", pUsed[i]);
					break;
				case 4:
					printf("%04d", pUsed[i]);
					break;
				case 5:
					printf("%05d", pUsed[i]);
					break;
				case 6:
					printf("%06d", pUsed[i]);
					break;
				case 7:
					printf("%07d", pUsed[i]);
					break;
				}				
	
}

void CBigNumber::reNewAndSet(CBigNumber nPrev)
{	
	long lSize = nPrev.pUsedCount * 2;	
	delete[]pUsed;
	pUsed = new unsigned long[lSize];
	ZeroMemory(pUsed, sizeof(unsigned long)*lSize);
	for (long lSet = 0; lSet < nPrev.pUsedCount; lSet++)
		pUsed[lSet] = nPrev.pUsed[lSet];
	pUsedCount = lSize;  //占用位
	pValidCount = nPrev.pValidCount; //已用位
	return;
}

void CBigNumber::reNewAndSet()
{
	long lSize = pUsedCount * 2;	
	if (lSize < 0)
		throw "Result must great than zero,can not process!";


	unsigned long * pUsedNext = new unsigned long[lSize];
	ZeroMemory(pUsedNext, sizeof(unsigned long)*lSize);
	for (long lSet = 0; lSet < pUsedCount; lSet++)
		pUsedNext[lSet] = pUsed[lSet];
	pUsedCount = lSize;  //占用位
	delete[]pUsed;
	pUsed = pUsedNext;
	return;
}

long CBigNumber::getValidCount()
{
	return this->pValidCount;
}

