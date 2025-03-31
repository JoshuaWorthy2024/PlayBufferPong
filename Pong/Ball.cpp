// This file's header
#include "Ball.h"

// Other includes
#include "Bat.h"
#include "Config.h"

// Typedef GameEntity as PARENT for readability
typedef GameEntity PARENT;

Ball::Ball(std::string inSpriteName, Play::Vector2D inPosition)
{
    // Set sprite name and position
    m_SpriteName = inSpriteName;
    m_Position = inPosition;

    // Set initial velocity
    m_Velocity = { BALL_INITIAL_X_VELOCITY, BALL_INITIAL_Y_VELOCITY };
}

void Ball::Update(const float& elapsedTime, const Bat& inPlayer1, const Bat& inPlayer2)
{
    m_Position += m_Velocity *  elapsedTime;

    // Bounce off top/bottom
    if (m_Position.y <= BALL_SIZE / 2 || m_Position.y >= DISPLAY_HEIGHT - BALL_SIZE / 2)
    {
        m_Velocity.y *= -1.0f;
    }

    // Check collision with Player 1
    if (CheckCollision(m_Position, BALL_SIZE, BALL_SIZE, inPlayer1.GetPosition(), BAT_WIDTH, BAT_HEIGHT))
    {
        m_Velocity.x = std::abs(m_Velocity.x);
        ApplyBounceYVariation(inPlayer1);
    }

    // Check collision with Player 2
    if (CheckCollision(m_Position, BALL_SIZE, BALL_SIZE, inPlayer2.GetPosition(), BAT_WIDTH, BAT_HEIGHT))
    {
        m_Velocity.x = -std::abs(m_Velocity.x);
        ApplyBounceYVariation(inPlayer2);
    }
}

bool Ball::CheckCollision(const Play::Vector2f& aPos, float aWidth, float aHeight,
                          const Play::Vector2f& bPos, float bWidth, float bHeight)
{
    // Calculate the distance between the centers of the two objects
    float dx = std::abs(aPos.x - bPos.x);
    float dy = std::abs(aPos.y - bPos.y);

    // Calculate the combined half-widths and half-heights
    float combinedHalfWidth = (aWidth + bWidth) / 2.0f;
    float combinedHalfHeight = (aHeight + bHeight) / 2.0f;

    // Check for overlap on both axes
    bool overlapX = dx < combinedHalfWidth;
    bool overlapY = dy < combinedHalfHeight;

    // If we overlap on both axis we have a collision
    bool doesOverlap = overlapX && overlapY;

    // return result flag
    return doesOverlap;
}

void Ball::ApplyBounceYVariation(const Bat& bat)
{
    // Calculate how far the ball is from the center of the bat
    float batCenterY = bat.GetPosition().y;
    float ballCenterY = m_Position.y;
    float verticalOffset = ballCenterY - batCenterY;

    // Normalize the offset to a value between -1 and 1
    // -1 means hit the bottom edge, 0 means center, 1 means top edge
    float normalizedOffset = verticalOffset / (BAT_HEIGHT / 2.0f);

    // Use the normalized offset to determine the new vertical velocity
    // This makes the ball bounce away at different angles depending on where it hit
    float horizontalSpeed = std::abs(m_Velocity.x); // keep the speed magnitude consistent
    m_Velocity.y = normalizedOffset * horizontalSpeed;

    // Increase overall speed slightly after each bounce
    m_Velocity *= 1.05f; // 5% speed increase
}

void Ball::Reset()
{
    // Reset the ball's position to the center of the screen
    m_Position = { DISPLAY_WIDTH / 2.0f, DISPLAY_HEIGHT / 2.0f };

    // Set the starting speed of the ball
    float speed = 300.0f;

    // Randomly choose a horizontal direction: -1 (left) or 1 (right)
    float dirX = (rand() % 2 == 0) ? -1.0f : 1.0f;

    // Generate a random vertical direction between -1.0 and 1.0
    // This adds some variety to the ball's initial angle
    float dirY = ((rand() % 200) - 100) / 100.0f;

    // Create the direction vector
    Play::Vector2f direction = { dirX, dirY };

    // Normalize the direction vector so it has a length of 1
    direction.Normalize();

    // Apply the speed to the direction to get the velocity
    m_Velocity = direction * speed;
}


