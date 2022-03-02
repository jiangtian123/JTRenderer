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
	bool IsInsideTriangle(float xn, float yn, const MathLib::Vec2 a1, const  MathLib::Vec2 a2, const MathLib::Vec2 a3);
	void RasterizeTriangle(Triangle& tir);
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
	FrameBuffer defult_frame_buffer;
};
