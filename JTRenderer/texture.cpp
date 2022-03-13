#include <stdlib.h>
#include <iostream>
#include "texture.h"
#include "MathLib.h"
using namespace MathLib;
Texture::Texture(const char* path)
{
	pi = stbi_load(path, &width, &height, &nrChannels, 4);
	if (pi == NULL)
	{
		std::cout << "PATH IS ERROR" << std::endl;
	}
}
Texture::~Texture()
{
	
}
float CMID(float x)
{
	return (x < 0.0f) ? 0.0f : ((x > 1.0) ? 1.0f : x);
}
float REPEAT(float x)
{
	if (x > 1.0f)
	{
		return x - std::floorf(x);
	}
	if (x < 0.0f)
	{
		x = std::abs(x);
		return x - std::floorf(x);
	}
}
Color Texture::GetColor(float u, float v, Srruound sr)
{
	if (pi == NULL)
	{
		std::cout << "TEXTURE IS NULL" << std::endl;
		return Color();
	}
	float tem_u;
	float tem_v;
	switch (sr)
	{
	case Srruound::Repeat:
		tem_u = REPEAT(u);
		tem_v = REPEAT(v);
		break;
	case Srruound::CLAMP_TO_EDGE:
		tem_u = CMID(u);
		tem_v = CMID(v);
		break;
	default:
		break;
	}
	int x = (int)(tem_v * (height - 1));
	int y = (int)(tem_u * (width - 1));
	static int a = 0;

	Color res;
	int idex = (x * width + y) * 4;
	res.r = pi[idex];
	res.g = (short)pi[idex + 1];
	res.b = (short)pi[idex + 2];
	res.a = (short)(pi[idex + 3] / 255.0f);
	return res;
}