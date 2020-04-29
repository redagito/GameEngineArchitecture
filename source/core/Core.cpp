#include "core/Core.h"

#include <cassert>

#include "core/Object.h"

void Core::addInitializer(Core::Initializer init) { getInitializer().push_back(init); }

void Core::initialize()
{
    // Objects should not exist pre-init
    size_t count = Object::inUse().size();

    assert(count == 0);
    if (count != 0)
    {
        Object::printInUse("objects_init.log", "Objects were created before pre-main initialization");
    }

    for (auto init : getInitializer())
    {
        init();
    }

    // Number of objects created during pre-main init
    startObjects() = Object::inUse().size();
}

void Core::addTerminator(Core::Terminator term) { getTerminator().push_back(term); }

void Core::terminate()
{
    // All objects created during application lifetime should be deleted by now
    size_t count = Object::inUse().size();

    assert(count == startObjects());
    if (startObjects() != count)
    {
        Object::printInUse("objects_preterm.log", "Not all objects were deleted before post-main termination");
    }

    for (auto term : getTerminator())
    {
        term();
    }

    // No objects should exist / be deleted after termination
    finalObjects() = Object::inUse().size();

    assert(finalObjects() == 0);
    if (finalObjects() != 0)
    {
        Object::printInUse("objects_postterm.log", "Objects were deleted after post-main termination");
    }
}

std::vector<Core::Initializer>& Core::getInitializer()
{
    static std::vector<Core::Initializer> initializer;
    return initializer;
}

std::vector<Core::Terminator>& Core::getTerminator()
{
    static std::vector<Core::Terminator> terminator;
    return terminator;
}

size_t& Core::startObjects()
{
    static size_t count = 0;
    return count;
}

size_t& Core::finalObjects()
{
    static size_t count = 0;
    return count;
}