#pragma once
#include <SGShader.h>
#include <SGVertex.h>
#include <SGTexture.h>

#include <glad/glad.h> // holds all OpenGL type declarations
#include <vector>

namespace SG
{
    class SGMesh {
    public:
        // constructor
        SGMesh(std::vector<SGVertex> vertices, std::vector<unsigned int> indices, std::vector<SGTexture> textures)
        {
            this->vertices = vertices;
            this->indices = indices;
            this->textures = textures;

            // now that we have all the required data, set the vertex buffers and its attribute pointers.
            SetupMesh();
        }

        // render the mesh
        void Draw(SGShader& shader);
    protected:
        // initializes all the buffer objects/arrays
        void SetupMesh();

    public:
        // Mesh Data
        std::vector<SGVertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<SGTexture> textures;
        unsigned int VAO;

    private:
        // Render data
        uint32_t VBO, EBO;
    };
}
