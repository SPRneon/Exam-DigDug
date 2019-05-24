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
#include "Singleton.h"


namespace dae{

	
	class Cell
	{
	public:
		Cell(int row, int column, bool visited,glm::vec2 pos, glm::vec2 scale, Color color);

		friend class LevelGrid;
	
		std::shared_ptr<GameObject> GetGameObject()const {return m_pGameObject;}
		bool IsVisited() const {return m_Visited;}
		void SetVisited(bool visited){m_Visited = visited;}
		glm::vec2 GetPosition() const { return m_Position;}
		glm::vec2 GetCenter() const { return m_Center;}
		glm::vec2 GetScale() const { return m_Scale;}
		int GetRow()const { return m_Row;}
		int GetCol()const { return m_Column;}
		Color GetColor() const {return m_Color;}

		
	private:
		int m_Row = -1, m_Column =-1;
		bool m_Visited = false;
		glm::vec2 m_Position;
		glm::vec2 m_Center;
		glm::vec2 m_Scale;
		dae::Color m_Color;
		std::shared_ptr<GameObject> m_pGameObject;
	};


	//TYPEDEF for grid -> vector in vector creates matrix like structure
	//TODO: Clean this up 
	typedef std::vector<std::vector<std::shared_ptr<Cell>>> Grid;

	class Subject;

class LevelGrid : public Singleton<LevelGrid>
	{
public:
	LevelGrid();
	~LevelGrid();
	void CleanUp();

	void Initialize(int rows, int columns, glm::vec2 pos, glm::vec2 scale );

	void Update();
	void Draw();

	void SetRowsAndCollums(const int rows, const int columns, glm::vec2 pos, glm::vec2 scale);

	std::shared_ptr<Cell>& GetCell(int row, int column){ return m_GridCells[row][column];}
	std::shared_ptr<Cell>& GetCell(glm::vec2 pos);

	Grid GetCells() const {return m_GridCells;}


	int GetNrCells() const {return m_NrCells;}
	int GetRows() const {return m_Rows;}
	int GetColumns() const {return m_Columns;}

	void SetCellInactive(int row, int column);
	glm::vec2 GetPathForDir(Direction dir, glm::vec2 pos);
	std::vector<std::pair<std::shared_ptr<Cell>,dae::Direction>> GetNeighbourCells(std::array<Direction,4> directionOrder, std::shared_ptr<Cell> currCell);

	void SetSubject(std::shared_ptr<Subject> obs){m_pSubject = obs;}
	std::shared_ptr<Subject> GetSubject(){return m_pSubject;}

private:
	int m_Rows = -1;
	int m_Columns = -1;
	int m_NrCells = -1;
	glm::vec2 m_Pos = {0.f,0.f};
	glm::vec2 m_Scale= {0.f,0.f};
	Color m_GroundColors[4] = { Colors::LightSand, Colors::DarkSand, Colors::LightClay, Colors::DarkClay};

	Grid m_GridCells;
	

	std::shared_ptr<Subject> m_pSubject;
};
}

