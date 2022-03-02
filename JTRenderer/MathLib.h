/**
 * @brief ��ѧ��������ο�
 * ����ͳһ�����о���
 * ����˷�Ϊ���
 * ����ģ���̣�û����ģ�壬��ͷ�ع�
*/
#pragma once
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <assert.h>
#include "global.h"
namespace MathLib {
	struct Vec2;
	struct Vec3;
	struct Vec4;
	typedef Vec2 UV;
	typedef Vec4 Point;
	struct Color
	{
		Color() :r(0), g(0), b(0), a(1.0f) {}
		explicit Color(const unsigned short n) :r(n), g(n), b(n), a(1.0f) {}
		explicit Color(const unsigned short x, const unsigned short y, const unsigned short z, const float w=1.0f) :r(x), g(y), b(z), a(w) {}
		~Color() = default;
		Color(const Color& a)
		{
			this->r = a.r;
			this->g = a.g;
			this->b = a.b;
			this->a = a.a;
		}
		Color& operator=(const Color& a)
		{
			this->r = a.r;
			this->g = a.g;
			this->b = a.b;
			this->a = a.a;
			return *this;
		}
		unsigned short r;
		unsigned short g;
		unsigned short b;
		float a;
	};
	/**
	 * @brief �������ռ����Ĭ�ϵ�w����Ϊ1.0f
	*/
	struct Vec4
	{
		Vec4() :x(0), y(0), z(0), w(0.0f) {}
		explicit Vec4(const float a) :x(a), y(a), z(a), w(a) {}
		explicit Vec4(const float a, const float b, const float c, const float d=1.0f) :x(a), y(b), z(c), w(d) {}
		~Vec4() = default;
		Vec4(const Vec4& a)
		{
			this->x = a.x;
			this->y = a.y;
			this->z = a.z;
			this->w = a.w;
		}
		Vec4& operator=(const Vec4& a)
		{
			this->x = a.x;
			this->y = a.y;
			this->z = a.z;
			this->w = a.w;
			return *this;
		}
		Vec4 operator*(const float a)
		{
			Vec4 res;
			res.x = a * this->x;
			res.y = a * this->y;
			res.z = a * this->z;
			res.w = a * this->w;
			return res;
		}
		float x;
		float y;
		float z;
		float w;
	};
	struct Vec3
	{
		Vec3() :x(0), y(0), z(0) {}
		explicit Vec3(const float a) :x(a), y(a), z(a) {}
		explicit Vec3(const float a, const float b, const float c) :x(a), y(b), z(c) {}
		~Vec3() = default;
		Vec3(const Vec3& a)
		{
			this->x = a.x;
			this->y = a.y;
			this->z = a.z;
		}
		Vec3(const Vec4& a)
		{
			this->x = a.x;
			this->y = a.y;
			this->z = a.z;
		}
		Vec3 operator=(const Vec4& a)
		{
			Vec3 res;
			res.x = a.x;
			res.y = a.y;
			res.z = a.z;
			return res;
		}
		Vec3& operator=(const Vec3& a)
		{
			x = a.x;
			y = a.y;
			z = a.z;
			return *this;
		}
		Vec3 operator*(const float a)
		{
			Vec3 res;
			res.x = a * this->x;
			res.y = a * this->y;
			res.z = a * this->z;
			return res;
		}
		float x;
		float y;
		float z;
	};
	struct Vec2
	{
		Vec2() :x(0), y(0) {}
		explicit Vec2(const float a) :x(a), y(a) {}
		explicit Vec2(const float a, const float b):x(a),y(b){}
		~Vec2() = default;
		Vec2(const Vec2& a)
		{
			this->x = a.x;
			this->y = a.y;
		}
		Vec2(const Vec3& a)
		{
			this->x = a.x;
			this->y = a.y;
		}
		Vec2(const Vec4& a)
		{
			this->x = a.x;
			this->y = a.y;
		}
		Vec2& operator=(const Vec2& a)
		{
			x = a.x;
			y = a.y;
			return *this;
		}
		Vec2& operator=(const Vec3& a)
		{
			x = a.x;
			y = a.y;
			return *this;
		}
		Vec2& operator=(const Vec4& a)
		{
			x = a.x;
			y = a.y;
			return *this;
		}
		Vec2 operator*(const float a)
		{
			Vec2 res;
			res.x = a * this->x;
			res.y = a * this->y;
			return res;
		}
		float x;
		float y;
	};
	/**
	 * @brief 4x4����Ĭ�Ϲ��캯����һ����λ����
	*/
	struct Mat4x4
	{
		Mat4x4()
		{
			for (unsigned int i = 0; i < 4; i++)
			{
				for (unsigned int j = 0; j < 4; j++)
				{
					if (i==j)
					{
						this->mat[i][j] = 1.0f;
					}
					else
					{
						this->mat[i][j] = 0.0f;
					}			
				}
			}
		}
		Mat4x4(const Mat4x4& a)
		{
			for (unsigned int i = 0; i < 4; i++)
			{
				for (unsigned int j = 0; j < 4; j++)
				{
					this->mat[i][j] = a.mat[i][j];
				}
			}
		}
		Mat4x4& operator=(const Mat4x4& a)
		{
			for (unsigned int i = 0; i < 4; i++)
			{
				for (unsigned int j = 0; j < 4; j++)
				{
					this->mat[i][j] = a.mat[i][j];
				}
			}
			return *this;
		}
		float * const operator[](const unsigned int a)
		{
			if (a>3)
			{
				assert(0);
			}
			return this->mat[a];
		}
		//����һ��constָ������������ֹ���� const mat[][]�����
		const float * const operator[](const unsigned int a) const
		{
			if (a > 3)
			{
				assert(0);
			}
			return this->mat[a];
		}
		Mat4x4 operator*(const float a)
		{
			Mat4x4 res;
			for (unsigned int i = 0; i < 4; i++)
			{
				for (unsigned int j = 0; j < 4; j++)
				{
					res[i][j] = this->mat[i][j] * a;
				}
			}
			return res;
		}
		void SetZero()
		{
			for (unsigned int i = 0; i < 4; i++)
			{
				for (unsigned int j = 0; j < 4; j++)
				{
					this->mat[i][j] = 0;
				}
			}
		}
		float mat[4][4];
	};
	Vec2 operator+(const Vec2 a, const Vec2 b);
	Vec2 operator-(const Vec2 a, const Vec2 b);
	bool operator==(const Vec2 a, const Vec2 b);
	bool operator!=(const Vec2 a, const Vec2 b);
	bool operator==(const Vec2 a, const float b);
	bool operator!=(const Vec2 a, const float b);
	std::ostream& operator<<(std::ostream& os, const Vec2& a);
	Vec3 operator+(const Vec3 a, const Vec3 b);
	Vec3 operator-(const Vec3 a, const Vec3 b);
	bool operator==(const Vec3 a, const Vec3 b);
	bool operator!=(const Vec3 a, const Vec3 b);
	bool operator==(const Vec3 a, const float b);
	bool operator!=(const Vec3 a, const float b);
	std::ostream& operator<<(std::ostream& os, const Vec3& a);
	Vec4 operator+(const Vec4 a, const Vec4 b);
	Vec4 operator-(const Vec4 a, const Vec4 b);
	bool operator==(const Vec4 a, const Vec4 b);
	bool operator!=(const Vec4 a, const Vec4 b);
	bool operator==(const Vec4 a, const float b);
	bool operator!=(const Vec4 a, const float b);
	std::ostream& operator<<(std::ostream& os, const Vec4& a);
	float DotProduct(const Vec3 a, const Vec3 b);
	Vec3 CrossProduct(const Vec3 a, const Vec3 b);
	float Length(const Vec3 a);
	void Normalize(Vec3& a);
	Mat4x4 operator+(const Mat4x4& a, const Mat4x4& b);
	Mat4x4 operator-(const Mat4x4& a, const Mat4x4& b);
	Mat4x4 operator*(const Mat4x4& a, const Mat4x4& b);
	Vec4 operator*(const Mat4x4& a, const Vec4 b);
	/**
	 * @brief ����һ��ƽ�ƾ���
	 * @param translate ��ά������ÿ�������������ڸ÷�����ƽ�Ƶľ���
	 * @return ƽ�ƾ���
	*/
	Mat4x4 GetTranslateMat(const Vec3 translate);
	/**
	 * @brief ����һ�����ž���
	 * @param sacle ��ά������ÿ�������������ڸ÷��������ŵĴ�С
	 * @return ���ž���
	*/
	Mat4x4 GetScaleMat(const Vec3 sacle);
	/**
	 * @brief ����һ����ת����
	 * @param sacle ��ά������ÿ�������������ڸ÷�������ת�ĽǶ�
	 * @return ���ž���
	*/
	Mat4x4 GetRotateMat(const Vec3 rotate);
	/**
	 * @brief Χ��һ������������ת
	 * @param rotate Χ�Ƶ�����
	 * @param angle ��ת�Ƕ�
	 * @return ��ת����
	*/
	Mat4x4 GetRotateMatWithVector(Vec3 rotate, const float angle);
	/**
	 * @brief ����lookat����
	 * @param eye ����ĵ�
	 * @param up ��������ϵ�����
	 * @param at ������ڵ�λ��
	 * @return view ����
	*/
	Mat4x4 GetLookAtMat(const Vec3 eye, const Vec3 up, const Vec3 at);
	/**
	 * @brief ����һ������ͶӰ����
	 * @param l min x
	 * @param b min y
	 * @param n near
	 * @param r max x
	 * @param t max y
	 * @param f far
	 * @return ����ͶӰ����
	*/
	Mat4x4 GetOrthoMat(const float l, const float b, const float n, const float r, const float t, const float f);
	/**
	 * @brief ����һ��͸��ͶӰ����
	 * @param fov �ӽǵĴ�С
	 * @param aspect ��߱���
	 * @param near ��ƽ��
	 * @param far ԭƽ��
	 * @return ͸��ͶӰ����
	*/
	Mat4x4 GetPerspectiveMat(const float fov, const float aspect, const float near, const float far);
	/**
	 * @brief ��ת�þ���
	 * @param a Դ
	 * @return 
	*/
	Mat4x4 Transpose(const Mat4x4 a);
	/**
	 * @brief �������
	 * @param a 
	 * @return 
	*/
	Mat4x4 Inverse(const Mat4x4 a);
	float learp(const float x1, const float x2, const float t);
	Vec2 learp(const Vec2 x1, const Vec2 x2,const Vec2 t);
	Vec3 learp(const Vec3 x1, const Vec3 x2, const Vec3 t);
	Vec4 learp(const Vec4 x1, const Vec4 x2, const Vec4 t);


}
