#pragma once

#include <cstdint>
#include <cstring>

using HRESULT = int32_t;
using ULONG = uint32_t;

inline constexpr HRESULT S_OK = 0;
inline constexpr HRESULT S_FALSE = 1;
inline constexpr HRESULT E_NOTIMPL = static_cast<HRESULT>( -1 );
inline constexpr HRESULT E_NOINTERFACE = static_cast<HRESULT>( -2 );
inline constexpr HRESULT E_POINTER = static_cast<HRESULT>( -3 );
inline constexpr HRESULT E_FAIL = static_cast<HRESULT>( -4 );
inline constexpr HRESULT E_UNEXPECTED = static_cast<HRESULT>( -5 );
inline constexpr HRESULT E_OUTOFMEMORY = static_cast<HRESULT>( -6 );
inline constexpr HRESULT E_INVALIDARG = static_cast<HRESULT>( -7 );

constexpr bool SUCCEEDED( HRESULT hr ) { return hr >= 0; }
constexpr bool FAILED( HRESULT hr ) { return hr < 0; }

struct IID
{
    uint64_t id;
};

inline bool operator == ( const IID & a, const IID & b )
{
    return a.id == b.id;
}

inline bool operator!=( const IID & a, const IID & b )
{
    return !( a == b );
}

class IUnknown
{
public:
    virtual HRESULT QueryInterface( const IID & iid, void ** ppv ) = 0;
    virtual ULONG AddRef() = 0;
    virtual ULONG Release() = 0;

protected:
    virtual ~IUnknown() = default;
};
