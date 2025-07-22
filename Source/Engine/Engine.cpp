#include "Engine.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"

namespace Cpain {

	bool Engine::initialize() {
		m_renderer = std::make_unique<Cpain::Renderer>();
		m_renderer->initialize();
		m_renderer->createWindow("Cpain Engine", 1280, 1024);

		m_input = std::make_unique<InputSystem>();
		m_input->initialize();

		m_audio = std::make_unique<AudioSystem>();
		m_audio->initialize();

		return true;
	}

	void Engine::shutdown() {
		m_audio->shutdown();
		m_input->shutdown();
		m_renderer->shutdown();
	}

	void Engine::update() {
		m_time.tick();
		m_audio->update();
		m_input->update();
	}

	void Engine::draw() {

	}	

	Engine& getEngine() {
		static Engine engine;
		return engine;
	}
}