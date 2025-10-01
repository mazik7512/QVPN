#pragma once
#include <string_view>
#include <string>
#include <vector>
#include <array>
#include <memory>


namespace QVPN {
	namespace Core
	{
		namespace DataStructures {


			class Adapter;

			template<class T>
			concept is_adapter_criteria =
				requires (T t) {
					{ true };
					{ t.check_criteria(std::declval<const Adapter&>()) } -> std::same_as<bool>;
			};

			using Byte = char;
			using ULONG = unsigned long long;

			enum AdapterFlags : ULONG {
				DdnsEnabled = 0x1,
				RegisterAdapterSuffix = 0x2,
				DhcpvEnabled = 0x4,
				ReceiveOnly = 0x8,
				NoMulticast = 0x10,
				Ipv6OtherStatefulConfig = 0x20,
				NetbiosOverTcpipEnabled = 0x40,
				Ipv4Enabled = 0x80,
				Ipv6Enabled = 0x100,
				Ipv6ManagedAddressConfigurationSupported = 0x200
			};

			class Adapter final {
			private:
				std::string adapter_name;
				std::string adapter_desc;
				std::string friendly_name;
				std::vector<Byte> PhysAdress;
				ULONG Flags = 0;
				ULONG Mtu = 0;

			public:

				Adapter();
				Adapter(std::string_view a_name, std::string_view a_desc, std::string_view a_fname);
				Adapter(std::string_view a_name, std::string_view a_desc, std::string_view a_fname, ULONG flags, ULONG mtu);
				Adapter(const Byte* begin, const Byte* end);
				
				Adapter(std::string_view a_name, std::string_view a_desc, std::string_view a_fname, const Byte* begin, const Byte* end);
				Adapter(std::string_view a_name, std::string_view a_desc, std::string_view a_fname, ULONG flags, ULONG mtu, const Byte* begin, const Byte* end);
				Adapter(std::string_view a_name, std::string_view a_desc, std::string_view a_fname, ULONG flags, ULONG mtu, std::vector<Byte>::const_iterator begin, std::vector<Byte>::const_iterator end);

				void set_data(std::string_view a_name, std::string_view a_desc, std::string_view a_fname, ULONG flags, ULONG mtu);
				void set_name(std::string_view a_name);
				void set_desc(std::string_view a_desc);
				void set_friendly_name(std::string_view a_fname);
				void set_phys_addr(std::vector<Byte>::const_iterator begin, std::vector<Byte>::const_iterator end);
				void set_phys_addr(const Byte* begin, const Byte* end);
				void set_phys_addr(std::unique_ptr<Byte> begin, std::unique_ptr<Byte> end);
				void set_flags(ULONG flags);
				void set_mtu(ULONG mtu);
				

				std::string_view get_name() const;
				std::string_view get_desc() const;
				std::string_view get_friendly_name() const;
				std::pair<std::vector<Byte>::const_iterator, std::vector<Byte>::const_iterator> get_phys_addr() const;
				ULONG get_flags() const;
				ULONG get_mtu() const;
				ULONG get_flag(AdapterFlags flag) const;

				~Adapter();


			};



			class AdapterList final : public std::vector<Adapter> {
				
			public:

				template<is_adapter_criteria U>
				std::unique_ptr<Adapter> get_default_adapter()
				{
					for (const auto& it : *this)
					{
						if (U::check_criteria(it))
						{
							return std::make_unique<Adapter>(it);
						}
					}
					return nullptr;
				}

				~AdapterList(){}
			};
		}
	}
}

