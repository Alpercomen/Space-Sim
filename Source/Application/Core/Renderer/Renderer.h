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
        void DrawScene(Scene& scene, float aspectRatio)
        {
            const Camera& camera = *ECS::Get().GetComponent<Camera>(scene.GetActiveCameraID());

            for (size_t i = 0; i < scene.GetSceneObjectSize(); ++i)
            {
                const auto& object = scene.GetSceneObject(i);
                EntityID id = object->GetEntityID();
                const auto& transform = ECS::Get().GetComponent<Transform>(id);
                if (!transform) 
                    continue;

                auto& pos = transform->position;
                auto& rot = transform->rotation;
                auto& sca = transform->scale;

                const auto& sphere = ECS::Get().GetComponent<Sphere>(id);
                if (!sphere) 
                    continue;

                sphere->m_shader.Use(); // Use Shader

                glm::mat4 model = glm::translate(Math::Mat4f(1.0f), pos.GetWorld()) * rot.toMatrix() * sca.toMatrix();
                glm::mat4 view = camera.GetViewMatrix();
                glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), aspectRatio, 0.1f, 10000.0f);

                glm::mat4 mvp = projection * view * model;

                GLuint mvpLoc = glGetUniformLocation(sphere->m_shader.GetID(), "uMVP");
                glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

                GLuint topColorLoc = glGetUniformLocation(sphere->m_shader.GetID(), "topColor");
                glUniform3fv(topColorLoc, 1, glm::value_ptr(sphere->m_sphereDesc.topColor));

                GLuint botColorLoc = glGetUniformLocation(sphere->m_shader.GetID(), "botColor");
                glUniform3fv(botColorLoc, 1, glm::value_ptr(sphere->m_sphereDesc.botColor));

                glBindVertexArray(sphere->m_sphereMesh.vao.m_data);
                glDrawElements(GL_TRIANGLE_STRIP, sphere->m_sphereMesh.ebo.m_indexCount, GL_UNSIGNED_INT, 0);
            }
        }

	};
}