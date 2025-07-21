#include "Core/Random.h"

#include "Framework/Scene.h"

#include "Math/Vector2.h"

#include "Renderer/Model.h"

#include "Player.h"

#include "SpaceGame.h"

#include <vector>
#include <memory>

bool SpaceGame::initialize(){
    std::unique_ptr<Cpain::CScene::Scene> m_scene = std::make_unique<Cpain::CScene::Scene>();

    std::vector<Cpain::CVec2::vec2> points{
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

    std::shared_ptr<Cpain::Model> model = std::make_shared<Cpain::Model>(points, Cpain::CVec3::vec3{ 0, 1, 0 });

    for (int i = 0; i < 50; i++) {
        Cpain::Transform transform

        { Cpain::CVec2::vec2(Cpain::CRandom::getRandomFloat() * 1280, Cpain::CRandom::getRandomFloat() * 1020),
            Cpain::CRandom::getRandomFloat() * 360,
            Cpain::CRandom::getRandomFloat() * 10 };

        std::unique_ptr<Player> player = std::make_unique<Player>(transform, model);
        m_scene->addActor(std::move(player));
    }

    return true;
}

void SpaceGame::update(){

}

void SpaceGame::shutdown(){

}

void SpaceGame::draw(){
   
}
