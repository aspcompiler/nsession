// ReadOnlySession.h : Declaration of the CReadOnlySession

#pragma once
#include "resource.h"       // main symbols



#include "NSessionNative_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CReadOnlySession

class ATL_NO_VTABLE CReadOnlySession :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CReadOnlySession, &CLSID_ReadOnlySession>,
	public IDispatchImpl<IReadOnlySession, &IID_IReadOnlySession, &LIBID_NSessionNativeLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CComQIPtr<ISessionStateClient> spSessionStateClient;
	CReadOnlySession()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_READONLYSESSION)

DECLARE_NOT_AGGREGATABLE(CReadOnlySession)

BEGIN_COM_MAP(CReadOnlySession)
	COM_INTERFACE_ENTRY(IReadOnlySession)
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

		return spSessionStateClient->GetItem();	}

	void FinalRelease()
	{
	}

public:



};

OBJECT_ENTRY_AUTO(__uuidof(ReadOnlySession), CReadOnlySession)
