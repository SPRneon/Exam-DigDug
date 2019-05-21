#include "MiniginPCH.h"
#include "LevelGrid.h"
#include "GameObject.h"

//*****CELLS*********//
dae::Cell::Cell(int row, int column, bool visited,glm::vec2 pos, glm::vec2 scale, Color color)
		:m_Row(row),m_Column(column),m_Visited(visited),
		m_Scale(scale), m_Color(color), m_Position(pos)
{
	m_pGameObject = std::make_shared<GameObject>();
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
	m_pGameObject->AddComponent(collider);

}

//*****PILLARS******//
dae::Pillar::Pillar(glm::vec2 pos, glm::vec2 scale)
	:m_Position(pos),
	m_Scale(scale)
{
	m_pGameObject = std::make_shared<GameObject>();
	m_pGameObject->GetTransform()->SetPosition(m_Position);
	m_pGameObject->GetTransform()->SetScale(m_Scale);
	auto collider = std::make_shared<ColliderComponent>(
				SDL_Rect{static_cast<int>(m_Position.x),
					static_cast<int>(m_Position.y),
					static_cast<int>(m_Scale.x),
					static_cast<int>(m_Scale.y)},
					WALL,true);
	collider->SetIgnoreFlags(TERRAIN);
	m_pGameObject->AddComponent(collider);
}

//******GRID********//
dae::LevelGrid::LevelGrid(int rows, int columns, glm::vec2 pos, glm::vec2 scale)
	:m_Rows(rows),
	m_Columns(columns),
	m_NrCells(rows * columns)
{
	auto rowEdge = static_cast<int>(rows / 3);

	//INIT CELLS
	for(int i = 0; i < rows;++i)
	{
		std::vector<Cell> colVector;
		for(int j = 0; j < columns;++j)
		{
			auto cellPos = glm::vec2{pos.x + j * scale.x, pos.y + i * scale.y}; 
			colVector.push_back(Cell(i,j,false, cellPos,scale, m_GroundColors[static_cast<int>(i/rowEdge)]));
		}
		m_GridCells.push_back(colVector);
	}

	//INIT PILLARS
	glm::vec2 pillarScale = scale /5.f;
	for(int i = 0; i < rows +1; ++i)
	{
		for(int j = 0; j < columns +1; ++j)
		{
			auto pillarPos = glm::vec2{pos.x + j *scale.x - pillarScale.x / 2, pos.y + i * scale.y- pillarScale.y / 2};
			m_GridPillars.push_back(Pillar(pillarPos,pillarScale));
		}
	}
		
	m_Rows = rows;
	m_Columns = columns;
	
}


dae::LevelGrid::~LevelGrid()
{
	//Clear all the collumns
	for(auto row : m_GridCells)
		row.clear();
	//Clear all the rows
	m_GridCells.clear();
}

void dae::LevelGrid::Update()
{

	for(auto& row : m_GridCells)
	{
		for(auto& col : row)
		{
			if(!col.m_pGameObject->GetComponent<ColliderComponent>()->IsSleeping() && col.m_pGameObject->GetComponent<ColliderComponent>()->HasCollided())
			{
				col.m_pGameObject->GetComponent<ColliderComponent>()->PutToSleep();
				col.SetVisited(true);
			}
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
		std::vector<Cell> colVector;
		for(int j = 0; j < columns;++j)
		{
			colVector.push_back(Cell(i,j,false, pos,scale,m_GroundColors[i/rowEdge]));
		}
		m_GridCells.push_back(colVector);
	}
		
	m_Rows = rows;
	m_Columns = columns;
}


