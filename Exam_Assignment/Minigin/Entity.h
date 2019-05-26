#pragma once
namespace dae{
	class GameObject;
	class LevelGrid;
class Entity
{
public:
	Entity(std::string name = "GameObject");
	virtual ~Entity() = default;

	virtual void Update() = 0;

	virtual void Place(int row, int column, std::shared_ptr<LevelGrid> grid) = 0;
	virtual void Reset() = 0;
	void MarkForDestroy();
	const bool IsMarkedForDestroy() const {return m_MarkedForDestroy;}
	const bool IsDead() const {return m_IsDead;}
	std::shared_ptr<GameObject> GetGameObject(){return m_pGameObject;}

protected:
	std::shared_ptr<GameObject> m_pGameObject;
	std::string m_Name;

	bool m_MarkedForDestroy = false;
	bool m_IsDead = false;

};
}

