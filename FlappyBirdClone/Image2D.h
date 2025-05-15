#pragma once

#include "Object2D.h"


struct SDL_Texture;


class CImage2D : public CObject2D
{
public:
    void SetTexture(SDL_Texture* texture);
    void Render(SDL_Renderer* renderer) override;

private:

    SDL_Texture* m_Texture = nullptr;

};
