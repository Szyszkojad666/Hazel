#pragma once

namespace Hazel {

enum class EShaderDataType : uint8_t
{
	None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
};

static uint32_t GetShaderDataTypeSize(EShaderDataType Type)
{
	switch (Type)
	{
		case EShaderDataType::Float:	return 4;
		case EShaderDataType::Float2:	return 4 * 2;
		case EShaderDataType::Float3:	return 4 * 3;
		case EShaderDataType::Float4:	return 4 * 4;
		case EShaderDataType::Mat3:		return 4 * 3 * 3;
		case EShaderDataType::Mat4:		return 4 * 4 * 4;
		case EShaderDataType::Int:		return 4 * 2;
		case EShaderDataType::Int2:		return 4 * 2;
		case EShaderDataType::Int3:		return 4 * 3;
		case EShaderDataType::Int4:		return 4 * 4;
		case EShaderDataType::Bool:		return 1;
	}

	HZ_CORE_ASSERT(false, "Unkown EShaderDataType!");
	return 0;
}

struct BufferElement
{
	EShaderDataType Type;
	std::string Name;
	uint32_t Size;
	uint32_t Offset;
	uint8_t bNormalized;
	
	BufferElement() {}

	BufferElement(EShaderDataType BufferType, const std::string& BufferName, bool Normalized = false)
		: Type(BufferType), Name(BufferName), Size(GetShaderDataTypeSize(BufferType)), Offset(0), bNormalized(Normalized)
	{
	}

	uint32_t GetComponentCount() const
	{
		switch (Type)
		{
			case EShaderDataType::Float:	return 1;
			case EShaderDataType::Float2:	return 2;
			case EShaderDataType::Float3:	return 3;
			case EShaderDataType::Float4:	return 4;
			case EShaderDataType::Mat3:		return 3 * 3;
			case EShaderDataType::Mat4:		return 4 * 4;
			case EShaderDataType::Int:		return 1;
			case EShaderDataType::Int2:		return 2;
			case EShaderDataType::Int3:		return 3;
			case EShaderDataType::Int4:		return 4;
			case EShaderDataType::Bool:		return 1;
		}

		HZ_CORE_ASSERT(false, "Unkown EShaderDataType!");
		return 0;
	}
};

class BufferLayout
{

public:

	BufferLayout() {}

	BufferLayout(const std::initializer_list<BufferElement>& BufferElements)
		: Elements(BufferElements) 
		{
		}

	inline const std::vector<BufferElement>& GetElements() const { return Elements; }
	inline uint32_t GetStride() const { return Stride; }

	std::vector<BufferElement>::iterator begin() { return Elements.begin(); }
	std::vector<BufferElement>::iterator end() { return Elements.end(); }
	
private:

	void CalculateOffsetAndStride()
	{
		uint32_t Offset = 0;
		Stride = 0;
		for (auto& Element : Elements)
		{
			Element.Offset = Offset;
			Offset += Element.Size;
			Stride += Element.Size;
		}
	}

private:
	std::vector<BufferElement> Elements;
	uint32_t Stride = 0;
};

class VertexBuffer
{
public:

	virtual ~VertexBuffer() {}

	virtual void Bind() const = 0;
	virtual void UnBind() const = 0;

	virtual void SetLayout(const BufferLayout& Layout) = 0;
	virtual const BufferLayout& GetLayout() const = 0;

	static VertexBuffer* Create(float* Vertices, uint32_t Size);
};

class IndexBuffer
{
public:

	virtual ~IndexBuffer() {}

	virtual void Bind() const = 0;
	virtual void UnBind() const  = 0;

	virtual uint32_t GetCount() const = 0;

	static IndexBuffer* Create(uint32_t* Indices, uint32_t IdxCount);
};

}