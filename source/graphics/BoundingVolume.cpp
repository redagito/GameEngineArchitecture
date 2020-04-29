#include "graphics/BoundingVolume.h"

#include "graphics/SphereBV.h"

BoundingVolume::BoundingVolume() {}

BoundingVolume::~BoundingVolume() {}

BoundingVolume* BoundingVolume::create()
{
    return nullptr;
    // return new SphereBV{};
    // return new BoxBV{};
}