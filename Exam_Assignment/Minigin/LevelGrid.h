#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include <array>


namespace dae{
	class GameObject;
	struct Cell
	{
		Cell(int row, int column, bool visited,glm::vec2 pos, glm::vec2 scale):row(row),column(column),visited(visited), scale(scale)
		{
			position.x = scale.x * column + pos.x;
			position.y = scale.y * row + pos.y;
		}
		int row = -1, column =-1;
		bool visited = false;
		glm::vec2 position;
		glm::vec2 scale;
	};

	typedef std::vector<std::vector<Cell>> CellGrid;



class LevelGrid 
	{
public:
	LevelGrid(int rows, int columns, glm::vec2 pos, glm::vec2 scale );
	~LevelGrid();

	void SetRowsAndCollums(const int rows, const int columns, glm::vec2 pos, glm::vec2 scale);
	Cell GetCell(int row, int column){ return m_GridCells[row][column];}
	CellGrid GetCells() const {return m_GridCells;}
	int GetNrCells() const {return m_NrCells;}
	int GetRows() const {return m_Rows;}
	int GetColumns() const {return m_Columns;}
private:
	int m_Rows;
	int m_Columns;
	int m_NrCells;


	CellGrid m_GridCells;

};
}

