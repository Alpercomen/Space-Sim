#pragma once
#include <iostream>
#include <vector>

#include <Application/Constants/Constants.h>
#include <Application/Resource/Components/Components.h>
#include <Application/Resource/Camera/Camera.h>
#include <Application/Resource/Physics/Meter.h>
#include <Application/Resource/EntityManager/EntityManager.h>
#include <Application/Core/SceneManager/SceneManager.h>
#include <Application/Resource/ShaderProgram/ShaderProgram.h>


namespace Nyx
{
	class Renderer 
	{
	public:
        void DrawScene(Scene& scene)
        {
            const Camera& camera = *ECS::Get().GetComponent<Camera>(scene.GetActiveCameraID());

            for (size_t i = 0; i < scene.GetSceneObjectSize(); ++i)
            {
                const auto& object = scene.GetSceneObject(i);
                object->Draw(camera);
            }
        }

	};
}