#if !defined(_AP_FOR_MAP_H_)
#define _AP_FOR_MAP_H_

#ifndef _MEMORY_
#error AutoPtrForMap.h requires STD "memory" header to be included first in order to get std::auto_ptr class
#endif

template<class _Ty>
	class auto_ptr_for_map: public std::auto_ptr<_Ty>
{
public:
	explicit auto_ptr_for_map(_Ty *_Ptr = 0) _THROW0()
		: std::auto_ptr<_Ty>(_Ptr)
	{
	}
	/*auto_ptr_for_map(auto_ptr_for_map<_Ty>& _Right) _THROW0()
		: std::auto_ptr<_Ty>(_Right.release())
		{	
		}*/
	auto_ptr_for_map(const auto_ptr_for_map<_Ty>& _Right) _THROW0()
		: std::auto_ptr<_Ty>(_Right.releaseConst())
	{	
	}
	auto_ptr_for_map(std::auto_ptr_ref<_Ty> _Right) _THROW0()
		: std::auto_ptr<_Ty>(_Right._Ref.release())
	{	// construct by assuming pointer from _Right auto_ptr_ref
	}
	template<class _Other>
		operator auto_ptr_for_map<_Other>() _THROW0()
	{	// convert to compatible auto_ptr
			return (auto_ptr_for_map<_Other>(*this));
	}
	template<class _Other>
		operator std::auto_ptr_ref<_Other>() _THROW0()
	{	// convert to compatible auto_ptr_ref
			return (std::auto_ptr_ref<_Other>(*this));
	}

	template<class _Other>
		auto_ptr_for_map(auto_ptr_for_map<_Other>& _Right) _THROW0()
		: std::auto_ptr<_Ty>(_Right.release())
	{	// construct by assuming pointer from _Right
	}

	_Ty *releaseConst() const _THROW0()
	{	// return wrapped pointer and give up ownership
		 auto_ptr_for_map *pThis = const_cast<auto_ptr_for_map*>( this );		
		return pThis->release();
	}	
};

#endif //_AP_FOR_MAP_H_