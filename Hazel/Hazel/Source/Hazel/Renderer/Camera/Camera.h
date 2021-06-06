#pragma once

#include "glm/glm.hpp"

namespace Hazel {

class Camera
{
public:

	Camera(float Left, float Right, float Bottom, float Top);

	const glm::vec3& GetPosition() const;
	float GetRotation() const;
	
	void SetPosition(const glm::vec3& Position);
	void SetRotation(float Rotation);

	const glm::mat4& GetProjectionMatrix() const;
	const glm::mat4& GetViewMatrix() const;
	const glm::mat4& GetViewProjectionMatrix() const;

protected:

	virtual void RecalculateViewMatrix();

private:

	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ViewProjectionMatrix;

	glm::vec3 CameraPosition {0.f};
	float CameraRotation = 0.f;
};
///////////////////////////////////////
// Inlines

FORCEINLINE float Camera::GetRotation() const 
{ 
	return CameraRotation; 
}

FORCEINLINE const glm::vec3& Camera::GetPosition() const
{
	return CameraPosition;
}

FORCEINLINE const glm::mat4& Camera::GetProjectionMatrix() const
{
	return ProjectionMatrix;
}

FORCEINLINE const glm::mat4& Camera::GetViewMatrix() const
{
	return ViewMatrix;
}

FORCEINLINE const glm::mat4& Camera::GetViewProjectionMatrix() const
{
	return ViewProjectionMatrix;
}

}
