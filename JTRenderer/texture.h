#pragma once
#include <string>
#include "stb-master/stb_image.h"
#include <stdio.h>
namespace MathLib { class Color; }
enum class Srruound
{
	Repeat=0,
	CLAMP_TO_EDGE
};
/**
 * @brief 纹理的0.0在左上角
*/
class Texture
{
public:
	friend class BufferManage;
	Texture(const char* path);
	Texture(const Texture& a)
	{
		width = a.width;
		height = a.height;
		nrChannels = a.nrChannels;
		pi = a.pi;
	}
	~Texture();
	MathLib::Color GetColor(float u, float v, Srruound sr= Srruound::CLAMP_TO_EDGE);
private:
	int width;
	int height;
	int nrChannels;
	unsigned char* pi;
};
