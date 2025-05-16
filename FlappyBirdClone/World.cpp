#include "World.h"
#include "Obstacle.h"
#include "Image2D.h"
#include "ResourceManager.h"
#include "GameLogic.h"
#include <cstdlib>

void CWorld::Initialize(const CResourceManager& resourceManager)
{
    m_Background.SetTexture(resourceManager.GetTexture(CGameLogic::BACKGROUND));

    m_Ceil.SetPosition(0.0f, -100.0f);
    m_Ceil.SetSize(100.0f, 100.0f);

    for (auto& floor : m_Floor)
        floor.SetTexture(resourceManager.GetTexture(CGameLogic::FLOOR));

    for (auto& obstacle : m_Obstacles)
        obstacle.Initialize(resourceManager);

    SetInitialFloorPosition();
    SetInitalObstaclesPosition();
}

void CWorld::ResetWorld()
{
    SetInitialFloorPosition();
    SetInitalObstaclesPosition();

    m_FirstObstacleIndex = 0;
}

void CWorld::SetInitialFloorPosition()
{
    int floorId = 0;
    for (auto& floor : m_Floor)
    {
        floor.SetPosition(floorId * floor.GetWidth(), FLOOR_Y);
        floorId++;
    }
}

void CWorld::SetInitalObstaclesPosition()
{
    int obstacleId = 0;
    float previousDistanceAdded = 0;
    for (auto& obstacle : m_Obstacles)
    {
        previousDistanceAdded += GetObstacleRandomDistanceX();
        obstacle.SetPosition(OBSTACLE_START_OFFSET_X + previousDistanceAdded, GetObstacleRandomYPosition());
        obstacleId++;
    }
}

bool CWorld::CheckPlayerCollision(const CObject2D& player) const
{
    auto result = false;
    const auto& obstacle = GetFirstObstacle();
    const auto& pipes = obstacle.GetPipes();
    
    for (const auto& pipe : pipes)
        result |= pipe.CheckCollisionWith(player);

    result |= m_Ceil.CheckCollisionWith(player);


    result |= m_Floor[0].CheckCollisionWith(player);
    result |= m_Floor[1].CheckCollisionWith(player);

    return result;
}

const CObstacle& CWorld::GetFirstObstacle() const
{
    return m_Obstacles[m_FirstObstacleIndex];
}

int CWorld::GetFirstObstacleIndex() const
{ 
    return m_FirstObstacleIndex;
}

void CWorld::UpdateFirstObstacleIndex(const float playerStartX)
{
    for (int obstacleIndex = 0; obstacleIndex < OBSTACLES_COUNT; obstacleIndex++)
    {
        if (m_Obstacles[obstacleIndex].GetX()  > playerStartX)
        {
            m_FirstObstacleIndex = obstacleIndex;
            break;
        }
    }
}

void CWorld::CheckToMoveObstacles()
{
    if (m_FirstObstacleIndex == MOVE_OBSTACLES_INDEX)
    {
        float distanceX = m_Obstacles[OBSTACLES_COUNT - 1].GetX();

        for (int obstacleIndex = 0; obstacleIndex < 2; obstacleIndex++) //move first 2 obstacles to the end of last 4 obstacles
        {
            distanceX += GetObstacleRandomDistanceX();
            m_Obstacles[obstacleIndex].SetPosition(distanceX, GetObstacleRandomYPosition());
        }

        CObstacle tempObstacles[OBSTACLES_COUNT];

        for (int i = 0; i < OBSTACLES_COUNT; i++)
        {
            tempObstacles[i] = m_Obstacles[(i + 2) % OBSTACLES_COUNT];
        }

        for (int obstacleIndex = 0; obstacleIndex < OBSTACLES_COUNT; obstacleIndex++)
        {
            m_Obstacles[obstacleIndex] = tempObstacles[obstacleIndex];
        }
    }

}

float CWorld::GetObstacleRandomYPosition() const
{
    return static_cast<float>(rand() % static_cast<int>(OBSTACLE_MAX_Y - OBSTACLE_MIN_Y)) + OBSTACLE_MIN_Y;
}

float CWorld::GetObstacleRandomDistanceX() const
{
    return static_cast<float>(rand() % static_cast<int>(OBSTACLE_MAX_DIST_X - OBSTACLE_MIN_DIST_X)) + OBSTACLE_MIN_DIST_X;
}

void CWorld::Update(float deltaTime)
{
    for (auto& floor : m_Floor)
    {
        floor.SetPosition(floor.GetX() - m_WorldMoveSpeed * deltaTime, FLOOR_Y);
        if (floor.GetX() < -floor.GetWidth())
            floor.SetPosition(floor.GetX() + floor.GetWidth() * FLOOR_COUNT, FLOOR_Y);
    }

    for (auto& obstacle : m_Obstacles)
    {
        obstacle.SetPosition(obstacle.GetX() - m_WorldMoveSpeed * deltaTime, obstacle.GetY());
    }

}

void CWorld::Render(SDL_Renderer* renderer)
{
    m_Background.Render(renderer);

    for (auto& obstacle : m_Obstacles)
        obstacle.Render(renderer);

    for (auto& floor : m_Floor)
        floor.Render(renderer);
}
