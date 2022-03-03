#pragma once
#include <functional>
#include "Buffer.h"
#include "shader.h"
#include "global.h"
class Camera;
enum class Primitive
{
	POINT=0,
	LINE=1,
	Triangle=2
};
/**
 * @brief 一个光栅化器
*/
class Rasterizer
{
public:
	Rasterizer() = delete;
	Rasterizer(unsigned int w, unsigned int h);
	~Rasterizer()
	{
		BufferManage::GetManage()->DeleteBuffer(*vertex_buffer);
		BufferManage::GetManage()->DeleteBuffer(*index_buffer);
	}
	void InIt();
	inline void BindVertexShader(std::function<Vertex(vertex_shader)> vershader)
	{
		this->ver_shader = vershader;
	}
	inline void BindFragmentShader(std::function<MathLib::Color(fragment_shader)> frshader)
	{
		this->fra_shader = frshader;
	}
	inline void BindVertex(unsigned int* const vertexId)
	{
		this->vertex_buffer = vertexId;
	}
	inline void BindIndex(unsigned int* const indexId)
	{
		this->index_buffer = indexId;
	}
	inline void BindModelMat(const MathLib::Mat4x4& mo)
	{
		this->Model = mo;
	}
	inline void BindViewMat(const MathLib::Mat4x4& vi)
	{
		this->View = vi;
	}
	inline void BindProMat(const MathLib::Mat4x4& pr)
	{
		this->Pro = pr;
	}
	inline void BindCamera(Camera* const ca)
	{
		m_camera = ca;
	}
	inline void SetBackGroundColor(const MathLib::Color bc)
	{
		backColor = bc;
	}
	inline unsigned int GetDefultColorBuffer()
	{
		return defult_frame_buffer.GetFirstColorBuffer();
	}
	inline int GetWidth()
	{
		return width;
	}
	inline int GetHeight()
	{
		return height;
	}
	bool IsInsideTriangle(float xn, float yn, const MathLib::Vec2 a1, const  MathLib::Vec2 a2, const MathLib::Vec2 a3);
	void RasterizeTriangle(Triangle& tir, std::array<MathLib::Vec4, 3> wordPos);
	/**
	 * @brief 绘制函数
	 * @param vertex_size 顶点个数
	 * @param index_size 索引个数
	 * @param drawType 绘制类型
	 * @param pri_size 图元个数
	*/
	void Draw(const unsigned int vertex_size, const unsigned int index_size, const Primitive drawType, const unsigned int pri_size);
	
private:
	MathLib::Mat4x4 Model;
	MathLib::Mat4x4 View;
	MathLib::Mat4x4 Pro;
	std::function<fragment_shader(vertex_shader)> ver_shader;
	std::function<MathLib::Color(fragment_shader)> fra_shader;
private:
	Camera* m_camera;
	unsigned int width;
	unsigned int height;
	unsigned int* vertex_buffer;
	unsigned int* index_buffer;
	MathLib::Color backColor = MathLib::Color(0);
	FrameBuffer defult_frame_buffer;
};
