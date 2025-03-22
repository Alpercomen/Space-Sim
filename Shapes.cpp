#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shapes.h"
#include "Core.h"

void Shapes::CreateCircle(float centerX, float centerY, float radius, int res)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY); // Center of the circle

    for (int i = 0; i <= res; ++i)
    {
        float angle = 2.0f * M_PI * (static_cast<float>(i) / res);
        float x = centerX + cos(angle) * radius;
        float y = centerY + sin(angle) * radius;
        glVertex2f(x, y); // Changed to glVertex2f()
    }

    glEnd();
}