#pragma once
#include <iostream>
#include <vector>

#include <Application/Constants/Constants.h>
#include <Application/Resource/Mesh/Sphere/Sphere.h>
#include <Application/Resource/Camera/Camera.h>
#include <Application/Resource/Physics/Meter.h>
#include <Application/Resource/EntityManager/EntityManager.h>

namespace SpaceSim
{
	class Renderer 
	{
	public:
        void Draw(GLuint& shader, float aspectRatio, Camera& camera)
        {
            const auto& spheres = ECS::Get().GetAllComponents<Sphere>();
            const auto& ids = ECS::Get().GetAllComponentIDs<Sphere>();

            for (size_t i = 0; i < spheres.size(); ++i)
            {
                EntityID id = ids[i];
                const auto* pos = ECS::Get().GetComponent<Position>(id);
                if (!pos) continue;

                glm::mat4 model = glm::translate(glm::mat4(1.0f), pos->GetWorld());
                float scaledRadius = spheres[i].m_circleDesc.radius.GetNormal() * METERS_PER_UNIT;
                model = glm::scale(model, glm::vec3(scaledRadius));

                glm::mat4 view = camera.GetViewMatrix();
                glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), aspectRatio, 0.1f, 1000.0f);
                glm::mat4 mvp = projection * view * model;

                GLuint mvpLoc = glGetUniformLocation(shader, "uMVP");
                glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

                GLuint topColorLoc = glGetUniformLocation(shader, "topColor");
                glUniform3fv(topColorLoc, 1, glm::value_ptr(spheres[i].m_circleDesc.topColor));

                GLuint botColorLoc = glGetUniformLocation(shader, "botColor");
                glUniform3fv(botColorLoc, 1, glm::value_ptr(spheres[i].m_circleDesc.botColor));

                glBindVertexArray(spheres[i].m_sphereMesh.circleVAO);
                glDrawElements(GL_TRIANGLE_STRIP, spheres[i].m_sphereMesh.indexCount, GL_UNSIGNED_INT, 0);
            }
        }

	};
}