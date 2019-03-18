#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "Base/InputManager.h"
#include "Base/SceneManager.h"
#include "Graphics/Renderer.h"
#include "Content/ResourceManager.h"
#include "Base/GameTime.h"
#include <SDL.h>
#include "Scenegraph/TextObject.h"
#include "Scenegraph/GameObject.h"
#include "Scenegraph/Scene.h"
#include "Components/TextComponent.h"
#include "Game/FPSScene.h"


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
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	SceneManager::GetInstance().CreateScene<FPSScene>("Demo");
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		
		auto t = std::chrono::high_resolution_clock::now();
		auto& gameTime = GameTime::GetInstance();
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		while (doContinue)
		{
			doContinue = input.ProcessInput();

			gameTime.Update();
			sceneManager.Update();
			renderer.Render();

			t += std::chrono::milliseconds(msPerFrame);
			std::this_thread::sleep_until(t);
		}
	}

	Cleanup();
}
