#pragma once
#include "MathLib.h"

class Camera
{
public:
	enum class CameraType
	{
		ORTHO,
		PERSPECTIVE
	};
	Camera(const MathLib::Vec3 e, const MathLib::Vec3 up, const MathLib::Vec3 at, const CameraType ty = CameraType::PERSPECTIVE) :
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
	MathLib::Mat4x4 GetLookAt();
	MathLib::Mat4x4 GetProjection();
	MathLib::Vec3 GetCameraPos();
	inline void SetAspect(const float as)
	{
		aspect = as;
	}
	inline float GetNear()
	{
		return near;
	}
	inline float GetFar()
	{
		return far;
	}
	inline float GetAspect()
	{
		return aspect;
	}
	CameraType GetCameraType()
	{
		return type;
	}
private:
	float fov = 45.0;
	float near = 0.1f;
	float far = 100.0f;
	float aspect = 1.0f;
	CameraType type;
	MathLib::Vec3 camera_eye;
	MathLib::Vec3 camera_up;
	MathLib::Vec3 camera_at;
};

