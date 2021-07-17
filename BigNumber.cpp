#include "stdafx.h"
#include "BigNumber.h"
#include <stdexcept>

CBigNumber::CBigNumber()
{
	pUsedCount = MAXLENGTH;
	pUsed = new unsigned long[pUsedCount];
	ZeroMemory((char *)pUsed, sizeof(unsigned long)*pUsedCount);
	pValidCount = 0;

}

CBigNumber::CBigNumber(long lSize)
{
	if (lSize < MAXLENGTH)
	{
		pUsedCount = MAXLENGTH;
		pUsed = new unsigned long[pUsedCount];
		ZeroMemory((char *)pUsed, sizeof(unsigned long)*pUsedCount);
		pValidCount = 0;
		return;
	}	
	pUsedCount = lSize;
	pUsed = new unsigned long[lSize];
	ZeroMemory((char *)pUsed, sizeof(unsigned long)*lSize);
	pValidCount = 0;

}

CBigNumber::CBigNumber(CBigNumber &cNumSource)
{
	long lSize = cNumSource.getUsedCount();
	pUsedCount = lSize;
	pUsed = new unsigned long[lSize];
	ZeroMemory((char *)pUsed, sizeof(unsigned long)*lSize);
	
	memcpy((char *)pUsed, (char *)cNumSource.pUsed, (cNumSource.getValidCount()+1)*sizeof(unsigned long));
	
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
	ZeroMemory((char *)pUsed, sizeof(unsigned long)*pUsedCount);
	memcpy((char *)pUsed, (char *)cNumSource.pUsed, (cNumSource.getValidCount() + 1)*sizeof(unsigned long));
	pValidCount = cNumSource.getValidCount();
}

void CBigNumber::setNumber(CBigNumber &cNumSource, long lSize)
{
	if (pUsedCount < cNumSource.getUsedCount())
	{
		delete[]pUsed;
		pUsed = new unsigned long[cNumSource.getUsedCount()];
		pUsedCount = cNumSource.getUsedCount();
	}
	ZeroMemory((char *)pUsed, sizeof(unsigned long)*pUsedCount);
	memcpy((char *)pUsed, (char *)cNumSource.pUsed+ (cNumSource.getValidCount()+1- lSize)*sizeof(unsigned long), lSize*sizeof(unsigned long));
	pValidCount = lSize-1;
}

