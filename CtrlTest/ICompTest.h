#pragma once
#include <Unknwn.h>

// {506FA5EA-4359-4A3D-8D17-57F26D6094EF}
static const GUID IID_ICompTest =
{ 0x506fa5ea, 0x4359, 0x4a3d, { 0x8d, 0x17, 0x57, 0xf2, 0x6d, 0x60, 0x94, 0xef } };

class ICompTest : public IUnknown
{
public:
	virtual char* _stdcall HelloWorld() = 0;
};