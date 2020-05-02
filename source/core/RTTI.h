#pragma once

#include <string>

/**
 * Runtime type information for single inheritance tree
 */
class RTTI
{
   public:
    RTTI(const std::string& name, const RTTI* base = nullptr);

    /**
     * Type name string identifier
     */
    const std::string& getName() const;

    /**
     * Is the provided type
     */
    bool isExactly(const RTTI& type) const;

    /**
     * Is either the same type or a derived type
     */
    bool isDerived(const RTTI& type) const;

   private:
    // Type name
    std::string m_name;
    // Base type
    const RTTI* m_base;
};

/**
 * RTTI helper macros for Object class and derived types
 */
#define RTTI_DECLARE(CLASS_NAME, BASE_NAME)                       \
    inline static const RTTI& Type()                              \
    {                                                             \
        static RTTI type = RTTI{#CLASS_NAME, &BASE_NAME::Type()}; \
        return type;                                              \
    }                                                             \
    inline virtual const RTTI& getType() const { return Type(); }

#define RTTI_DECLARE_NO_BASE(CLASS_NAME)      \
    inline static const RTTI& Type()          \
    {                                         \
        static RTTI type = RTTI{#CLASS_NAME}; \
        return type;                          \
    }                                         \
    inline virtual const RTTI& getType() const { return Type(); }
