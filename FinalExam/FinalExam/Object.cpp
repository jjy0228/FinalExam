#include <cstdint> // uintptr_t를 위해 추가
#include <cstdarg> // va_list를 위해 추가
#include "Object.h"
#include "Transform.h"
#include <cmath>

const float gravity = 4.9f; // 중력 가속도 줄임 (4.9 m/s²)

Player::Player()
    : size(50.0f),
    borderThickness(3.0f),
    velocityY(0.0f),
    gravity(4.9f),
    jumpForce(5.0f),
    isJumping(false),
    posY(100.0f + size / 2),
    rotation(0.0f), // 회전 각도 초기화
    position{ 100.0f, 100.0f + size / 2 }
{
    color[0] = 1.0f; // R:255
    color[1] = 0.0f; // G:0
    color[2] = 0.0f; // B:0

    borderColor[0] = 0.0f; // R:0
    borderColor[1] = 0.0f; // G:0
    borderColor[2] = 0.0f; // B:0
}

void Player::Render() const
{
    // 내부 사각형
    glPushMatrix();
    glTranslatef(position.x, posY, 0.0f);
    glRotatef(rotation, 0.0f, 0.0f, 1.0f); // 회전 적용

    glColor3fv(color);
    glBegin(GL_QUADS);
    glVertex2f(-size / 2, -size / 2);
    glVertex2f(size / 2, -size / 2);
    glVertex2f(size / 2, size / 2);
    glVertex2f(-size / 2, size / 2);
    glEnd();

    // 테두리 사각형
    glColor3fv(borderColor);
    glLineWidth(borderThickness);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-size / 2, -size / 2);
    glVertex2f(size / 2, -size / 2);
    glVertex2f(size / 2, size / 2);
    glVertex2f(-size / 2, size / 2);
    glEnd();

    glPopMatrix();
}

void Player::Update(float deltaTime)
{
    // 중력 적용
    velocityY -= gravity * deltaTime;
    posY += velocityY * deltaTime;

    // 땅에 닿으면 멈춤
    float playerSize = 50.0f; // 50cm
    float groundLevel = 100.0f + playerSize / 2;

    if (posY < groundLevel) {
        posY = groundLevel;
        velocityY = 0.0f;
        isJumping = false;
        rotation = 0.0f; // 회전 각도 초기화
    }
    else {
        // 점프 중 회전
        rotation -= 360.0f * deltaTime; // 시계 방향 회전
    }
}

void Player::Jump(float power)
{
    if (!isJumping) { // 땅에 있을 때만 점프 가능
        velocityY = power;
        isJumping = true;
    }
}

EnemyBlock::EnemyBlock(float x, float y, float width, float height)
    : position{ x, y }, width(width), height(height)
{
    color[0] = 0.0f; // R:0
    color[1] = 1.0f; // G:255
    color[2] = 0.0f; // B:0
}

void EnemyBlock::Render() const
{
    glColor3fv(color);
    glBegin(GL_QUADS);
    glVertex2f(position.x, position.y);
    glVertex2f(position.x + width, position.y);
    glVertex2f(position.x + width, position.y + height);
    glVertex2f(position.x, position.y + height);
    glEnd();
}

bool PhysicsAABB(Object& A, Object& B)
{
    float Ax = A.GetX();
    float Ay = A.GetY();
    float Aw = A.GetWidth();
    float Ah = A.GetHeight();

    float Bx = B.GetX();
    float By = B.GetY();
    float Bw = B.GetWidth();
    float Bh = B.GetHeight();

    return (Ax < Bx + Bw && Ax + Aw > Bx &&
        Ay < By + Bh && Ay + Ah > By);
}
