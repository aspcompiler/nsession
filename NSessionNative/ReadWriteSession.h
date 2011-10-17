// ReadWriteSession.h : Declaration of the CReadWriteSession

#pragma once
#include "resource.h"       // main symbols

#include "NSessionNative_i.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;

// CReadWriteSession

class ATL_NO_VTABLE CReadWriteSession :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CReadWriteSession, &CLSID_ReadWriteSession>,
	public IDispatchImpl<IReadWriteSession, &IID_IReadWriteSession, &LIBID_NSessionNativeLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CComQIPtr<NSession::ISessionStateClient> spSessionStateClient;
	CReadWriteSession()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_READWRITESESSION)

DECLARE_NOT_AGGREGATABLE(CReadWriteSession)

BEGIN_COM_MAP(CReadWriteSession)
	COM_INTERFACE_ENTRY(IReadWriteSession)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		HRESULT hr; 

		hr = spSessionStateClient.CoCreateInstance(OLESTR("NSession.SessionStateClient")); 
		if (FAILED(hr)) 
		{ 
			_tprintf(_T( 
				"ISessionStateClient.CoCreateInstance failed w/err 0x%08lx\n" 
				), hr); 
			return hr; 
		} 

		return spSessionStateClient->GetItemExclusive();
	}

	void FinalRelease()
	{
		CComQIPtr<mscorlib::IDisposable>  spDisposable = spSessionStateClient;
		//spSessionStateClient->SetAndReleaseItemExclusive();
		spDisposable->Dispose();
	}

public:



};

OBJECT_ENTRY_AUTO(__uuidof(ReadWriteSession), CReadWriteSession)
