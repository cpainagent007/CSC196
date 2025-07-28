#include "Core/Random.h"

#include "Framework/Scene.h"

#include "Input/InputSystem.h"

#include "Math/Vector2.h"

#include "Renderer/Model.h"
#include "Renderer/Renderer.h"

#include "Engine.h"

#include "Player.h"

#include "SpaceGame.h"
#include "Enemy.h"
#include "GameData.h"

#include <vector>
#include <memory>

bool SpaceGame::initialize(){
    m_scene = std::make_unique<Cpain::Scene>();

    return true;
}

void SpaceGame::update(float deltaTime){
    switch (m_gameState) {
    case SpaceGame::GameState::Initialize:
		m_gameState = GameState::Title;
        break;
    case SpaceGame::GameState::Title:
        if (Cpain::getEngine().getInput().getKeyPressed(SDL_SCANCODE_SPACE)) {
			m_gameState = GameState::StartGame;
        }
        break;
	case SpaceGame::GameState::StartGame:
        m_score = 0;
		m_lives = 3;
		m_gameState = GameState::StartLevel;
        break;
    case SpaceGame::GameState::StartLevel:

        {
            // Player
            std::shared_ptr<Cpain::Model> model = std::make_shared<Cpain::Model>(Cpain::playerPoints, Cpain::vec3{ 0.0f, 1.0f, 0.0f });
            Cpain::Transform transform{ Cpain::vec2{ Cpain::getEngine().getRenderer().getWidth() * 1.0f, Cpain::getEngine().getRenderer().getHeight() * 1.0f}, 0, 10.0f };
            std::unique_ptr<Player> player = std::make_unique<Player>(transform, model);
            player->damping = 3.0f;
            player->shipSpeed = 300.0f;
            player->rotationSpeed = 180.0f;
            player->name = "Player";
            player->tag = "Player";

            m_scene->addActor(move(player));
			m_gameState = GameState::Playing;
        }

        break;
    case SpaceGame::GameState::Playing:
		m_enemySpawnTimer -= deltaTime;
        if (m_enemySpawnTimer <= 0.0f) {
            m_enemySpawnTimer = 4;

            {
                std::shared_ptr<Cpain::Model> enemyModel = std::make_shared<Cpain::Model>(Cpain::enemyPoints, Cpain::vec3{ 1.0f, 0.25f, 0.0f });
                Cpain::Transform transform{ Cpain::vec2{ Cpain::getRandomFloat() * 1280, Cpain::getRandomFloat() * 1024 }, 0, 7 };
                std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, enemyModel);
                enemy->damping = 2.5f;
                enemy->speed = Cpain::getRandomFloat() * 200.0f + 50.0f;
                enemy->tag = "Enemy";

                m_scene->addActor(std::move(enemy));
            }

        }
        break;
    case SpaceGame::GameState::PlayerDied:
		m_lives--;
        if (m_lives == 0) m_gameState = GameState::EndGame;
		else m_gameState = GameState::StartLevel;
        break;
    case SpaceGame::GameState::EndGame:
        break;
    default:
        break;
    }
	m_scene->update(Cpain::getEngine().getTime().getDeltaTime());
}

void SpaceGame::shutdown(){

}

void SpaceGame::draw(){
	m_scene->draw(Cpain::getEngine().getRenderer());
}
