#include <stdio.h>
#include <stdint.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

extern "C" int LLVMFuzzerInitialize(int *argc, char **argv) {
    return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFileFromMemory(
            data, 
            size, 
            aiProcess_Triangulate | 
            aiProcess_FlipUVs | 
            aiProcess_CalcTangentSpace |
            aiProcess_JoinIdenticalVertices |
            aiProcess_SortByPType,
            "fbx");
    importer.FreeScene(); 
    return 0;
}
