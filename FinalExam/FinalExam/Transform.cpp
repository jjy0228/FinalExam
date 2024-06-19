#include "Transform.h"
#include <cmath>

namespace Transform
{
    const float PI = 3.14159265358979323846f;

    Vertex MoveVertex(Vertex point, Vector meter)
    {
        Vertex result;
        result.x = point.x + meter.x_meter;
        result.y = point.y + meter.y_meter;
        return result;
    }

    Vertex RotateVertex(Vertex point, float angle_degree)
    {
        Vertex result;
        float angle_radian = angle_degree * (PI / 180.0f); // 각도를 라디안으로 변환
        result.x = point.x * cos(angle_radian) + point.y * sin(angle_radian);
        result.y = -point.x * sin(angle_radian) + point.y * cos(angle_radian); // 시계 방향 회전
        return result;
    }

    Vertex ScaleVertex(Vertex point, Vector scale)
    {
        Vertex result;
        result.x = point.x * scale.x_meter;
        result.y = point.y * scale.y_meter;
        return result;
    }
}
