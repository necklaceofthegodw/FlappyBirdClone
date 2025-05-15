#pragma once

#include "Object2D.h"
#include "Image2D.h"


class CResourceManager;


class CObstacle : public CObject2D
{
public:
    ~CObstacle() override = default;

    void Initialize(const CResourceManager& resourceManager);

    void Render(SDL_Renderer* renderer) override;

    void SetPosition(float x, float y) override;

    const CImage2D(&GetPipes() const)[2]
    {
        return m_Pipes;
    }

private:

    CImage2D m_Pipes[2];

    static constexpr float TOP_PIPE_Y = -265.0f;
    static constexpr float BOTTOM_PIPE_Y = 400.0f;

};
