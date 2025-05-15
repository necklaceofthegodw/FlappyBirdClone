#include "ResourceManager.h"

#include <SDL3/SDL.h>
#include <SDL_image.h>


bool CResourceManager::LoadTexture(const std::string& id, const std::string& filePath, SDL_Renderer* renderer)
{
    if (m_Textures.count(id) > 0)
        return true;

    std::string fullPath = SDL_GetBasePath() + filePath;
    SDL_Texture* texture = IMG_LoadTexture(renderer, fullPath.c_str());
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

     if (!texture)
        return false;

    m_Textures[id] = texture;
    return true;
}


SDL_Texture* CResourceManager::GetTexture(const std::string& id) const
{
    auto it = m_Textures.find(id);
    if (it != m_Textures.end())
        return it->second;

    return nullptr;
}


void CResourceManager::UnloadTexture(const std::string& id)
{
    auto it = m_Textures.find(id);
    if (it != m_Textures.end())
    {
        SDL_DestroyTexture(it->second);
        m_Textures.erase(it);
    }
}


void CResourceManager::Cleanup()
{
    for (auto& pair : m_Textures)
        SDL_DestroyTexture(pair.second);

    m_Textures.clear();
}
