
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
    scale(height_ / bb_.get_size().y);
    set_org_vertices();

    for (unsigned int i : loaded_mesh.Indices) {
        indices_.push_back(i);
    }

    texture_ = texture;
}
