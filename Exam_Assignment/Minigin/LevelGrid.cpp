#include "MiniginPCH.h"
#include "LevelGrid.h"
#include "GameObject.h"


dae::LevelGrid::LevelGrid(int rows, int columns, glm::vec2 pos, glm::vec2 scale)
	:m_Rows(rows),
	m_Columns(columns),
	m_NrCells(rows * columns)
{
	auto rowEdge = static_cast<int>(rows / 3);


	for(int i = 0; i < rows;++i)
	{
		std::vector<Cell> colVector;
		for(int j = 0; j < columns;++j)
		{
			colVector.push_back(Cell(i,j,false, pos,scale, m_GroundColors[static_cast<int>(i/rowEdge)]));
		}
		m_GridCells.push_back(colVector);
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
