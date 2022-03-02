#include"MathLib.h"
float DegToRad(float deg) { return deg * MY_PI / 180.0f; }
float RadToDeg(float rad) { return rad * 180.0f / MY_PI; }
namespace MathLib
{
	Vec2 operator+(const Vec2 a, const Vec2 b)
	{
		Vec2 res;
		res.x = a.x + b.x;
		res.y = a.y + b.y;
		return res;
	}
	Vec2 operator-(const Vec2 a, const Vec2 b)
	{
		Vec2 res;
		res.x = a.x - b.x;
		res.y = a.y - b.y;
		return res;
	}
	bool operator==(const Vec2 a, const Vec2 b)
	{
		return (a.x == b.x && a.y == b.y);
	}
	bool operator!=(const Vec2 a, const Vec2 b)
	{
		return (a.x != b.x || a.y != b.y);
	}
	bool operator==(const Vec2 a, const float b)
	{
		return (a.x == b && a.y == b);
	}
	bool operator!=(const Vec2 a, const float b)
	{
		return (a.x != b || a.y != b);
	}
	std::ostream& operator<<(std::ostream& os, const Vec2& a)
	{
		os << a.x << " " << a.y << std::endl;
		return os;
	}
	Vec3 operator+(const Vec3 a, const Vec3 b)
	{
		Vec3 res;
		res.x = a.x + b.x;
		res.y = a.y + b.y;
		res.z = a.z + b.z;
		return res;
	}
	Vec3 operator-(const Vec3 a, const Vec3 b)
	{
		Vec3 res;
		res.x = a.x - b.x;
		res.y = a.y - b.y;
		res.z = a.z - b.z;
		return res;
	}
	bool operator==(const Vec3 a, const Vec3 b)
	{
		return (a.x == b.x && a.y == b.y && a.z == b.z);
	}
	bool operator!=(const Vec3 a, const Vec3 b)
	{
		return (a.x != b.x || a.y != b.y || a.z != b.z);
	}
	bool operator==(const Vec3 a, const float b)
	{
		return (a.x == b && a.y == b && a.z == b);
	}
	bool operator!=(const Vec3 a, const float b)
	{
		return  (a.x != b || a.y != b || a.z != b);
	}
	std::ostream& operator<<(std::ostream& os, const Vec3& a)
	{
		os << a.x << " " << a.y << " " << a.z << std::endl;
		return os;
	}
	Vec4 operator+(const Vec4 a, const Vec4 b)
	{
		Vec4 res;
		res.x = a.x + b.x;
		res.y = a.y + b.y;
		res.z = a.z + b.z;
		res.w = a.w + b.w;
		return res;
	}
	Vec4 operator-(const Vec4 a, const Vec4 b)
	{
		Vec4 res;
		res.x = a.x - b.x;
		res.y = a.y - b.y;
		res.z = a.z - b.z;
		res.w = a.w - b.w;
		return res;
	}
	bool operator==(const Vec4 a, const Vec4 b)
	{
		return (a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w);
	}
	bool operator!=(const Vec4 a, const Vec4 b)
	{
		return (a.x != b.x || a.y != b.y || a.z != b.z || a.w != b.w);
	}
	bool operator==(const Vec4 a, const float b)
	{
		return (a.x == b && a.y == b && a.z == b && a.w == b);
	}
	bool operator!=(const Vec4 a, const float b)
	{
		return (a.x != b || a.y != b || a.z != b || a.w != b);
	}
	std::ostream& operator<<(std::ostream& os, const Vec4& a)
	{
		os << a.x << " " << a.y << " " << a.z << " " << a.w << std::endl;
		return os;
	}
	float DotProduct(const Vec3 a, const Vec3 b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}
	Vec3 CrossProduct(const Vec3 a, const Vec3 b)
	{
		Vec3 res;
		res.x = a.y * b.z - a.z * b.y;
		res.y = a.z * b.x - a.x * b.z;
		res.z = a.x * b.y - a.y * b.x;
		return res;
	}
	float Length(const Vec3 a)
	{
		float sq = a.x * a.x + a.y * a.y + a.z * a.z;
		return (float)sqrt(sq);
	}
	void Normalize(Vec3& a)
	{
		float length = Length(a);
		if (length != 0)
		{
			float inv = 1.0f / length;
			a.x *= inv;
			a.y *= inv;
			a.z *= inv;
		}
	}
	Mat4x4 operator+(const Mat4x4& a, const Mat4x4& b)
	{
		Mat4x4 res;
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				res[i][j] = a[i][j] + b[i][j];
			}
		}
		return res;
	}
	Mat4x4 operator-(const Mat4x4& a, const Mat4x4& b)
	{
		Mat4x4 res;
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				res[i][j] = a[i][j] - b[i][j];
			}
		}
		return res;
	}
	Mat4x4 operator*(const Mat4x4& a, const Mat4x4& b)
	{
		Mat4x4 res;
		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				res[i][j] = (a[i][0] * b[0][j] + a[i][1] * b[1][j] + a[i][2] * b[2][j] + a[i][3] * b[3][j]);
			}
		}
		return res;
	}
	Vec4 operator*(const Mat4x4& a, const Vec4 b)
	{
		Vec4 res;
		res.x = a[0][0] * b.x + a[0][1] * b.y + a[0][2] * b.z + a[0][3] * b.w;
		res.y = a[1][0] * b.x + a[1][1] * b.y + a[1][2] * b.z + a[1][3] * b.w;
		res.z = a[2][0] * b.x + a[2][1] * b.y + a[2][2] * b.z + a[2][3] * b.w;
		res.w = a[3][0] * b.x + a[3][1] * b.y + a[3][2] * b.z + a[3][3] * b.w;
		return res;
	}
	/**
	 * @brief 构建一个平移矩阵
	 * @param translate 三维向量的每个分量都代表在该分量上平移的距离
	 * @return 平移矩阵
	*/
	Mat4x4 GetTranslateMat(const Vec3 translate)
	{
		Mat4x4 res;
		res[0][3] = translate.x;
		res[1][3] = translate.y;
		res[2][3] = translate.z;
		return res;
	}
	/**
	 * @brief 构建一个缩放矩阵
	 * @param sacle 三维向量的每个分量都代表在该分量上缩放的大小
	 * @return 缩放矩阵
	*/
	Mat4x4 GetScaleMat(const Vec3 sacle)
	{
		Mat4x4 res;
		res[0][0] = sacle.x;
		res[1][1] = sacle.y;
		res[2][2] = sacle.z;
		return res;
	}
	/**
	 * @brief 构建一个旋转矩阵
	 * @param sacle 三维向量的每个分量都代表在该分量上旋转的角度
	 * @return 缩放矩阵
	*/
	Mat4x4 GetRotateMat(const Vec3 rotate)
	{
		float angle_x = rotate.x;
		float angle_y = rotate.y;
		float angle_z = rotate.z;
		Mat4x4 Rx;
		Rx[1][1] = Rx[2][2] = (float)cos(DegToRad(angle_x));
		Rx[2][1] = (float)sin(DegToRad(angle_x));
		Rx[1][2] = -1.0f * (float)sin(DegToRad(angle_x));
		Mat4x4 Ry;
		Ry[0][0] = Ry[2][2] = (float)cos(DegToRad(angle_y));
		Ry[0][2] = (float)sin(DegToRad(angle_y));
		Ry[2][0] = -1.0f * (float)sin(DegToRad(angle_y));
		Mat4x4 Rz;
		Rz[0][0] = Rz[1][1] = (float)cos(DegToRad(angle_z));
		Rz[0][1] = -1.0f * (float)sin(DegToRad(angle_z));
		Rz[1][0] = (float)sin(DegToRad(angle_z));
		return Rz * Ry * Rx;
	}
	/**
	 * @brief 围绕一个向量进行旋转
	 * @param rotate 围绕的向量
	 * @param angle 旋转角度
	 * @return 旋转矩阵
	*/
	Mat4x4 GetRotateMatWithVector(Vec3 rotate, const float angle)
	{
		Mat4x4 res;
		Normalize(rotate);
		float nx = rotate.x;
		float ny = rotate.y;
		float nz = rotate.z;
		float costheta = (float)cos(DegToRad(angle));
		float minus_costheta = (float)(1.0 - costheta);
		float sintheta = (float)sin(DegToRad(angle));
		res[0][0] = nx * nx * minus_costheta + costheta;
		res[0][1] = nx * ny * minus_costheta - nz * sintheta;
		res[0][2] = nx * nz * minus_costheta + ny * sintheta;

		res[1][0] = nx * ny * minus_costheta + nz * sintheta;
		res[1][1] = ny * ny * minus_costheta + costheta;
		res[1][2] = ny * nz * minus_costheta - nx * sintheta;

		res[2][0] = nx * nz * minus_costheta - ny * sintheta;
		res[2][1] = ny * nz * minus_costheta + nx * sintheta;
		res[2][2] = nz * nz * minus_costheta + costheta;
		return res;
	}
	/**
	 * @brief 构建lookat矩阵
	 * @param eye 看向的点
	 * @param up 相机的向上的向量
	 * @param at 相机所在的位置
	 * @return view 矩阵
	*/
	Mat4x4 GetLookAtMat(const Vec3 eye, const Vec3 up, const Vec3 at)
	{
		Vec3 Z_Aixs = eye - at;
		Normalize(Z_Aixs);
		Vec3 X_Aixs = CrossProduct(Z_Aixs, up);
		Normalize(X_Aixs);
		Vec3 Y_Aixs = CrossProduct(X_Aixs, Z_Aixs);
		Mat4x4 view_mat;
		view_mat[0][0] = X_Aixs.x;
		view_mat[1][0] = X_Aixs.y;
		view_mat[2][0] = X_Aixs.z;
		view_mat[0][1] = Y_Aixs.x;
		view_mat[1][1] = Y_Aixs.y;
		view_mat[2][1] = Y_Aixs.z;
		view_mat[0][2] = Z_Aixs.x;
		view_mat[1][2] = Z_Aixs.y;
		view_mat[2][2] = Z_Aixs.z;
		Mat4x4 tran;
		tran[0][3] = -1.0f * at.x;
		tran[1][3] = -1.0f * at.y;
		tran[2][3] = -1.0f * at.z;
		return view_mat * tran;
	}
	/**
	 * @brief 构建一个正交投影矩阵
	 * @param l min x
	 * @param b min y
	 * @param n near
	 * @param r max x
	 * @param t max y
	 * @param f far
	 * @return 正交投影矩阵
	*/
	Mat4x4 GetOrthoMat(const float l, const float b, const float n, const float r, const float t, const float f)
	{
		Mat4x4 res;
		res[0][0] = 2.0f / (r - l);
		res[1][1] = 2.0f / (t - b);
		res[2][2] = 2.0f / (f - n);
		Mat4x4 tra;
		tra[0][3] = -1.0f * ((l + r) / 2);
		tra[1][3] = -1.0f * ((b + t) / 2);
		tra[2][3] = -1.0f * ((n + f) / 2);
		return res * tra;
	}
	/**
	 * @brief 生成一个透视投影矩阵
	 * @param fov 视角的大小
	 * @param aspect 宽高比例
	 * @param near 近平面
	 * @param far 原平面
	 * @return 透视投影矩阵
	*/
	Mat4x4 GetPerspectiveMat(const float fov, const float aspect, const float near, const float far)
	{
		Mat4x4 per2ortho;
		per2ortho[0][0] = near;
		per2ortho[1][1] = near;
		per2ortho[2][2] = near + far;
		per2ortho[2][3] = -1.0f * near * far;
		per2ortho[3][2] = 1.0f;
		per2ortho[3][3] = 0.0f;
		float t = near * tan(DegToRad(fov * 0.5f));
		float r = t * aspect;
		float l = -1.0f * r;
		float b = -1.0f * t;
		Mat4x4 ortho = GetOrthoMat(l, b, near, r, t, far);
		return ortho * per2ortho;
	}
	Mat4x4 Transpose(const Mat4x4 a)
	{
		Mat4x4 res;
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				res[i][j] = a[j][i];
			}
		}
		return res;
	}
	Mat4x4 Inverse(const Mat4x4 a)
	{
		return Mat4x4();
	}
	float learp(const float x1, const float x2, const float t)
	{
		return x1 + (x2 - x1) * t;
	}
	Vec2 learp(const Vec2 x1, const Vec2 x2, const Vec2 t)
	{
		Vec2 res;
		res.x = learp(x1.x, x2.x, t.x);
		res.y = learp(x1.y, x2.y, t.y);
		return res;
	}
	Vec3 learp(const Vec3 x1, const Vec3 x2, const Vec3 t)
	{
		Vec3 res;
		res.x = learp(x1.x, x2.x, t.x);
		res.y = learp(x1.y, x2.y, t.y);
		res.z = learp(x1.z, x2.z, t.z);
		return res;
	}
	Vec4 learp(const Vec4 x1, const Vec4 x2, const Vec4 t)
	{
		Vec4 res;
		res.x = learp(x1.x, x2.x, t.x);
		res.y = learp(x1.y, x2.y, t.y);
		res.z = learp(x1.z, x2.z, t.z);
		res.w = learp(x1.w, x2.w, t.w);
		return res;
	}
}