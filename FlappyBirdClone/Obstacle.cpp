#include "Obstacle.h"
#include "ResourceManager.h"
#include "GameLogic.h"


void CObstacle::Initialize(const CResourceManager& resourceManager)
{
    m_Pipes[0].SetTexture(resourceManager.GetTexture(CGameLogic::DOWN_PIPE));
    m_Pipes[0].SetPosition(GetX(), GetY() + TOP_PIPE_Y);

    m_Pipes[1].SetTexture(resourceManager.GetTexture(CGameLogic::UP_PIPE));
    m_Pipes[1].SetPosition(GetX(), GetY() + BOTTOM_PIPE_Y);

    // height is not important, so is set to huge value
    SetSize(m_Pipes[0].GetWidth(), 2000);
}


void CObstacle::SetPosition(float x, float y)
{
    CObject2D::SetPosition(x, y);

    m_Pipes[0].SetPosition(GetX(), GetY() + TOP_PIPE_Y);
    m_Pipes[1].SetPosition(GetX(), GetY() + BOTTOM_PIPE_Y);
}


void CObstacle::Render(SDL_Renderer* renderer)
{
    for (auto& pipe : m_Pipes)
        pipe.Render(renderer);
}
