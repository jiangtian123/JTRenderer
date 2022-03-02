#pragma once
#include <vector>
#include "MathLib.h"
typedef std::vector<unsigned int> Index;
struct Vertex
{
	Vertex() = default;
	/**
	 * @brief 
	 * @param p 坐标
	 * @param u uv坐标
	 * @param n 法线
	 * @param c 颜色
	*/
	Vertex(MathLib::Vec4 p, MathLib::UV u,MathLib::Vec3 n=MathLib::Vec3(0), MathLib::Color c = MathLib::Color(0, 0, 0))
		:vex(p), uv(u), normal(n),color(c) {};
	Vertex(const Vertex& a);
	Vertex& operator=(const Vertex& a);
	inline void SetNormal(MathLib::Vec3 no)
	{
		 normal = no;
	}
	inline void SetTex(MathLib::UV tex)
	{
		uv = tex;
	}
	inline void SetColor(MathLib::Color co)
	{
		color = co;
	}
	inline void SetRwh(float a)
	{
		rwh = a;
	}
	MathLib::Point vex;
	MathLib::Vec3 normal;
	MathLib::Color color;
	MathLib::UV uv;
	float rwh;
};
class Triangle
{
public:
	Triangle() = default;
	Triangle(const Triangle& a) = default;
	Triangle& operator=(const Triangle& a) = default;
	Triangle(Vertex a, Vertex b, Vertex c)
	{
		pos[0] = a;
		pos[1] = b;
		pos[2] = c;
	}
	~Triangle()=default;
	inline void UpData()
	{
		if (pos[0].normal == 0.0f && pos[1].normal == 0.0f && pos[3].normal == 0.0f)
		{
			MathLib::Vec3 A = pos[0].vex - pos[1].vex;
			MathLib::Vec3 B = pos[2].vex - pos[1].vex;
			MathLib::Vec3 Normal = MathLib::CrossProduct(A,B);
			MathLib::Normalize(Normal);
			pos[0].SetNormal(Normal);
			pos[1].SetNormal(Normal);
			pos[2].SetNormal(Normal);
			
		}
	}
	inline MathLib::Point a()
	{
		return pos[0].vex;
	}
	inline MathLib::Point b()
	{
		return pos[1].vex;
	}
	inline MathLib::Point c()
	{
		return pos[2].vex;
	}
	inline MathLib::Vec3 GetNormal(unsigned int a)
	{
		if (a>2)
		{
			return pos[2].normal;
		}
		return pos[a].normal;
	}
	inline MathLib::UV GetUv(unsigned int a)
	{
		if (a>2)
		{
			return pos[2].uv;
		}
		return pos[a].uv;
	}
private:
	Vertex pos[3];
};
