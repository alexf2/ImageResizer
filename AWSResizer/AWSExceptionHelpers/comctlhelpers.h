#if !defined(_COM_CTL_HELPERS_H_)
#define _COM_CTL_HELPERS_H_

#pragma once


#ifndef _WINDOWS_
	#error ComCtlHelpers.h requires "windows.h" to be included first
#endif

#ifndef _INC_TCHAR
	#error ComCtlHelpers.h requires "tchar.h" to be included first
#endif

#ifndef _STRING_
	#error ComCtlHelpers.h requires "string" to be included first
#endif

#ifndef _EXCEPTION_
	#error ComCtlHelpers.h requires "exception" to be included first
#endif

#ifdef _DEBUG
	#ifndef _INC_CRTDBG
		#error ComCtlHelpers.h requires "CrtDbg.h" to be included first
	#endif
#endif

#ifndef _INC_COMMDLG
	#error ComCtlHelpers.h requires "commdlg.h" to be included first
#endif

#ifndef _STRING_
	#error ComCtlHelpers.h requires "string" to be included first
#endif


#pragma comment(lib, "comdlg32.lib")

#pragma pack( push, 1 )
struct TParamsFileDlg
{

friend bool __fastcall SelectFileForSave( TParamsFileDlg& rPFD );

	TParamsFileDlg( LPCTSTR lpcDefExt = NULL, LPCTSTR lpcDefFlt = NULL ) throw();
		

	BYTE						bCenterInParent : 1;
	BYTE						bFirstShow : 1;
	HWND						hParent;
	HINSTANCE					hInstance;
	int							iX, iY;

	TCHAR						arrDefExt[ _MAX_EXT ];
	TCHAR						arrFilter[ 2 * _MAX_PATH ];
	TCHAR						arrFile[ _MAX_PATH ];
	TCHAR						arrFileTitle[ _MAX_PATH ];
	TCHAR						arrInitialDir[ _MAX_PATH ];
	TCHAR						arrTitle[ _MAX_PATH ];

	int							nFilterIndex;

protected:
	UINT_PTR CALLBACK HookFileDlg(
		HWND hdlg,      // handle to child dialog box
		UINT uiMsg,     // message identifier
		WPARAM wParam,  // message parameter
		LPARAM lParam   // message parameter 
		);

	CMyThunk<TParamsFileDlg> m_thunkFileDlg;
};
#pragma pack( pop )

bool __fastcall SelectFileForSave( TParamsFileDlg& );

#endif //_COM_CTL_HELPERS_H_
