#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameTime.h"
#include <SDL.h>

#include "LevelScene.h"
#include "MenuScene.h"
#include "LevelGrid.h"



bool dae::Minigin::Continue = true;

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		450,
		580,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance()->Init(window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	SceneManager::GetInstance()->CreateScene<MenuScene>("Demo");
	SceneManager::GetInstance()->SetActiveScene("Demo");
	InputAction ia{69,KeyState::Released,VK_ESCAPE,-41,XINPUT_GAMEPAD_BACK};
	InputManager::GetInstance()->AddInput(ia,std::make_shared<ExitCommand>());
	 ia ={96,KeyState::Released,VK_F1,-41,XINPUT_GAMEPAD_START};
	InputManager::GetInstance()->AddInput(ia,std::make_shared<NextSceneCommand>());

}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance()->Destroy();
	ResourceManager::DestroyInstance();
	Renderer::GetInstance()->DestroyInstance();
	InputManager::GetInstance()->CleanUp();
	InputManager::GetInstance()->DestroyInstance();
	GameTime::GetInstance()->DestroyInstance();
	SceneManager::GetInstance()->DestroyInstance();
	ColliderComponent::m_pColliderMap.clear();
	//TODO Do this in scene
	LevelGrid::GetInstance()->CleanUp();
	LevelGrid::DestroyInstance();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance()->Init("../Data/");
	InputManager::GetInstance()->Init();
	LoadGame();
	{
		auto gameTime = GameTime::GetInstance();
		gameTime->Reset();
		gameTime->Stop();
		auto renderer = Renderer::GetInstance();
		auto sceneManager = SceneManager::GetInstance();
		auto input = InputManager::GetInstance();

		//Locator::initialize();
		while (Continue)
		{
			
			//Get time in order
			gameTime->Update();
			//Handle Input
			input->ProcessInput();
			//Update scenes 
			sceneManager->Update();
			//Draw
			renderer->Render();
	
		}
	}

	Cleanup();
	_CrtDumpMemoryLeaks();
}
