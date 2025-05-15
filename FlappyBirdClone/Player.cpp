#include "Player.h"
#include "ResourceManager.h"
#include "GameLogic.h"
#include <SDL3/SDL.h>


void CPlayer::Initialize(const CResourceManager& resourceManager)
{
    m_AnimationImages[0].SetTexture(resourceManager.GetTexture(CGameLogic::BIRD1));
    m_AnimationImages[1].SetTexture(resourceManager.GetTexture(CGameLogic::BIRD2));
    m_AnimationImages[2].SetTexture(resourceManager.GetTexture(CGameLogic::BIRD3));

    SetSize(m_AnimationImages[0].GetWidth(), m_AnimationImages[0].GetHeight());
    SetRotation(ROTATION_UP);
}


void CPlayer::Reset()
{
    CObject2D::Reset();

    SetRotation(0.0f);
    EnablePhysicsUpdate(false);
    m_UpwardForce = 0.0f;
    m_AnimationTime = 0.0f;
    m_CurrentImageIndex = 0;
}


void CPlayer::Update(float deltaTime)
{
    CObject2D::Update(deltaTime);

    Animate(deltaTime);
    HandlePhysics(deltaTime);
}


void CPlayer::Animate(float deltaTime)
{
    m_AnimationTime += deltaTime;
    if (m_AnimationTime >= ANIMATION_INTERVAL)
    {
        m_AnimationTime = 0.0f;
        m_CurrentImageIndex = (m_CurrentImageIndex + 1) % 3;
    }
}


void CPlayer::HandlePhysics(float deltaTime)
{
    if (!m_UpdatePhysics)
        return;

    if (m_UpwardForce > 0.0f)
    {
        m_UpwardForce -= JUMP_FORCE * deltaTime;
    }

    passedTime += deltaTime; 
    if (passedTime > ROTATION_UPDATE_TIME)
    {

        if (GetY() - lastFrameY > 0)
        {
            SetRotation(ROTATION_DOWN);
        }
        else
        {
            SetRotation(ROTATION_UP);
        }

        passedTime = 0;
        lastFrameY = GetY();
    }


    if (m_UpwardForce < 0.0f)
    {
        m_UpwardForce = 0.0f;
    }

    m_y += (GRAVITY - m_UpwardForce) * deltaTime;

}


void CPlayer::Render(SDL_Renderer* renderer)
{
    if (m_CurrentImageIndex < 0 || m_CurrentImageIndex >= ANIMATION_FRAMES_COUNT)
        return;

    m_AnimationImages[m_CurrentImageIndex].SetRotation(GetRotation());
    m_AnimationImages[m_CurrentImageIndex].SetPosition(GetX(), GetY());
    m_AnimationImages[m_CurrentImageIndex].Render(renderer);
}


void CPlayer::Flap()
{
    m_UpwardForce = JUMP_FORCE;
}


void CPlayer::EnablePhysicsUpdate(bool enable)
{
    m_UpdatePhysics = enable;
}
