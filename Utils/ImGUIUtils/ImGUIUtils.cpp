#include <vector>

#include "ImGUIUtils/ImGUIUtils.h"
#include "Engine/Engine.h"

void ImGUIUtils::Initialize(GLFWwindow* window)
{
    // Initialize ImGUI
    IMGUI_CHECKVERSION();
    printf("ImGui Version: %s\n", IMGUI_VERSION);

    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");  // Use your actual GLSL version
}

ImVec2 ImGUIUtils::DrawGameView(GLuint& sceneTextureID)
{
    ImGui::Begin("Game View");
    ImVec2 textureSize = ImGui::GetContentRegionAvail(); // available ImGui space
    ImGui::Image(
        (ImTextureID)(intptr_t)sceneTextureID,
        textureSize,
        ImVec2(0, 1),        // uv0
        ImVec2(1, 0),        // uv1
        ImVec4(1, 1, 1, 1),  // tint (white)
        ImVec4(0, 0, 0, 0)   // border (none)
    );
    ImGui::End();

    return textureSize;
}

void ImGUIUtils::DrawSimulationInfo(std::vector<Sphere>& objects, Camera& camera)
{
    ImGui::Begin("Simulation Info");
    ImGui::Text("Objects: %d", static_cast<int>(objects.size()));

    for (size_t i = 0; i < objects.size(); ++i)
    {
        auto& sphere = objects[i];
        auto pos = sphere.circleDesc.getPosition();
        auto vel = sphere.circleDesc.getVelocity();
        ImGui::Text("[%s]", sphere.circleDesc.name.c_str());
        ImGui::Text("Pos: (%.2f, %.2f, %.2f)", pos.x, pos.y, pos.z);
        ImGui::Text("Vel: (%.2f, %.2f, %.2f)", vel.x, vel.y, vel.z);
    }

    ImGui::Separator();
    ImGui::Text("Camera Info");
    ImGui::Text("Position: (%.2f, %.2f, %.2f)", camera.Position.x, camera.Position.y, camera.Position.z);
    ImGui::Text("Yaw: %.2f", camera.Yaw);
    ImGui::Text("Pitch: %.2f", camera.Pitch);

    ImGui::End();
}

void ImGUIUtils::DrawSimulationControl(std::vector<Sphere>& objects, Camera& camera)
{
    ImGui::Begin("Simulation Control");
    ImGui::SliderFloat("Time Scale", &TIME_SCALE, 0.0f, 100.0f, "%.8f", ImGuiSliderFlags_Logarithmic);

    ImGui::Separator();

    for (size_t i = 0; i < objects.size(); ++i)
    {
        std::string buttonName = "Focus on " + objects[i].circleDesc.name;

        if (ImGui::Button(buttonName.c_str()))
            camera.FocusOn(objects[i].circleDesc.getPosition(), objects[i].circleDesc.radius.get() * 2);
    }

    ImGui::End();
}

void ImGUIUtils::InitDockableWindowSpace()
{
    // If docking is enabled, set dockspace.
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        // Optional flags:
        // dockspace_flags |= ImGuiDockNodeFlags_NoSplit;
        // dockspace_flags |= ImGuiDockNodeFlags_NoResize;
        // dockspace_flags |= ImGuiDockNodeFlags_NoDockingInCentralNode;
        // dockspace_flags |= ImGuiDockNodeFlags_PassthruCentralNode;
        // dockspace_flags |= ImGuiDockNodeFlags_AutoHideTabBar;

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGuiID dockspace_id = ImGui::GetID("MainDockspace");

        ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGui::DockSpaceOverViewport(dockspace_id, viewport, dockspace_flags);
    }
}