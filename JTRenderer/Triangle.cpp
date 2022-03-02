#include "Triangle.h"
Vertex::Vertex(const Vertex& a)
{
	this->vex = a.vex;
	this->color = a.color;
	this->normal = a.normal;
	this->uv = a.uv;
}
Vertex& Vertex::operator=(const Vertex& a)
{
	this->vex = a.vex;
	this->color = a.color;
	this->normal = a.normal;
	this->uv = a.uv;
	return *this;
}