#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "core/Pointer.h"
#include "graphics/BoundingVolume.h"
#include "graphics/sg/Spatial.h"

class Geometry : public Spatial
{
   public:
    // Supported types
    enum class GeometryType
    {
        // Collection of points
        Polypoint,

        // Collections of line segments
        // Set of line segments without connection
        PolylineSegments,
        // Line strip
        PolylineOpen,
        // Line loop
        PolylineClosed,

        // Triangle mesh
        Trimesh,

        // Keep at end
        Max
    };
    // Default to points
    GeometryType geometryType = GeometryType::Polypoint;

    /**
     * Geometric update for world bounds
     */
    std::vector<glm::vec3> vertices;
    std::vector<std::uint32_t> indices;
    std::vector<glm::vec3> normals;
    Pointer<BoundingVolume> modelBound;

    Geometry() = default;
    Geometry(const std::vector<glm::vec3>& vertices);
    Geometry(const std::vector<glm::vec3>& vertices, const std::vector<uint32_t>& indices);
    virtual ~Geometry() = default;

    /**
     * Update for model data
     * Updates model bound and model normals
     */
    void updateModelState(bool updateNormals);

    // Internal use
    Pointer<GlobalState> states[static_cast<std::underlying_type<GlobalState::Type>::type>(GlobalState::Type::Max)];

   protected:
    virtual void updateModelBound();
    virtual void updateModelNormals();

    /**
     * Transform model bounding volume to world bounding volume
     */
    virtual void updateWorldBound() override;

    /**
     * Update rendering state
     */
    virtual void updateState(std::stack<GlobalState*>& globalStates, std::stack<Light*>& lights) override;
};