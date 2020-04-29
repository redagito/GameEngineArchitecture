#pragma once

#include <string>
#include <vector>

/**
 * For human readable representation of object hierarchies
 */
class StringTree
{
   public:
    StringTree(size_t stringCount, size_t childCount);
    virtual ~StringTree();

    // Strings
    size_t getStringCount() const;
    void setString(size_t index, const std::string& str);
    std::string& getString(size_t index);

    // Children
    size_t getChildCount() const;
    void setChild(size_t index, StringTree* child);
    StringTree* getChild(size_t index);

   private:
    std::vector<std::string> m_strings;
    std::vector<StringTree*> m_children;
};