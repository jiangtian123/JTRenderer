/*
* �����ڴ�
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
	 * @brief Ĭ���ڴ�Ϊ��߷ֱ�Ϊ800��600��rgba�ռ䣬ÿ����ɫֵռ��һ���ֽ�
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
	 * @brief �����ڴ溯��
	 * @param w ���
	 * @param y �߶�
	 * @param t ����
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
	///����ζ���ж�����
	unsigned int width;
	///�ߣ���ζ���ж�����
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
	 * @brief ע��һ��������
	 * @param id ���ע��ɹ��û�������ID
	 * @param type Ҫע��Ļ�����������
	 * @param w Ҫע��Ļ������Ŀ��
	 * @param h Ҫע��Ļ������ĸ߶�
	*/
	void RegisterBuffer(unsigned int& id,const BufferType type, const unsigned int w, const unsigned int h);
	void RegisterTextureBuffer(unsigned int& id, const char* path);
	/**
	 * @brief ��һ����ɫ��������д��
	 * @param id ����ɫ��������id
	 * @param x x��λ��
	 * @param y y��λ��
	 * @param color д�����ɫֵ
	*/
	void WriteColorBuffer(const unsigned int id,const unsigned int x, const unsigned int y,const MathLib::Color color);
	/**
	 * @brief ��ȡһ����ɫ������������
	 * @param id ��ȡ�Ļ�������id
	 * @param x ��ȡ��x��λ��
	 * @param y ��ȡ��y��λ��
	 * @return ��ɫֵ
	*/
	MathLib::Color ReadColorBuffer(const unsigned int id, const unsigned int x, const unsigned int y);
	/**
	 * @brief ��һ����Ȼ�������д��
	 * @param id ����ɫ��������id
	 * @param x x��λ��
	 * @param y y��λ��
	 * @param de д������ֵ
	*/
	void WriteDepthBuffer(const unsigned int id, const unsigned int x, const unsigned int y, const float de);
	/**
	 * @brief ��ȡһ����Ȼ�����������
	 * @param id ��ȡ�Ļ�������id
	 * @param x ��ȡ��x��λ��
	 * @param y ��ȡ��y��λ��
	 * @return ���ֵ
	*/
	float ReadDepthBuffer(const unsigned int id, const unsigned int x, const unsigned int y);
	/**
	 * @brief ��һ������������ؽ����㻺��
	 * @param id ��һ�����㻺��id
	 * @param ver ���������ͷָ��
	 * @param size �����������ʵ��С�����ֽڼ���
	 * @param count ��������ĸ���
	*/
	void WriteVertexBuffer(const unsigned int id, const Vertex* ver, const unsigned int size, const unsigned int count);
	/**
	 * @brief ��һ�����㻺��
	 * @param id �󶨶��㻺���id
	 * @param index ����
	 * @return Vertex
	*/
	const Vertex ReadVertexBuffer(const unsigned int id, const unsigned int index);
	/**
	 * @brief ��һ����������������ؽ���������
	 * @param id ��һ��������������id
	 * @param ver �������������ͷָ��
	 * @param size ���������������ʵ��С�����ֽڼ���
	 * @param count ������������ĸ���
	*/
	void WriteIndexBuffer(const unsigned int id, const int* index, const unsigned int size, const unsigned int count);
	/**
	 * @brief ��һ��������������
	 * @param id �󶨶��㻺���id
	 * @param index ����
	 * @return int
	*/
	const unsigned int ReadIndexBuffer(const unsigned int id, const unsigned int index);
	MathLib::Color Tex(const  unsigned int id, const float u, const float v);
	/**
	 * @brief ɾ��һ��������
	 * @param id 
	*/
	void DeleteBuffer(const unsigned int id);
	/**
	 * @brief ���һ��������
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



