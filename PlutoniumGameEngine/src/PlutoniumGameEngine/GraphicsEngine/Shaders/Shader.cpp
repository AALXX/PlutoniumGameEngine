#include "pphd.h"
#include "Shader.h"


#include "PlutoniumGameEngine/GraphicsEngine/Renderer/RendererApi.h"
#include "Platofrm/OpenGlApi/OpenGLShader/OpenGLShader.h"

namespace PGE {
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:    PGE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGl:  return std::make_shared<PGE_OPENGL::OpenGLShader>(filepath);
		}

		PGE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:    PGE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGl:  return std::make_shared<PGE_OPENGL::OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		PGE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		PGE_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	PGE::Ref<PGE::Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	PGE::Ref<PGE::Shader> ShaderLibrary::Load(const std::string& name, std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	PGE::Ref<PGE::Shader> ShaderLibrary::Get(const std::string& name)
	{
		PGE_CORE_ASSERT(Exists(name), "Shader not found!");

		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}
