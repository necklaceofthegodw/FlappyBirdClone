#pragma once


struct SDL_Renderer;

class CObject2D
{
public:
    virtual ~CObject2D() = default;

    bool CheckCollisionWith(const CObject2D& other) const;

    [[nodiscard]] float GetX() const
    {
        return m_x;
    }

    [[nodiscard]] float GetY() const
    {
        return m_y;
    }

    virtual void SetPosition(float x, float y)
    {
        m_x = x;
        m_y = y;
    }

    [[nodiscard]] float GetWidth() const
    {
        return m_Width;
    }

    [[nodiscard]] float GetHeight() const
    {
        return m_Height;
    }

    void SetSize(float width, float height)
    {
        m_Width = width;
        m_Height = height;
    }

    [[nodiscard]] float GetRotation() const
    {
        return m_Rotation;
    }

    void SetRotation(float rotation)
    {
        m_Rotation = rotation;
    }

    [[nodiscard]] bool IsRotating() const
    {
        return m_RotationTime > 0.0f;
    }

    [[nodiscard]] float GetDestinationAngle() const
    {
        return m_DestinationAngle;
    }

    [[nodiscard]] float GetRotationTime() const
    {
        return m_RotationTime;
    }

    virtual void Render(SDL_Renderer* renderer);
    virtual void Reset();

    void StartRotate(float angle, float time);

    virtual void Update(float deltaTime);


protected:
    float m_x = 0.0f;
    float m_y = 0.0f;
    float m_Width = 0.0f;
    float m_Height = 0.0f;
    float m_Rotation = 0.0f;

    float m_DestinationAngle = 0.0f;
    float m_RotationTime = 0.0f;

};
