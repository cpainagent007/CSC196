#include "Core/Random.h"

#include "Framework/Scene.h"

#include "Math/Vector2.h"

#include "Renderer/Model.h"
#include "Renderer/Renderer.h"

#include "Engine.h"

#include "Player.h"

#include "SpaceGame.h"
#include "Enemy.h"

#include <vector>
#include <memory>

bool SpaceGame::initialize(){
	m_scene = std::make_unique<Cpain::Scene>();

    std::vector<Cpain::vec2> points{
        { 4, 0 },
        { -4, -4 },
        { -3, 0 },
        { -4, 3 },
        { 4, 0 },
    };

    std::vector<Cpain::vec2> enemyPoints{
       {-1, 4},
       {-1, 2},
       {-1, 1},
       {0, 2},
       {1, 1},
       {1, 2},
       {1, 4},
       {2, 1},
       {2, -2},
       {4, 0},
       {1, 0},
       {0, -2},
       {-1, 0},
       {-4, 0},
       {-2, -2},
       {0, -2},
       {-2, -4},
       {-2, -2},
       {2, -2},
       {2, -4},
       {0, -2},
       {-2, -2},
       {-2, 1},
       {-1, 4}
    };

    // Player
    std::shared_ptr<Cpain::Model> model = std::make_shared<Cpain::Model>(points, Cpain::vec3{ 0.0f, 1.0f, 0.0f });
    Cpain::Transform transform{ Cpain::vec2{ Cpain::getEngine().getRenderer().getWidth() * 1.0f, Cpain::getEngine().getRenderer().getHeight() * 1.0f}, 0, 10.0f };
	std::unique_ptr<Player> player = std::make_unique<Player>(transform, model);
    player->damping = 1.5f;
	player->shipSpeed = 200.0f;
    player->rotationSpeed = 180.0f;
	player->name = "Player";

	m_scene->addActor(move(player));

    // Enemies
    std::shared_ptr<Cpain::Model> enemyModel = std::make_shared<Cpain::Model>(enemyPoints, Cpain::vec3{ 1.0f, 0.25f, 0.0f });
    for (int i = 0; i < 10; i++) {
        Cpain::Transform transform{ Cpain::vec2{ Cpain::getRandomFloat() * 1280, Cpain::getRandomFloat() * 1024 }, 0, 10 };
        std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, enemyModel);
		enemy->damping = 1.5f;

        m_scene->addActor(std::move(enemy));
    }
    
    return true;
}

void SpaceGame::update(){
	m_scene->update(Cpain::getEngine().getTime().getDeltaTime());
}

void SpaceGame::shutdown(){

}

void SpaceGame::draw(){
	m_scene->draw(Cpain::getEngine().getRenderer());
}
