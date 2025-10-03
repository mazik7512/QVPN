#include "structures.hpp"

using Byte = QVPN::Core::DataStructures::Byte;
using UByte = QVPN::Core::DataStructures::UByte;
using UShort = QVPN::Core::DataStructures::UShort;
using UInt = QVPN::Core::DataStructures::UInt;
using ubyte_const_iter = QVPN::Core::DataStructures::ubyte_const_iter;


QVPN::Core::DataStructures::Adapter::Adapter()
{
	PhysAdress.reserve(10);
}

QVPN::Core::DataStructures::Adapter::Adapter(const Byte* begin, const Byte* end)
	: QVPN::Core::DataStructures::Adapter::Adapter()
{
	PhysAdress.insert(PhysAdress.cend(), begin, end);
}

QVPN::Core::DataStructures::Adapter::Adapter(std::string_view a_name, std::string_view a_desc, std::string_view a_fname)
	: adapter_name(a_name), adapter_desc(a_desc), friendly_name(a_fname)
{
	PhysAdress.reserve(10);
}

QVPN::Core::DataStructures::Adapter::Adapter(std::string_view a_name, std::string_view a_desc, std::string_view a_fname, const Byte* begin, const Byte* end)
	: adapter_name(a_name), adapter_desc(a_desc), friendly_name(a_fname)
{
	PhysAdress.reserve(10);
	PhysAdress.insert(PhysAdress.cend(), begin, end);
}

QVPN::Core::DataStructures::Adapter::Adapter(std::string_view a_name, std::string_view a_desc, std::string_view a_fname, ULong flags, ULong mtu)
	: adapter_name(a_name), adapter_desc(a_desc), friendly_name(a_fname), Flags(flags), Mtu(mtu)
{
	PhysAdress.reserve(10);
}

QVPN::Core::DataStructures::Adapter::Adapter(std::string_view a_name, std::string_view a_desc, std::string_view a_fname, ULong flags, ULong mtu, const Byte* begin, const Byte* end)
	: adapter_name(a_name), adapter_desc(a_desc), friendly_name(a_fname), Flags(flags), Mtu(mtu)
{
	PhysAdress.reserve(10);
	PhysAdress.insert(PhysAdress.cend(), begin, end);
}

QVPN::Core::DataStructures::Adapter::Adapter(std::string_view a_name, std::string_view a_desc, std::string_view a_fname, ULong flags, ULong mtu, std::vector<Byte>::const_iterator begin, std::vector<Byte>::const_iterator end)
	: adapter_name(a_name), adapter_desc(a_desc), friendly_name(a_fname), Flags(flags), Mtu(mtu)
{
	PhysAdress.reserve(10);
	PhysAdress.insert(PhysAdress.cend(), begin, end);
}



void QVPN::Core::DataStructures::Adapter::set_data(std::string_view a_name, std::string_view a_desc, std::string_view a_fname, ULong flags, ULong mtu)
{
	adapter_name = a_name;
	adapter_desc = a_desc;
	friendly_name = a_fname;
	Flags = flags;
	Mtu = mtu;
}

void QVPN::Core::DataStructures::Adapter::set_name(std::string_view a_name)
{
	adapter_name = a_name;
}

void QVPN::Core::DataStructures::Adapter::set_desc(std::string_view a_desc)
{
	adapter_desc = a_desc;
}

void QVPN::Core::DataStructures::Adapter::set_friendly_name(std::string_view a_fname)
{
	friendly_name = a_fname;
}

void QVPN::Core::DataStructures::Adapter::set_phys_addr(std::vector<Byte>::const_iterator begin, std::vector<Byte>::const_iterator end)
{
	PhysAdress.clear();
	PhysAdress.insert(PhysAdress.end(), begin, end);
}

void QVPN::Core::DataStructures::Adapter::set_phys_addr(const Byte* begin, const Byte* end)
{
	PhysAdress.clear();
	PhysAdress.insert(PhysAdress.end(), begin, end);
}

void QVPN::Core::DataStructures::Adapter::set_phys_addr(std::unique_ptr<Byte> begin, std::unique_ptr<Byte> end)
{
	PhysAdress.clear();
	PhysAdress.insert(PhysAdress.end(), begin.get(), end.get());
}

