#pragma once
#include <GLFW/glfw3.h>
#include "Transform.h"

// Base class
class Object {
public:
    virtual void OnCollisionEnter(Object& other) {}
    virtual void Render() const {}
    virtual float GetX() const { return 0; }
    virtual float GetY() const { return 0; }
    virtual float GetWidth() const { return 0; }
    virtual float GetHeight() const { return 0; }
};

// Derived classes
class Player : public Object {
public:
    Player();
    void OnCollisionEnter(Object& other) override {}
    void Render() const override;
    void Update(float deltaTime);
    void Jump(float power);
    void SetJumping(bool jumping) { isJumping = jumping; }
    bool IsJumping() const { return isJumping; }
    float GetX() const override { return position.x; }
    float GetY() const override { return posY; }
    float GetWidth() const override { return size; }
    float GetHeight() const override { return size; }

    float velocityY; // 점프 속도
    float posY; // 위치
    float rotation; // 회전 각도
    bool isJumping; // 점프 상태

private:
    float size; // 50cm 한 변
    float borderThickness; // 3cm 테두리 두께
    float color[3]; // 빨강색 (R:255, G:0, B:0)
    float borderColor[3]; // 테두리 색 (검정색)
    float gravity; // 중력
    float jumpForce; // 점프력
    Transform::Vertex position; // 위치
};

class EnemyBlock : public Object {
public:
    EnemyBlock(float x, float y, float width, float height);
    void OnCollisionEnter(Object& other) override {}
    void Render() const override;
    float GetX() const override { return position.x; }
    float GetY() const override { return position.y; }
    float GetWidth() const override { return width; }
    float GetHeight() const override { return height; }

    Transform::Vertex position;

private:
    float width;
    float height;
    float color[3]; // 녹색 (R:0, G:255, B:0)
};

class Floor : public Object {
public:
    void OnCollisionEnter(Object& other) override {}
};

class Star : public Object {
public:
    void OnCollisionEnter(Object& other) override {}
};

bool PhysicsAABB(Object& A, Object& B);
