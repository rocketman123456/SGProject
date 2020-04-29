#pragma once
#include <glm/glm.hpp>

struct SGMaterial // for phong lighting model
{
    SGMaterial(float a1, float a2, float a3, float d1, float d2, float d3, float s1, float s2, float s3, float sh)
        :ambient(glm::vec3(a1, a2, a3)), diffuse(glm::vec3(d1, d2, d3)), specular(glm::vec3(s1, s3, s3)), shininess(sh){}
    SGMaterial(glm::vec3 a, glm::vec3 d, glm::vec3 s, float sh)
        :ambient(a), diffuse(d), specular(s), shininess(sh) {}
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};
