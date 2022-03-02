#include "camera.h"
void Camera::SetFov(const float fo)
{
	this->fov = fo;
}
void Camera::SetNear(const float n)
{
	this->near = n;
}
void Camera::SetFar(const float fa)
{
	this->far = fa;
}