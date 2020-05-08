#pragma once
#include <vector>
#include <string>

uint32_t CubeMapFromFile(std::vector<std::string> faces);
uint32_t TextureFromFile(const char* path, const std::string& directory, bool gamma = false);
