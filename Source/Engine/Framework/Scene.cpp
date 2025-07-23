#include "Scene.h"
#include "Actor.h"
#include "../Renderer/Renderer.h"

namespace Cpain {

	void Scene::update(float deltaTime) {
		for (auto& actor : m_actors) {
			actor->update(deltaTime);
		}
	}

	void Scene::draw(Renderer& renderer) {
		for (auto& actor : m_actors) {
			actor->draw(renderer);
		}
	}

	void Scene::addActor(std::unique_ptr<Actor> actor) {
		actor->scene = this;
		m_actors.push_back(std::move(actor));
	}

	Actor* Scene::getActorByName(const std::string& name) {
		for (auto& actor : m_actors) {
			if(actor->name == name) {
				return actor.get();
			}
		}
		return nullptr;
	}
}


