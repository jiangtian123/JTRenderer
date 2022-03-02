#include <stdlib.h>
#include "Buffer.h"
#include "texture.h"
#include "stb-master/stb_image.h"
#include "rasterizer.h"
using namespace MathLib;
int main(void)
{
	MathLib::Mat4x4 view = MathLib::GetLookAtMat(MathLib::Vec3(0,0,0), MathLib::Vec3(0, 1, 0), MathLib::Vec3(0, 1, 3));
	MathLib::Mat4x4 test1 = MathLib::GetPerspectiveMat(90.0, 3.0f / 2.0f, 0.1, 100);
	float a=1.0;
}