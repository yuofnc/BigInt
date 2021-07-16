#pragma once

#define SINGLEITEM 3
#define MAXITEM 1000
#define ONEK       1024
#define MAXLENGTH   8*1024
class CBigNumber
{

public:
	CBigNumber();
	CBigNumber(long lSize);
	CBigNumber(CBigNumber &cNumSource);
	
	virtual ~CBigNumber();
	void setNumber(unsigned long lset);
	void setNumber(CBigNumber &cNumSource);
	void setNumber(CBigNumber &cNumSource,long lSize);
	CBigNumber copyNumber(CBigNumber &cNumSource);
	void Add(unsigned long lAdd);
	void Add(CBigNumber &cNumSource);

	void Mul(unsigned long lMul);
	void Mul(CBigNumber &cNumSource);

	void Div(unsigned long lDiv);

	void Div(CBigNumber &cNumSource);

	int Sub(CBigNumber &cNumSource);

	void MulMAXITEM(unsigned int iTimes);
	//void  Mul(CBigNumber ba, unsigned long lMul);
	long getValidCount();
	long getUsedCount();
	void SetValidCount(unsigned long uSet);
	void printResu();
public:
	unsigned long * pUsed;
protected:
	void reNew(long lSize);
	void reNewAndSet(CBigNumber nPrev);
	void reNewAndSet(long lSize);
	void reNewAndSet();
private:
	unsigned long ConvNumber(CBigNumber &NumSource);
private:
	
	unsigned long pUsedCount;  //占用位
	unsigned long pValidCount; //已用位
};

