#include <utility>
#include <iostream>
#include <assert.h>
#include "MathLib.h"
#include "Buffer.h"
#include <float.h>
using namespace MathLib;
typedef unsigned int INT32;
inline BufferType operator|(const BufferType a, const BufferType b)
{
	return BufferType((int)a | (int)b);
}

inline BufferType operator&(const BufferType a,const BufferType b)
{
	return BufferType((int)a & (int)b);
}
BufferManage::BufferManage()
{

}
BufferManage::~BufferManage()
{
	auto buffer_begin = Bufferlist.begin();
	auto texture_begin = TextureBufferlist.begin();
	while (buffer_begin != Bufferlist.end())
	{
		free(buffer_begin->second.buffer);
		buffer_begin->second.buffer = NULL;
		buffer_begin++;
	}
	while (texture_begin != TextureBufferlist.end())
	{
		stbi_image_free(texture_begin->second.pi);
		texture_begin->second.pi = NULL;
		buffer_begin++;
	}
	TextureBufferlist.clear();
	Bufferlist.clear();
}
std::map<unsigned int, Buffer> BufferManage::Bufferlist = {};
std::map<unsigned int, Texture> BufferManage::TextureBufferlist = {};
unsigned int BufferManage::ID = 0;
BufferManage::ManagePtr BufferManage::m_manage = std::shared_ptr<BufferManage>(new BufferManage);
void BufferManage::RegisterBuffer(unsigned int& id, const BufferType type, const  unsigned int w, const unsigned int h)
{
	Buffer buf = Buffer(w, h, type);
	id = ID++;
	Bufferlist.insert(std::pair<unsigned int, Buffer>{id, buf});
}
void BufferManage::RegisterTextureBuffer(unsigned int& id, const char* path)
{
	Texture tex(path);
	id = ID++;
	TextureBufferlist.insert(std::pair<unsigned int, Texture>{id, tex});
}
MathLib::Color BufferManage::Tex(const  unsigned int id, const float u, const float v)
{
	std::map<unsigned int, Texture>::iterator it = TextureBufferlist.find(id);
	if (it== TextureBufferlist.end())
	{
		return MathLib::Color();
	}
	const MathLib::Color result_color = it->second.GetColor(u, v);
	return result_color;
}
void BufferManage::WriteColorBuffer(const unsigned int id, const unsigned int x, const unsigned int y, const MathLib::Color co)
{
	
	std::map<unsigned int, Buffer>::iterator res = Bufferlist.find(id);
	if (res == Bufferlist.end() && res->second.type != BufferType::COLOR)
	{
		std::cout << "ID NOT EXITS OR IS NOT COLOR BUFFER" << std::endl;
		assert(0);
	}
	unsigned int w = res->second.max_w;
	unsigned int h = res->second.max_h;
	///行数不可以大于高度，列数不可以大于宽度
	if (x > h && y > w)
	{
		std::cout << "OVER W OR H" << std::endl;
		return;
	}
	static int count;
	if (count++==40800)
	{
		int a = 11;
	}
	unsigned int* const colorbuffer = (unsigned int*)((char*)res->second.buffer+ (x * res->second.width + y)*4);
	unsigned int tem_color = (co.r<<24)|(co.g<<16)|(co.b<<8)|co.a;
	*colorbuffer = tem_color;
}
MathLib::Color BufferManage::ReadColorBuffer(const unsigned int id, const unsigned int x, const unsigned int y)
{
	std::map<unsigned int, Buffer>::iterator res = Bufferlist.find(id);
	if (res == Bufferlist.end() && res->second.type != BufferType::COLOR)
	{
		std::cout << "ID NOT EXITS OR IS NOT COLOR BUFFER" << std::endl;
		assert(0);
	}
	///行数不可以大于高度，列数不可以大于宽度
	unsigned int w = res->second.max_w;
	unsigned int h = res->second.max_h;
	if (x > h && y > w)
	{
		std::cout << "OVER W OR H" << std::endl;
		assert(0);
	}
	int* const colorbuffer = (int*)res->second.buffer;
	unsigned int index = x * res->second.width + y;
	int tem_co = colorbuffer[index];
	MathLib::Color co;
	co.r= (tem_co >> 24) & 0xFF;
	co.g = (tem_co>> 16) & 0xFF;
	co.b = (tem_co >> 8) & 0xFF;
	co.a =  tem_co & 0xFF;
	return co;
}
void BufferManage::WriteDepthBuffer(const unsigned int id, const unsigned int x, const unsigned int y, const float de)
{
	std::map<unsigned int, Buffer>::iterator res = Bufferlist.find(id);
	if (res == Bufferlist.end() && res->second.type != BufferType::DEPTH)
	{
		std::cout << "ID NOT EXITS OR IS NOT DEPTH BUFFER" << std::endl;
		assert(0);
	}
	///行数不可以大于高度，列数不可以大于宽度
	unsigned int w = res->second.max_w;
	unsigned int h = res->second.max_h;
	if (x > h && y > w)
	{
		std::cout << "OVER W OR H" << std::endl;
		return;
	}
	float* const depthbuffer = (float*)((char*)res->second.buffer+ (x * res->second.width + y) * 4);
	*depthbuffer = de;
}
float BufferManage::ReadDepthBuffer(const unsigned int id, const unsigned int x, const unsigned int y)
{
	std::map<unsigned int, Buffer>::iterator res = Bufferlist.find(id);
	if (res == Bufferlist.end() && res->second.type != BufferType::DEPTH)
	{
		std::cout << "ID NOT EXITS OR IS NOT DEPTH BUFFER" << std::endl;
		assert(0);
	}
	unsigned int w = res->second.max_w;
	unsigned int h = res->second.max_h;
	if (x > h && y > w)
	{
		std::cout << "OVER W OR H" << std::endl;
		assert(0);
	}
	float* depthbuffer = (float*)res->second.buffer;
	unsigned int index = x * res->second.width + y;
	float res_depth = depthbuffer[index];
	return res_depth;
}
void BufferManage::WriteVertexBuffer(const unsigned int id, const Vertex*  ver, const unsigned int size, const unsigned int count)
{
	std::map<unsigned int, Buffer>::iterator res = Bufferlist.find(id);
	if (res == Bufferlist.end() && res->second.type != BufferType::VERTEX)
	{
		std::cout << "ID NOT EXITS OR IS NOT VERTEX BUFFER" << std::endl;
		assert(0);
	}
	if (size > res->second.size)
	{
		std::cout << "OVER BUFFER" << std::endl;
		return;
	}
	if (ver == NULL)
	{
		std::cout << "POINT IS NULL" << std::endl;
		return;
	}
	Vertex* buffer = (Vertex*)(res->second.buffer);
	for (unsigned int i = 0; i < count; i++)
	{
		buffer[i] = ver[i];
	}
}
void BufferManage::WriteIndexBuffer(const unsigned int id, const int*  index, const unsigned int size, const unsigned int count)
{
	std::map<unsigned int, Buffer>::iterator res = Bufferlist.find(id);
	if (res == Bufferlist.end() && res->second.type != BufferType::INDEX)
	{
		std::cout << "ID NOT EXITS OR IS NOT VERTEX BUFFER" << std::endl;
		assert(0);
	}
	if (size > res->second.size)
	{
		std::cout << "OVER BUFFER" << std::endl;
		return;
	}
	if (index == NULL)
	{
		std::cout << "POINT IS NULL" << std::endl;
		return;
	}
	
	for (unsigned int i = 0; i < count; i++)
	{
		int* const buffer = (int*)((char*)res->second.buffer+i*4);
		*buffer = index[i];
	}
}
const Vertex BufferManage::ReadVertexBuffer(const unsigned int id, const unsigned int index)
{
	std::map<unsigned int, Buffer>::iterator res = Bufferlist.find(id);
	if (res == Bufferlist.end() && res->second.type != BufferType::VERTEX)
	{
		std::cout << "ID NOT EXITS OR IS NOT VERTEX BUFFER" << std::endl;
		assert(0);
	}
	Vertex* buffer = (Vertex*)res->second.buffer;
	Vertex resVer = buffer[index];
	return resVer;
}
const unsigned int BufferManage::ReadIndexBuffer(const unsigned int id, const unsigned int index)
{
	std::map<unsigned int, Buffer>::iterator res = Bufferlist.find(id);
	if (res == Bufferlist.end() && res->second.type != BufferType::VERTEX)
	{
		std::cout << "ID NOT EXITS OR IS NOT VERTEX BUFFER" << std::endl;
		assert(0);
	}
	unsigned int* buffer = (unsigned int*)res->second.buffer;
	unsigned int res_ind = buffer[index];
	return res_ind;
}
void BufferManage::DeleteBuffer(const unsigned int id)
{
	std::map<unsigned int, Buffer>::iterator res = Bufferlist.find(id);
	if (res == Bufferlist.end())
	{
		std::cout << "IT NOT EXITS " << std::endl;
		return;
	}
	free(res->second.buffer);
	res->second.buffer = NULL;
	Bufferlist.erase(res);
}
void BufferManage::ClearBuffer(const unsigned int id)
{
	std::map<unsigned int, Buffer>::iterator res = Bufferlist.find(id);
	if (res == Bufferlist.end())
	{
		std::cout << "ID NOT EXITS " << std::endl;
		return;
	}
	char* depthbuffer = (char*)res->second.buffer;
	for (unsigned int i = 0; i < res->second.size; i++)
	{
		depthbuffer[i] = 0;
	}
}
BufferManage::ManagePtr const BufferManage::GetManage()
{
	return m_manage;
}
FrameBuffer::FrameBuffer()
{

}
FrameBuffer::FrameBuffer(unsigned int w, unsigned int h ,MathLib::Color backCo)
{
	ColorBuffer = {};
	DepthBuffer = {};
	unsigned int colorbuffer;
	BufferManage::GetManage()->RegisterBuffer(colorbuffer, BufferType::COLOR, w, h);
	ColorBuffer.insert(colorbuffer);
	for (size_t i = 0; i < h; i++)
	{
		for (size_t j = 0; j < w; j++)
		{
			BufferManage::GetManage()->WriteColorBuffer(colorbuffer,i,j, backCo);
		}
	}
	unsigned int depthbuffer;
	BufferManage::GetManage()->RegisterBuffer(depthbuffer, BufferType::DEPTH, w, h);
	for (size_t i = 0; i < h; i++)
	{
		for (size_t j = 0; j < w; j++)
		{
			BufferManage::GetManage()->WriteDepthBuffer(depthbuffer, i, j, FLT_MIN);
		}
	}
	DepthBuffer.insert(depthbuffer);
}
FrameBuffer::~FrameBuffer()
{
	
}
void FrameBuffer::AddColorBuffer(const unsigned int bufferId)
{
	std::set<unsigned int>::iterator color_buffer = ColorBuffer.find(bufferId);
	if (color_buffer!= ColorBuffer.end())
	{
		std::cout << "EXIST" << std::endl;
	}
	ColorBuffer.insert(bufferId);
}
void FrameBuffer::DeleteColorBuffer(const unsigned int bufferId)
{
	std::set<unsigned int>::iterator color_buffer = ColorBuffer.find(bufferId);
	if (color_buffer == ColorBuffer.end())
	{
		std::cout << "NO EXIST" << std::endl;
	}
	BufferManage::GetManage()->DeleteBuffer(*color_buffer);
	ColorBuffer.erase(bufferId);
}
const unsigned int FrameBuffer::GetColorBufferCount()
{
	return ColorBuffer.size();
}
void FrameBuffer::AddDepthBuffer(const unsigned int bufferId)
{
	std::set<unsigned int>::iterator depth_buffer = DepthBuffer.find(bufferId);
	if (depth_buffer != DepthBuffer.end())
	{
		std::cout << "EXIST" << std::endl;
	}
	DepthBuffer.insert(bufferId);
}
void FrameBuffer::DeleteDepthBuffer(const unsigned int bufferId)
{
	std::set<unsigned int>::iterator depth_buffer = DepthBuffer.find(bufferId);
	if (depth_buffer == DepthBuffer.end())
	{
		std::cout << "NO EXIST" << std::endl;
	}
	BufferManage::GetManage()->DeleteBuffer(*depth_buffer);
	DepthBuffer.erase(bufferId);
}
void FrameBuffer::DeleteAll()
{
	std::set<unsigned int>::iterator color_buffers = ColorBuffer.begin();
	while (color_buffers != ColorBuffer.end())
	{
		BufferManage::GetManage()->DeleteBuffer(*color_buffers);
		color_buffers++;
	}
	ColorBuffer.clear();
	std::set<unsigned int>::iterator depth_buffers = DepthBuffer.begin();
	while (depth_buffers != DepthBuffer.end())
	{
		BufferManage::GetManage()->DeleteBuffer(*depth_buffers);
		depth_buffers++;
	}
	DepthBuffer.clear();
}
const unsigned int FrameBuffer::GetDepthBufferCount()
{
	return DepthBuffer.size();
}