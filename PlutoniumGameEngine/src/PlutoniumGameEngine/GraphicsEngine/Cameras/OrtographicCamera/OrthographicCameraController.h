#pragma once
#include <PlutoniumGameEngine/GraphicsEngine/Cameras/OrtographicCamera/OrthographicCamera.h>
#include <PlutoniumGameEngine/Core/Timestep/TimeStep.h>

#include <PlutoniumGameEngine/EventSystem/MouseEvent.h>
#include <PlutoniumGameEngine/EventSystem/AplicationEvent.h>

namespace PGE {
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera()const  { return m_Camera; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;


		glm::vec3 m_CameraPosition = {0,0,0};
		float m_CameraRotation = 0.0f;

		float m_CameraTranslationSpeed = 5.0f;
		float m_CameraRotationSpeed = 180.0f;
	};
 }