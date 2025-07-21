#pragma once

#include "Audio/AudioSystem.h"

#include "Core/Time.h"

#include "Input/InputSystem.h"

#include "Renderer/Renderer.h"

#include <memory>

namespace Cpain {
	class AudioSystem;
	class Time;
	class InputSystem;
	class Renderer;

	class Engine {
	public:
		Engine() = default;

		bool initialize();
		void shutdown();

		void update();
		void draw();

		CAudio::AudioSystem& getAudio() { return *m_audio; }
		CTime::Time& getTime() { return m_time; }
		CInput::InputSystem& getInput() { return *m_input; }
		Renderer& getRenderer() { return *m_renderer; }

	private:
		std::unique_ptr<CAudio::AudioSystem> m_audio;
		CTime::Time m_time;
		std::unique_ptr<CInput::InputSystem> m_input;
		std::unique_ptr<Renderer> m_renderer;
		

	};

	Engine& getEngine();

}