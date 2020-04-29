#include "core/Object.h"

#include <cassert>
#include <fstream>
#include <iomanip>

#include "core/Controller.h"
#include "core/Stream.h"

Object::Object() {
    inUse()[getId()] = this;
}

Object::~Object() {
    inUse()[getId()] = nullptr;
}

const RTTI& Object::Type()
{
   static RTTI type = RTTI{"Object"};
   return type;
}

bool Object::isExactly(const RTTI& type) const {
    return getType().isExactly(type);
}

bool Object::isDerived(const RTTI& type) const {
    return getType().isDerived(type);
}
       
bool Object::isExactlyTypeOf(const Object* type) const {
    return type != nullptr && getType().isExactly(type->getType());
}

bool Object::isDerivedTypeOf(const Object* type) const {
    return type != nullptr && getType().isDerived(type->getType());
}

const RTTI& Object::getType() const {
    return Type();
}

void Object::setName(const std::string& name) {
    m_name = name;
}

const std::string& Object::getName() const {
    return m_name;
}

Object* Object::getObjectByName(const std::string& name) {
    // Default implementation
    if (m_name == name) return this;
    return nullptr;
}

std::vector<Object*> Object::getAllObjectsByName(const std::string& name) {
    // Default implementation
    if (m_name == name) return {this};
    return {};
}

Object::Id Object::getId() const {
    return m_id;
}

Object::Id Object::getNextId() {
    static Id id = 0;
    return id++;
}

Object* Object::getObjectById(Id id) {
    // Default implementation
    if (getId() == id) return this;
    return nullptr;
}

void Object::incrementReferences() {
    ++m_references;
}

void Object::decrementReferences() {
    assert(m_references > 0);
    --m_references;
}

int Object::getReferences() const {
    return m_references;
}

std::unordered_map<Object::Id, Object*>& Object::inUse() {
    static std::unordered_map<Object::Id, Object*> objects;
    return objects;
}

void Object::printInUse(const std::string& fileName, const std::string& message) {
    std::ofstream ofs{fileName};
    // TODO Log error
    if (!ofs) return;

    ofs << message << "\n";
    ofs << "Runtime object information\n";
    ofs << "-----------------------------------------------------------\n";
    ofs << "ID         | Name            | Typename        | References\n";

    for (const auto& entry : inUse()) {
        ofs << std::setw(13) << std::left
            << entry.first;
        
        std::string name = "";
        std::string type = "";
        int references = 0;
        
        if (entry.second != nullptr)
        {
            name = entry.second->getName();
            type = entry.second->getType().getName();
            references = entry.second->getReferences();
        }
        
        ofs << std::setw(18) << std::left << name
            << std::setw(18) << std::left << type
            << std::setw(10) << std::left << references
            << "\n";
    }
}

void Object::setController(Controller* controller) {
    m_controllers.push_back(controller);
    controller->setObject(this);
}

size_t Object::getControllerCount() const {
    return m_controllers.size();
}

Controller* Object::getController(size_t index) const {
    return m_controllers.at(index);
}

void Object::removeController(Controller* controller) {
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

void Object::removeAllControllers() {
    m_controllers.clear();
}

void Object::updateControllers(double deltaTime) {
    for (auto controller : m_controllers)
    {
        controller->update(deltaTime);
    }
}

std::unordered_map<std::string, Object::FactoryFunction>& Object::getFactories() {
    static std::unordered_map<std::string, Object::FactoryFunction> factories;
    return factories;
}

bool Object::registerFactory() {
    return false;
}

void Object::initializeFactory() {
}

void Object::terminateFactory() {
}

Object* Object::factory(Stream& stream) {
    return nullptr;
}

void Object::load(Stream& stream, Link* link) {
}

void Object::link(Stream& stream, Link* link) {
}

void Object::registerStream(Stream& stream) const {
}

void Object::save(Stream& stream) const {
}

size_t Object::getMemoryUsed() const {
    return sizeof(Object);
}

size_t Object::getDiskUsed() const {
    return sizeof(Object);
}