#pragma once
#include "SGMesh.h"
#include "SGTexture.h"
#include "SGShader.h"

#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

class SGModel
{
public:
    SGModel(const char* path);
    void Draw(SGShader& shader);
protected:
    // 函数
    void loadModel(const std::string& path);
    void processNode(aiNode* node, const aiScene* scene);
    SGMesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<SGTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
protected:
    // 模型数据
    std::vector<SGMesh> meshes;
    std::vector<SGTexture> textures_loaded;
    std::string directory;
    bool gammaCorrection;
};

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);
