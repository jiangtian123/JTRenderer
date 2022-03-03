/*
* 申请内存
*/
#pragma once
#include <map>
#include <unordered_map>
#include <stdlib.h>
#include <iostream>
#include "texture.h"
#include "Triangle.h"
#include <set>
enum class BufferType
{
	COLOR = 1,
	DEPTH = 2,
	VERTEX = 4,
	INDEX = 5
};
namespace MathLib { struct Color; }
class Buffer
{
public:
	friend class BufferManage;
	/**
	 * @brief 默认内存为宽高分别为800，600的rgba空间，每个颜色值占据一个字节
	*/
	Buffer():width(800),height(600),type(BufferType::COLOR)
	{
		max_w = width - 1;
		max_h = height - 1;
		int offest;
		switch (type)
		{
		case BufferType::COLOR:
			offest = 4;
			break;
		case BufferType::DEPTH:
			offest = 4;
			break;
		case BufferType::VERTEX:
			offest = 12;
			break;
		case BufferType::INDEX:
			offest = 4;
			break;
		default:
			break;
		}
		size = width * height * offest;
		buffer = malloc(size);
		if (buffer==NULL)
		{
			LOG("error");
		}
	}
	/**
	 * @brief 构造内存函数
	 * @param w 宽度
	 * @param y 高度
	 * @param t 类型
	*/
	Buffer(const unsigned int w, const unsigned int y, BufferType t) :width(w), height(y), type(t)
	{
		max_w = width - 1;
		max_h = height - 1;
		int offest;
		switch (type)
		{
		case BufferType::COLOR:
			offest = 4;
			break;
		case BufferType::DEPTH:
			offest = 4;
			break;
		case BufferType::VERTEX:
			offest = 52;
			break;
		case BufferType::INDEX:
			offest = 4;
			break;
		default:
			break;
		}
		size = width * height * offest;
		buffer = malloc(size);
		if (buffer == NULL)
		{
			LOG("error");
		}
		count = 0;
	}
	Buffer(const Buffer &a)
	{
		type = a.type;
		width = a.width;
		height = a.height;
		max_w = a.max_w;
		max_h = a.max_h;
		size = a.size;
		buffer = a.buffer;
		count = a.count;
	}
	~Buffer()
	{
		
	}
private:
	BufferType type;
	///宽，意味着有多少列
	unsigned int width;
	///高，意味着有多少行
	unsigned int height;
	unsigned int max_w;
	unsigned int max_h;
	unsigned int size;
	unsigned int count;
	void* buffer;
};
class BufferManage
{
private:
	BufferManage();
	BufferManage(BufferManage&) = delete;
	BufferManage& operator=(BufferManage&) = delete;
public:
	typedef std::shared_ptr<BufferManage> ManagePtr;
	~BufferManage();
	/**
	 * @brief 注册一个缓冲区
	 * @param id 如果注册成功该缓冲区的ID
	 * @param type 要注册的缓冲区的类型
	 * @param w 要注册的缓冲区的宽度
	 * @param h 要注册的缓冲区的高度
	*/
	void RegisterBuffer(unsigned int& id,const BufferType type, const unsigned int w, const unsigned int h);
	void RegisterTextureBuffer(unsigned int& id, const char* path);
	/**
	 * @brief 向一个颜色缓冲区中写入
	 * @param id 该颜色缓冲区的id
	 * @param x x的位置
	 * @param y y的位置
	 * @param color 写入的颜色值
	*/
	void WriteColorBuffer(const unsigned int id,const unsigned int x, const unsigned int y,const MathLib::Color color);
	/**
	 * @brief 读取一个颜色缓冲区的内容
	 * @param id 读取的缓冲区的id
	 * @param x 读取的x的位置
	 * @param y 读取的y的位置
	 * @return 颜色值
	*/
	MathLib::Color ReadColorBuffer(const unsigned int id, const unsigned int x, const unsigned int y);
	/**
	 * @brief 向一个深度缓冲区中写入
	 * @param id 该颜色缓冲区的id
	 * @param x x的位置
	 * @param y y的位置
	 * @param de 写入的深度值
	*/
	void WriteDepthBuffer(const unsigned int id, const unsigned int x, const unsigned int y, const float de);
	/**
	 * @brief 读取一个深度缓冲区的内容
	 * @param id 读取的缓冲区的id
	 * @param x 读取的x的位置
	 * @param y 读取的y的位置
	 * @return 深度值
	*/
	float ReadDepthBuffer(const unsigned int id, const unsigned int x, const unsigned int y);
	/**
	 * @brief 将一个顶点数组加载进顶点缓冲
	 * @param id 绑定一个顶点缓冲id
	 * @param ver 顶点数组的头指针
	 * @param size 顶点数组的真实大小，以字节计算
	 * @param count 顶点数组的个数
	*/
	void WriteVertexBuffer(const unsigned int id, const Vertex* ver, const unsigned int size, const unsigned int count);
	/**
	 * @brief 读一个顶点缓冲
	 * @param id 绑定顶点缓冲的id
	 * @param index 索引
	 * @return Vertex
	*/
	const Vertex ReadVertexBuffer(const unsigned int id, const unsigned int index);
	/**
	 * @brief 将一个顶点索引数组加载进索引缓冲
	 * @param id 绑定一个顶点索引缓冲id
	 * @param ver 顶点索引数组的头指针
	 * @param size 顶点索引数组的真实大小，以字节计算
	 * @param count 顶点索引数组的个数
	*/
	void WriteIndexBuffer(const unsigned int id, const int* index, const unsigned int size, const unsigned int count);
	/**
	 * @brief 读一个顶点索引缓冲
	 * @param id 绑定顶点缓冲的id
	 * @param index 索引
	 * @return int
	*/
	const unsigned int ReadIndexBuffer(const unsigned int id, const unsigned int index);
	MathLib::Color Tex(const  unsigned int id, const float u, const float v);
	/**
	 * @brief 删除一个缓冲区
	 * @param id 
	*/
	void DeleteBuffer(const unsigned int id);
	/**
	 * @brief 清空一个缓冲区
	 * @param id 
	*/
	void ClearBuffer(const unsigned int id);
	static ManagePtr const  GetManage();
private:
	static std::map<unsigned int, Buffer> Bufferlist;
	static std::map<unsigned int, Texture> TextureBufferlist;
	static unsigned int ID;
private:
	static ManagePtr m_manage;
};
class FrameBuffer
{
public:
	FrameBuffer();
	explicit FrameBuffer(unsigned int w ,unsigned int h, MathLib::Color backCo = MathLib::Color(0, 0, 0));
	~FrameBuffer();
	void AddColorBuffer(const unsigned int bufferId);
	void DeleteColorBuffer(const unsigned int bufferId);
	const unsigned int GetColorBufferCount();
	void AddDepthBuffer(const unsigned int bufferId);
	void DeleteDepthBuffer(const unsigned int bufferId);
	const unsigned int GetDepthBufferCount();
	void DeleteAll();
	inline const unsigned int GetFirstColorBuffer()
	{
		return *ColorBuffer.begin();
	}
	inline const unsigned int GetFirstColorDepth()
	{
		return *DepthBuffer.begin();
	}
private:
	std::set<unsigned int> ColorBuffer;
	std::set<unsigned int> DepthBuffer;
};



