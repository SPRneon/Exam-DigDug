#include "MiniginPCH.h"
#include "LevelScene.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "MathHelper.h"
#include "LevelGrid.h"
#include "GameObject.h"
#include "CommandComponent.h"


dae::LevelScene::LevelScene(const std::string & name)
	:Scene(name)
{
}

void dae::LevelScene::Initialize()
{
	//Grid
	m_pGrid = new LevelGrid(14,16,{0,0},{640/13,480/15});

	//Player
	m_pPlayer = new GameObject();
	m_pPlayer->AddComponent(std::make_shared<CommandComponent>());


}

void dae::LevelScene::Update()
{
}

void dae::LevelScene::Draw() const
{
	
	
}

void dae::LevelScene::PostDraw() const
{
	int i =5;
	for(auto row : m_pGrid->GetCells())
	{
		i += 5;
		for(auto col : row)
		{
			Renderer::GetInstance().RenderSquare(col.position.x,col.position.y,col.scale.x,col.scale.y,{UINT8(i),0,0});
		}
	}
}
