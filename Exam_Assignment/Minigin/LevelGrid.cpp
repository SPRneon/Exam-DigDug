#include "MiniginPCH.h"
#include "LevelGrid.h"
#include "GameObject.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include "glm/geometric.hpp"
#pragma warning(pop)
#include "MathHelper.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "Subject.h"
#include "Renderer.h"


//*****CELLS*********//
dae::Cell::Cell(int row, int column, bool visited,glm::vec2 pos, glm::vec2 scale, Color color)
		:m_Row(row),m_Column(column),m_Visited(visited),
		m_Scale(scale), m_Color(color), m_Position(pos)
{
	m_Center = m_Position + (m_Scale / 2.f);
	m_pGameObject = std::make_shared<GameObject>("Cell");
	m_pGameObject->GetTransform()->SetPosition(m_Position);
	m_pGameObject->GetTransform()->SetScale(m_Scale);
	auto collider = std::make_shared<ColliderComponent>(
				SDL_Rect{static_cast<int>(m_Position.x),
					static_cast<int>(m_Position.y),
					static_cast<int>(m_Scale.x),
					static_cast<int>(m_Scale.y)},
					TERRAIN,true);
	collider->SetIgnoreFlags(TERRAIN);
	collider->SetIgnoreFlags(ENEMIES);
	collider->SetIgnoreFlags(WALL);
	collider->SetIgnoreFlags(ROCK);
	m_pGameObject->AddComponent(collider);

	auto font = ResourceManager::GetInstance()->LoadFont("Lingua.otf", 12);
	auto text = std::make_shared<TextComponent>("Test",font, Colors::black);
	text->SetText(std::to_string(column) + ',' + std::to_string(row));
	text->SetNeedsUpdate(false);
	//text->SetPosition(m_Position.x,m_Position.y);
	m_pGameObject->AddComponent(text);

}


//******GRID********//
dae::LevelGrid::LevelGrid()
{
	
}


void dae::LevelGrid::Initialize(int rows, int columns, glm::vec2 pos, glm::vec2 scale)
	
{
	m_Rows = rows;
	m_Columns= columns;
	m_NrCells = (rows * columns),
	m_Pos = pos;
	m_Scale =scale;

	auto rowEdge = static_cast<int>(rows / 3);
	auto cellscale = scale;
	cellscale.x /= (m_Columns);
	cellscale.y /= (m_Rows);
	//INIT CELLS
	for(int i = 0; i < rows;++i)
	{
		std::vector<std::shared_ptr<Cell>> colVector;
		for(int j = 0; j < columns;++j)
		{
			auto cellPos = glm::vec2{pos.x  + j * cellscale.x, pos.y  + i * cellscale.y }; 
			colVector.push_back(std::make_shared<Cell>(i,j,false, cellPos,cellscale, m_GroundColors[static_cast<int>(i/rowEdge)]));
		}
		m_GridCells.push_back(colVector);
	}

	
	
}


dae::LevelGrid::~LevelGrid()
{
	//Clear all the collumns
	for(auto& row : m_GridCells)
		row.clear();
	//Clear all the rows
	m_GridCells.clear();

}

void dae::LevelGrid::CleanUp()
{
	//Clear all the collumns
	for(auto& row : m_GridCells)
	{
		for(auto& cell : row)
			cell.reset();
	}
	//Clear all the rows
	m_GridCells.clear();

}

void dae::LevelGrid::Update()
{

	for(auto& row : m_GridCells)
	{
		for(auto& col : row)
		{
			

			if(!col->m_pGameObject->GetComponent<ColliderComponent>()->IsSleeping() 
				&& col->m_pGameObject->GetComponent<ColliderComponent>()->HasCollided()  
				&& !col->m_ContainsRock)
			{
				col->m_pGameObject->GetComponent<TextComponent>()->SetColor(Colors::white);
				col->m_pGameObject->GetComponent<ColliderComponent>()->PutToSleep();
				m_pSubject->notify(std::make_shared<ScoreEvent>(10));
				col->SetVisited(true);
			}
		}
	}
}

void dae::LevelGrid::Draw()
{
	for(auto row : m_GridCells)
	{
		for(auto col : row)
		{
			if(!col->IsVisited())
				Renderer::GetInstance()->RenderSquare(col->GetPosition().x,col->GetPosition().y,col->GetScale().x,col->GetScale().y,col->GetColor(), true);
			
		}
	}
}

void dae::LevelGrid::SetRowsAndCollums(const int rows, const int columns, glm::vec2 pos, glm::vec2 scale)
{
	//Clear all the collumns
	for(auto row : m_GridCells)
		row.clear();
	//Clear all the rows
	m_GridCells.clear();

	auto rowEdge = static_cast<int>(rows / 4);
	for(int i = 0; i < rows;++i)
	{
		std::vector<std::shared_ptr<dae::Cell>> colVector;
		for(int j = 0; j < columns;++j)
		{
			colVector.push_back(std::make_shared<Cell>(i,j,false, pos,scale,m_GroundColors[i/rowEdge]));
		}
		m_GridCells.push_back(colVector);
	}
		
	m_Rows = rows;
	m_Columns = columns;
}

