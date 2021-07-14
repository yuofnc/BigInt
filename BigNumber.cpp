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

CBigNumber::CBigNumber(CBigNumber &cNumSource)
{
	long lSize = cNumSource.getUsedCount();
	pUsedCount = lSize;
	pUsed = new unsigned long[lSize];
	ZeroMemory(pUsed, sizeof(unsigned long)*lSize);	
	
	memcpy(pUsed, cNumSource.pUsed, (cNumSource.getValidCount()+1)*sizeof(unsigned long));
	
	pValidCount = cNumSource.getValidCount();
	return;
}

CBigNumber::~CBigNumber()
{
	delete[]pUsed;
}

void CBigNumber::setNumber(CBigNumber &cNumSource)
{
	if (pUsedCount < cNumSource.getUsedCount())
	{
		delete[]pUsed;
		pUsed = new unsigned long[cNumSource.getUsedCount()];
		pUsedCount = cNumSource.getUsedCount();
	}
	ZeroMemory(pUsed, sizeof(unsigned long)*pUsedCount);
	memcpy(pUsed, cNumSource.pUsed, (cNumSource.getValidCount() + 1)*sizeof(unsigned long));
	pValidCount = cNumSource.getValidCount();
}

void CBigNumber::setNumber(unsigned long lset)
{
	long i = lset / SINGLEITEM;
	if (i*SINGLEITEM < lset)
		i++;
	ZeroMemory(pUsed, sizeof(unsigned long)*pUsedCount);
	unsigned long * pCurr;
	for (long k = 0; k < i; k++)
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

void  CBigNumber::Add(CBigNumber &cNumSource)
{
	unsigned long * pSource = cNumSource.pUsed;
	unsigned long l1Count = cNumSource.getValidCount();
	long iNext = 0;
	if (pValidCount == 0)
		pValidCount = l1Count;
	if (pValidCount<l1Count)
		pValidCount = l1Count;
	if (pUsedCount < (cNumSource.getUsedCount() - 1))
	{
		reNewAndSet(cNumSource.getUsedCount());
	}

	for (long i = 0; i <= l1Count; i++)
	{
		pUsed[i] += iNext;
		pUsed[i] += pSource[i];
		iNext = pUsed[i] / MAXITEM;
		pUsed[i] = pUsed[i] % MAXITEM;
	}
	long i = l1Count+1;
	while (iNext > 0)
	{
		if (i > (pUsedCount - 1))
		{
			reNewAndSet();
		}
		pUsed[i] += iNext;
		iNext = pUsed[i] / MAXITEM;
		pUsed[i] = pUsed[i] % MAXITEM;
		i++;		
	}
	i--;
	if (i > pValidCount)
		pValidCount = i;	
}

CBigNumber copyNumber(CBigNumber &cNumSource)
{
	CBigNumber cCopyNum(cNumSource);
	return cCopyNum;
}

void  CBigNumber::Mul(unsigned long lMul)
{	
	//计算偏移位	
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

void  CBigNumber::Mul(CBigNumber &cNumSource)
{
	//a*b=a*((long)(b/1000)*1000+b%1000)
	//计算cNumSource后面的0数量
	CBigNumber cNumbebPrev = CBigNumber(*this);
	this->setNumber(0);
	unsigned long * pSource = cNumSource.pUsed;
	unsigned long l1Count = cNumSource.getValidCount();
	long lShift = 0;
	long lZero = 0;
	for (long i = 0; i < l1Count; i++)
	{
		if (pSource[i] == 0)
			lZero++;
		else
			break;
	}
	long lSize = l1Count+pValidCount+2;
	if (lSize < 0)
		throw("Result is too big, can not calculate!");
	if (lSize > pUsedCount)
	{
		if ((long)(lSize / 1024) * 1024 < lSize)
			lSize = (long)(lSize /1024 + 1) * 1024;
		reNewAndSet(lSize);
	}
	CBigNumber cNumber = CBigNumber(cNumSource);
	//移位
	if (lZero > 0)
	{
		MulMAXITEM(lZero);
		for (long i = 0; i <= (cNumber.getValidCount()- lZero); i++)
		{
			cNumber.pUsed[i] = cNumber.pUsed[i+ lZero];
		}
		for (long i = cNumber.getValidCount(); i >(cNumber.getValidCount()-lZero); i--)
		{
			cNumber.pUsed[i] = 0;
		}
		cNumber.SetValidCount(cNumber.getValidCount() - lZero);		
		//printf("计算值为：\r\n");
		//printResu();
		if ((cNumber.pValidCount == 0) && (cNumber.pUsed[0] == 1))
			return;
		if ((cNumber.pValidCount == 0) && (cNumber.pUsed[0] > 1))
		{
			Mul(cNumber.pUsed[0]);
			return;
		}
	}	
	lShift = lZero;
	long lBegin = 0;
	CBigNumber cNumber2 = CBigNumber(cNumbebPrev);
	do
	{		
		cNumber2.setNumber(cNumbebPrev);
		if (lShift > 0)
			cNumber2.MulMAXITEM(lShift);
		cNumber2.Mul(cNumber.pUsed[lBegin]);

		cNumber.pUsed[lBegin] = 0;

		pSource = cNumber.pUsed;
		l1Count = cNumber.getValidCount();
		lZero = 0;
		for (long i = lBegin; i < l1Count; i++)
		{
			if (pSource[i] == 0)
				lZero++;
			else
				break;
		}
		lBegin += lZero;		
		lShift += lZero;
		Add(cNumber2);
		if ((cNumber.pValidCount == lBegin) && (cNumber.pUsed[lBegin] > 0))
		{			
			cNumber2.setNumber(cNumbebPrev);
			if (lShift > 0)
				cNumber2.MulMAXITEM(lShift);
			cNumber2.Mul(cNumber.pUsed[lBegin]);
			Add(cNumber2);
			return;
		}

		
	} while (cNumber.pValidCount >= lBegin);
}

void CBigNumber::MulMAXITEM(unsigned int iTimes)
{	
	if ((pValidCount + iTimes)>(pUsedCount - 1))
		reNewAndSet();
	pValidCount = pValidCount + iTimes;
	for (long k =0, i = pValidCount; i >= iTimes; i--)
	{
		pUsed[pValidCount-k] = pUsed[pValidCount - iTimes-k];
		k++;
	}
	for (long i = iTimes-1; i >= 0; i--)
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


	for (long i = pValidCount; i >= 0; i--)
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

void CBigNumber::reNewAndSet(long lSize)
{
	unsigned long * pUsedNext = new unsigned long[lSize];
	ZeroMemory(pUsedNext, sizeof(unsigned long)*lSize);
	for (long lSet = 0; lSet < pUsedCount; lSet++)
		pUsedNext[lSet] = pUsed[lSet];
	pUsedCount = lSize;  //占用位
	delete[]pUsed;
	pUsed = pUsedNext;
}

void CBigNumber::reNewAndSet()
{
	long lSize = pUsedCount * 2;	
	if (lSize < 0)
		throw "Result too big,can not process!";

	reNewAndSet(lSize);	
	return;
}

long CBigNumber::getValidCount()
{
	return this->pValidCount;
}


long CBigNumber::getUsedCount()
{
	return this->pUsedCount;
}

void CBigNumber::SetValidCount(unsigned long uSet)
{
	this->pValidCount = uSet;
}
