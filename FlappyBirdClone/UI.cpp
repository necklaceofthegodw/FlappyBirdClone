#include "UI.h"
#include "GameLogic.h"
#include <SDL3/SDL.h>


void CUi::Render(const CGameLogic& gameLogic, SDL_Renderer* renderer)
{
    int w = 0, h = 0;
    SDL_GetRenderOutputSize(renderer, &w, &h);

    char message[4] = {};
    SDL_itoa(gameLogic.GetPoints(), message, 10);

    DrawStringTop(renderer, message, gameLogic.GetPointsScale());


    switch (gameLogic.GetGameState())
    {
    case EGameState::Start:
        DrawStringCenter(renderer, "Press SPACE to start", 0.0f, 0.0f, 2.0f);
        break;

    case EGameState::Pause:
        DrawStringCenter(renderer, "PAUSE", 0.0f, -10.0f, 4.0f);
        DrawStringCenter(renderer, "Press SPACE to resume", 0.0f, 0.0f, 2.0f);
        break;

    case EGameState::GameOver:
        DrawStringCenter(renderer, "GAME OVER", 0.0f, -10.0f, 4.0f);
        DrawStringCenter(renderer, "Press SPACE to play again", 0.0f, 0.0f, 2.0f);
        break;

    default:
        break;
    }
}


void CUi::DrawStringCenter(SDL_Renderer* renderer, const char* str, float xOffset, float yOffset, float scale)
{
    int w = 0, h = 0;
    SDL_GetRenderOutputSize(renderer, &w, &h);

    float x, y;
    x = ((w / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * SDL_strlen(str)) / 2;
    y = ((h / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE) / 2;

    DrawString(renderer, str, x + xOffset, y + yOffset, scale);
}


void CUi::DrawStringTop(SDL_Renderer* renderer, const char* str, float scale)
{
    int w = 0, h = 0;
    SDL_GetRenderOutputSize(renderer, &w, &h);

    float x, y;
    x = ((w / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * SDL_strlen(str)) / 2;
    y = ((h / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE) / 12;

    DrawString(renderer, str, x, y, scale);
}


void CUi::DrawString(SDL_Renderer* renderer, const char* str, float x, float y, float scale)
{
    SDL_SetRenderScale(renderer, scale, scale);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDebugText(renderer, x + 1.0f, y + 1.0f, str);

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderDebugText(renderer, x, y, str);

    SDL_SetRenderScale(renderer, 1.0f, 1.0f);
}
