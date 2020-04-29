#pragma once

#include "core/Pointer.h"
#include "graphics/Spatial.h"

class Node : public Spatial
{
   public:
    Node(size_t quantity = 1);
    virtual ~Node();

    // Total size of child array
    size_t getQuantity() const;
    // How many children are in use
    size_t getUsed() const;

    // Attach / detach child, return index
    size_t attachChild(Spatial* child);
    // TODO Return which index when child not found or NULL?
    size_t detachChild(const Spatial* child);

    Pointer<Spatial> detachChildAt(size_t index);
    Pointer<Spatial> setChild(size_t index, Spatial* child);
    Pointer<Spatial> getChild(size_t index);

   protected:
    /**
     * Geometric update for world bounds
     */
    virtual void updateWorldData(double appTime) override;
    virtual void updateWorldBound() override;

   private:
    std::vector<Pointer<Spatial>> m_children;
    // Open slots in the array
    size_t m_used = 0;
};