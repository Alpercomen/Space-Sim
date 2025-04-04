#include <vector>

#include "ImGUIUtils.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

void ImGUIUtils::Initialize(GLFWwindow* window)
{
    // Initialize ImGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");  // Use your actual GLSL version
}

void ImGUIUtils::DrawWindow(std::vector<Circle>& objects)
{
    // Start new ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Simulation Control");

    for (auto& obj : objects)
    {
        ImGui::Text(obj.circleDesc.name.c_str()); 

        float currentVelocityX = static_cast<float>(obj.circleDesc.acc.getX());
        float currentVelocityY = static_cast<float>(obj.circleDesc.acc.getY());

        std::string labelX = obj.circleDesc.name + " Velocity X";
        std::string labelY = obj.circleDesc.name + " Velocity Y";

        if (ImGui::SliderFloat(labelX.c_str(), &currentVelocityX, -20000.0f, 20000.0f)) {
            obj.circleDesc.vel.setX(static_cast<double>(currentVelocityX));
        }
        if (ImGui::SliderFloat(labelY.c_str(), &currentVelocityY, -20000.0f, 20000.0f)) {
            obj.circleDesc.vel.setY(static_cast<double>(currentVelocityY));
        }
    }

    ImGui::End();

    // Render ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}