#include "MiniginPCH.h"
#include "LevelGrid.h"
#include "GameObject.h"


dae::LevelGrid::LevelGrid(int rows, int columns, glm::vec2 pos, glm::vec2 scale)
	:m_Rows(rows),
	m_Columns(columns),
	m_NrCells(rows * columns)
{
	SetRowsAndCollums(m_Rows,m_Columns, pos, scale);
	
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
	for(int i = 0; i < rows;++i)
	{
		std::vector<Cell> colVector;
		for(int j = 0; j < columns;++j)
		{
			colVector.push_back(Cell(i,j,false, pos,scale));
		}
		m_GridCells.push_back(colVector);
	}
		
	m_Rows = rows;
	m_Columns = columns;
}
