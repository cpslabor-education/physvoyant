#ifndef COMPONENT_IDENTIFIER
#define COMPONENT_IDENTIFIER

class ComponentIdentifier;

#include "../defines.hpp"

constexpr unsigned char halfBits = sizeof(uintStandard_t) / 2 * 8;
constexpr uintStandard_t lowMask = (1ULL << halfBits) - 1;
constexpr uintStandard_t highMask = ~lowMask;

//class ComponentIdentifier
//{
//	uintStandard_t ID;
//public:
//	enum class ComponentTypes
//	{
//		NoneType = 0,
//		Collider
//	};
//	ComponentIdentifier() : ID(0)
//	{
//	}
//	ComponentIdentifier(uintStandard_t ID) : ID(ID)
//	{
//	}
//	~ComponentIdentifier() = default;
//
//	operator uintStandard_t() const
//	{
//		return ID;
//	}
//	bool operator==(const ComponentIdentifier& other) const
//	{
//		return other.ID == this->ID;
//	}
//	bool operator!=(const ComponentIdentifier& other) const
//	{
//		return !(other == *this);
//	}
//
//	bool operator==(const uintStandard_t& other) const
//	{
//		return other == this->ID;
//	}
//	bool operator!=(const uintStandard_t& other) const
//	{
//		return !(other == *this);
//	}
//
//	uintStandard_t LowBits()
//	{
//		return ID & lowMask;
//	}
//
//	uintStandard_t HighBits()
//	{
//		return ID & highMask;
//	}
//};


#endif
