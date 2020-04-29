#pragma once
#include "SGMesh.h"
#include "SGTexture.h"
#include "SGShader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <string>

class SGModel
{
public:
    SGModel(char* path)
    {
        loadModel(path);
    }
    void Draw(SGShader shader);
private:
    // ģ������
    std::vector<SGMesh> meshes;
    std::string directory;
    // ����
    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    SGMesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<SGTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};
