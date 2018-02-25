
#include "stdafx.h"

#include <commdlg.h>
#include <string>
#include <CrtDbg.h>
#include <exception>
#include <string>
#include <tchar.h>

#include "ComCtlHelpers.h"

#include "ErrHlp.h"

bool __fastcall SelectFileForSave( TParamsFileDlg& rPFD )
{
	OPENFILENAME ofn;

	memset( &ofn, 0, sizeof ofn );

	ofn.lStructSize		= sizeof ofn;
	ofn.hwndOwner		= rPFD.hParent;
	//ofn.hInstance		= rPFD.hInstance;
	ofn.Flags			= OFN_ENABLEHOOK | OFN_EXPLORER | OFN_EXTENSIONDIFFERENT |
		OFN_FILEMUSTEXIST | OFN_LONGNAMES | OFN_PATHMUSTEXIST | OFN_ENABLESIZING | OFN_HIDEREADONLY;
	ofn.lpfnHook		= (LPOFNHOOKPROC)&rPFD.m_thunkFileDlg;
	ofn.lCustData		= (LPARAM)&rPFD;

	ofn.lpstrDefExt		= rPFD.arrDefExt;
	ofn.lpstrFilter		= rPFD.arrFilter;
	ofn.nFilterIndex	= rPFD.nFilterIndex;

	ofn.lpstrFile		= rPFD.arrFile;
	ofn.nMaxFile		= sizeof rPFD.arrFile;

	ofn.lpstrFileTitle  = rPFD.arrFileTitle;
	ofn.nMaxFileTitle	= sizeof rPFD.arrFileTitle;

	ofn.lpstrInitialDir = rPFD.arrInitialDir;
	ofn.lpstrTitle		= rPFD.arrTitle;

	if( GetOpenFileName(&ofn) == FALSE )
	{
		DWORD dwErr;
		if( (dwErr = CommDlgExtendedError()) == 0 ) return false;
		ThrowCommonDlgError( dwErr );
	}
	return true;
}

TParamsFileDlg::TParamsFileDlg( LPCTSTR lpcDefExt, LPCTSTR lpcDefFlt ) throw():
		bCenterInParent( 1 ),
		bFirstShow( 1 ),
		hParent( 0 ),
		hInstance( 0 ),
		iX( 0 ), iY( 0 ),
		nFilterIndex( 0 )
{
	memset( arrDefExt,	   0, sizeof arrDefExt );
	memset( arrFilter,	   0, sizeof arrFilter );
	memset( arrFile,	   0, sizeof arrFile );
	memset( arrFileTitle,  0, sizeof arrFileTitle );
	memset( arrInitialDir, 0, sizeof arrInitialDir );
	memset( arrTitle,	   0, sizeof arrTitle );

	GetCurrentDirectory( sizeof(arrInitialDir)/sizeof(arrInitialDir[0]), arrInitialDir );

	bCenterInParent = 0;
	nFilterIndex = 1;
	_tcscpy( arrDefExt, (lpcDefExt ? lpcDefExt:_T("tif")) );

	static const LPCTSTR lpcszFlt = _T("All Files (*.*)\0*.*\0")
		_T("All images (*.gif;*.tif;*.bmp;*.png;*.wmf;*.emf;*.jpg)\0*.gif;*.tif;*.bmp;*.png;*.wmf;*.emf;*.jpg\0")
		_T("Bitmaps (*.bmp)\0*.bmp\0")
		_T("Gifs (*.gif)\0*.gif\0")
		_T("Tifs (*.tif)\0*.tif\0")
		_T("Metafiles (*.wmf;*.emf)\0*.emf;*wmf\0")
		_T("Jpegs (*.jpg;*.jpeg)\0*.jpg;*.jpeg\0\0");		

	if( lpcDefFlt )
		memcpy( arrFilter, lpcDefFlt, DoubleNullSize(lpcDefFlt) );
	else
		memcpy( arrFilter, lpcszFlt, DoubleNullSize(lpcszFlt) );
					
	_tcscpy( arrTitle, _T("Open File") );

	m_thunkFileDlg.Init( (CMyThunk<TParamsFileDlg>::TPFN)&TParamsFileDlg::HookFileDlg, this );
}

UINT_PTR CALLBACK TParamsFileDlg::HookFileDlg(
		HWND hdlg,      // handle to child dialog box
		UINT uiMsg,     // message identifier
		WPARAM wParam,  // message parameter
		LPARAM lParam   // message parameter 
		)
{
	RECT rc1, rc2;

	switch( uiMsg )
	{		
		case WM_NOTIFY: //CDN_INITDONE://WM_INITDIALOG:
		{
			OFNOTIFY* pN = (OFNOTIFY*)lParam;			

			if( pN->hdr.code == CDN_INITDONE )
			{
				hdlg = pN->hdr.hwndFrom;

				if( (bCenterInParent || bFirstShow)  && hParent )
				{
					bFirstShow = 0;

					::GetWindowRect( hParent, &rc1 );
					::GetWindowRect( hdlg, &rc2 );

					iX = (rc1.left + rc1.right) / 2 - (rc2.right - rc2.left) / 2;
					if( iX < 0 ) iX = 0;

					iY = (rc1.top + rc1.bottom) / 2 - (rc2.bottom - rc2.top) / 2;
					if( iY < 0 ) iY = 0;

					//BOOL bb = ::IsWindow( hdlg );
					::SetWindowPos( hdlg, 0, iX, iY, 0, 0,
						SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOREDRAW );				
				}
				else
					::SetWindowPos( hdlg, 0, iX, iY, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOREDRAW );

				/*::GetWindowRect( hdlg, &rc1 );
				::SetWindowPos( hdlg, 0, 500, 200, 0, 0,
						SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER );
				::GetWindowRect( hdlg, &rc1 );*/

				break;
			}
			else if( pN->hdr.code == CDN_TYPECHANGE )
			{
				nFilterIndex = pN->lpOFN->nFilterIndex;
			}
		};
		case WM_DESTROY:
		{
			::GetWindowRect( hdlg, &rc1 );
			iX = rc1.left;
			iY = rc1.top;
			break;
		};
	};

	return 0;
}
