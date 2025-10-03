#pragma once
#include "general.hpp"
#include "structures.hpp"
#include <wintun.h>


namespace QVPN
{
	namespace WinTunExt
	{

		class WinTunDriver final
		{
		private:
			QVPN::Core::DataStructures::AdapterList captured_adapters_;
			QVPN::Core::DataStructures::Adapter main_adapter_;
			

		private:
			HMODULE wintun_;
			WINTUN_SESSION_HANDLE session_;
			WINTUN_ADAPTER_HANDLE adapter_;

		public:

			WinTunDriver();

			WinTunDriver(const WinTunDriver&) = delete;
			WinTunDriver(WinTunDriver&&) = delete;
			WinTunDriver& operator=(const WinTunDriver&) = delete;
			WinTunDriver& operator=(WinTunDriver&&) = delete;

			~WinTunDriver();

			void create_adapter_impl();
			void capture_main_adapter_impl();
			void capture_adapter_impl();
			void capture_adapter_impl(std::string_view adapter);
			void capture_adapter_impl(QVPN::Core::DataStructures::Adapter& adapter);
			void close_adapter_impl(std::unique_ptr<QVPN::Core::DataStructures::Adapter> adapter);
			void close_all_adapters_impl();

			std::unique_ptr<QVPN::Core::DataStructures::AdapterList> get_adapters_list_impl() const;

		private:
			void main_adapter_loop_handler();
			void adapter_loop_handler(std::unique_ptr<QVPN::Core::DataStructures::Adapter> adapter);
			void choose_main_adapter(QVPN::Core::DataStructures::AdapterList adapters);
			void init_wintun();


		};

	}

}