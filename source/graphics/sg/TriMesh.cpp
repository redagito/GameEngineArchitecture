#include "graphics/sg/TriMesh.h"

TriMesh::TriMesh(const std::vector<glm::vec3>& vertices, const std::vector<std::uint32_t>& indices,
                 bool generateNormals, bool cacheNormals)
    : Geometry(vertices, indices)
{
    geometryType = GeometryType::Trimesh;
}

size_t TriMesh::getTriangleQuantity() const
{
    // 3 vertices produce one triangle
    return vertices.size() / 3;
}

void TriMesh::generateNormals() {}

TriMesh::TriMesh() {}
void TriMesh::updateModelNormals() {}