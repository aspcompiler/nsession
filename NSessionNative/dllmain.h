// dllmain.h : Declaration of module class.

class CNSessionNativeModule : public ATL::CAtlDllModuleT< CNSessionNativeModule >
{
public :
	DECLARE_LIBID(LIBID_NSessionNativeLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_NSESSIONNATIVE, "{23EF03EE-7F6D-4F7D-9764-E0BC497DC2CE}")
};

extern class CNSessionNativeModule _AtlModule;
