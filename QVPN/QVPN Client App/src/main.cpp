#include <lib.hpp>
#include <iostream>
#include <bitset>
#include <pcap_ext.hpp>
#include <wintun_ext.hpp>

using PcapDriver = QVPN::Core::NetDriver<QVPN::PcapExt::PcapNetDriver>;
using WinTunDriver = QVPN::Core::NetDriver<QVPN::WinTunExt::WinTunDriver>;
using AdapterCriteria = QVPN::PcapExt::AdapterCriteria;

int main()
{
    PcapDriver driver;
    auto d_list = driver.get_adapters_list();
    for (const auto& it : *d_list)
    {
        std::cout << it.get_name() << "  " << it.get_desc() << std::endl;
    }
    system("chcp 1251");
    auto a = d_list->get_default_adapter<AdapterCriteria>();
    std::cout << a->get_friendly_name() << std::endl;
    driver.capture_adapter(a->get_friendly_name());
    
    /*
    for (size_t i = 0; i < 10; i++)
    {
        std::cout << (t << i) << std::endl;
    }
    std::cout << std::endl << std::endl;
    std::cout << std::bitset<sizeof(unsigned long long) * 8>(QVPN::Core::DataStructures::AdapterFlags::DdnsEnabled) << std::endl;
    std::cout << std::bitset<sizeof(unsigned long long) * 8>(QVPN::Core::DataStructures::AdapterFlags::RegisterAdapterSuffix) << std::endl;
    std::cout << std::bitset<sizeof(unsigned long long) * 8>(QVPN::Core::DataStructures::AdapterFlags::DhcpvEnabled) << std::endl;
    std::cout << std::bitset<sizeof(unsigned long long) * 8>(QVPN::Core::DataStructures::AdapterFlags::ReceiveOnly) << std::endl;
    std::cout << std::bitset<sizeof(unsigned long long) * 8>(QVPN::Core::DataStructures::AdapterFlags::NoMulticast) << std::endl;
    std::cout << std::bitset<sizeof(unsigned long long) * 8>(QVPN::Core::DataStructures::AdapterFlags::Ipv6OtherStatefulConfig) << std::endl;
    std::cout << std::bitset<sizeof(unsigned long long) * 8>(QVPN::Core::DataStructures::AdapterFlags::NetbiosOverTcpipEnabled) << std::endl;
    std::cout << std::bitset<sizeof(unsigned long long) * 8>(QVPN::Core::DataStructures::AdapterFlags::Ipv4Enabled) << std::endl;
    std::cout << std::bitset<sizeof(unsigned long long) * 8>(QVPN::Core::DataStructures::AdapterFlags::Ipv6Enabled) << std::endl;
    std::cout << std::bitset<sizeof(unsigned long long) * 8>(QVPN::Core::DataStructures::AdapterFlags::Ipv6ManagedAddressConfigurationSupported) << std::endl
    */
    return 0;
}