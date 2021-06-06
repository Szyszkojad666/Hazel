#include "Hzpch.h"
#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Hazel {

	Camera::Camera(float Left, float Right, float Bottom, float Top)
		: ProjectionMatrix(glm::ortho(Left, Right, Bottom, Top, -1.0f, 1.0f)), ViewMatrix(1.0f)
	{
		ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
	}

	void Camera::SetPosition(const glm::vec3& Position)
	{
		CameraPosition = Position;
		RecalculateViewMatrix();
	}

	void Camera::SetRotation(float Rotation)
	{
		CameraRotation = Rotation;
		RecalculateViewMatrix();
	}

	void Camera::RecalculateViewMatrix()
	{
		glm::mat4 Transform = glm::translate(glm::mat4(1.0f), CameraPosition) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(CameraRotation), glm::vec3(0.f, 0.f, 1.0f));

		ViewMatrix = glm::inverse(Transform);
		ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
	}

}
