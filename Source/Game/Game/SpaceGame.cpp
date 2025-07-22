#include "Core/Random.h"

#include "Framework/Scene.h"

#include "Math/Vector2.h"

#include "Renderer/Model.h"

#include "Player.h"

#include "SpaceGame.h"

#include <vector>
#include <memory>

bool SpaceGame::initialize(){
	m_scene = std::make_unique<Cpain::Scene>();

    std::vector<Cpain::vec2> points{
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

    std::shared_ptr<Cpain::Model> model = std::make_shared<Cpain::Model>(points, Cpain::vec3{ 0, 1, 0 });

    return true;
}

void SpaceGame::update(){

}

void SpaceGame::shutdown(){

}

void SpaceGame::draw(){
   
}
