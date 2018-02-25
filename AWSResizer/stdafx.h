// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef STRICT
#define STRICT
#endif

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows 95 and Windows NT 4 or later.
#define WINVER 0x0400		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows NT 4 or later.
#define _WIN32_WINNT 0x0400	// Change this to the appropriate value to target Windows 2000 or later.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 4.0 or later.
#define _WIN32_IE 0x0400	// Change this to the appropriate value to target IE 5.0 or later.
#endif

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

// turns off ATL's hiding of some common and often safely ignored warning messages
#define _ATL_ALL_WARNINGS

#include <atlbase.h>
#include <atlcom.h>
#include <atlwin.h>
#include <atltypes.h>
#include <atlctl.h>
#include <atlhost.h>

#include <atlutil.h>

#include <Gdiplus.h> 

#include <string>
#include <exception>
#include <memory>
#include <sstream>
#include <iomanip>
#include <ios>

#include <CrtDbg.h>
#include <ComUtil.h>
#include <ComDef.h>
#include <WindowsX.h>

#include <urlmon.h>

#include <memory.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <tchar.h>
#include <direct.h>


using namespace ATL;
#include "ErrHlp.h"
#include "ResourceHolders.h"
#include "ResourceManagers.h"
#include "AutoPtrForMap.h"

#include "ComCtlHelpers.h"
#include "GDIPHlp.h"
#include "GDIInit.h"
#include "PropsHelper.h"

#include <MSHtmDid.h>

#pragma comment( lib, "gdiplus.lib" )
#pragma comment( lib, "urlmon.lib" )

#import <mshtml.tlb> 
#import "Imports\shdocvw.dll" exclude("tagREADYSTATE") 

#define ARRSIZE( arr ) (sizeof(arr) / sizeof(arr[0]))