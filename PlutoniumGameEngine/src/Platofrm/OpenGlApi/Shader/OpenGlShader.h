#pragma once
#include "pphd.h"
#include "PlutoniumGameEngine/Core/Core.h"

namespace PGE_OPENGL {
	class OpenGlShader
	{
	public:
		OpenGlShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGlShader();

		void Bind() const;
		void UnBind() const;

	private:
		uint32_t m_RendererID;
	};
}