#pragma once

#include "general.hpp"
#include <structures.hpp>

namespace QVPN
{
    namespace Core
    {

        template <typename T>
        concept is_net_driver =
            requires(T t) {
                { true };
                /*
                { t.create_adapter_impl(std::declval<std::string_view>()) } -> std::same_as<void>;
                { t.close_adapter_impl() } -> std::same_as<void>;
                { t.get_adapter_list_impl() } -> std::same_as<std::unique_ptr<std::vector<std::string>>>;*/
        };

        template <class T>
            requires is_net_driver<T>
        class NetDriver final
        {
        private:
            T driver_;

        public:

            inline std::unique_ptr<QVPN::Core::DataStructures::AdapterList> get_adapters_list() const
            {
                return driver_.get_adapters_list_impl();
            }


            inline void capture_adapter(std::string_view adapter)
            {
                driver_.capture_adapter_impl(adapter);
            }

            inline void capture_adapter(QVPN::Core::DataStructures::Adapter adapter)
            {
                driver_.capture_adapter_impl(adapter);
            }
        };
    }
    
}
