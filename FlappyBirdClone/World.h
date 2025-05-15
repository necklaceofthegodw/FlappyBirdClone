#pragma once

#include "Image2D.h"
#include "Obstacle.h"

struct SDL_Renderer;
class CResourceManager;

class CWorld : public CObject2D
{
public:

    bool CheckPlayerCollision(const CObject2D& player) const;

    const CObstacle& GetFirstObstacle() const;
    int GetFirstObstacleIndex() const;

    void UpdateFirstObstacleIndex(const float playerStartX);

    void Initialize(const CResourceManager& resourceManager);

    void Render(SDL_Renderer* renderer) override;

    void ResetWorld();

    void SetInitialFloorPosition();

    void SetInitalObstaclesPosition();

    void SetWorldMoveSpeed(float speed) { m_WorldMoveSpeed = speed; }

    void Update(float deltaTime) override;

    void CheckToMoveObstacles();

private:

    float GetObstacleRandomYPosition() const;
    float GetObstacleRandomDistanceX() const;

    static constexpr int OBSTACLES_COUNT = 6;
    static constexpr int FLOOR_COUNT = 2;
    static constexpr float FLOOR_Y = 500.0f;
    static constexpr float OBSTACLE_START_OFFSET_X = 500.0f;
    static constexpr float OBSTACLES_DISTANCE = 250.0f;
    static constexpr float OBSTACLE_MIN_Y = -110.0f;
    static constexpr float OBSTACLE_MAX_Y = 60.0f;
    static constexpr float OBSTACLE_MIN_DIST_X = 200.0f;
    static constexpr float OBSTACLE_MAX_DIST_X = 500.0f;
    static constexpr int MOVE_OBSTACLES_INDEX = 3;

    CImage2D m_Background;
    CImage2D m_Floor[2];
    CObject2D m_Ceil;
    CObstacle m_Obstacles[OBSTACLES_COUNT];

    float m_WorldMoveSpeed = 0.0f;
    int m_FirstObstacleIndex = 0;
};
