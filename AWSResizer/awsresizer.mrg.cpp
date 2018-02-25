// Created by Microsoft (R) C/C++ Compiler Version 13.10.3077
//
// c:\work\resizersln\awsresizer\awsresizer.mrg.cpp
// compiler-generated file created 11/15/05 at 18:28:31
//
// This C++ source file is intended to be a representation of the
// source code injected by the compiler.  It may not compile or
// run exactly as the original source file.
//



//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "c:\\work\\resizersln\\awsresizer\\awsresizer.cpp"

#ifndef GUID_DEFINED
#define GUID_DEFINED
typedef struct _GUID 
{
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[ 8 ];
} 
GUID;
#endif

extern "C" const __declspec(selectany) GUID __LIBID_ = {0x73dbde64,0xf31f,0x4186,{0xa8,0x68,0x32,0xe2,0xfb,0x2e,0xed,0x38}};
struct __declspec(uuid("73dbde64-f31f-4186-a868-32e2fb2eed38")) AWSResizer;

//--- End Injected Code For Attribute 'module'
// AWSResizer.cpp : Implementation of DLL Exports.

#include "stdafx.h"
//+++ Start Injected Code
[no_injected_text(true)];      // Suppress injected text, it has already been injected
#pragma warning(disable: 4543) // Suppress warnings about skipping injected text
#pragma warning(disable: 4199) // Suppress warnings from attribute providers

// M00PRAGMA("\n\nNOTE: This merged source file should be visually inspected for correctness.\n\n")
//--- End Injected Code


#include "resource.h"

// The module attribute causes DllMain, DllRegisterServer and DllUnregisterServer to be automatically implemented for you
[ module(dll, uuid = "{73DBDE64-F31F-4186-A868-32E2FB2EED38}", 
		 name = "AWSResizer", 
		 helpstring = "AWSResizer 1.0 Type Library",
		 resource_name = "IDR_AWSRESIZER") ]
class CAWSResizerModule
 :
    /*+++ Added Baseclass */ public CAtlDllModuleT<CAWSResizerModule>
{
public:
// Override CAtlDllModuleT members

	//+++ Start Injected Code For Attribute 'module'
    #injected_line 7 "c:\\work\\resizersln\\awsresizer\\awsresizer.cpp"

						DECLARE_LIBID(__uuidof(AWSResizer))
					
	//--- End Injected Code For Attribute 'module'
};

//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "c:\\work\\resizersln\\awsresizer\\awsresizer.cpp"

extern CAWSResizerModule _AtlModule;

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "c:\\work\\resizersln\\awsresizer\\awsresizer.cpp"
extern "C" STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "c:\\work\\resizersln\\awsresizer\\awsresizer.cpp"
extern "C" STDAPI DllRegisterServer(void);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "c:\\work\\resizersln\\awsresizer\\awsresizer.cpp"
extern "C" STDAPI DllUnregisterServer(void);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "c:\\work\\resizersln\\awsresizer\\awsresizer.cpp"
extern "C" STDAPI DllCanUnloadNow(void);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "c:\\work\\resizersln\\awsresizer\\awsresizer.cpp"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 7 "c:\\work\\resizersln\\awsresizer\\awsresizer.cpp"

CAWSResizerModule _AtlModule;

#injected_line 7 "c:\\work\\resizersln\\awsresizer\\awsresizer.cpp"
extern "C" STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv) 
{
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}
#injected_line 7 "c:\\work\\resizersln\\awsresizer\\awsresizer.cpp"
extern "C" STDAPI DllRegisterServer(void) 
{
    return _AtlModule.DllRegisterServer();
}
#injected_line 7 "c:\\work\\resizersln\\awsresizer\\awsresizer.cpp"
extern "C" STDAPI DllUnregisterServer(void) 
{
    return _AtlModule.DllUnregisterServer();
}
#injected_line 7 "c:\\work\\resizersln\\awsresizer\\awsresizer.cpp"
extern "C" STDAPI DllCanUnloadNow(void) 
{
    return _AtlModule.DllCanUnloadNow();
}
#injected_line 7 "c:\\work\\resizersln\\awsresizer\\awsresizer.cpp"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) 
{
    hInstance;
    return _AtlModule.DllMain(dwReason, lpReserved);
}
#injected_line 7 "c:\\work\\resizersln\\awsresizer\\awsresizer.cpp"

#if defined(_M_IX86)
#pragma comment(linker, "/EXPORT:DllMain=_DllMain@12,PRIVATE")
#pragma comment(linker, "/EXPORT:DllRegisterServer=_DllRegisterServer@0,PRIVATE")
#pragma comment(linker, "/EXPORT:DllUnregisterServer=_DllUnregisterServer@0,PRIVATE")
#pragma comment(linker, "/EXPORT:DllGetClassObject=_DllGetClassObject@12,PRIVATE")
#pragma comment(linker, "/EXPORT:DllCanUnloadNow=_DllCanUnloadNow@0,PRIVATE")
#elif defined(_M_IA64)
#pragma comment(linker, "/EXPORT:DllMain,PRIVATE")
#pragma comment(linker, "/EXPORT:DllRegisterServer,PRIVATE")
#pragma comment(linker, "/EXPORT:DllUnregisterServer,PRIVATE")
#pragma comment(linker, "/EXPORT:DllGetClassObject,PRIVATE")
#pragma comment(linker, "/EXPORT:DllCanUnloadNow,PRIVATE")
#endif	

//--- End Injected Code For Attribute 'module'

		 
