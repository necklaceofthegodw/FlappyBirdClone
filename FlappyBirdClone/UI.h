#pragma once


struct SDL_Renderer;
class CGameLogic;


class CUi
{
public:

    void Render(const CGameLogic& gameLogic, SDL_Renderer* renderer);

private:
    void DrawStringCenter(SDL_Renderer* renderer, const char* str, float xOffset, float yOffset, float scale);
    void DrawStringTop(SDL_Renderer* renderer, const char* str, float scale);

    void DrawString(SDL_Renderer* renderer, const char* str, float x, float y, float scale);
};
