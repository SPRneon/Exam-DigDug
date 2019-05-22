#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int dae::Scene::idCounter = 0;

dae::Scene::Scene(const std::string& name) : mName(name) {}


void dae::Scene::Add(const std::shared_ptr<GameObject>& object)
{
	mObjects.push_back(object);
	object->SetScene(shared_from_this());
}

void dae::Scene::Remove(const std::shared_ptr<GameObject>& object)
{
	auto it = std::find(mObjects.begin(), mObjects.end(),object);
	if(it != mObjects.end())
	{
		mObjects.erase(it);
	}
}



void dae::Scene::RootInitialize()
{
	Initialize();

	for(auto gameObject : mObjects)
	{
		gameObject->Initialize();
	}
}


void dae::Scene::RootUpdate()
{
	Update();

	for(auto gameObject : mObjects)
	{
		gameObject->Update();
	}

	PostUpdate();

}

void dae::Scene::RootDraw()
{
	Draw();

	for (const auto gameObject : mObjects)
	{
		gameObject->Draw();
	}

	PostDraw();
}


