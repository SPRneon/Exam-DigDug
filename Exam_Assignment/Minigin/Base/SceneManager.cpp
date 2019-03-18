#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scenegraph\Scene.h"



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

//template  <class T>
//dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
//{
//	const auto scene = std::shared_ptr<Scene>(new Scene(name));
//
//	const auto it = std::find(mScenes.begin(), mScenes.end(), scene);
//
//
//	if(it == mScenes.end())
//	{
//		mScenes.push_back(scene);
//		scene->RootInitialize();
//	
//	
//	}
//	return *scene;
//}
