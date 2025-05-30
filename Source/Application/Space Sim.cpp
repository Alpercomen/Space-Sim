#pragma once
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include <Application/Window/Window.h>
#include <Application/Resource/Mesh/Sphere/Sphere.h>
#include <Application/Resource/Utils/ShaderUtils/ShaderUtils.h>
#include <Application/Resource/Utils/SpaceUtils/SpaceUtils.h>
#include <Application/Constants/Constants.h>
#include <Application/Core/Engine/Engine.h>
#include <Application/Core/Input/InputDispatcher.h>
#include <Application/Resource/EntityManager/EntityManager.h>
#include <Application/Resource/Components/Components.h>

#include <glm/gtc/random.hpp>

using namespace SpaceSim;

struct SatelliteDesc {
    std::string name;
    double distanceKm;
    double massKg;
    glm::vec3 color;
};

int main()
{
    BasicWindow window;
    Engine engine(window.GetHandle());

    SphereDesc earthDesc;
    earthDesc.res = 50;
    earthDesc.radius.SetWorld(25.0);
    earthDesc.topColor = glm::vec3(0.28, 0.56, 0.93);
    earthDesc.botColor = glm::vec3(0.11, 0.23, 0.37);

    SphereDesc moonDesc;
    moonDesc.res = 50;
    moonDesc.radius.SetWorld(6.0);
    moonDesc.topColor = glm::vec3(0.89, 0.96, 0.96);
    moonDesc.botColor = glm::vec3(0.30, 0.41, 0.41);

    std::vector<SatelliteDesc> satellites = {
        { "Moon",     384.4000,    7.342e22,  glm::vec3(0.6f, 0.6f, 0.7f) },
        { "Ganymede", 1070.400,    1.4819e23, glm::vec3(0.7f, 0.6f, 0.5f) },
        { "Io",       4217.000,    8.9319e22, glm::vec3(0.9f, 0.7f, 0.4f) },
        { "Europa",   6710.340,    4.8e22,    glm::vec3(0.7f, 0.8f, 0.9f) },
    };

    EntityID earthID = ECS::Get().CreateEntity();
    ECS::Get().AddComponent(earthID, Position{});
    ECS::Get().AddComponent(earthID, Acceleration{});
    ECS::Get().AddComponent(earthID, Sphere{ earthDesc });
    ECS::Get().AddComponent(earthID, Rigidbody{ 5.972e24 }); // Earth mass
    ECS::Get().AddComponent(earthID, Name{ "Earth" });

    for (const auto& sat : satellites) {
        EntityID moonID = ECS::Get().CreateEntity();

        // Random angle around Y axis
        float theta = glm::linearRand(0.0f, glm::two_pi<float>());
        glm::vec3 offset = glm::vec3(std::cos(theta), 0.0f, std::sin(theta)) * static_cast<float>(sat.distanceKm);

        ECS::Get().AddComponent(moonID, Position{ offset });
        ECS::Get().AddComponent(moonID, Acceleration{});
        ECS::Get().AddComponent(moonID, Sphere{ moonDesc });
        ECS::Get().AddComponent(moonID, Rigidbody{ sat.massKg });
        ECS::Get().AddComponent(moonID, Name{ sat.name });

        // Assign unique visual color
        ECS::Get().GetComponent<Sphere>(moonID)->m_circleDesc.topColor = sat.color;
        ECS::Get().GetComponent<Sphere>(moonID)->m_circleDesc.botColor = sat.color;

        InitializeCircularOrbit(moonID, earthID);
    }

    EntityID cameraID = ECS::Get().CreateEntity();
    ECS::Get().AddComponent(cameraID, Camera{});
    ECS::Get().AddComponent(cameraID, Position{ glm::vec3(0.0f, 0.0f, 25.0f) });
    ECS::Get().AddComponent(cameraID, Name{ "Camera" });

    auto camera = ECS::Get().GetComponent<Camera>(cameraID);

    window.Show();
    while(window.IsActive())
    {
        window.PollEvents();
        engine.Render(window.GetHandle(), *camera);
        window.SwapBuffers();
    }
    window.Hide();

    return 0;
}