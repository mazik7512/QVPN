#include "wintun_ext.hpp"

std::unique_ptr<QVPN::Core::DataStructures::Adapter> QVPN::WinTunExt::WinTunDriver::create_adapter_impl()
{
    return std::unique_ptr<QVPN::Core::DataStructures::Adapter>();
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

void QVPN::WinTunExt::WinTunDriver::capture_adapter_impl(std::string_view adapter)
{
}

void QVPN::WinTunExt::WinTunDriver::capture_adapter_impl(QVPN::Core::DataStructures::Adapter& adapter)
{
}
