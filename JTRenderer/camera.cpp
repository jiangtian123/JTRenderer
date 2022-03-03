#include "camera.h"
#include "MathLib.h"
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
MathLib::Vec3 Camera::GetCameraPos()
{
	return camera_at;
}
MathLib::Mat4x4 Camera::GetLookAt()
{
	return MathLib::GetLookAtMat(camera_eye,camera_up,camera_at);
}
MathLib::Mat4x4 Camera::GetProjection()
{
	if (type == CameraType::PERSPECTIVE)
	{
		return MathLib::GetPerspectiveMat(fov,aspect,near,far);
	}
	float t = near * tan(MathLib::DegToRad(fov * 0.5f));
	float r = t * aspect;
	float l = -1.0f * r;
	float b = -1.0f * t;
	return MathLib::GetOrthoMat(l,b,near,r,t,far);
}
