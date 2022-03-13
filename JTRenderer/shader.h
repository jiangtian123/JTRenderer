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
	MathLib::Vec3 cameraPos;
	MathLib::Vec3 wordPos;
	MathLib::Vec3 lightPos;
	std::vector<unsigned int*> tex;
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
