#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameTime.h"
#include <cassert>


void dae::SceneManager::Update()
{
	assert(m_pActiveScene != nullptr);
	m_pActiveScene->RootUpdate();
	/*for(auto scene : mScenes)
	{
		scene->RootUpdate();
	}*/
	
}

void dae::SceneManager::Draw()
{
	assert(m_pActiveScene != nullptr);
	
	m_pActiveScene->RootDraw();
	/*for (const auto scene : mScenes)
	{
		scene->RootDraw();
	}*/
}

void dae::SceneManager::CleanUp()
{
	m_pActiveScene.reset();
	for(auto& scene : mScenes)
	{
		scene->CleanUp();
		scene.reset();
	}
	mScenes.clear();
}

void dae::SceneManager::GoToNextScene()
{
	m_pActiveScene->RootCleanUp();
	for(size_t i = 0; i < mScenes.size(); ++i)
	{
		if(mScenes[i] == m_pActiveScene)
		{
			if(i == mScenes.size()-1)
				m_pActiveScene = mScenes[0];
			else
				m_pActiveScene = mScenes[i+1];

			m_pActiveScene->RootInitialize();
			return;
		}

	}

	
}

void dae::SceneManager::SetActiveScene(std::string sceneName)
{
	for(size_t i = 0; i < mScenes.size(); ++i)
	{
		if(mScenes[i]->mName == sceneName)
		{
			
			m_pActiveScene = mScenes[i];
			m_pActiveScene->RootInitialize();
			return;
		}

	}
}




