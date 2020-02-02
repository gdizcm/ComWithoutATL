// CtrlTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ICompTest.h"

int main()
{
	CoInitialize(NULL);
	IUnknown* pUnknown = NULL;
	GUID CLSID_CompTestClass;
	HRESULT hResult = CLSIDFromProgID(L"COMCTL.CompTest", &CLSID_CompTestClass);
	if (S_OK != hResult)
	{
		std::cout << "can't find CLSID\n";
		system("pause");
		return -1;
	}
	else
	{
		LPOLESTR szCLSID;
		StringFromCLSID(CLSID_CompTestClass, &szCLSID);
		wprintf(L"find CLSID \"%s\"\n", szCLSID);
		CoTaskMemFree(szCLSID);
	}

	hResult = CoCreateInstance(CLSID_CompTestClass, NULL, CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)& pUnknown);
	if (S_OK != hResult || NULL == pUnknown)
	{
		std::cout << "create failed\n";
		return -1;
	}
	ICompTest* pCompTest = NULL;
	hResult = pUnknown->QueryInterface(IID_ICompTest, (void**)& pCompTest);
	if (SUCCEEDED(hResult))
	{
		std::cout << pCompTest->HelloWorld();
		pCompTest->Release();
	}
	pUnknown->Release();
	CoUninitialize();
	system("pause");
}
