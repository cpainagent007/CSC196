#include "Scene.h"
#include "Actor.h"
#include "../Renderer/Renderer.h"

void Cpain::CScene::Scene::update(float deltaTime) {
	for (auto& actor : m_actors) {
		actor->update(deltaTime);
	}
}

void Cpain::CScene::Scene::draw(Renderer& renderer) {
	for (auto& actor : m_actors) {
		actor->draw(renderer);
	}
}

void Cpain::CScene::Scene::addActor(std::unique_ptr<Cpain::CActor::Actor> actor) {
	m_actors.push_back(std::move(actor));
}