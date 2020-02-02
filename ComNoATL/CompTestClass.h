#pragma once
#include "stdafx.h"
#include "ICompTest.h"

// {A175900B-D6F9-4819-8361-0288CAB13B63}
//static const GUID CLSID_CompTestClass =
//{ 0xa175900b, 0xd6f9, 0x4819, { 0x83, 0x61, 0x2, 0x88, 0xca, 0xb1, 0x3b, 0x63 } };
// {9A4F2931-A471-4AE6-A39B-E9B06F7FC692}
static const GUID CLSID_CompTestClass =
{0x9a4f2931, 0xa471, 0x4ae6, { 0xa3, 0x9b, 0xe9, 0xb0, 0x6f, 0x7f, 0xc6, 0x92}};

class CompTestClass :
	public ICompTest
{
public:
	CompTestClass();
	~CompTestClass();

	virtual HRESULT _stdcall QueryInterface(const IID& riid, void** ppvObject);
	virtual ULONG _stdcall AddRef();
	virtual ULONG _stdcall Release();

	virtual char* _stdcall HelloWorld();

	static int Init();
	ULONG ObjNum();
protected:
	ULONG m_Ref;
	static ULONG m_objNum;
};

