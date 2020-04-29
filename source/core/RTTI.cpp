#include "core/RTTI.h"


RTTI::RTTI(const std::string& name, const RTTI* base) : m_name(name), m_base(base){}

const std::string& RTTI::getName() const { return m_name; } 

bool RTTI::isExactly(const RTTI& type) const {
	// RTTI objects are persistent over runtime, just compare address
	return this == &type;
}

bool RTTI::isDerived(const RTTI& type) const {
	// Single inheritance tree, walk nodes until match or no more nodes
	for (auto curr = this; curr != nullptr; curr = curr->m_base)
	{
		if (curr == &type) return true;
	}
	return false;
}