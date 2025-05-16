#pragma once

#include "Object2D.h"
#include "Image2D.h"


class CResourceManager;


class CPlayer : public CObject2D
{
public:

    void Initialize(const CResourceManager& resourceManager);
    void Reset() override;

    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer) override;

    void Flap();

    void EnablePhysicsUpdate(bool enable);

private:
    void Animate(float deltaTime);
    void HandlePhysics(float deltaTime);

    static constexpr float ANIMATION_INTERVAL = 0.1f;
    static constexpr float GRAVITY = 400.0f;
    static constexpr int ANIMATION_FRAMES_COUNT = 3;
    static constexpr float JUMP_FORCE = 780.0f;
    static constexpr float START_FALL_ROTATION_VALUE = JUMP_FORCE/4.0f;
    static constexpr float MAX_UP_ANGLE = -35.0f;
    static constexpr float MAX_DOWN_ANGLE = 90.0f;
    static constexpr float FALL_ROTATION_TIME = 0.4f;
    static constexpr float FLY_UP_ROTATION_TIME = 0.2f;
    static constexpr float ROTATION_UP = -25.0f;
    static constexpr float ROTATION_DOWN = 70.0f;
    static constexpr float ROTATION_UPDATE_TIME = 0.05f;

    CImage2D m_AnimationImages[ANIMATION_FRAMES_COUNT];
    int m_CurrentImageIndex = 0;
    float m_AnimationTime = 0.0f;
    float m_LastFrameY = 0.0f;
    float m_PassedTime = 0.0f;

    float m_UpwardForce = 0.0f;
    bool m_UpdatePhysics = false;
};
