
#include "mesh.h"
#include "OBJ_Loader.h"

#include "spdlog/spdlog.h"

Mesh::Mesh(MESHES mesh, TEXTURES texture)
{
    objl::Loader loader;
    loader.LoadFile(Meshes::get_obj_path(mesh));
    objl::Mesh & loaded_mesh = loader.LoadedMeshes[0];


    for (objl::Vertex & vertex : loaded_mesh.Vertices) {
        vertices_.push_back(vertex.Position.X);
        vertices_.push_back(vertex.Position.Z);
        vertices_.push_back(vertex.Position.Y);

        uv_.push_back(vertex.TextureCoordinate.X);
        uv_.push_back(vertex.TextureCoordinate.Y);
    }
    update_bb();
    transpose(-bb_.get_base());

    for (unsigned int i : loaded_mesh.Indices) {
        indices_.push_back(i);
    }

    texture_ = texture;
}

void Mesh::update_bb() {
    for (int i = 0; i < vertices_.size(); i+=3) {
        bb_.add_point(glm::vec3(vertices_[i], vertices_[i + 1], vertices_[1 + 2]));
    }
}

void Mesh::transpose(const glm::vec3 & diff) {
    for (int i = 0; i < vertices_.size(); i+=3) {
        vertices_[i] += diff.x;
        vertices_[i + 1] += diff.y;
        vertices_[i + 2] += diff.z;
    }
    update_bb();
}