#pragma comment(lib, "Opengl32.lib")

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <cmath>
#include "Object.h"

void errorCallback(int error, const char* description)
{
    printf("GLFW Error: %s\n", description);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // 키 입력 처리 (현재 비어 있음)
}

int Physics()
{
    return 0;
}

int Initialize()
{
    return 0;
}

int Update()
{
    return 0;
}

int Render(Player& player, Floor& floor, EnemyBlock obstacles[], int obstacleCount)
{
    // 배경색 설정 (하늘색, RGB: 0, 30, 100)
    glClearColor(0.0f, 30.0f / 255.0f, 100.0f / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // 지면 렌더링
    floor.Render();

    // 장애물 렌더링
    for (int i = 0; i < obstacleCount; ++i) {
        obstacles[i].Render();
    }

    // 플레이어 렌더링
    player.Render();

    return 0;
}

int main(void)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // GLFW 라이브러리 초기화
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(800, 600, "Google Dino Run Copy Game", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

    Initialize();

    Player player;
    Floor floor;

    // 장애물 생성
    const int obstacleCount = 4;
    EnemyBlock obstacles[obstacleCount] = {
        EnemyBlock(0.5f, 1.0f, -0.5f, -0.9f), // 낮은 장애물 1
        EnemyBlock(0.5f, 1.0f, 0.5f, -0.9f),  // 낮은 장애물 2
        EnemyBlock(0.5f, 3.0f, -0.25f, -0.9f), // 높은 장애물 1
        EnemyBlock(0.5f, 3.0f, 0.25f, -0.9f)  // 높은 장애물 2
    };

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        Physics();
        Update();
        Render(player, floor, obstacles, obstacleCount);
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
