#include "structures.hpp"

using Byte = QVPN::Core::DataStructures::Byte;

QVPN::Core::DataStructures::Adapter::Adapter()
{
	PhysAdress.reserve(10);
}

QVPN::Core::DataStructures::Adapter::Adapter(const Byte* begin, const Byte* end)
	: QVPN::Core::DataStructures::Adapter::Adapter()
{

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

QVPN::Core::DataStructures::Adapter::Adapter(std::string_view a_name, std::string_view a_desc, std::string_view a_fname, ULONG flags, ULONG mtu)
	: adapter_name(a_name), adapter_desc(a_desc), friendly_name(a_fname), Flags(flags), Mtu(mtu)
{
	PhysAdress.reserve(10);
}

QVPN::Core::DataStructures::Adapter::Adapter(std::string_view a_name, std::string_view a_desc, std::string_view a_fname, ULONG flags, ULONG mtu, const Byte* begin, const Byte* end)
	: adapter_name(a_name), adapter_desc(a_desc), friendly_name(a_fname), Flags(flags), Mtu(mtu)
{
	PhysAdress.reserve(10);
	PhysAdress.insert(PhysAdress.cend(), begin, end);
}

QVPN::Core::DataStructures::Adapter::Adapter(std::string_view a_name, std::string_view a_desc, std::string_view a_fname, ULONG flags, ULONG mtu, std::vector<Byte>::const_iterator begin, std::vector<Byte>::const_iterator end)
	: adapter_name(a_name), adapter_desc(a_desc), friendly_name(a_fname), Flags(flags), Mtu(mtu)
{
	PhysAdress.reserve(10);
	PhysAdress.insert(PhysAdress.cend(), begin, end);
}



void QVPN::Core::DataStructures::Adapter::set_data(std::string_view a_name, std::string_view a_desc, std::string_view a_fname, ULONG flags, ULONG mtu)
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

void QVPN::Core::DataStructures::Adapter::set_flags(ULONG flags)
{
	Flags = flags;
}

void QVPN::Core::DataStructures::Adapter::set_mtu(ULONG mtu)
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


QVPN::Core::DataStructures::ULONG QVPN::Core::DataStructures::Adapter::get_flags() const
{
	return Flags;
}

QVPN::Core::DataStructures::ULONG QVPN::Core::DataStructures::Adapter::get_flag(AdapterFlags flag) const
{
	return Flags & flag;
}


QVPN::Core::DataStructures::ULONG QVPN::Core::DataStructures::Adapter::get_mtu() const
{
	return Mtu;
}

QVPN::Core::DataStructures::Adapter::~Adapter()
{
}