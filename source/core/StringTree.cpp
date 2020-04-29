#include "core/StringTree.h"

StringTree::StringTree(size_t stringCount, size_t childCount)
{
    m_strings.resize(stringCount);
    m_children.resize(childCount);
}

StringTree::~StringTree()
{
    // TODO Delete all the children?
    //      Just use unique_ptr instead
}

size_t StringTree::getStringCount() const { return m_strings.size(); }

void StringTree::setString(size_t index, const std::string& str) { m_strings[index] = str; }

std::string& StringTree::getString(size_t index) { return m_strings.at(index); }

size_t StringTree::getChildCount() const { return m_children.size(); }

void StringTree::setChild(size_t index, StringTree* child) { m_children[index] = child; }

StringTree* StringTree::getChild(size_t index) { return m_children.at(index); }