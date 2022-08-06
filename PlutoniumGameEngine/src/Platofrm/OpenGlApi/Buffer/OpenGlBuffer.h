#pragma once
#include <Glad/glad.h>
#include <glm/glm.hpp>

namespace PGE_OPENGL {

	enum class ShaderDataType
	{
		None = 0, Float , Float2 , Float3 , Float4 , Mat3 , Mat4 , Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type) {
		switch (type)
		{
		case PGE_OPENGL::ShaderDataType::Float:
			return 4;
		case PGE_OPENGL::ShaderDataType::Float2:
			return 4 * 2;
		case PGE_OPENGL::ShaderDataType::Float3:
			return 4 * 3;
		case PGE_OPENGL::ShaderDataType::Float4:
			return 4 * 4;
		case PGE_OPENGL::ShaderDataType::Mat3:
			return 4 * 3 * 3;
		case PGE_OPENGL::ShaderDataType::Mat4:
			return 4 * 4 * 4;
		case PGE_OPENGL::ShaderDataType::Int:
			return 4;
		case PGE_OPENGL::ShaderDataType::Int2:
			return 4 * 2;
		case PGE_OPENGL::ShaderDataType::Int3:
			return 4 *3;
		case PGE_OPENGL::ShaderDataType::Int4:
			return 4 * 4;
		case PGE_OPENGL::ShaderDataType::Bool:
			return 1;
		}

		PGE_CORE_ASSERT(false, "Unknown Shader Type");

		return 0;
	}

	struct BufferElements
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Offset;
		uint32_t Size;
		BufferElements(ShaderDataType type, const std::string& name)
			:Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0)
		{

		}
	};

	class OpenGLBufferLayout {
	public:
		OpenGLBufferLayout(const std::initializer_list<BufferElements>& elements) 
			:m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		};
		inline const std::vector<BufferElements>& GetElements()  const { return m_Elements; };

		std::vector<BufferElements>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElements>::iterator end() { return m_Elements.end(); }
	private:

		void CalculateOffsetsAndStride() {
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

	private:
		std::vector<BufferElements> m_Elements;
		uint32_t m_Stride = 0;
	};

	class OpenGLVertexBuffer
	{
	public:
		OpenGLVertexBuffer(glm::mat3x3 &vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual const OpenGLBufferLayout& GetLayout() const { return m_Layout ; };
		virtual void SetLayout(const OpenGLBufferLayout& layout) { m_Layout = layout; };

		virtual void Bind() const;
		virtual void Unbind() const;
	private:
		uint32_t m_RendererID;
		OpenGLBufferLayout m_Layout;

	};

	class OpenGLIndexBuffer 
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual uint32_t GetCount() const { return m_Count; }
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}
