#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

extern "C" int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Failed to open file");
        return 1;
    }

    char buffer[111565];
    size_t bytes_read;

    // Read up to 1000 bytes at a time
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }

    fclose(fp);
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFileFromMemory(
            &buffer, 
            sizeof(buffer), 
            aiProcess_Triangulate | 
            aiProcess_FlipUVs | 
            aiProcess_CalcTangentSpace |
            aiProcess_JoinIdenticalVertices |
            aiProcess_SortByPType,
            "fbx");

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        // Handle error
        printf("Error: %s\n", importer.GetErrorString());
	return -1;
    }
    importer.FreeScene(); 
    return 0;
}
