#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include <array>
#include "MathHelper.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"


namespace dae{
	class Cell
	{
	public:
		Cell(int row, int column, bool visited,glm::vec2 pos, glm::vec2 scale, Color color);

		friend class LevelGrid;
	
		std::shared_ptr<GameObject> GetGameObject() const {return m_pGameObject;}
		bool IsVisited() const {return m_Visited;}
		void SetVisited(bool visited){m_Visited = visited;}
		glm::vec2 GetPosition() const { return m_Position;}
		glm::vec2 GetScale() const { return m_Scale;}
		Color GetColor() const {return m_Color;}
	private:
		int m_Row = -1, m_Column =-1;
		bool m_Visited = false;
		glm::vec2 m_Position;
		glm::vec2 m_Scale;
		dae::Color m_Color;
		std::shared_ptr<GameObject> m_pGameObject;
	};

	class Pillar
	{
	public:
		Pillar(glm::vec2 pos, glm::vec2 scale);

		friend class LevelGrid;
		std::shared_ptr<GameObject> GetGameObject() const {return m_pGameObject;}
		glm::vec2 GetPosition() const { return m_Position;}
		glm::vec2 GetScale() const { return m_Scale;}
	private:
		glm::vec2 m_Position;
		glm::vec2 m_Scale;
		std::shared_ptr<GameObject> m_pGameObject;
	};

	//TYPEDEF for grid -> vector in vector creates matrix like structure
	//TODO: Clean this up 
	typedef std::vector<std::vector<Cell>> Grid;



class LevelGrid 
	{
public:
	LevelGrid(int rows, int columns, glm::vec2 pos, glm::vec2 scale );
	~LevelGrid();

	void Update();

	void SetRowsAndCollums(const int rows, const int columns, glm::vec2 pos, glm::vec2 scale);
	Cell GetCell(int row, int column){ return m_GridCells[row][column];}
	Grid GetCells() const {return m_GridCells;}
	std::vector<Pillar> GetPillars() const {return m_GridPillars;}
	int GetNrCells() const {return m_NrCells;}
	int GetRows() const {return m_Rows;}
	int GetColumns() const {return m_Columns;}

private:
	int m_Rows;
	int m_Columns;
	int m_NrCells;
	Color m_GroundColors[4] = { Colors::LightSand, Colors::DarkSand, Colors::LightClay, Colors::DarkClay};

	Grid m_GridCells;
	std::vector<Pillar> m_GridPillars;

};
}

