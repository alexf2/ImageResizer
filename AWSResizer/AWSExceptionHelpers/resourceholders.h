#ifndef _RESOURCE_HOLDER_
#define _RESOURCE_HOLDER_

#pragma once

#ifndef _INC_MEMORY
	#error ResourceHolders.h requires "memory.h" to be included first
#endif

#ifndef __oaidl_h__
	#error ResourceHolders.h requires "OAIDL.h" to be included first
#endif

#ifndef _OLEAUTO_H_
	#error ResourceHolders.h requires "OleAuto.h" to be included first
#endif



template< class THandleType, class TResultType = bool >
struct __declspec(novtable) CBaseRcManager
{	
	bool __fastcall IsValidRes( THandleType trt ) const throw() {}
	TResultType __fastcall ReleaseRes( THandleType trt ) throw() {}
	void __fastcall ClearRes( THandleType& rTrt ) throw() {}
};



/*
struct __declspec(novtable) CVoidRcManager: public CBaseRcManager< void*, bool >
{	
	bool IsValidRes( void *trt ) const throw() { return trt != NULL; }
	bool ReleaseRes( void *trt ) throw()  { free( trt ); }
	void ClearRes( void *&rTrt ) throw()  { rTrt = NULL; }
};
*/


template< class THandleType, class TManager >
class CRcHolder: private TManager
{

typedef TManager TBase;

public:
	CRcHolder() throw()
	{
		TBase::ClearRes( m_tht );
	}

	CRcHolder( const THandleType tht ) throw(): m_tht( tht )
	{
	}

	CRcHolder( CRcHolder& rRH ) throw()
	{
		TBase::ClearRes( m_tht );
		this->operator=( rRH );
	}	

	CRcHolder& __fastcall operator=( const THandleType tht ) throw()
	{
		Release();
		m_tht = tht;
		return *this;
	}

	CRcHolder& __fastcall operator=( CRcHolder& rRH ) throw()
	{
		Release();
		m_tht = rRH.Clear();
		return *this;
	}

	__fastcall operator THandleType() const throw()
	{
		return m_tht;
	}

	THandleType* __fastcall operator&() throw()
	{
		_ASSERTE( TBase::IsValidRes(m_tht) != true );
		return &m_tht;
	}

	THandleType __fastcall operator->() const throw()
	{
		_ASSERTE( TBase::IsValidRes(m_tht) == true );
		return m_tht;
	}

	~CRcHolder() throw()
	{
		Release();
	}

	void __fastcall Release() throw()
	{		
		if( TBase::IsValidRes(m_tht) ) TBase::ReleaseRes( m_tht ), TBase::ClearRes( m_tht );
	}

	THandleType __fastcall Clear() throw()
	{
		THandleType htTmp = m_tht;
		TBase::ClearRes( m_tht );
		return htTmp;
	}

	bool __fastcall IsValid() const throw()
	{
		return TBase::IsValidRes( m_tht );
	}

private:
	THandleType m_tht;
};


template<class T> class CGDIStrategy
{
public:
	HBITMAP __fastcall Select( HDC hdc, T hbm ) throw()
	{
		return (T)SelectObject( hdc, hbm );
	}		
	bool __fastcall Release( T hbm ) throw()
	{
		return DeleteObject( hbm ) != FALSE;
	}
	short __fastcall IsValid( T hbmOld ) throw()
	{
		return hbmOld == NULL ? 0:1;
	}
	short __fastcall IsValidCtx( HDC hdc ) throw()
	{
		return hdc == NULL ? 0:1;
	}
};


template<class THandle, class TContext, class TStrategy = CGDIStrategy<THandle> >
class CGDIHolder: private TStrategy
{
public:	

	typedef TStrategy TBase;

