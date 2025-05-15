#include "GameLogic.h"
#include "World.h"

#include <SDL3/SDL.h>
#include <ctime>
#include <cstdlib>
#include <string>


const char* CGameLogic::BACKGROUND = "background";
const char* CGameLogic::BIRD1 = "bird1";
const char* CGameLogic::BIRD2 = "bird2";
const char* CGameLogic::BIRD3 = "bird3";
const char* CGameLogic::DOWN_PIPE = "down_pipe";
const char* CGameLogic::UP_PIPE = "up_pipe";
const char* CGameLogic::FLOOR = "floor";


void CGameLogic::Initialize(SDL_Renderer* renderer)
{
    srand(static_cast <unsigned> (time(0)));

    m_ResourceManager.LoadTexture(BACKGROUND, "assets/Background.png", renderer);
    m_ResourceManager.LoadTexture(FLOOR, "assets/Foreground.png", renderer);
    m_ResourceManager.LoadTexture(BIRD1, "assets/Bird1.png", renderer);
    m_ResourceManager.LoadTexture(BIRD2, "assets/Bird2.png", renderer);
    m_ResourceManager.LoadTexture(BIRD3, "assets/Bird3.png", renderer);
    m_ResourceManager.LoadTexture(UP_PIPE, "assets/UpPipe.png", renderer);
    m_ResourceManager.LoadTexture(DOWN_PIPE, "assets/DownPipe.png", renderer);

    m_World.Initialize(m_ResourceManager);
    m_Player.Initialize(m_ResourceManager);

    ResetGame();
}


void CGameLogic::Update(float deltaTime)
{
    if (m_GameState == EGameState::Pause)
        return;

    m_World.Update(deltaTime);
    m_Player.Update(deltaTime);

    if (m_GameState == EGameState::Play)
    {
        if (CheckCollisions())
        {
            GameOver();
            return;
        }
    }

    if (m_GameState == EGameState::Play)
    {
        UpdatePointsCount();
        UpdatePointsAnimation(deltaTime);
    }
}


void CGameLogic::Render(SDL_Renderer* renderer)
{
    m_World.Render(renderer);
    m_Player.Render(renderer);

    m_Ui.Render(*this, renderer);
}


bool CGameLogic::CheckCollisions()
{
    return m_World.CheckPlayerCollision(m_Player);
}


void CGameLogic::UpdatePointsCount()
{

    if (m_World.GetFirstObstacle().GetX() < PLAYER_START_X &&
        m_LastScoredObstacleIndex != m_World.GetFirstObstacleIndex())
    {
        m_Points++;
        m_LastScoredObstacleIndex = m_World.GetFirstObstacleIndex();

        m_PointsScale = POINTS_OBTAINSCALE;
        m_PointsScaleAnimTime = POINTS_SCALE_ANIM_TIME;

        m_World.CheckToMoveObstacles();
        m_World.UpdateFirstObstacleIndex(PLAYER_START_X);
    }

}


void CGameLogic::UpdatePointsAnimation(float deltaTime)
{
    if (m_PointsScaleAnimTime > 0.0f)
    {
        m_PointsScale = POINTS_OBTAINSCALE + (POINTS_DEFAULTSCALE - POINTS_OBTAINSCALE) * (m_PointsScaleAnimTime / POINTS_SCALE_ANIM_TIME);
        m_PointsScaleAnimTime -= deltaTime;
    }
    else if (m_PointsScaleAnimTime < 0.0f)
    {
        m_PointsScale = POINTS_DEFAULTSCALE;
        m_PointsScaleAnimTime = 0.0f;
    }
}


SDL_AppResult CGameLogic::ProcessInput(SDL_Event* event)
{
    if (event->type == SDL_EVENT_KEY_DOWN)
    {
        if (event->key.repeat == 0 && event->key.key == SDLK_SPACE)
        {
            if (m_GameState == EGameState::Start || m_GameState == EGameState::Pause)
                StartGame();
            else if (m_GameState == EGameState::Play)
                m_Player.Flap();
            else if (m_GameState == EGameState::GameOver)
                ResetGame();
        }
        else if (event->key.repeat == 0 && event->key.key == SDLK_ESCAPE)
        {
            if (m_GameState == EGameState::Play)
                PauseGame();
            else
                return SDL_APP_SUCCESS;
        }
    }

    return SDL_APP_CONTINUE;
}


void CGameLogic::StartGame()
{
    m_GameState = EGameState::Play;
    m_World.SetWorldMoveSpeed(m_PlayerSpeed);
    m_Player.EnablePhysicsUpdate(true);
}


void CGameLogic::PauseGame()
{
    if (m_GameState == EGameState::Play)
    {
        m_Player.EnablePhysicsUpdate(false);
        m_World.SetWorldMoveSpeed(0.0f);
        m_GameState = EGameState::Pause;
    }
    else
    {
        SDL_Log("[CGameLogic::PauseGame] Game is not in play state, cannot pause. Current state: %d", static_cast<int>(m_GameState));
    }
}


void CGameLogic::GameOver()
{
    if (m_GameState == EGameState::Play)
    {
        m_World.SetWorldMoveSpeed(0.0f);
        m_GameState = EGameState::GameOver;
    }
    else
    {
        SDL_Log("[CGameLogic::GameOver] Game is not in play state, cannot game over. Current state: %d", static_cast<int>(m_GameState));
    }
}


void CGameLogic::ResetGame()
{
    m_Player.SetPosition(PLAYER_START_X, PLAYER_START_Y);
    m_Player.Reset();

    m_World.ResetWorld();

    m_Points = 0;
    m_LastScoredObstacleIndex = -1;

    m_GameState = EGameState::Start;
}
