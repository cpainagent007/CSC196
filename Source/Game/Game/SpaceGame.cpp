#include "SpaceGame.h"
#include "Framework/Scene.h"
#include "Core/Random.h"
#include "Math/Vector2.h"
#include "Renderer/Model.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "GameData.h"

#include <vector>

bool SpaceGame::initialize()
{
    m_scene = std::make_unique<Cpain::Scene>();

    return true;
}

void SpaceGame::update(float deltaTime)
{
    switch (m_gameState)
    {
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
        // create player
        std::shared_ptr<Cpain::Model> model = std::make_shared<Cpain::Model>(Cpain::playerPoints, Cpain::vec3{ 0.0f, 0.4f, 1.0f });
        Cpain::Transform transform{ Cpain::vec2{ Cpain::getEngine().getRenderer().getWidth() * 0.5f, Cpain::getEngine().getRenderer().getHeight() * 0.5f }, 0, 5 };
        std::unique_ptr<Player> player = std::make_unique<Player>(transform, model);
        player->shipSpeed = 1500.0f;
        player->rotationSpeed = 180.0f;
        player->damping = 1.5f;
        player->name = "player";
        player->tag = "player";

        m_scene->addActor(std::move(player));
        m_gameState = GameState::Playing;
    }
    break;
    case SpaceGame::GameState::Playing:
        m_enemySpawnTimer -= deltaTime;
        if (m_enemySpawnTimer <= 0) {
            m_enemySpawnTimer = 4;

            // create enemies
            std::shared_ptr<Cpain::Model> enemyModel = std::make_shared<Cpain::Model>(Cpain::enemyPoints, Cpain::vec3{ Cpain::getRandomFloat(), Cpain::getRandomFloat(), Cpain::getRandomFloat() });
            Cpain::Transform transform{ Cpain::vec2{ Cpain::getRandomFloat() * Cpain::getEngine().getRenderer().getWidth(), Cpain::getRandomFloat() * Cpain::getEngine().getRenderer().getHeight() }, 0, 10 };
            std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, enemyModel);
            enemy->damping = 0.2f;
            enemy->speed = (Cpain::getRandomFloat() * 800) + 500;
            enemy->tag = "enemy";
            m_scene->addActor(std::move(enemy));
        }

        break;
    case SpaceGame::GameState::PlayerDied:
        m_lives--;
        if (m_lives == 0) m_gameState = GameState::EndGame;
        else {
            m_gameState = GameState::StartLevel;
        }
        break;
    case SpaceGame::GameState::EndGame:
        break;
    default:
        break;
    }

    m_scene->update(Cpain::getEngine().getTime().getDeltaTime());
}

void SpaceGame::draw()
{
    m_scene->draw(Cpain::getEngine().getRenderer());
}

void SpaceGame::shutdown()
{
    //
}