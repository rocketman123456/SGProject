#include "SGModel.h"

void SGModel::Draw(SGShader shader)
{
    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        meshes[i].Draw(shader);
    }
}
