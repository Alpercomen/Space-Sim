#include <vector>
#include <iostream>

#include <spdlog/spdlog.h>
#include <Application/Utils/ImGUIUtils/ImGUIUtils.h>

void ImGUIUtils::Initialize(void* window)
{
    // Initialize ImGUI
    IMGUI_CHECKVERSION();
    spdlog::info("ImGui Version: {:30}", IMGUI_VERSION);

    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(window), true);
    ImGui_ImplOpenGL3_Init("#version 330");  // Use your actual GLSL version
}

void ImGUIUtils::InitDockableWindow()
{
    // If docking is enabled, set dockspace.
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGuiID dockspace_id = ImGui::GetID("MainDockspace");

        ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // Optional flags:
        // dockspace_flags |= ImGuiDockNodeFlags_NoSplit;
        // dockspace_flags |= ImGuiDockNodeFlags_NoResize;
        // dockspace_flags |= ImGuiDockNodeFlags_NoDockingInCentralNode;
        // dockspace_flags |= ImGuiDockNodeFlags_PassthruCentralNode;
        // dockspace_flags |= ImGuiDockNodeFlags_AutoHideTabBar;

        ImGui::DockSpaceOverViewport(dockspace_id, viewport, dockspace_flags);
    }
}

ImVec2 ImGUIUtils::DrawGameWindow(GLuint sceneTextureID)
{
    ImGui::Begin("Game View");
    ImVec2 textureSize = ImGui::GetContentRegionAvail(); // available ImGui space
    ImGui::Image(
        (ImTextureID)(intptr_t)sceneTextureID,
        textureSize,
        ImVec2(0, 1),  // uv0
        ImVec2(1, 0),  // uv1
        ImVec4(1, 1, 1, 1),  // tint (white)
        ImVec4(0, 0, 0, 0)   // border (none)
    );
    ImGui::End();

    return textureSize;
}

void ImGUIUtils::DrawSimulationInfo(Camera & camera, std::vector<std::shared_ptr<Sphere>>& objects)
{
    ImGui::Begin("Simulation Info");

    ImGui::Text("Objects: %d", static_cast<int>(objects.size()));

    for (size_t i = 0; i < objects.size(); ++i)
    {
        auto& sphere = objects[i];
        auto pos = sphere->circleDesc.pos.getPosition();
        auto vel = sphere->circleDesc.vel.getVelocity();
        ImGui::Text("[%s]", sphere->circleDesc.name.c_str());
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

void ImGUIUtils::DrawSimulationControl(Camera& camera, std::vector<std::shared_ptr<Sphere>>& objects)
{
    ImGui::Begin("Simulation Control");
    ImGui::SliderFloat("Time Scale", &TIME_SCALE, 0.0f, 10000.0f, "%.8f", ImGuiSliderFlags_Logarithmic);
    ImGui::End();
}

void ImGUIUtils::DrawWindow(Engine* engine, GLuint sceneTextureID, Camera& camera, std::vector<std::shared_ptr<Sphere>>& objects)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGUIUtils::InitDockableWindow();
    ImVec2 textureSize = ImGUIUtils::DrawGameWindow(sceneTextureID);
    ImGUIUtils::DrawSimulationInfo(camera, objects);
    ImGUIUtils::DrawSimulationControl(camera, objects);

    engine->ResizeFBO((int)textureSize.x, (int)textureSize.y);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup);
    }
}