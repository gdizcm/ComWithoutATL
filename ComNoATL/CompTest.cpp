// dllmain.cpp : Defines the entry point for the DLL application.
#include <iostream>
#include <Windows.h>
#include "factory.h"
#include "CompTestClass.h"
using namespace std;

HMODULE g_hModule;	//dll process handler
ULONG g_num;		// the num of object in CompTestClass, use to judge if can unload component, if 0 can unload

int myReg(LPCWSTR lpPath)	//use to register this component to registry, including CLSID, lpPath, ProgID
{
	HKEY thk, tclsidk;
	//open Key HKEY_CLASSES_ROOT\CLSID, create new CLSID which key is CompTestClass
	//under this key create InprocServer32, and set current component dll lpPath to default key value

	if (ERROR_SUCCESS == RegOpenKey(HKEY_CLASSES_ROOT, L"CLSID", &thk))
	{
		if (ERROR_SUCCESS == RegCreateKey(thk, L"{9A4F2931-A471-4AE6-A39B-E9B06F7FC692}", &tclsidk))
		{
			HKEY tinps32k;
			if (ERROR_SUCCESS == RegCreateKey(tclsidk, L"InprocServer32", &tinps32k))
			{
				if (ERROR_SUCCESS == RegSetValue(tinps32k, NULL, REG_SZ, lpPath, wcslen(lpPath) * 2))
				{
				}
				RegCloseKey(tinps32k);
			}
			RegCloseKey(tclsidk);
		}
		RegCloseKey(thk);
	}

	//under key HKEY_CLASSES_ROOT, create new key COMCTL.ComTest
	//create sub key under this new key, and set CLSID of CompTestClass as default value
	if (ERROR_SUCCESS == RegCreateKey(HKEY_CLASSES_ROOT, L"COMCTL.CompTest", &thk))
	{
		if (ERROR_SUCCESS == RegCreateKey(thk, L"CLSID", &tclsidk))
		{
			if (ERROR_SUCCESS == RegSetValue(tclsidk,
				NULL,
				REG_SZ,
				L"{9A4F2931-A471-4AE6-A39B-E9B06F7FC692}",
				wcslen(L"{9A4F2931-A471-4AE6-A39B-E9B06F7FC692}")*2))
			{
				cout << "register success" << endl;
			}
			RegCloseKey(tclsidk);
		}
		RegCloseKey(thk);
	}
	return 0;
}

extern "C" HRESULT _stdcall DllRegisterServer()
{
	WCHAR szModule[1024];
	DWORD dwResult = GetModuleFileName(g_hModule, szModule, 1024);
	if (0 == dwResult)
	{
		return -1;
	}
	MessageBox(NULL, szModule, L"path", MB_OK);
	myReg(szModule);
	return 0;
}

int myDelKey(HKEY hk, LPCWSTR lp)
{
	if (ERROR_SUCCESS == RegDeleteKey(hk, lp))
	{
	}
	return 0;
}

int myDel()
{
	HKEY thk;
	if (ERROR_SUCCESS == RegOpenKey(HKEY_CLASSES_ROOT, L"CLSID", &thk))
	{
		myDelKey(thk, L"{9A4F2931-A471-4AE6-A39B-E9B06F7FC692}\\InprocServer32");
		myDelKey(thk, L"{9A4F2931-A471-4AE6-A39B-E9B06F7FC692}");

		RegCloseKey(thk);
	}
	if (ERROR_SUCCESS == RegOpenKey(HKEY_CLASSES_ROOT, L"COMCTL.CompTest", &thk))
	{
		myDelKey(thk, L"CLSID");
	}
	myDelKey(HKEY_CLASSES_ROOT, L"COMCTL.CompTest");
	return 0;
}

extern "C" HRESULT _stdcall DllUnregisterServer()
{
	myDel();
	return 0;
}
							
extern "C" HRESULT _stdcall DllCanUnloadNow()
{
	if (0 == g_num)
	{
		return S_OK;
	}
	else
	{
		return S_FALSE;
	}
}

extern "C" HRESULT _stdcall DllGetClassObject(__in REFCLSID rclsid, __in REFIID riid, LPVOID FAR* ppv)
{
	if (CLSID_CompTestClass == rclsid)
	{
		CompTestFactory* pFactory = new CompTestFactory();
		if (NULL == pFactory)
		{
			return E_OUTOFMEMORY;
		}
		HRESULT result = pFactory->QueryInterface(riid, ppv);
		return result;
	}
	else
	{
		return CLASS_E_CLASSNOTAVAILABLE;
	}
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
	g_hModule = hModule;
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

