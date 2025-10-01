#pragma once
#include "general.hpp"
#include "structures.hpp"



namespace QVPN
{
	namespace WinTunExt
	{

		class WinTunDriver final
		{
		private:
			QVPN::Core::DataStructures::AdapterList captured_adapters_;

		public:
			std::unique_ptr<QVPN::Core::DataStructures::Adapter> create_adapter_impl();
			void capture_adapter_impl(std::string_view adapter);
			void capture_adapter_impl(QVPN::Core::DataStructures::Adapter& adapter);
			void close_adapter_impl(std::unique_ptr<QVPN::Core::DataStructures::Adapter> adapter);
			void close_all_adapters_impl();

			std::unique_ptr<QVPN::Core::DataStructures::AdapterList> get_adapters_list_impl() const;


		};

	}

}