void CBigNumber::setNumber(unsigned long lset)
{	
	unsigned long lPrev = lset;
	long i=0;
	do
	{
		lPrev = lPrev / MAXITEM;
		i++;
	} while (lPrev>0);

	ZeroMemory((char *)pUsed, sizeof(unsigned long)*pUsedCount);
	unsigned long * pCurr;
	for (long k = 0; k <= i; k++)
	{
		//pCurr = pUsed+k;
		pUsed[k] = lset % MAXITEM;
		lset = lset / MAXITEM;
	}
	pValidCount = i-1;
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
	if (((pValidCount + 20)) > pUsedCount)
		reNewAndSet();
	unsigned long llMul = lMul;
			
	long iCurr;
	long lNext = 0;
	iCurr = 0;
	pUsed[iCurr] *= lMul;
	if ((pUsed[iCurr] < MAXITEM) && (iCurr == pValidCount))
		return;
	for (long lCount = 1; lCount <= pValidCount; lCount++)
	{
		if (lCount == pValidCount)
		{
		
		}
		else
		{
			if (pUsed[lCount] >= MAXITEM)
			{
				lNext = pUsed[lCount] / MAXITEM;
				pUsed[lCount] %= MAXITEM;
				pUsed[lCount + 1] += lNext;
			}
		}
		
		pUsed[lCount] *= lMul;
	}		
	lNext = 0;
	for (long lCount = 0; lCount <= pValidCount; lCount++)
	{
		pUsed[lCount] += lNext;
		lNext = 0;
		if (pUsed[lCount] >= MAXITEM)
		{
			lNext = pUsed[lCount] / MAXITEM;
			pUsed[lCount] = pUsed[lCount] % MAXITEM;
		}
	}
	if (lNext > 0)
	{
		pValidCount++;
		do
		{
			pUsed[pValidCount] += lNext;
			if (pUsed[pValidCount] >= MAXITEM)
			{
				lNext = pUsed[pValidCount] / MAXITEM;
				pUsed[pValidCount] = pUsed[pValidCount] % MAXITEM;
				pValidCount++;
			}
			else
				break;

		} while (true);
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
	unsigned long lSize = l1Count+pValidCount+2;
	if (lSize < 0)
		throw("Result is too big, can not calculate!");
	if (lSize > pUsedCount)
	{		
		reNewAndSet(pUsedCount*2);
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

int CBigNumber::Sub(CBigNumber &cNumSource)
{
	//够减返回0
	//其余返回1
	//最高位减1
	if (pValidCount < cNumSource.getValidCount())
		return 1;
	long lDiv = 0;
	if (pValidCount == cNumSource.getValidCount())
	{			if (pValidCount == 0)
		{
			if (pUsed[0] >= cNumSource.pUsed[0])
			{
				pUsed[0] -= cNumSource.pUsed[0];
				return 0;
			}
			else
				return 1;
		}
		pUsed[pValidCount]--;		 
		//剩余位增加
		for (long lsize = 0; lsize < pValidCount; lsize++)
		{
			if (lsize ==0)
				pUsed[lsize] += MAXITEM ;
			else
				pUsed[lsize] += (MAXITEM - 1);
		}
			
		//减法运算
		for (long lsize = 0; lsize < pValidCount; lsize++)
			pUsed[lsize] -= cNumSource.pUsed[lsize];
		for (long lsize = 0; lsize < pValidCount; lsize++)
		{
			if (lsize == 199)
			{
				int test = 0;
			}
			if (pUsed[lsize] >= MAXITEM)
			{
				lDiv = pUsed[lsize] / MAXITEM;
				pUsed[lsize] -= MAXITEM*lDiv;
				pUsed[lsize + 1]+= lDiv;
			}
		}		
		if (pUsed[pValidCount] < cNumSource.pUsed[pValidCount])
			return 1;
		pUsed[pValidCount] -= cNumSource.pUsed[pValidCount];
		long lsize = pValidCount;
		for (lsize = pValidCount; lsize > 0; lsize--)
		{
			if (pUsed[lsize] > 0)
				break;

		}			
		pValidCount = lsize;
		return 0;
	}
	long lSourceCount = cNumSource.getValidCount();
	pUsed[pValidCount]--;
	//剩余位增加
	for (long lsize = 0; lsize < pValidCount; lsize++)
	{
		if (lsize == 0)
			pUsed[lsize] += MAXITEM;
		else
			pUsed[lsize] += (MAXITEM - 1);
	}
	//减法运算	
	for (long lsize = 0; lsize <= lSourceCount; lsize++)
		pUsed[lsize] -= cNumSource.pUsed[lsize];
	for (long lsize = 0; lsize < pValidCount; lsize++)
	{
		if (pUsed[lsize] >= MAXITEM)
		{
			lDiv = pUsed[lsize] / MAXITEM;
			pUsed[lsize] -= MAXITEM*lDiv;
			pUsed[lsize + 1] += lDiv;
		}
	}
	long lsize = pValidCount;
	for (lsize = pValidCount; lsize >= 0; lsize--)
	{
		if (pUsed[lsize] > 0)
			break;
	}		
	pValidCount = lsize;
	return 0;	
}


void  CBigNumber::Div(unsigned long lDiv)
{
	
	//计算位数
	unsigned long lTemp = lDiv;
	unsigned long lLen = 0;
	while (lTemp > 0)
	{
		lTemp = lTemp / 10;
		lLen++;
	}
	long lFirst = 0;
	lTemp = pUsed[pValidCount];
	while (lTemp > 0)
	{
		lTemp = lTemp / 10;
		lFirst++;
	}
	if ((pValidCount*SINGLEITEM+lFirst)<lLen)
	{
		//不够除
		setNumber(0);
		return;
	}
	/*
	lTemp = lDiv;
	lLen = 0;
	while (lTemp > 0)
	{
	lTemp = lTemp / 10;
	lLen++;
	if (lLen == pValidCount*SINGLEITEM)
	break;
	}
	if (lTemp > pUsed[pValidCount])
	{
	//不够除
	setNumber(0);
	return;
	}
	*/
	CBigNumber cNumber = CBigNumber(*this);
	CBigNumber cNumber2 = CBigNumber(*this);
	CBigNumber CNumberProc = CBigNumber();
	CBigNumber cNumberResu = CBigNumber();
	unsigned long uCalSource = 0;
	unsigned long uCalDest = 0;
	do
	{
		long lSource = 0; //当前总运算位
		long lSourceCount = 0; //当前运算位数
		cNumber.setNumber(*this);
		cNumber2.setNumber(*this);
		CNumberProc.setNumber(lDiv);
		cNumber2.setNumber(*this, CNumberProc.getValidCount() + 1);
		long iDiv = 0;
		if (cNumber2.pUsed[cNumber2.getValidCount()] <= CNumberProc.pUsed[CNumberProc.getValidCount()])
		{
			lSourceCount = CNumberProc.getValidCount() + 1 + 1;
			cNumber2.setNumber(*this, CNumberProc.getValidCount() + 2);				
			pValidCount = pValidCount - CNumberProc.getValidCount() - 1;
			lSource = pValidCount;
			ZeroMemory((char *)pUsed + (pValidCount)*sizeof(unsigned long), (CNumberProc.getValidCount() + 2)*sizeof(unsigned long));
			uCalSource = ConvNumber(cNumber2);
			uCalDest = ConvNumber(CNumberProc);
			iDiv = uCalSource / uCalDest;
		}
		else
		{
			lSourceCount = CNumberProc.getValidCount() + 1;
			pValidCount = pValidCount - CNumberProc.getValidCount();
			ZeroMemory((char *)pUsed + (pValidCount)*sizeof(unsigned long), (CNumberProc.getValidCount() + 1)*sizeof(unsigned long));
			lSource = pValidCount;
			uCalSource = ConvNumber(cNumber2);
			uCalDest = ConvNumber(CNumberProc);
			iDiv = uCalSource / uCalDest;
		}


		CBigNumber cNumber3 = CBigNumber(CNumberProc);
		CBigNumber cNumber2Copy = CBigNumber(cNumber2);
		CNumberProc.setNumber(cNumber3);
		CNumberProc.Mul(iDiv);

		
		//按位相减
		do
		{
			if (cNumber2.Sub(CNumberProc) == 0)
				break;
			else
			{
				iDiv--;
				CNumberProc.setNumber(cNumber3);
				CNumberProc.Mul(iDiv);
				cNumber2.setNumber(cNumber2Copy);
			}
		} while (true);
		//结果回写
		for (long lw = cNumber2.getValidCount(); lw >= 0; lw--)
		{
			pUsed[pValidCount + lw] = cNumber2.pUsed[lw];
		}
		
		pValidCount += cNumber2.getValidCount();		
		for (long lw = pValidCount; lw >= 0; lw--)
		{
			if (pUsed[pValidCount] == 0)
				pValidCount--;
		}

		//iDiv保存到结果
		if (iDiv >= MAXITEM)
		{
			cNumberResu.pUsed[lSource] = iDiv%MAXITEM;
			cNumberResu.pUsed[lSource + 1] = iDiv / MAXITEM;
			if (cNumberResu.getValidCount() == 0)
					cNumberResu.SetValidCount(lSource+1);
		}
		else
		{
			cNumberResu.pUsed[lSource] = iDiv%MAXITEM;			
			if (cNumberResu.getValidCount() == 0)
				cNumberResu.SetValidCount(lSource );
		}
		
		

		cNumber2.setNumber(*this);


		//pUsed[lSource - 1 - CNumberProc.getValidCount()] = iDiv;
		//cNumber2.setNumber(*this, CNumberProc.getValidCount() + 1);
		//如果除后结果比被除数小
		CNumberProc.setNumber(cNumber3);
		cNumber2Copy.setNumber(cNumber2);
		bool bSmall = false;
		if (cNumber2.getValidCount() < CNumberProc.getValidCount())
			bSmall = true;
		if (!bSmall)
		{
			if (cNumber2.getValidCount() == CNumberProc.getValidCount())
			{
				if (cNumber2.pUsed[cNumber2.getValidCount()]<CNumberProc.pUsed[cNumber2.getValidCount()])
					bSmall = true;
				else
				{
					if (cNumber2.Sub(CNumberProc) == 0)
					{
						if ((cNumber2.getValidCount() == 0) && (cNumber2.pUsed[0] == 0))
						{							
							cNumberResu.pUsed[0] = 1;
							setNumber(cNumberResu);
							return;
						}
					}
					else
						bSmall = true;
				}
			}
		}
		
		
		
		if (bSmall)
		{			
			setNumber(cNumberResu);
			return;
		}
	} while (true);
	

	//填充结果
	//计算结果后补的零个数
	//改变除数  （除数/被除数 = resu）
}

void CBigNumber::Div(CBigNumber &cNumSource)
{
	if (cNumSource.pValidCount <= 1)
	{
		unsigned long uCalSource = ConvNumber(cNumSource);
		return Div(uCalSource);
	}
	CBigNumber cResult;
	CBigNumber cDiv;

	CBigNumber cSave;
	cSave.setNumber(*this);

	CBigNumber cTemp;
	CBigNumber cTemp2;
	CBigNumber cTemp3;
	while (pValidCount > cNumSource.getValidCount())
	{
		cDiv.setNumber(0);
		cDiv.SetValidCount(cNumSource.getValidCount());
		long lBit = cNumSource.getValidCount();

		for (int i = 0; i <= 1; i++)
		{
			cDiv.pUsed[lBit] = cNumSource.pUsed[lBit];
			lBit--;
		}

		unsigned long lCalSource = 0;
		lBit = pValidCount;
		for (int i = 0; i <= 2; i++)
		{
			lCalSource *= MAXITEM;
			lCalSource += pUsed[lBit];
			lBit--;
		}
		unsigned long lCalDest = 0;
		lCalDest = 0;
		lBit = cDiv.getValidCount();
		for (int i = 0; i <= 1; i++)
		{
			lCalDest *= MAXITEM;
			if (i == 1)
			{
				lCalDest += 999;
			}
			else
				lCalDest += cDiv.pUsed[lBit];
			lBit--;
		}
		//除最高位
		long lResu = lCalSource / lCalDest;		
		cTemp.setNumber(cNumSource);
		cTemp.Mul(lResu);
		long lShift = (pValidCount - cNumSource.getValidCount() - 1);
		if ((pValidCount - cNumSource.getValidCount() - 1)>0)
			cTemp.MulMAXITEM(pValidCount-cNumSource.getValidCount()-1);
		cTemp2.setNumber(*this);
		if (Sub(cTemp) == 0)
		{
			cTemp3.setNumber(lResu);
			if ((lShift)>0)
				cTemp3.MulMAXITEM(lShift);
			cResult.Add(cTemp3);
		}
		else
		{
			setNumber(cTemp2);
			break;
		}
			
	}
	for (long lResu = 1000; lResu >= 10; lResu /= 10)
	{
		cTemp.setNumber(cNumSource);
		cTemp.Mul(lResu);
		do
		{
			cTemp2.setNumber(*this);
			if (Sub(cTemp) == 0)
			{
				cResult.Add(lResu);
			}
			else
			{
				setNumber(cTemp2);
				break;
			}
		} while (true);
	}

	do
	{
		cTemp2.setNumber(*this);
		if (Sub(cNumSource) == 0)
		{
			cResult.Add(1);
		}
		else
		{
			setNumber(cTemp2);
			break;
		}
			
	} while (true);

	
	
	printf("\r\n--------------------------------------\r\n");

	printf("\r\n被除数为：\r\n");
	cSave.printResu();
	printf("\r\n最后结果为：\r\n");
	cResult.printResu();
	printf("\r\n当前数：\r\n");
	printResu();
	printf("\r\n除数为：\r\n");
	cNumSource.printResu();


	CBigNumber cCheck;
	cCheck.setNumber(cNumSource);
	cCheck.Mul(cResult);
	cCheck.Add(*this);

	printf("\r\ns校验数为：\r\n");
	cCheck.printResu();

	
	setNumber(cResult);
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
	ZeroMemory((char *)pUsed, sizeof(unsigned long)*lSize);
	for (long lSet = 0; lSet < nPrev.pUsedCount; lSet++)
		pUsed[lSet] = nPrev.pUsed[lSet];
	pUsedCount = lSize;  //占用位
	pValidCount = nPrev.pValidCount; //已用位
	return;
}

void CBigNumber::reNewAndSet(long lSize)
{
	unsigned long * pUsedNext = new unsigned long[lSize];
	ZeroMemory((char *)pUsedNext, sizeof(unsigned long)*lSize);
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

unsigned long CBigNumber::ConvNumber(CBigNumber &NumSource)
{
	unsigned long lResu = 0;
	if (NumSource.getValidCount()>5)
		throw "Result too big,can not process!";
	for (int i = NumSource.getValidCount(); i >= 0; i--)
	{
		lResu *= MAXITEM;
		lResu += NumSource.pUsed[i];
	}
	return lResu;
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
