#pragma once
#include "MathLib.h"

class Camera
{
public:
	enum class CameraTypr
	{
		ORTHO,
		PERSPECTIVE
	};
	Camera(const MathLib::Vec3 e, const MathLib::Vec3 up, const MathLib::Vec3 at, const CameraTypr ty = CameraTypr::PERSPECTIVE) :
		camera_eye(e), camera_up(up), camera_at(at),type(ty)
	{
		fov = 45.0f;
		near = 0.1f;
		far = 100.0f;
	};
	~Camera()=default;
	void SetFov(const float fo);
	void SetNear(const float n);
	void SetFar(const float fa);
	CameraTypr GetCameraType()
	{
		return type;
	}
private:
	float fov;
	float near;
	float far;
	CameraTypr type;
	MathLib::Vec3 camera_eye;
	MathLib::Vec3 camera_up;
	MathLib::Vec3 camera_at;
};

