#include "core/Object.h"

#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "core/Controller.h"
#include "core/Core.h"
#include "core/Stream.h"

Object::Object() { inUse()[getId()] = this; }

Object::~Object() { inUse().erase(getId()); }

bool Object::isExactly(const RTTI& type) const { return getType().isExactly(type); }

bool Object::isDerived(const RTTI& type) const { return getType().isDerived(type); }

bool Object::isExactlyTypeOf(const Object* type) const
{
    return type != nullptr && getType().isExactly(type->getType());
}

bool Object::isDerivedTypeOf(const Object* type) const
{
    return type != nullptr && getType().isDerived(type->getType());
}

void Object::setName(const std::string& name) { m_name = name; }

const std::string& Object::getName() const { return m_name; }

Object* Object::getObjectByName(const std::string& name)
{
    // Default implementation
    if (m_name == name)
        return this;
    return nullptr;
}

std::vector<Object*> Object::getAllObjectsByName(const std::string& name)
{
    // Default implementation
    if (m_name == name)
        return {this};
    return {};
}

Object::Id Object::getId() const { return m_id; }

Object::Id Object::getNextId()
{
    static Id id = 0;
    return id++;
}

Object* Object::getObjectById(Id id)
{
    // Default implementation
    if (getId() == id)
        return this;
    return nullptr;
}

void Object::incrementReferences() { ++m_references; }

void Object::decrementReferences()
{
    assert(m_references > 0);
    --m_references;
}

int Object::getReferences() const { return m_references; }

std::unordered_map<Object::Id, Object*>& Object::inUse()
{
    static std::unordered_map<Object::Id, Object*> objects;
    return objects;
}

void Object::printInUse(const std::string& fileName, const std::string& message)
{
    std::ofstream ofs{fileName};
    // TODO Log error
    if (!ofs)
        return;

    ofs << message << "\n";
    ofs << "Runtime object information\n";
    ofs << "-----------------------------------------------------------\n";
    ofs << "ID         | Name            | Typename        | References\n";
    ofs << "-----------------------------------------------------------\n";

    for (const auto& entry : inUse())
    {
        ofs << std::setw(13) << std::left << entry.first;

        std::string name = "";
        std::string type = "";
        int references = 0;

        if (entry.second != nullptr)
        {
            name = entry.second->getName();
            type = entry.second->getType().getName();
            references = entry.second->getReferences();
        }

        ofs << std::setw(18) << std::left << name << std::setw(18) << std::left << type << std::setw(10) << std::left
            << references << "\n";
    }
}

void Object::setController(Controller* controller)
{
    m_controllers.push_back(controller);
    controller->setObject(this);
}

size_t Object::getControllerCount() const { return m_controllers.size(); }

Controller* Object::getController(size_t index) const { return m_controllers.at(index); }

void Object::removeController(Controller* controller)
{
    for (auto iter = m_controllers.begin(); iter != m_controllers.end();)
    {
        if (*iter == controller)
        {
            iter = m_controllers.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}

void Object::removeAllControllers() { m_controllers.clear(); }

void Object::updateControllers(double appTime)
{
    for (auto controller : m_controllers)
    {
        controller->update(appTime);
    }
}

std::unordered_map<std::string, Object::FactoryFunction>& Object::getFactories()
{
    static std::unordered_map<std::string, Object::FactoryFunction> factories;
    return factories;
}

bool Object::registerFactory() { return false; }

void Object::initializeFactory() {}

void Object::terminateFactory() {}

Object* Object::factory(Stream& stream) { return nullptr; }

void Object::load(Stream& stream, Link* link)
{
    // Old object address
    void* oldAddress = nullptr;
    stream.read(oldAddress);
    stream.insertInMap(static_cast<Object*>(oldAddress), link);

    // Name
    stream.read(m_name);

    // Link data
    size_t controllerCount;
    stream.read(controllerCount);

    for (size_t i = 0; i < controllerCount; ++i)
    {
        // Old controller address
        void* controller = nullptr;
        stream.read(controller);

        // Build controller list, filled in by link
        m_controllers.push_back(static_cast<Controller*>(controller));
    }
}

void Object::link(Stream& stream, Link* link)
{
    // Currently the stored controller addresses are invalid
    // Linking resolves this by mapping old to new addresses
    // TODO This looks wrong
    for (auto& controller : m_controllers)
    {
        Object* linkId = link->getLinkId();
        controller = static_cast<Controller*>(stream.getFromMap(linkId));
    }
}

bool Object::registerStream(Stream& stream)
{
    if (!stream.insertInMap(this, nullptr))
        return false;

    // Ensure objects are saved in order corresponding to
    // depth-first traversal
    stream.insertInOrdered(this);

    // Register controllers
    for (auto controller : m_controllers)
    {
        if (controller != nullptr)
            controller->registerStream(stream);
    }
    return true;
}

void Object::save(Stream& stream) const
{
    // RTTI name for factory lookup on load
    stream.write(getType().getName());

    // Address of the object to use as unique id on load/link
    stream.write(this);

    // Object name
    stream.write(getName());

    // Link data
    stream.write(m_controllers.size());
    for (auto controller : m_controllers)
    {
        stream.write(controller);
    }
}

size_t Object::getMemoryUsed() const { return 0; }

size_t Object::getDiskUsed() const { return 0; }

Pointer<Object> Object::copy()
{
    // Save object to memory
    Stream stream;
    stream.insert(this);

    // Write to buffer
    std::uint8_t* buffer = nullptr;
    size_t size = 0;
    if (!stream.save(buffer, size))
    {
        // Failed to save
        return nullptr;
    }

    // Load from buffer
    // TODO Make sure stream can be reused, might need clear?
    if (!stream.load(buffer, size))
    {
        delete[] buffer;
        return nullptr;
    }

    delete[] buffer;
    buffer = nullptr;

    // Generate unique names
    for (size_t i = 0; i < stream.getOrderedCount(); ++i)
    {
        Object* object = stream.getOrderedObject(i);
        assert(object != nullptr);

        std::string name = object->getName();
        if (!name.empty())
        {
            // Object has name, append char to make it unique
            // TODO This is kinda weird, why not keep original name,
            //      nothing SHOULD rely on object names being unique?
            name.push_back(nameAppend());
        }
    }

    // TODO Additional checks to make sure only one object is present
    return stream.getObject(0);
}

char Object::nameAppend() { return '#'; }

StringTree* Object::saveStrings(const std::string& title) { return nullptr; }

INITIALIZE_DEFINE(Object);
TERMINATE_DEFINE(Object);

void Object::initialize()
{
    // Sample initializer
}

void Object::terminate()
{
    // Sample terminater
}