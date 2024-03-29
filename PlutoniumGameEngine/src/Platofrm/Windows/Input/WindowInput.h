#pragma once
#include "PlutoniumGameEngine/Core/Input/Input.h"

namespace PGE {
	class WindowsInput: public Input{

	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		
		virtual std::pair<float, float>GetMousePosImpl() override;

		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	
	};
}