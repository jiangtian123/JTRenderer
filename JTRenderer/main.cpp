#include <stdlib.h>
#include "Buffer.h"
#include "texture.h"
#include "stb-master/stb_image.h"
#include "rasterizer.h"
#include "camera.h"
using namespace MathLib;
MathLib::Color fra_shader(fragment_shader inf)
{
	return MathLib::Color(255,0,0);
}
Camera minCam(Vec3(0), Vec3(0, 1, 0), Vec3(0, 0, 3));
int main(void)
{
	float color_ziae = sizeof(Color);
	Rasterizer ras(800, 600);
	ras.BindCamera(&minCam);
	ras.SetBackGroundColor(MathLib::Color(20,100,50));
	ras.BindModelMat(MathLib::Mat4x4());
	ras.InIt();
	ras.BindFragmentShader(fra_shader);
	std::vector<Vertex> vertexarray = {
		Vertex(Vec4(-0.6,0.6,0,1),Vec2(0,0)),
		Vertex(Vec4(0.6,0.6,0,1),Vec2(1,0)),
		Vertex(Vec4(-0.6,-0.6,0,1),Vec2(0,1)),
		Vertex(Vec4(0.6,-0.6,0,1),Vec2(1,1))
	};
	std::vector<int> indexarray{
		0,1,3,0,3,2
	};
	unsigned int VerBuffer;
	BufferManage::GetManage()->RegisterBuffer(VerBuffer, BufferType::VERTEX, vertexarray.size(),1);
	BufferManage::GetManage()->WriteVertexBuffer(VerBuffer, vertexarray.data(), vertexarray.size() * sizeof(Vertex), vertexarray.size());
	unsigned int indexBuffer;
	BufferManage::GetManage()->RegisterBuffer(indexBuffer, BufferType::INDEX, indexarray.size(),1);
	BufferManage::GetManage()->WriteIndexBuffer(indexBuffer,indexarray.data(), indexarray.size() * sizeof(int), indexarray.size());
	ras.BindVertex(&VerBuffer);
	ras.BindIndex(&indexBuffer);
	ras.Draw(vertexarray.size(), indexarray.size(),Primitive::Triangle, indexarray.size()/3);
	FILE* fp = fopen("binary3.ppm", "wb");
	(void)fprintf(fp, "P6\n%d %d\n255\n",ras.GetWidth(),ras.GetHeight() );
	for (auto i = 0; i < ras.GetHeight(); ++i) {
		for (size_t j = 0; j < ras.GetWidth(); j++)
		{
			MathLib::Color tem_color = BufferManage::GetManage()->ReadColorBuffer(ras.GetDefultColorBuffer(),i,j);
			static unsigned char color[3];
			color[0] = (unsigned char)(std::pow(MathLib::Clamp(tem_color.r, 0, 255), 1));
			color[1] = (unsigned char)(std::pow(MathLib::Clamp(tem_color.g, 0, 255), 1));
			color[2] = (unsigned char)(std::pow(MathLib::Clamp(tem_color.b, 0, 255), 1));
			fwrite(color, 1, 3, fp);
		}
		
	}
	fclose(fp);
}