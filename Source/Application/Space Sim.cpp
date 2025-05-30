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

using namespace SpaceSim;

int main()
{
    BasicWindow window;
    Engine engine(window.GetHandle());

    SphereDesc earthDesc;
    earthDesc.res = 50;
    earthDesc.radius.SetWorld(12.5);
    earthDesc.topColor = glm::vec3(0.28, 0.56, 0.93);
    earthDesc.botColor = glm::vec3(0.11, 0.23, 0.37);

    SphereDesc moonDesc;
    moonDesc.res = 50;
    moonDesc.radius.SetWorld(3.0);
    moonDesc.topColor = glm::vec3(0.89, 0.96, 0.96);
    moonDesc.botColor = glm::vec3(0.30, 0.41, 0.41);

    EntityID earthID = ECS::Get().CreateEntity();
    ECS::Get().AddComponent(earthID, Position{});
    ECS::Get().AddComponent(earthID, Velocity{});
    ECS::Get().AddComponent(earthID, Acceleration{});
    ECS::Get().AddComponent(earthID, Sphere{ earthDesc });
    ECS::Get().AddComponent(earthID, Rigidbody{ 5.972e24 }); // Earth mass
    ECS::Get().AddComponent(earthID, Name{ "Earth" });

    EntityID moonID = ECS::Get().CreateEntity();
    ECS::Get().AddComponent(moonID, Position{ glm::vec3(384.400, 0.0, 0.0) });

    float mass = ECS::Get().GetComponent<Rigidbody>(earthID)->mass;
    float distance = glm::distance(ECS::Get().GetComponent<Position>(earthID)->GetWorld(), ECS::Get().GetComponent<Position>(moonID)->GetWorld());
    float velocity = CalculateOrbitalVelocity(mass, distance);

    ECS::Get().AddComponent(moonID, Velocity{ glm::vec3(0.0f, 0.0f, velocity)});
    ECS::Get().AddComponent(moonID, Acceleration{});
    ECS::Get().AddComponent(moonID, Sphere{ moonDesc });
    ECS::Get().AddComponent(moonID, Rigidbody{ 7.342e22 }); // Moon mass
    ECS::Get().AddComponent(moonID, Name{ "Moon" });

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