void QVPN::Core::DataStructures::Adapter::set_flags(ULong flags)
{
	Flags = flags;
}

void QVPN::Core::DataStructures::Adapter::set_mtu(ULong mtu)
{
	Mtu = mtu;
}

std::string_view QVPN::Core::DataStructures::Adapter::get_name() const
{
	return adapter_name;
}

std::string_view QVPN::Core::DataStructures::Adapter::get_desc() const
{
	return adapter_desc;
}

std::string_view QVPN::Core::DataStructures::Adapter::get_friendly_name() const
{
	return friendly_name;
}

std::pair<std::vector<Byte>::const_iterator, std::vector<Byte>::const_iterator> QVPN::Core::DataStructures::Adapter::get_phys_addr() const
{
	return std::make_pair<>(PhysAdress.cbegin(), PhysAdress.cend());
}


QVPN::Core::DataStructures::ULong QVPN::Core::DataStructures::Adapter::get_flags() const
{
	return Flags;
}

QVPN::Core::DataStructures::ULong QVPN::Core::DataStructures::Adapter::get_flag(AdapterFlags flag) const
{
	return Flags & flag;
}


QVPN::Core::DataStructures::ULong QVPN::Core::DataStructures::Adapter::get_mtu() const
{
	return Mtu;
}

QVPN::Core::DataStructures::Adapter::~Adapter()
{
}

UByte QVPN::Core::DataStructures::Ipv4PacketLittleEndian::get_version_impl() const
{
	return header_[0] >> 4;
}

UByte QVPN::Core::DataStructures::Ipv4PacketLittleEndian::get_header_length_impl() const
{
	return header_[0] & 0xF;
}

UByte QVPN::Core::DataStructures::Ipv4PacketLittleEndian::get_dscp_impl() const
{
	return header_[1] >> 2;
}

UByte QVPN::Core::DataStructures::Ipv4PacketLittleEndian::get_ecn_impl() const
{
	return header_[1] & 0x3;
}

UShort QVPN::Core::DataStructures::Ipv4PacketLittleEndian::get_total_length_impl() const
{
	UShort first = header_[2] << 8;
	UShort total = first | header_[3];
	return total;
}

UShort QVPN::Core::DataStructures::Ipv4PacketLittleEndian::get_id_impl() const
{
	UShort first = header_[4] << 8;
	UShort id = first | header_[5];
	return id;
}

UByte QVPN::Core::DataStructures::Ipv4PacketLittleEndian::get_flags_impl() const
{
	return header_[6] >> 5;
}

UShort QVPN::Core::DataStructures::Ipv4PacketLittleEndian::get_offset_impl() const
{
	UShort first = (header_[6] & 0x1F) << 5;
	UShort offset = first | header_[7];
	return offset;
}

UByte QVPN::Core::DataStructures::Ipv4PacketLittleEndian::get_ttl_impl() const
{
	return header_[8];
}

UByte QVPN::Core::DataStructures::Ipv4PacketLittleEndian::get_protocol_impl() const
{
	return header_[9];
}

UShort QVPN::Core::DataStructures::Ipv4PacketLittleEndian::get_checksum_impl() const
{
	UShort first = header_[10] << 8;
	UShort checksum = first | header_[11];
	return checksum;
}

UInt QVPN::Core::DataStructures::Ipv4PacketLittleEndian::get_source_impl() const
{
	UInt first = header_[12] << 24;
	UInt second = header_[13] << 16;
	UInt third = header_[14] << 8;
	return first | second | third | header_[15];
}

UInt QVPN::Core::DataStructures::Ipv4PacketLittleEndian::get_dest_impl() const
{
	UInt first = header_[16] << 24;
	UInt second = header_[17] << 16;
	UInt third = header_[18] << 8;
	return first | second | third | header_[19];
}

std::pair<ubyte_const_iter, ubyte_const_iter> QVPN::Core::DataStructures::Ipv4PacketLittleEndian::get_additional_header_impl() const
{
	return std::make_pair<>(additional_header_.cbegin(), additional_header_.cend());
}

std::pair<ubyte_const_iter, ubyte_const_iter> QVPN::Core::DataStructures::Ipv4PacketLittleEndian::get_data_impl() const
{
	return std::make_pair<>(data_.cbegin(), data_.cend());
}
