#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "core/Pointer.h"
#include "core/RTTI.h"

/**
 * RTTI macros
 */
#define RTTI_DECLARE(CLASS_NAME, BASE_NAME)                       \
    inline static const RTTI& Type()                              \
    {                                                             \
        static RTTI type = RTTI{#CLASS_NAME, &BASE_NAME::Type()}; \
        return type;                                              \
    }                                                             \
    inline const RTTI& getType() const { return Type(); }

// Forward declare
// TODO Resolve circular dependencies
class Controller;
class Stream;
class Link;

/**
 * Base object for RTTI
 */
class Object
{
   public:
    // Object ID
    using Id = std::uint64_t;

    // Factory function
    using FactoryFunction = Object* (*)(Stream&);

    Object();
    virtual ~Object();

    /**
     * RTTI support
     */
    static const RTTI& Type();

    bool isExactly(const RTTI& type) const;
    bool isDerived(const RTTI& type) const;

    bool isExactlyTypeOf(const Object* type) const;
    bool isDerivedTypeOf(const Object* type) const;

    virtual const RTTI& getType() const;

    /**
     * Object runtime name
     */
    void setName(const std::string& name);
    const std::string& getName() const;

    virtual Object* getObjectByName(const std::string& name);
    virtual std::vector<Object*> getAllObjectsByName(const std::string& name);

    /**
     * Unique runtime ID
     */
    Id getId() const;
    static Id getNextId();
    virtual Object* getObjectById(Id id);

    /**
     * Smart pointer and sharing
     */
    void incrementReferences();
    void decrementReferences();
    int getReferences() const;

    static std::unordered_map<Id, Object*>& inUse();
    static void printInUse(const std::string& fileName, const std::string& message);

    /**
     * Controller support
     */
    void setController(Controller* controller);
    size_t getControllerCount() const;
    Controller* getController(size_t index) const;
    void removeController(Controller* controller);
    void removeAllControllers();
    void updateControllers(double deltaTime);

    /**
     * Streaming support
     */
    static std::unordered_map<std::string, FactoryFunction>& getFactories();
    static bool registerFactory();
    static void initializeFactory();
    static void terminateFactory();
    static Object* factory(Stream& stream);

    virtual void load(Stream& stream, Link* link);
    virtual void link(Stream& stream, Link* link);
    virtual bool registerStream(Stream& stream);
    virtual void save(Stream& stream) const;

    virtual size_t getMemoryUsed() const;
    virtual size_t getDiskUsed() const;

   private:
    // Object name
    std::string m_name;

    // UID
    const Id m_id = getNextId();

    // Reference count
    // TODO Should be unsigned but keep signed for in now in case of bugs
    //      where we might get negative count
    int m_references = 0;

    // Attached controllers
    std::vector<Controller*> m_controllers;
};

template <typename T>
T* staticCast(Object* obj)
{
    return reinterpret_cast<T*>(obj);
}

template <typename T>
const T* staticCast(const Object* obj)
{
    return reinterpret_cast<const T*>(obj);
}

template <typename T>
T* dynamicCast(Object* obj)
{
    if (obj != nullptr && obj->isDerived(T::Type()))
        return dynamic_cast<T*>(obj);
    return nullptr;
}

template <typename T>
const T* dynamicCast(const Object* obj)
{
    if (obj != nullptr && obj->isDerived(T::Type()))
        return dynamic_cast<const T*>(obj);
    return nullptr;
}