#pragma once
#include <pcap.h>
#include "general.hpp"
#include <structures.hpp>
#include "Packet32.h"
#include "iphlpapi.h"
#include <lib.hpp>

#pragma comment(lib, "IPHLPAPI.lib")

namespace QVPN
{
    namespace PcapExt
    {


        class AdapterCriteria final {
        public:

            static bool check_criteria(const QVPN::Core::DataStructures::Adapter& adapter);
        };

        class PcapNetDriver final
        {
        public:
            std::unique_ptr<QVPN::Core::DataStructures::AdapterList> get_adapters_list_impl() const;
            void capture_adapter_impl(std::string_view adapter);
            void capture_adapter_impl(QVPN::Core::DataStructures::Adapter &adapter);

            //static QVPN::Core::DataStructures::Adapter convert_from_pcap_adapter(const IP_ADAPTER_ADDRESSES& adapter);
            static QVPN::Core::DataStructures::Adapter convert_from_pcap_adapter(const pcap_if_t* adapter);

        };
    }

    
}