#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"



void dae::SceneManager::Update()
{
	for(auto scene : mScenes)
	{
		scene->RootUpdate();
	}
}

void dae::SceneManager::Draw()
{
	for (const auto scene : mScenes)
	{
		scene->RootDraw();
	}
}

void dae::SceneManager::CleanUp()
{
	/*for(auto scene : mScenes)
		delete &scene;*/
}



