#include "CompTestClass.h"
#include "MyLock.h"

ULONG CompTestClass::m_objNum = 0;
CompTestClass::CompTestClass() {
	m_Ref = 0;
	AutoLock tlock;
	m_objNum++;
}

CompTestClass::~CompTestClass() {
	AutoLock tlock;
	m_objNum--;
}

HRESULT _stdcall CompTestClass::QueryInterface(const IID& riid, void** ppvObject)
{
	if (IID_IUnknown == riid)
	{
		*ppvObject = (IUnknown*)this;
		((IUnknown*)(*ppvObject))->AddRef();
	}
	else if (IID_ICompTest == riid)
	{
		*ppvObject = (ICompTest*)this;
		((ICompTest*)(*ppvObject))->AddRef();
	}
	else {
		*ppvObject = NULL;
		return E_NOINTERFACE;
	}
	return S_OK;
}

ULONG _stdcall CompTestClass::AddRef()
{
	m_Ref++;
	return m_Ref;
}

ULONG _stdcall CompTestClass::Release()
{
	m_Ref--;
	if (0 == m_Ref)
	{
		delete this;
		return 0;
	}
	return m_Ref;
}

char* _stdcall CompTestClass::HelloWorld()
{
	return (char*)"hello world";
}

int CompTestClass::Init()
{
	m_objNum = 0;
	return 0;
}

ULONG CompTestClass::ObjNum()
{
	return m_objNum;
}