#include "graphics/TriMesh.h"

TriMesh::TriMesh(const std::vector<glm::vec3>& vertices, const std::vector<std::uint32_t>& indices,
                 bool generateNormals, bool cacheNormals)
    : Geometry(vertices, indices)
{
    geometryType = GeometryType::Trimesh;
}

size_t TriMesh::getTriangleQuantity() const {}
void TriMesh::generateNormals() {}

TriMesh::TriMesh() {}
void TriMesh::updateModelNormals() {}