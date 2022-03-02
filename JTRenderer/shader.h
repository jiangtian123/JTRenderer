#pragma once
#include "texture.h"
#include <vector>
#include "Triangle.h"
struct fragment_shader
{
	fragment_shader()
	{
		
	}
	fragment_shader(const fragment_shader& a) = default;
	fragment_shader& operator=(const fragment_shader& a) = default;
	fragment_shader(Vertex ver):vertex(ver)
	{

	}
	Vertex vertex;
};
struct vertex_shader
{
	vertex_shader() = default;
	vertex_shader(Vertex ver) :vertex(ver) {};
	Vertex vertex;
	MathLib::Mat4x4 model;
	MathLib::Mat4x4 view;
	MathLib::Mat4x4 project;

};
