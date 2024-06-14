#pragma once

#include <GLFW/glfw3.h>

class Object {
public:
    virtual void OnCollisionEnter(Object& other) = 0;
    virtual void Render() = 0;
};

class Player : public Object {
public:
    void OnCollisionEnter(Object& other) override {
    }

    void Render() override {
        float size = 50.0f / 100.0f; // 50cm�� ���� ������ ��ȯ
        float borderSize = 3.0f / 100.0f; // 3cm�� ���� ������ ��ȯ

        // �׵θ� (������)
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(-size / 2, -size / 2);
        glVertex2f(size / 2, -size / 2);
        glVertex2f(size / 2, size / 2);
        glVertex2f(-size / 2, size / 2);
        glEnd();

        // ���� ���簢�� (������)
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(-size / 2 + borderSize, -size / 2 + borderSize);
        glVertex2f(size / 2 - borderSize, -size / 2 + borderSize);
        glVertex2f(size / 2 - borderSize, size / 2 - borderSize);
        glVertex2f(-size / 2 + borderSize, size / 2 - borderSize);
        glEnd();
    }
};

class EnemyBlock : public Object {
public:
    float width;
    float height;
    float posX;
    float posY;

    EnemyBlock(float w, float h, float x, float y)
        : width(w), height(h), posX(x), posY(y) {}

    void OnCollisionEnter(Object& other) override {
    }

    void Render() override {
        // ��ֹ� (���)
        glColor3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(posX - width / 2, posY);
        glVertex2f(posX + width / 2, posY);
        glVertex2f(posX + width / 2, posY + height);
        glVertex2f(posX - width / 2, posY + height);
        glEnd();
    }
};

class Floor : public Object {
public:
    void OnCollisionEnter(Object& other) override {
    }

    void Render() override {
        float floorHeight = 0.1f; // �ٴ� ���� (1m)

        glColor3f(1.0f, 0.78f, 0.058f); // Ȳ�� (RGB: 255, 200, 15)
        glBegin(GL_QUADS);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(1.0f, -1.0f + floorHeight);
        glVertex2f(-1.0f, -1.0f + floorHeight);
        glEnd();
    }
};

class Star : public Object {
public:
    void OnCollisionEnter(Object& other) override {
    }

    void Render() override {
    }
};

int PhysicsAABB(Object& A, Object& B)
{
    return 0;
}
