#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "Base/Texture2D.h"
class ShaderTextureNode;

class ShaderTextureManager
{
public:
    ShaderTextureManager();
    ~ShaderTextureManager();

    void Register(ShaderTextureNode* node);
    void Unregister(ShaderTextureNode* node);

    void UpdateShaders();

    void Bind(uint32_t slot);

public:
    uint32_t textureArray;
    std::vector<ShaderTextureNode*> textureNodes;
};