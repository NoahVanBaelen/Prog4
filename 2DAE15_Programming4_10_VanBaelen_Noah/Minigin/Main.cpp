//#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "FPSComponent.h"
#include "MoveInCircleComponent.h"
#include "Controller.h"
#include "ScoreComponent.h"
#include "LiveComponent.h"
#include "GridComponent.h"
#include "Input.h"

#include <iostream>
#include <rapidjson/rapidjson.h>
#include "rapidjson/document.h"
#include "rapidjson/stream.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/filereadstream.h"
#include <fstream>

#include "UIDisplay.h"
#include "Logging_Sound_System.h"
#include "Servicelocator.h"
#include "SDL_Sound_System.h"

#include "BombComponent.h"
#include "PlayerStatsComponent.h"

#include "CollisionComponent.h"
#include "CollisionServicelocator.h"
#include "Logging_Collision_System.h"
#include "NVB_Collision_System.h"

#include "ItemComponent.h"
#include "TriggerComponent.h"
void load()
{
	//Collision
	CollisionServicelocator::register_collision_system(std::make_unique<NVB_Collision_System>());//need to be created one time at the start
	auto& collisionSystem = CollisionServicelocator::get_collision_system();
	collisionSystem.SetUpComleteMessage();

	const float textureScale{ 1.3f };
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go_Grid = std::make_shared<dae::GameObject>();
	go_Grid->AddComponent<RenderComponent>();
	go_Grid->GetComponent<RenderComponent>()->SetTexture("Resources/Bomberman_Playfield.png");
	go_Grid->GetComponent<RenderComponent>()->ScaleTexture(textureScale);
	scene.Add(go_Grid);

	const float tileWidth{ (go_Grid->GetComponent<RenderComponent>()->GetTextureWidth() * textureScale)/ 31.f};
	const float tileHeight{ (go_Grid->GetComponent<RenderComponent>()->GetTextureHeight() * textureScale) / 13.f };

	go_Grid->AddComponent<GridComponent>();
	go_Grid->GetComponent<GridComponent>()->InitializeGrid(13, 31, tileWidth, tileHeight);
	go_Grid->GetComponent<GridComponent>()->InitializeLevel("..\\/Data/Resources/Level3_Layout.json", textureScale);

	////WEEK 5 & 6
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);

	auto go_BomberManScoreCounter = std::make_shared<dae::GameObject>();
	go_BomberManScoreCounter->AddComponent<RenderComponent>();
	go_BomberManScoreCounter->AddComponent<TextComponent>();
	go_BomberManScoreCounter->GetComponent<TextComponent>()->SetColor(SDL_Color{ 0, 255, 0 });
	go_BomberManScoreCounter->GetComponent<TextComponent>()->SetFont(font);
	go_BomberManScoreCounter->GetComponent<TextComponent>()->SetText("Points: 0");
	go_BomberManScoreCounter->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3(0.f, 100.f, 0.f));
	scene.Add(go_BomberManScoreCounter);

	auto go_BomberManLiveCounter = std::make_shared<dae::GameObject>();
	go_BomberManLiveCounter->AddComponent<RenderComponent>();
	go_BomberManLiveCounter->AddComponent<TextComponent>();
	go_BomberManLiveCounter->GetComponent<TextComponent>()->SetColor(SDL_Color{ 0, 255, 0 });
	go_BomberManLiveCounter->GetComponent<TextComponent>()->SetFont(font);
	go_BomberManLiveCounter->GetComponent<TextComponent>()->SetText("Lives: 3");
	go_BomberManLiveCounter->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3(0.f, 130.f, 0.f));
	scene.Add(go_BomberManLiveCounter);

	auto go_FPS = std::make_shared<dae::GameObject>();
	go_FPS->AddComponent<RenderComponent>();
	go_FPS->AddComponent<TextComponent>();
	go_FPS->GetComponent<TextComponent>()->SetColor(SDL_Color{ 255, 0, 255 });
	go_FPS->GetComponent<TextComponent>()->SetFont(font);
	go_FPS->AddComponent<FPSComponent>();
	scene.Add(go_FPS);

	int playerCollisionGroupID{ 1 };
	std::vector<int> playerCanCollideWithIDs{ 2,3 };
	auto go_BomberMan = std::make_shared<dae::GameObject>();
	go_BomberMan->AddComponent<RenderComponent>();
	go_BomberMan->GetComponent<RenderComponent>()->SetTexture("Resources/Bomberman.png");
	go_BomberMan->GetComponent<RenderComponent>()->ScaleTexture(textureScale);
	go_BomberMan->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3(tileWidth, tileHeight, 0.f));

	go_BomberMan->AddComponent<CollisionComponent>()->SetUpCollisionBox(static_cast<int>(tileWidth/2), static_cast<int>(tileHeight/2), playerCollisionGroupID, playerCanCollideWithIDs);

	go_BomberMan->AddComponent<ScoreComponent>();
	go_BomberMan->GetComponent<ScoreComponent>()->AddObserver(new UIDisplay{ go_BomberManScoreCounter.get() });
	go_BomberMan->AddComponent<LiveComponent>();
	go_BomberMan->GetComponent<LiveComponent>()->SetRespawn(glm::vec3(tileWidth, tileHeight, 0.f));
	go_BomberMan->GetComponent<LiveComponent>()->AddObserver(new UIDisplay{ go_BomberManLiveCounter.get() });
	go_BomberMan->AddComponent<PlayerStatsComponent>()->SetStartPosition(glm::vec2(tileWidth, tileHeight));

	scene.Add(go_BomberMan);

	//SOUND
	Servicelocator::register_sound_system(std::make_unique<SDL_Sound_System>());
	auto& ss = Servicelocator::get_sound_system();
	ss.OpenAudio();
	int placeBombSoundID = ss.AddSound("..\\/Data/Resources/Bomberman_PlaceBomb.wav");
	int explosionsSoundID = ss.AddSound("..\\/Data/Resources/Bomberman_Explosion.wav");

	//INPUT
	auto& input = Input::GetInstance();
	int numController1 = input.AddController();
	//int numController2 = input.AddController();
	//Input Player 1
	input.AddCommand(numController1, Controller::ControllerButton::DPadUp, Input::ButtonLogic::Pressed, new MoveCommand{ go_BomberMan.get(),glm::vec3(0.f,-1.f,0.f) });
	input.AddCommand(numController1, Controller::ControllerButton::DPadDown, Input::ButtonLogic::Pressed, new MoveCommand{ go_BomberMan.get(),glm::vec3(0.f,1.f,0.f) });
	input.AddCommand(numController1, Controller::ControllerButton::DPadRight, Input::ButtonLogic::Pressed, new MoveCommand{ go_BomberMan.get(),glm::vec3(1.f,0.f,0.f) });
	input.AddCommand(numController1, Controller::ControllerButton::DPadLeft, Input::ButtonLogic::Pressed, new MoveCommand{ go_BomberMan.get(),glm::vec3(-1.f,0.f,0.f) });
	input.AddCommand(numController1, Controller::ControllerButton::ButtonRight, Input::ButtonLogic::Down, new SpawnBombCommand{go_BomberMan,go_Grid,static_cast<int>(tileWidth),static_cast<int>(tileHeight),placeBombSoundID,explosionsSoundID});
	input.AddCommand(numController1, Controller::ControllerButton::ButtonBottom, Input::ButtonLogic::Down, new DetonateBombCommand{ go_BomberMan });

	//Controls
	std::cout << "\nMove Player 1 with controller DPad & Player 2 with Keyboard WASD\n";
	std::cout << "To Place Bombs press on the B button on the controller (XBOX) - Placing & Exploding bombs make sound\n";
	std::cout << "To Detonate Bombs press on the A button on the controller (XBOX) \n";
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);

	//Close Audio
	auto& ss = Servicelocator::get_sound_system();
	ss.CloseAudio();

    return 0;
}