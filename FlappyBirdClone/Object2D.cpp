#include "Object2D.h"
#include <SDL3/SDL.h>
#include<SDL3/SDL_render.h>

bool CObject2D::CheckCollisionWith(const CObject2D& other) const
{
    return (m_x < other.m_x + other.m_Width &&
        m_x + m_Width > other.m_x &&
        m_y < other.m_y + other.m_Height &&
        m_y + m_Height > other.m_y);
}


void CObject2D::StartRotate(float destinationAngle, float rotationTime)
{
    m_DestinationAngle = destinationAngle;
    m_RotationTime = rotationTime;
}


void CObject2D::Render(SDL_Renderer* renderer)
{

}

void CObject2D::Reset()
{
    m_DestinationAngle = 0.0f;
    m_RotationTime = 0.0f;
}


void CObject2D::Update(float deltaTime)
{
    if (m_RotationTime > 0.0f)
    {
        m_RotationTime -= deltaTime;
        if (m_RotationTime <= 0.0f)
        {
            m_RotationTime = 0.0f;
            m_Rotation = m_DestinationAngle;
        }
        else
        {
            float rotationStep = (m_DestinationAngle - m_Rotation) * (deltaTime / m_RotationTime);
            m_Rotation += rotationStep;
        }
    }
}
