#include "rasterizer.h"
#include <vector>
#include <array>
#include "camera.h"
Rasterizer::Rasterizer(unsigned int w = 800, unsigned int h = 600) :width(w), height(h)
{
	
};
void Rasterizer::InIt()
{
	defult_frame_buffer = FrameBuffer(width, height,backColor);
	vertex_buffer = NULL;
	index_buffer = NULL;
	BindViewMat(m_camera->GetLookAt());
	BindProMat(m_camera->GetProjection());
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
		for (size_t pri = 0; pri < pri_size; pri++)
		{
			///取一个三角形
			int index_ = pri*3;
			if (index_> index_size)
			{
				return;
			}
			unsigned int current_index1 = BufferManage::GetManage()->ReadIndexBuffer(*index_buffer, index_++);
			unsigned int current_index2 = BufferManage::GetManage()->ReadIndexBuffer(*index_buffer, index_++);
			unsigned int current_index3 = BufferManage::GetManage()->ReadIndexBuffer(*index_buffer, index_++);
			if (current_index1> vertex_size|| current_index2 > vertex_size|| current_index3 > vertex_size)
			{
				return;
			}
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
			std::array<MathLib::Vec4, 3> word_pos
			{
				(Model * tri.a()),(Model * tri.b()),(Model * tri.c())
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
				i.z =  i.w;
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
			MathLib::Vec2 BA = B1.vex - A1.vex;
			MathLib::Vec2 CA = C1.vex - A1.vex;
			///判断是顺时针还是逆时针
			if (MathLib::CrossProduct(BA,CA)>0)
			{
				RasterizeTriangle(tri, word_pos);
			}		
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
void Rasterizer::RasterizeTriangle(Triangle& tri, std::array<MathLib::Vec4, 3> wordPos)
{
	MathLib::Vec3 a = tri.a();
	MathLib::Vec3 b = tri.b();
	MathLib::Vec3 c = tri.c();
	float minX = std::min(a.x, std::min(b.x, c.x));
	float minY = std::min(a.y, std::min(b.y, c.y));
	float maxX = std::max(a.x, std::max(b.x, c.x));
	float maxY = std::max(a.y, std::max(b.y, c.y));
	int MinX = (int)std::floor(minX);
	int MinY = (int)std::floor(minY);
	int MaxX = (int)std::ceil(maxX);
	int MaxY = (int)std::ceil(maxY);
	for (size_t i = MinX; i < MaxX; i++)
	{
		for (size_t j = MinY; j < MaxY; j++)
		{
			if (IsInsideTriangle((float)(i + 0.5f), (float)(j + 0.5), a, b, c))
			{
				auto [alpha, beta, gamma] = MathLib::ComputeBarycentric2D(MathLib::Vec2((float)(i + 0.5f), (float)(j + 0.5)), a, b, c);
				float Zn = 1.00f / (alpha / a.z + beta / b.z + gamma / c.z);
				float z = alpha * a.z + beta * b.z + gamma * c.z;
				if (z>BufferManage::GetManage()->ReadDepthBuffer(defult_frame_buffer.GetFirstColorDepth(),i,j))
				{
					MathLib::Vec3 normal = tri.GetNormal(0) * alpha + tri.GetNormal(1) * beta + tri.GetNormal(2) * gamma;
					MathLib::UV uv = tri.GetUv(0) * alpha + tri.GetUv(1) * beta + tri.GetUv(2) * gamma;
					MathLib::Vec3 worldP = wordPos[0] * alpha + wordPos[1] * beta + wordPos[2] * gamma;
					MathLib::Color color_(100,10,13);
					fragment_shader inP;
					inP.wordPos = worldP;
					inP.cameraPos = m_camera->GetCameraPos();
					Vertex vex(MathLib::Vec4(i+0.5,j+0.5,0.0f,1.0f), uv, normal, color_);
					inP.vertex = vex;
					for (auto tem_tex_map:texMap)
					{
						unsigned int* t = tem_tex_map.second;
						inP.tex.push_back(t);
					}
					MathLib::Color res_color = fra_shader(inP);
					BufferManage::GetManage()->WriteColorBuffer(defult_frame_buffer.GetFirstColorBuffer(),i,j, res_color);
					BufferManage::GetManage()->WriteDepthBuffer(defult_frame_buffer.GetFirstColorDepth(),i,j,z);
				}
			}
		}
	}

}