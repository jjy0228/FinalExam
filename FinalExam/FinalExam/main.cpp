#pragma comment(lib, "opengl32.lib")
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <chrono>
#include <cmath>
#include <vector>
#include "Object.h"
#include "Transform.h"

const float GRAVITY = 50.0f; // 중력 가속도 줄임 (4.9 m/s²)
const float MIN_JUMP_VELOCITY = 50.0f; // 최소 점프 속도 (5.0 m/s)
const float MAX_JUMP_VELOCITY = 150.0f; // 최대 점프 속도 (10.0 m/s)
const float MAX_HOLD_TIME = 1.0f; // 최대 점프 시간 (초)
const float OBSTACLE_SPEED = 1.0f; // 장애물 이동 속도 절반으로 줄임
const float OBSTACLE_MIN_SPACING = 850.0f; // 장애물 간격 3배 넓힘 (기존: 850.0f)

Player player;
bool isSpacePressed = false;
float spacePressedTime = 0.0f;

void errorCallback(int error, const char* description)
{
    printf("GLFW Error: %s\n", description);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        if (!isSpacePressed) {
            isSpacePressed = true;
            spacePressedTime = 0.0f;
        }
        else {
            spacePressedTime += 0.016f; // 프레임 시간에 따라 증가
        }
    }
    else {
        if (isSpacePressed) {
            isSpacePressed = false;
            if (!player.IsJumping()) {
                float jumpPower = std::min(spacePressedTime / MAX_HOLD_TIME, 1.0f);
                float jumpVelocity = MIN_JUMP_VELOCITY + jumpPower * (MAX_JUMP_VELOCITY - MIN_JUMP_VELOCITY);
                player.Jump(jumpVelocity);
            }
        }
    }
}

int Physics(Player& player, float deltaTime)
{
    // 중력 적용
    player.velocityY -= GRAVITY * deltaTime;
    player.posY += player.velocityY * deltaTime;

    // 바닥에 닿으면 속도만 0으로 설정하고 위치는 업데이트
    float playerSize = 50.0f; // 50cm
    float groundLevel = 100.0f + playerSize / 2;

    if (player.posY < groundLevel) {
        player.posY = groundLevel;
        player.velocityY = 0.0f;
        player.SetJumping(false); // 점프 상태 초기화
        player.rotation = 0.0f; // 회전 각도 초기화
    }
    else {
        // 점프 중 회전
        player.rotation -= 60.0f * deltaTime; // 시계 방향 회전
    }

    return 0;
}

int Initialize()
{
    return 0;
}

std::vector<EnemyBlock> obstacles = {
    EnemyBlock(900.0f, 100.0f, 50.0f, 100.0f), // 장애물 1
    EnemyBlock(1400.0f, 100.0f, 50.0f, 300.0f), // 장애물 2
    EnemyBlock(1900.0f, 100.0f, 50.0f, 100.0f) // 장애물 3
};

void RenderFloor()
{
    float height = 100.0f; // 100cm 높이

    // 지면 색 설정 (황색: R:255, G:200, B:15)
    float color[3] = { 1.0f, 200.0f / 255.0f, 15.0f / 255.0f };

    glColor3fv(color);
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(800.0f, 0.0f);
    glVertex2f(800.0f, height);
    glVertex2f(0.0f, height);
    glEnd();
}

void RenderObstacles()
{
    for (auto& obstacle : obstacles) {
        // 장애물 이동
        obstacle.position.x -= OBSTACLE_SPEED;

        // 장애물 재활용
        if (obstacle.position.x < -obstacle.GetWidth()) {
            obstacle.position.x = OBSTACLE_MIN_SPACING + rand() % 900; // 간격을 3배 넓힘
        }

        // 장애물 그리기
        obstacle.Render();
    }
}

int Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // 지면 렌더링
    RenderFloor();

    // 플레이어 렌더링
    player.Render();

    // 장애물 렌더링
    RenderObstacles();

    return 0;
}

void Update(GLFWwindow* window)
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    static auto lastTime = currentTime;
    std::chrono::duration<float> deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    // 입력 처리
    processInput(window);

    // 플레이어 업데이트
    player.Update(deltaTime.count());
    Physics(player, deltaTime.count());

    // 충돌 감지
    for (auto& obstacle : obstacles) {
        if (PhysicsAABB(player, obstacle)) {
            // 플레이어가 장애물에 충돌하면 게임 종료
            printf("충돌되었습니다 게임을 종료합니다.\n");
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }
}

int main(void)
{
    GLFWwindow* window;

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // GLFW 초기화
    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(800, 600, "Google Dino Run Copy Game", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);

    // 배경색 설정
    glClearColor(0.0f, 30.0f / 255.0f, 100.0f / 255.0f, 1.0f); // R:0, G:30, B:100

    // OpenGL 좌표계 설정
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    Initialize();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        Update(window);
        Render();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
