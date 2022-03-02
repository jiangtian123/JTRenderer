#include "rasterizer.h"
#include <vector>
#include <array>
Rasterizer::Rasterizer(unsigned int w = 800, unsigned int h = 600) :width(w), height(h)
{

};
void Rasterizer::InIt()
{
	defult_frame_buffer = FrameBuffer(width, height);
	vertex_buffer = NULL;
	index_buffer = NULL;
}
void Rasterizer::Draw(const unsigned int vertex_size, const unsigned int index_size, const Primitive drawType, const unsigned int pri_size)
{
	if (vertex_buffer==NULL)
	{
		LOG("NO VERTEX");
		return;
	}
	if (index_buffer == NULL)
	{
		LOG("NO INDEX");
	}
	if (m_camera == NULL)
	{
		LOG("NO CAMERA");
		return;
	}
	///如果是顶点绘制模式。则经过顶点变换后直接输出到缓冲区
	if (drawType== Primitive::POINT)
	{
		for (size_t i = 0; i < pri_size; i++)
		{
			Vertex a = BufferManage::GetManage()->ReadVertexBuffer(*vertex_buffer, i);
			vertex_shader vef;
			vef.vertex = a;
			vef.model = this->Model;
			vef.project = this->Pro;
			vef.view = this->View;
			fragment_shader fra = ver_shader(vef);
			MathLib::Color res_color = fra_shader(fra);

		}
	}
	if (drawType == Primitive::LINE)
	{

	}
	if (drawType == Primitive::Triangle)
	{
		Triangle tri;
		for (size_t pri = 0; pri < pri_size;)
		{
			///取一个三角形
			unsigned int current_index1 = BufferManage::GetManage()->ReadIndexBuffer(*index_buffer, pri++);
			unsigned int current_index2 = BufferManage::GetManage()->ReadIndexBuffer(*index_buffer, pri++);
			unsigned int current_index3 = BufferManage::GetManage()->ReadIndexBuffer(*index_buffer, pri++);
			Vertex a = BufferManage::GetManage()->ReadVertexBuffer(*vertex_buffer, current_index1);
			Vertex b = BufferManage::GetManage()->ReadVertexBuffer(*vertex_buffer, current_index2);
			Vertex c = BufferManage::GetManage()->ReadVertexBuffer(*vertex_buffer, current_index3);
			tri = Triangle(a, b, c);
			MathLib::Mat4x4 mvp = Pro * View * Model;
			tri.UpData();
			//经过mvp变换后的顶点
			std::array<MathLib::Vec4, 3> ndc_pos
			{
				(mvp*tri.a()),(mvp * tri.b()),(mvp * tri.c())
			};
			
			//世界坐标下的法线
			std::array<MathLib::Vec3, 3> w_normal
			{
				MathLib::Vec3(Model * MathLib::Vec4(tri.GetNormal(0).x,tri.GetNormal(0).y,tri.GetNormal(0).z,0)),
				MathLib::Vec3(Model * MathLib::Vec4(tri.GetNormal(1).x,tri.GetNormal(1).y,tri.GetNormal(1).z,0)),
				MathLib::Vec3(Model * MathLib::Vec4(tri.GetNormal(2).x,tri.GetNormal(2).y,tri.GetNormal(2).z,0))
			};
			for (auto& i : ndc_pos)
			{
				i.x /= i.w;
				i.y /= i.w;
				i.z /= i.w;
			}
			for (auto& i : ndc_pos)
			{
				i.x = (i.x + 1.0f) * 0.5 * this->width;
				i.y = (1.0f - i.y) * 0.5 * this->height;
			}
			Vertex A1(ndc_pos[0], tri.GetUv(0), w_normal[0]);
			A1.SetRwh(1.0f / ndc_pos[0].w);
			Vertex B1(ndc_pos[1], tri.GetUv(1), w_normal[1]);
			B1.SetRwh(1.0f / ndc_pos[1].w);
			Vertex C1(ndc_pos[2], tri.GetUv(2), w_normal[2]);
			C1.SetRwh(1.0f / ndc_pos[2].w);
			tri = Triangle(A1,B1,C1);

		}
	}
}
bool Rasterizer::IsInsideTriangle(float xn, float yn,const MathLib::Vec2 a0,const MathLib::Vec2 a1,const MathLib::Vec2 a2)
{
	MathLib::Vec2 p;
	p.x = xn;
	p.y = yn;
	MathLib::Vec2 AB = a1 - a0;
	MathLib::Vec2 BC = a2 - a1;
	MathLib::Vec2 CA = a0 - a2;
	MathLib::Vec2 AP = p - a0;
	MathLib::Vec2 BP = p - a1;
	MathLib::Vec2 CP = p - a2;
	return (AB.x * AP.y - AB.y * AP.x) >= 0 &&
		(BC.x * BP.y - BC.y * BP.x) >= 0 &&
		(CA.x * CP.y - CA.y * CP.x) >= 0;
}
///光栅化用包围盒计算三角形，回头改成扫描线
void Rasterizer::RasterizeTriangle(Triangle& tri)
{
	MathLib::Vec2 a = tri.a();
	MathLib::Vec2 b = tri.b();
	MathLib::Vec2 c = tri.c();
	float minX = std::min(a.x, std::min(b.x, c.x));
	float minY = std::min(a.y, std::min(b.y, c.y));
	float maxX = std::max(a.x, std::max(b.x, c.x));
	float maxY = std::min(a.y, std::max(b.y, c.y));
	int MinX = (int)std::floor(minX);
	int MinY = (int)std::ceil(minY);
	int MaxX = (int)std::floor(maxX);
	int MaxY = (int)std::ceil(maxY);
	for (size_t i = MinX; i < MaxX; i++)
	{
		for (size_t j = MinY; j < MaxY; j++)
		{
			if (IsInsideTriangle((float)(i + 0.5f), (float)(j + 0.5), a, b, c))
			{

			}
		}
	}

}