#include "Image2D.h"
#include <SDL3/SDL.h>


void CImage2D::SetTexture(SDL_Texture* texture)
{
    m_Texture = texture;

    if (m_Texture)
    {
        m_Width = static_cast<float>(m_Texture->w);
        m_Height = static_cast<float>(m_Texture->h);
    }
}


void CImage2D::Render(SDL_Renderer* renderer)
{
    if (!m_Texture)
        return;

    SDL_FPoint center;

    SDL_FRect dstRect;
    dstRect.x = m_x;
    dstRect.y = m_y;
    dstRect.w = m_Width;
    dstRect.h = m_Height;

    center.x = m_Width / 2.0f;
    center.y = m_Height / 2.0f;
    SDL_SetTextureScaleMode(m_Texture, SDL_SCALEMODE_NEAREST);
    SDL_RenderTextureRotated(renderer, m_Texture, nullptr, &dstRect, m_Rotation, &center, SDL_FLIP_NONE);
}