	CGDIHolder() throw()
	{
		m_h = m_hOld = NULL;
		m_ctx = NULL; 
		m_bSelected = m_bOwned = 0;		
	}
	explicit CGDIHolder( const THandle th ) throw()
	{
		m_hOld		= NULL;
		m_h			= th;
		m_ctx		= NULL;
		m_bSelected = 0; 
		m_bOwned	= TBase::IsValid(th);
	}
	explicit CGDIHolder( const TContext tc ) throw()
	{
		m_h = m_hOld = NULL;
		m_ctx = tc; 
		m_bSelected = m_bOwned = 0;		
	}
	explicit CGDIHolder( TContext tc, THandle th ) throw()
	{
		m_hOld		= NULL;
		m_h			= th;
		m_ctx		= tc; 
		m_bSelected = TBase::IsValidCtx( tc );
		m_bOwned	= TBase::IsValid( th );

		MySelect();
	}
	explicit CGDIHolder( CGDIHolder<THandle, TContext, TStrategy>& rCH ) throw()
	{
		m_h = m_hOld = NULL;
		m_ctx = NULL;
		m_bSelected = m_bOwned = 0;
		this->operator=( rCH );
	}

	~CGDIHolder() throw()
	{
		Release();
	}

	void __fastcall Release()	throw()
	{
		MyUnselect();
		MyRelease();
	}

	CGDIHolder<THandle, TContext, TStrategy>& __fastcall operator=( THandle th ) throw()
	{
		Release();
		m_h = th; m_bOwned = TBase::IsValid( th );
		MySelect();

		return *this;
	}
	CGDIHolder<THandle, TContext, TStrategy>& __fastcall operator=( TContext tc ) throw()
	{
		MyUnselect();		
		m_ctx = tc;
		MySelect();

		return *this;
	}
	CGDIHolder<THandle, TContext, TStrategy>& __fastcall operator=( CGDIHolder<THandle, TContext, TStrategy>& rCH ) throw()
	{
		Release();

		m_h			= rCH.m_h;
		m_hOld		= rCH.m_hOld;
		m_ctx		= rCH.m_ctx;
		m_bSelected = rCH.m_bSelected;
		m_bOwned	= rCH.m_bOwned;

		rCH.m_bSelected = 0, rCH.m_bOwned = 0;

		return *this;
	}

	__fastcall operator THandle() const throw() 
	{
		return m_h;
	}
	__fastcall operator TContext() const throw() 
	{
		return m_ctx;
	}

	THandle __fastcall Old() const throw()
	{
		return m_hOld;
	}

	THandle __fastcall Unselect() throw()
	{		
		THandle h = m_h;
		MyUnselect();
		return h;		
	}

	
protected:
	THandle m_h, m_hOld;
	TContext m_ctx;
	short m_bSelected: 1, m_bOwned: 1;

	void __fastcall MyUnselect() throw()
	{
		if( m_bSelected && TBase::IsValidCtx(m_ctx) )
			m_bSelected = 0, TBase::Select( m_ctx, m_hOld );
	}
	void __fastcall MyRelease() throw()
	{
		if( m_bOwned && TBase::IsValid(m_h) )
			m_bOwned = 0, TBase::Release( m_h );
	}
	void __fastcall MySelect() throw()
	{
		if( TBase::IsValid(m_h) && TBase::IsValidCtx(m_ctx) )
		{
			m_hOld = TBase::Select( m_ctx, m_h );
			m_bSelected = 1;
		}
	}
};

struct CVarHolder
{
  CVarHolder( VARIANT* pV, long lSz ) throw(): m_pV(pV), m_lSz(lSz)
  {
    if( pV ) memset( pV, 0, sizeof(VARIANT) * lSz );
  }
  ~CVarHolder() 
  {
    if( m_pV )
	{
	  VARIANT* pvKeep = m_pV;
	  for( ; m_lSz > 0; --m_lSz, ++m_pV )
	    if( V_DISPATCH(m_pV) ) V_DISPATCH(m_pV)->Release();

	  delete[] m_pV; m_pV = NULL;
	}
  }
  VARIANT* m_pV;
  long m_lSz;
};


#endif
