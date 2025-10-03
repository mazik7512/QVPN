#pragma once
#include <string_view>
#include <string>
#include <vector>
#include <array>
#include <memory>
#include <bitset>


namespace QVPN {
	namespace Core
	{
		namespace DataStructures {


			class Adapter;

			template<class EndianessPacketLike>
			concept is_adapter_criteria =
				requires (EndianessPacketLike t) {
					{ true };
					{ t.check_criteria(std::declval<const Adapter&>()) } -> std::same_as<bool>;
			};

			using Byte = char;
			using UByte = unsigned char;
			using UShort = unsigned short;
			using UInt = unsigned int;
			using ULong = unsigned long long;
			using ubyte_const_iter = std::vector<unsigned char>::const_iterator;

			enum AdapterFlags : ULong {
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
				ULong Flags = 0;
				ULong Mtu = 0;

			public:

				Adapter();
				Adapter(std::string_view a_name, std::string_view a_desc, std::string_view a_fname);
				Adapter(std::string_view a_name, std::string_view a_desc, std::string_view a_fname, ULong flags, ULong mtu);
				Adapter(const Byte* begin, const Byte* end);

				Adapter(std::string_view a_name, std::string_view a_desc, std::string_view a_fname, const Byte* begin, const Byte* end);
				Adapter(std::string_view a_name, std::string_view a_desc, std::string_view a_fname, ULong flags, ULong mtu, const Byte* begin, const Byte* end);
				Adapter(std::string_view a_name, std::string_view a_desc, std::string_view a_fname, ULong flags, ULong mtu, std::vector<Byte>::const_iterator begin, std::vector<Byte>::const_iterator end);

				void set_data(std::string_view a_name, std::string_view a_desc, std::string_view a_fname, ULong flags, ULong mtu);
				void set_name(std::string_view a_name);
				void set_desc(std::string_view a_desc);
				void set_friendly_name(std::string_view a_fname);
				void set_phys_addr(std::vector<Byte>::const_iterator begin, std::vector<Byte>::const_iterator end);
				void set_phys_addr(const Byte* begin, const Byte* end);
				void set_phys_addr(std::unique_ptr<Byte> begin, std::unique_ptr<Byte> end);
				void set_flags(ULong flags);
				void set_mtu(ULong mtu);


				std::string_view get_name() const;
				std::string_view get_desc() const;
				std::string_view get_friendly_name() const;
				std::pair<std::vector<Byte>::const_iterator, std::vector<Byte>::const_iterator> get_phys_addr() const;
				ULong get_flags() const;
				ULong get_mtu() const;
				ULong get_flag(AdapterFlags flag) const;

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

				~AdapterList() {}
			};


			template <class EndianessPacketLike>
			concept EndianessPacket =
				requires (EndianessPacketLike t) {
					{ true };
					{ t.get_version_impl() } -> std::same_as<UByte>;
					{ t.get_header_length_impl() } -> std::same_as<UByte>;
					{ t.get_dscp_impl() } -> std::same_as<UByte>;
					{ t.get_ecn_impl() } -> std::same_as<UByte>;
					{ t.get_total_length_impl() } -> std::same_as<UShort>;
					{ t.get_id_impl() } -> std::same_as<UShort>;
					{ t.get_flags_impl() } -> std::same_as<UByte>;
					{ t.get_offset_impl() } -> std::same_as<UShort>;
					{ t.get_ttl_impl() } -> std::same_as<UByte>;
					{ t.get_checksum_impl() } -> std::same_as<UShort>;
					{ t.get_source_impl() } -> std::same_as<UInt>;
					{ t.get_dest_impl() } -> std::same_as<UInt>;
					{ t.get_additional_header_impl() } -> std::same_as<std::pair<ubyte_const_iter, ubyte_const_iter>>;
					{ t.get_data_impl() } -> std::same_as<std::pair<ubyte_const_iter, ubyte_const_iter>>;
			};


			class Ipv4PacketLittleEndian {

			private:
				unsigned char header_[20];
				std::vector<UByte> additional_header_;
				std::vector<UByte> data_;

			public:

				UByte get_version_impl() const;
				UByte get_header_length_impl() const;

				UByte get_dscp_impl() const;
				UByte get_ecn_impl() const;

				UShort get_total_length_impl() const;

				UShort get_id_impl() const;

				UByte  get_flags_impl() const;
				UShort get_offset_impl() const;

				UByte get_ttl_impl() const;
				UByte get_protocol_impl() const;

				UShort get_checksum_impl() const;

				UInt get_source_impl() const;
				UInt get_dest_impl() const;

				std::pair<ubyte_const_iter, ubyte_const_iter> get_additional_header_impl() const;

				std::pair<ubyte_const_iter, ubyte_const_iter> get_data_impl() const;
			};


			template <EndianessPacket EndianessPacketLike>
			class Ipv4Packet_ final : private EndianessPacketLike {
			public:

				UByte get_version() const
				{
					return static_cast<const EndianessPacketLike*>(this)->get_version_impl();
				}

				UByte get_header_length() const
				{
					return static_cast<const EndianessPacketLike*>(this)->get_header_length_impl();
				}

				UByte get_dscp() const
				{
					return static_cast<const EndianessPacketLike*>(this)->get_dscp_impl();
				}

				UByte get_ecn() const
				{
					return static_cast<const EndianessPacketLike*>(this)->get_ecn_impl();
				}

				UShort get_total_length() const
				{
					return static_cast<const EndianessPacketLike*>(this)->get_total_length_impl();
				}

				UShort get_id() const
				{
					return static_cast<const EndianessPacketLike*>(this)->get_id_impl();
				}

				UByte  get_flags() const
				{
					return static_cast<const EndianessPacketLike*>(this)->get_flags_impl();
				}

				UShort get_offset() const
				{
					return static_cast<const EndianessPacketLike*>(this)->get_offset_impl();
				}

				UByte get_ttl() const
				{
					return static_cast<const EndianessPacketLike*>(this)->get_ttl_impl();
				}

				UByte get_protocol() const
				{
					return static_cast<const EndianessPacketLike*>(this)->get_protocol_impl();
				}

				UShort get_checksum() const
				{
					return static_cast<const EndianessPacketLike*>(this)->get_checksum_impl();
				}

				UInt get_source() const
				{
					return static_cast<const EndianessPacketLike*>(this)->get_source_impl();
				}

				UInt get_dest() const
				{
					return static_cast<const EndianessPacketLike*>(this)->get_dest_impl();
				}

				std::pair<ubyte_const_iter, ubyte_const_iter> get_additional_header() const
				{
					return static_cast<const EndianessPacketLike*>(this)->get_additional_header_impl();
				}

				std::pair<ubyte_const_iter, ubyte_const_iter> get_data() const
				{
					return static_cast<const EndianessPacketLike*>(this)->get_data_impl();
				}
			};



			using Ipv4Packet = Ipv4Packet_<Ipv4PacketLittleEndian>;
		}
	}
}

