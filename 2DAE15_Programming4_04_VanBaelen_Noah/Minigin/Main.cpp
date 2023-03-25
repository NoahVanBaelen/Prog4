#include <SDL.h>

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
#include "InputComponent.h"
#include "Controller.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go_BackGround = std::make_shared<dae::GameObject>();
	go_BackGround->AddComponent<RenderComponent>();
	go_BackGround->GetComponent<RenderComponent>()->SetTexture("background.tga");
	scene.Add(go_BackGround);

	auto go_Logo = std::make_shared<dae::GameObject>();
	go_Logo->AddComponent<RenderComponent>();
	go_Logo->GetComponent<RenderComponent>()->SetTexture("logo.tga");
	go_Logo->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3(216.f, 180.f, 0.f));
	scene.Add(go_Logo);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto go_Text = std::make_shared<dae::GameObject>();
	go_Text->AddComponent<TextComponent>();
	go_Text->AddComponent<RenderComponent>();
	go_Text->GetComponent<TextComponent>()->SetText("Programming 4 Assignment");
	go_Text->GetComponent<TextComponent>()->SetFont(font);
	go_Text->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3(80.f, 20.f, 0));
	scene.Add(go_Text);

	auto go_FPS = std::make_shared<dae::GameObject>();
	go_FPS->AddComponent<FPSComponent>();
	go_FPS->AddComponent<TextComponent>();
	go_FPS->AddComponent<RenderComponent>();
	go_FPS->GetComponent<TextComponent>()->SetFont(font);
	go_FPS->GetComponent<TextComponent>()->SetColor(SDL_Color{ 0, 255, 0 });
	scene.Add(go_FPS);

	//WEEK3
	/*auto go_BomberMan = std::make_shared<dae::GameObject>();
	go_BomberMan->AddComponent<RenderComponent>();
	go_BomberMan->GetComponent<RenderComponent>()->SetTexture("BomberMan.png");
	go_BomberMan->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3(320.f, 280.f, 0.f));
	go_BomberMan->AddComponent<MoveInCircleComponent>();
	go_BomberMan->GetComponent<MoveInCircleComponent>()->SetRadius(30.f);
	go_BomberMan->GetComponent<MoveInCircleComponent>()->SetMoveCounterClockWise(true);
	go_BomberMan->GetComponent<MoveInCircleComponent>()->SetSpeed(0.3f);
	scene.Add(go_BomberMan);

	auto go_Bomb = std::make_shared<dae::GameObject>();
	go_Bomb->AddComponent<RenderComponent>();
	go_Bomb->GetComponent<RenderComponent>()->SetTexture("Bomb.png");
	go_Bomb->AddComponent<MoveInCircleComponent>();
	go_Bomb->GetComponent<MoveInCircleComponent>()->SetRadius(30.f);
	go_Bomb->GetComponent<MoveInCircleComponent>()->SetSpeed(0.3f);
	go_Bomb->SetParent(go_BomberMan.get(), false);

	go_BomberMan->GetChildAt(0);

	scene.Add(go_Bomb);*/

	//WEEK5
	float moveSpeed{ 3.f };

	auto go_BomberMan = std::make_shared<dae::GameObject>();
	go_BomberMan->AddComponent<RenderComponent>();
	go_BomberMan->GetComponent<RenderComponent>()->SetTexture("BomberMan.png");
	go_BomberMan->GetComponent<TransformComponent>()->SetLocalPosition(glm::vec3(320.f, 280.f, 0.f));
	go_BomberMan->AddComponent<InputComponent>();
	//go_BomberMan->GetComponent<InputComponent>()->SetCommand(Controller::ControllerButton::DPadUp, Input::ButtonLogic::Pressed, new MoveCommand{go_BomberMan,moveSpeed,glm::vec3(0.f,1.f,0.f)});
	//go_BomberMan->GetComponent<InputComponent>()->SetCommand(Controller::ControllerButton::DPadDown, Input::ButtonLogic::Pressed, new MoveCommand{ go_BomberMan,moveSpeed,glm::vec3(0.f,-1.f,0.f) });
	//go_BomberMan->GetComponent<InputComponent>()->SetCommand(Controller::ControllerButton::DPadRight, Input::ButtonLogic::Pressed, new MoveCommand{ go_BomberMan,moveSpeed,glm::vec3(1.f,0.f,0.f) });
	//go_BomberMan->GetComponent<InputComponent>()->SetCommand(Controller::ControllerButton::DPadLeft, Input::ButtonLogic::Pressed, new MoveCommand{ go_BomberMan,moveSpeed,glm::vec3(-1.f,0.f,0.f) });
	scene.Add(go_BomberMan);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}