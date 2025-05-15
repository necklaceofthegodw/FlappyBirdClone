#pragma once

#include <unordered_map>
#include <string>

struct SDL_Texture;
struct SDL_Renderer;

class CResourceManager
{
public:
    CResourceManager() = default;
    ~CResourceManager() = default;

    bool LoadTexture(const std::string& id, const std::string& filePath, SDL_Renderer* renderer);
    SDL_Texture* GetTexture(const std::string& id) const;
    void UnloadTexture(const std::string& id);
    void Cleanup();

private:
    CResourceManager(const CResourceManager&) = delete;
    CResourceManager& operator=(const CResourceManager&) = delete;

    std::unordered_map<std::string, SDL_Texture*> m_Textures;
};