std::shared_ptr<dae::Cell>& dae::LevelGrid::GetCell(glm::vec2 pos)
{
	int col = (static_cast<int>(((pos.x - m_Pos.x) +0.001f )/ (m_Scale.x / m_Columns))) % m_Columns;
	int row = (static_cast<int>(((pos.y - m_Pos.y) +0.001f )/ (m_Scale.y / m_Rows))) % m_Rows;
	if(col < 0)
		col = 0;
	if(row < 0)
		row = 0;

	return GetCell(row,col);
}



void dae::LevelGrid::SetCellInactive(int row, int column)
{
	m_GridCells[row][column]->SetVisited(true);
	m_GridCells[row][column]->m_pGameObject->GetComponent<ColliderComponent>()->PutToSleep();
}

glm::vec2 dae::LevelGrid::GetPathForDir(Direction dir, glm::vec2 pos)
{
	if(!InRange(m_Pos,pos,m_Scale))
	{
		std::cout << "not in grid" << std::endl;
		return pos;
	}
	auto currCell = GetCell(pos);
	int tarRow = currCell->m_Row;
	int tarCol = currCell->m_Column;
	switch(dir)
	{
	case UP:
		if(tarRow != 0)
			tarRow--;
	break;
		case DOWN:
		if(tarRow < (m_Rows - 1))
		tarRow++;
	break;
		case LEFT:
		if(tarCol != 0)
			tarCol--;
	break;
		case RIGHT:
		if(tarCol < (m_Columns - 1))
			tarCol++;
	break;
	}

	if(tarRow == currCell->GetRow() && tarCol == currCell->m_Column)
		return GetPathForDir(IncrementDirectionCW(dir),pos);
	
	auto targetCell = GetCell(tarRow,tarCol);

	//Cant go into cell with rock
	if(targetCell->m_ContainsRock)
		return currCell->m_Center;


	//dist target-player + player-currcell
	auto dist1 = glm::distance(targetCell->m_Center, pos)+glm::distance(pos,currCell->m_Center);
	//dist target-currcell
	auto dist2 = glm::distance(targetCell->m_Center,currCell->m_Center);
	//IF PLAYER is already on the straight line between the cells
	if(std::abs(dist1-dist2) < 2.5f)
	{
		return targetCell->m_Center;
	}
	else
		return currCell->m_Center;
	
}

std::shared_ptr<dae::Cell> dae::LevelGrid::GetCellForDir(Direction dir, glm::vec2 pos)
{
	auto currCell = GetCell(pos);
	int tarRow = currCell->m_Row;
	int tarCol = currCell->m_Column;
	switch(dir)
	{
	case UP:
		if(tarRow != 0)
			tarRow--;
	break;
		case DOWN:
		if(tarRow < (m_Rows - 1))
		tarRow++;
	break;
		case LEFT:
		if(tarCol != 0)
			tarCol--;
	break;
		case RIGHT:
		if(tarCol < (m_Columns - 1))
			tarCol++;
	break;
	}

	
	
	return GetCell(tarRow,tarCol);
}

std::vector<std::pair<std::shared_ptr<dae::Cell>,dae::Direction>> dae::LevelGrid::GetNeighbourCells(std::array<Direction, 4> directionOrder, std::shared_ptr<Cell> currCel)
{
	std::vector<std::pair<std::shared_ptr<dae::Cell>,dae::Direction>> out;

	int currRow = currCel->GetRow();
	int currCol = currCel->GetCol();

	for(size_t i = 0; i < directionOrder.size();++i)
	{
		switch (directionOrder[i])
		{
		case UP:
			if(currRow != 0)
				out.push_back(std::pair<std::shared_ptr<dae::Cell>,Direction>(GetCell(currRow -1, currCol), UP));
		break;
		case DOWN:
			if(currRow != (m_Rows -1))
				out.push_back(std::pair<std::shared_ptr<dae::Cell>,Direction>(GetCell(currRow+1, currCol), DOWN));
			break;
		case LEFT:
			if(currCol != 0)
				out.push_back(std::pair<std::shared_ptr<dae::Cell>,Direction>(GetCell(currRow, currCol -1), LEFT));
			break;
		case RIGHT:
			if(currCol != (m_Columns -1))
				out.push_back(std::pair<std::shared_ptr<dae::Cell>,Direction>(GetCell(currRow, currCol+1), RIGHT));
		break;
		}
	}

	return out;
}




