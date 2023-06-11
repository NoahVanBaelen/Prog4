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
#include "GameState.h"
#include "CommandKeeper.h"

void load()
{
	//Collision
	CollisionServicelocator::register_collision_system(std::make_unique<NVB_Collision_System>());//need to be created one time at the start
	auto& collisionSystem = CollisionServicelocator::get_collision_system();
	collisionSystem.SetUpComleteMessage();

	const float textureScale{ 1.3f };
	auto& sceneSinglePlayer = dae::SceneManager::GetInstance().CreateScene("SinglePlayer");

	auto go_Grid = std::make_shared<dae::GameObject>();
	go_Grid->AddComponent<RenderComponent>();
	go_Grid->GetComponent<RenderComponent>()->SetTexture("Resources/Bomberman_Playfield.png");
	go_Grid->GetComponent<RenderComponent>()->ScaleTexture(textureScale);
	sceneSinglePlayer.Add(go_Grid);

	const float tileWidth{ (go_Grid->GetComponent<RenderComponent>()->GetTextureWidth() * textureScale) / 31.f };
	const float tileHeight{ (go_Grid->GetComponent<RenderComponent>()->GetTextureHeight() * textureScale) / 13.f };

	go_Grid->AddComponent<GridComponent>();
	go_Grid->GetComponent<GridComponent>()->InitializeGrid(13, 31, tileWidth, tileHeight);
	go_Grid->GetComponent<GridComponent>()->AddLevel("..\\/Data/Resources/Level1_Layout.json");
	go_Grid->GetComponent<GridComponent>()->AddLevel("..\\/Data/Resources/Level2_Layout.json");
	go_Grid->GetComponent<GridComponent>()->AddLevel("..\\/Data/Resources/Level3_Layout.json");
	go_Grid->GetComponent<GridComponent>()->GoToLevel(0);

	////FPS
	auto font = dae::ResourceManager::GetInstance().LoadFont("Silkscreen-Bold.ttf", 20);
	//font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);

	auto go_FPS = std::make_shared<dae::GameObject>();
	go_FPS->AddComponent<RenderComponent>();
	go_FPS->AddComponent<TextComponent>();
	go_FPS->GetComponent<TextComponent>()->SetColor(SDL_Color{ 255, 0, 255 });
	go_FPS->GetComponent<TextComponent>()->SetFont(font);
	go_FPS->AddComponent<FPSComponent>();
	sceneSinglePlayer.Add(go_FPS);

	//PLAYER
	int playerCollisionGroupID{ 1 };
	std::vector<int> playerCanCollideWithIDs{ 2,3 };
	auto go_BomberMan = std::make_shared<dae::GameObject>();
	go_BomberMan->AddComponent<RenderComponent>();
	go_BomberMan->GetComponent<RenderComponent>()->SetTexture("Resources/Bomberman.png");
	go_BomberMan->GetComponent<RenderComponent>()->ScaleTexture(textureScale);
	go_BomberMan->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3(tileWidth, tileHeight, 0.f));

	go_BomberMan->AddComponent<CollisionComponent>()->SetUpCollisionBox(static_cast<int>(tileWidth / 2), static_cast<int>(tileHeight / 2), playerCollisionGroupID, playerCanCollideWithIDs);

	//go_BomberMan->AddComponent<ScoreComponent>();
	//go_BomberMan->AddComponent<LiveComponent>();
	//go_BomberMan->GetComponent<LiveComponent>()->SetRespawn(glm::vec3(tileWidth, tileHeight, 0.f));
	go_BomberMan->AddComponent<PlayerStatsComponent>()->SetStartPosition(glm::vec2(tileWidth, tileHeight));

	sceneSinglePlayer.Add(go_BomberMan);

	//SOUND
	Servicelocator::register_sound_system(std::make_unique<SDL_Sound_System>());
	auto& ss = Servicelocator::get_sound_system();
	ss.OpenAudio();
	int placeBombSoundID = ss.AddSound("..\\/Data/Resources/Bomberman_PlaceBomb.wav");
	int explosionsSoundID = ss.AddSound("..\\/Data/Resources/Bomberman_Explosion.wav");

	//MainMenu Scene
	auto& sceneMainScreen = dae::SceneManager::GetInstance().CreateScene("MainMenu");

	auto go_BackGround = std::make_shared<dae::GameObject>();
	go_BackGround->AddComponent<RenderComponent>()->SetTexture("Resources/Logo.png");
	go_BackGround->GetComponent<RenderComponent>()->ScaleTexture(1.5f);
	go_BackGround->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3{ 150,20,0 });
	sceneMainScreen.Add(go_BackGround);

	auto go_TextSinglePlayer = std::make_shared<dae::GameObject>();
	go_TextSinglePlayer->AddComponent<RenderComponent>();
	go_TextSinglePlayer->AddComponent<TextComponent>()->SetFont(font);
	go_TextSinglePlayer->GetComponent<TextComponent>()->SetText("Single Player");
	go_TextSinglePlayer->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3{ 215,280,0 });
	sceneMainScreen.Add(go_TextSinglePlayer);

	auto go_TextMultiPlayer = std::make_shared<dae::GameObject>();
	go_TextMultiPlayer->AddComponent<RenderComponent>();
	go_TextMultiPlayer->AddComponent<TextComponent>()->SetFont(font);
	go_TextMultiPlayer->GetComponent<TextComponent>()->SetText("Co-Op");
	go_TextMultiPlayer->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3{ 275,320,0 });
	sceneMainScreen.Add(go_TextMultiPlayer);

	auto go_TextVersus = std::make_shared<dae::GameObject>();
	go_TextVersus->AddComponent<RenderComponent>();
	go_TextVersus->AddComponent<TextComponent>()->SetFont(font);
	go_TextVersus->GetComponent<TextComponent>()->SetText("Versus");
	go_TextVersus->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3{ 265,360,0 });
	sceneMainScreen.Add(go_TextVersus);

	auto go_Icon = std::make_shared<dae::GameObject>();
	go_Icon->AddComponent<RenderComponent>()->SetTexture("Resources/Bomberman.png");
	go_Icon->GetComponent<RenderComponent>()->ScaleTexture(2.f);
	go_Icon->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3{ 180,275,0 });
	sceneMainScreen.Add(go_Icon);

	std::vector<glm::vec2> iconPositions{};
	iconPositions.push_back(glm::vec2{ 180,275 });
	iconPositions.push_back(glm::vec2{ 240,315 });
	iconPositions.push_back(glm::vec2{ 230,355 });

	//INPUT
	auto& input = Input::GetInstance();
	int numController1 = input.AddController();
	//int numController2 = input.AddController();

	//Input Menu
	std::vector<std::pair<int, std::shared_ptr<CommandKeeper>>> m_CommandVector{};
	m_CommandVector.push_back(std::make_pair(0, std::make_shared<CommandKeeper>(new MoveInListDownCommand{ go_Icon, iconPositions },Input::ButtonLogic::Down,Controller::ControllerButton::DPadDown,numController1)));
	m_CommandVector.push_back(std::make_pair(0, std::make_shared<CommandKeeper>( new MoveInListUpCommand{ go_Icon, iconPositions },Input::ButtonLogic::Down,Controller::ControllerButton::DPadUp,numController1 )));
	m_CommandVector.push_back(std::make_pair(0, std::make_shared<CommandKeeper>( new SelectModeCommand{go_Icon, static_cast<int>(iconPositions[0].y),static_cast<int>(iconPositions[1].y),static_cast<int>(iconPositions[2].y) }
											,Input::ButtonLogic::Up,Controller::ControllerButton::ButtonRight,numController1 )));


	//Input Player 1
	m_CommandVector.push_back(std::make_pair(1, std::make_shared<CommandKeeper>(new MoveCommand{ go_BomberMan.get(),glm::vec3(0.f,-1.f,0.f) }, Input::ButtonLogic::Pressed, Controller::ControllerButton::DPadUp, numController1)));
	m_CommandVector.push_back(std::make_pair(1, std::make_shared<CommandKeeper>(new MoveCommand{ go_BomberMan.get(),glm::vec3(0.f,1.f,0.f) }, Input::ButtonLogic::Pressed, Controller::ControllerButton::DPadDown, numController1)));
	m_CommandVector.push_back(std::make_pair(1, std::make_shared<CommandKeeper>(new MoveCommand{ go_BomberMan.get(),glm::vec3(1.f,0.f,0.f) }, Input::ButtonLogic::Pressed, Controller::ControllerButton::DPadRight, numController1)));
	m_CommandVector.push_back(std::make_pair(1, std::make_shared<CommandKeeper>(new MoveCommand{ go_BomberMan.get(),glm::vec3(-1.f,0.f,0.f) }, Input::ButtonLogic::Pressed, Controller::ControllerButton::DPadLeft, numController1)));
	m_CommandVector.push_back(std::make_pair(1, std::make_shared<CommandKeeper>(new SpawnBombCommand{ go_BomberMan,go_Grid,static_cast<int>(tileWidth),static_cast<int>(tileHeight),placeBombSoundID,explosionsSoundID }, 
											Input::ButtonLogic::Down, Controller::ControllerButton::ButtonRight, numController1)));
	m_CommandVector.push_back(std::make_pair(1, std::make_shared<CommandKeeper>(new DetonateBombCommand{ go_BomberMan }, Input::ButtonLogic::Down, Controller::ControllerButton::ButtonBottom, numController1)));


	m_CommandVector.push_back(std::make_pair(1, std::make_shared<CommandKeeper>(new MoveCommand{ go_BomberMan.get(),glm::vec3(0.f,-1.f,0.f) }, Input::ButtonLogic::Pressed, SDL_SCANCODE_W, numController1)));
	m_CommandVector.push_back(std::make_pair(1, std::make_shared<CommandKeeper>(new MoveCommand{ go_BomberMan.get(),glm::vec3(0.f,1.f,0.f) }, Input::ButtonLogic::Pressed, SDL_SCANCODE_S, numController1)));
	m_CommandVector.push_back(std::make_pair(1, std::make_shared<CommandKeeper>(new MoveCommand{ go_BomberMan.get(),glm::vec3(1.f,0.f,0.f) }, Input::ButtonLogic::Pressed, SDL_SCANCODE_D, numController1)));
	m_CommandVector.push_back(std::make_pair(1, std::make_shared<CommandKeeper>(new MoveCommand{ go_BomberMan.get(),glm::vec3(-1.f,0.f,0.f) }, Input::ButtonLogic::Pressed, SDL_SCANCODE_A, numController1)));
	//Controls
	std::cout << "\nMove Player 1 with controller DPad & Player 2 with Keyboard WASD\n";
	std::cout << "To Place Bombs press on the B button on the controller (XBOX) - Placing & Exploding bombs make sound\n";
	std::cout << "To Detonate Bombs press on the A button on the controller (XBOX) \n";


	//SetActiveScene
	dae::SceneManager::GetInstance().SetState(std::make_shared<MainMenuState>(dae::SceneManager::GetInstance().GetSceneByName("MainMenu").get(),m_CommandVector));
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);

	//Close Audio
	auto& ss = Servicelocator::get_sound_system();
	ss.CloseAudio();

    return 0;
}