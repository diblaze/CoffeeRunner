cmake_minimum_required(VERSION 3.6)
project(TDP005)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/components/Collision.cc
        src/components/Collision.h
        src/components/Moveable.cc
        src/components/Moveable.h
        src/components/ImmobileObstacle.cc
        src/components/ImmobileObstacle.h
        src/components/PlayerComponent.cc
        src/components/PlayerComponent.h
        src/components/PlayerController.cc
        src/components/PlayerController.h
        src/interfaces/IComponent.cc
        src/interfaces/IComponent.h
        src/interfaces/IScene.cc
        src/interfaces/IScene.h
        src/objects/Object.cc
        src/objects/Object.h
        src/objects/ObjectFactory.cc
        src/objects/ObjectFactory.h
        src/scenes/GameScene.cc
        src/scenes/GameScene.h
        src/scenes/MenuScene.cc
        src/scenes/MenuScene.h
        src/Engine.cc
        src/Engine.h
        src/Game.cc
        src/Game.h
        src/World.cc
        src/World.h
        main.cc src/components/SlipperyObstacle.cc src/components/SlipperyObstacle.h src/components/AIStudent.cc src/components/AIStudent.h src/utils/Mathf.cc src/utils/Mathf.h src/scenes/EndScene.cc src/scenes/EndScene.h src/TextureManager.cc src/TextureManager.h)

add_executable(TDP005 ${SOURCE_FILES})
target_link_libraries(TDP005 sfml-graphics sfml-window sfml-system)
