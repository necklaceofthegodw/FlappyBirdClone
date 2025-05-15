#pragma once

#include "World.h"
#include "Player.h"
#include "Ui.h"
#include "ResourceManager.h"

struct SDL_Renderer;
union SDL_Event;
enum SDL_AppResult;

enum class EGameState : int
{
    None,
    Start,
    Play,
    Pause,
    GameOver,
};

class CGameLogic
{
public:
    CGameLogic() = default;
    ~CGameLogic() = default;

    void Initialize(SDL_Renderer* renderer);
    void Update(float deltaTime);
    SDL_AppResult ProcessInput(SDL_Event* event);
    void Render(SDL_Renderer* renderer);

    EGameState GetGameState() const { return m_GameState; }
    int GetPoints() const { return m_Points; }
    float GetPointsScale() const { return m_PointsScale; }

private:
    bool CheckCollisions();
    

    void StartGame();
    void PauseGame();
    void GameOver();
    void ResetGame();

    void UpdatePointsCount();
    void UpdatePointsAnimation(float deltaTime);

    static constexpr float PLAYER_START_X = 50.0f;
    static constexpr float PLAYER_START_Y = 270.0f;

    static constexpr float POINTS_DEFAULTSCALE = 4.0f;
    static constexpr float POINTS_OBTAINSCALE = 5.0f;
    static constexpr float POINTS_SCALE_ANIM_TIME = 0.25f;

    CPlayer m_Player;
    CWorld m_World;
    CUi m_Ui;
    CResourceManager m_ResourceManager;

    EGameState m_GameState = EGameState::None;

    float m_PlayerSpeed = 100.0f;

    int m_Points = 0;
    int m_LastScoredObstacleIndex = -1;

    float m_PointsScale = 4.0f;
    float m_PointsScaleAnimTime = 0.0f;

public:
    static const char* BACKGROUND;
    static const char* BIRD1;
    static const char* BIRD2;
    static const char* BIRD3;
    static const char* DOWN_PIPE;
    static const char* UP_PIPE;
    static const char* FLOOR;
};
