#pragma once
namespace PGE {


	class IAmGuiRendererAPI
	{
	public:

		virtual void Begin() = 0;
		virtual void End() = 0;
		virtual void OnAttach() = 0;
		virtual void OnDettach() = 0;
		virtual void OnImGuiRender() = 0;

	};

}