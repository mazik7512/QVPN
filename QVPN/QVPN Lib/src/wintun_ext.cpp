#include "wintun_ext.hpp"
#include <iostream>


static WINTUN_CREATE_ADAPTER_FUNC* WintunCreateAdapter;
static WINTUN_CLOSE_ADAPTER_FUNC* WintunCloseAdapter;
static WINTUN_OPEN_ADAPTER_FUNC* WintunOpenAdapter;
static WINTUN_GET_ADAPTER_LUID_FUNC* WintunGetAdapterLUID;
static WINTUN_GET_RUNNING_DRIVER_VERSION_FUNC* WintunGetRunningDriverVersion;
static WINTUN_DELETE_DRIVER_FUNC* WintunDeleteDriver;
static WINTUN_SET_LOGGER_FUNC* WintunSetLogger;
static WINTUN_START_SESSION_FUNC* WintunStartSession;
static WINTUN_END_SESSION_FUNC* WintunEndSession;
static WINTUN_GET_READ_WAIT_EVENT_FUNC* WintunGetReadWaitEvent;
static WINTUN_RECEIVE_PACKET_FUNC* WintunReceivePacket;
static WINTUN_RELEASE_RECEIVE_PACKET_FUNC* WintunReleaseReceivePacket;
static WINTUN_ALLOCATE_SEND_PACKET_FUNC* WintunAllocateSendPacket;
static WINTUN_SEND_PACKET_FUNC* WintunSendPacket;


QVPN::WinTunExt::WinTunDriver::WinTunDriver()
{
    init_wintun();
}

QVPN::WinTunExt::WinTunDriver::~WinTunDriver()
{
    WintunEndSession(session_);
}

void QVPN::WinTunExt::WinTunDriver::create_adapter_impl()
{
    GUID ExampleGuid = { 0xdeadbabe, 0xcafe, 0xbeef, { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef } };
    int try_numbers = 20;
    bool trying = true;
    while (trying && try_numbers-- > 0)
    {
        adapter_ = WintunCreateAdapter(L"QVPN Adapter", L"QVPN", &ExampleGuid);
        if (!adapter_) {
            auto LastError = GetLastError();
            std::cout << "Error while creating adapter. Error ¹" << LastError << std::endl;
            continue;
        }
        trying = false;
    }
}

void QVPN::WinTunExt::WinTunDriver::capture_main_adapter_impl()
{
}

void QVPN::WinTunExt::WinTunDriver::close_adapter_impl(std::unique_ptr<QVPN::Core::DataStructures::Adapter> adapter)
{
}

void QVPN::WinTunExt::WinTunDriver::close_all_adapters_impl()
{
}

std::unique_ptr<QVPN::Core::DataStructures::AdapterList> QVPN::WinTunExt::WinTunDriver::get_adapters_list_impl() const
{
    return std::unique_ptr<QVPN::Core::DataStructures::AdapterList>();
}

void QVPN::WinTunExt::WinTunDriver::main_adapter_loop_handler()
{
}

void QVPN::WinTunExt::WinTunDriver::adapter_loop_handler(std::unique_ptr<QVPN::Core::DataStructures::Adapter> adapter)
{
}

void QVPN::WinTunExt::WinTunDriver::choose_main_adapter(QVPN::Core::DataStructures::AdapterList adapters)
{
}

void QVPN::WinTunExt::WinTunDriver::init_wintun()
{
    HMODULE Wintun =
        LoadLibraryExW(L"wintun.dll", NULL, LOAD_LIBRARY_SEARCH_APPLICATION_DIR | LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!Wintun)
    {
        wintun_ = nullptr;
        return;
    }
        
#define X(Name) ((*(FARPROC *)&Name = GetProcAddress(Wintun, #Name)) == NULL)
    if (X(WintunCreateAdapter) || X(WintunCloseAdapter) || X(WintunOpenAdapter) || X(WintunGetAdapterLUID) ||
        X(WintunGetRunningDriverVersion) || X(WintunDeleteDriver) || X(WintunSetLogger) || X(WintunStartSession) ||
        X(WintunEndSession) || X(WintunGetReadWaitEvent) || X(WintunReceivePacket) || X(WintunReleaseReceivePacket) ||
        X(WintunAllocateSendPacket) || X(WintunSendPacket))
#undef X
    {
        DWORD LastError = GetLastError();
        FreeLibrary(Wintun);
        SetLastError(LastError);
        wintun_ = nullptr;
        return;
    }
    wintun_ = Wintun;
}

void QVPN::WinTunExt::WinTunDriver::capture_adapter_impl()
{
    session_ = WintunStartSession(adapter_, 0x400000);
}

void QVPN::WinTunExt::WinTunDriver::capture_adapter_impl(std::string_view adapter)
{
    
}

void QVPN::WinTunExt::WinTunDriver::capture_adapter_impl(QVPN::Core::DataStructures::Adapter& adapter)
{
}
