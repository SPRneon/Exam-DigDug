#pragma once
#include "BaseComponent.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include <SDL.h>
#include <map>
#include <algorithm>

namespace dae{
	enum ColliderGroups
	{
		TERRAIN = 0,
		WALL = 1,
		PLAYER = 2,
		ENEMIES = 3,
		FIRE = 4
	};

class ColliderComponent :
	public BaseComponent
{
public:
	//If the collision group is set to '0' it will check every other collider
	explicit ColliderComponent(SDL_Rect rect,ColliderGroups collisionGroup = TERRAIN, bool isStatic = false, bool isSleeping = false);
	virtual ~ColliderComponent() override;

	
	SDL_Rect* CheckCollisions() const;
	const SDL_Rect* GetShape() const {return &m_Shape;}
	void SetOffset(glm::vec2 offset){m_Offset = offset;}
	void SetRect(SDL_Rect rect);
	const glm::vec2 GetShapeCenter() const {return  glm::vec2{m_Shape.x + m_Shape.w / 2.f,m_Shape.y + m_Shape.h / 2.f};}
	const bool HasCollided() const{return m_HasCollided;}
	SDL_Rect* WillCollide(glm::vec2 movement);
	void SetStatic(){m_IsStatic = true;}
	void SetDynamic(){m_IsStatic = false;}
	void SetPivot(glm::vec2 pivot){m_Pivot = pivot;}
	void AddIgnoreGroup(ColliderGroups ignoreGroup){m_GroupsToIgnore.push_back(ignoreGroup);}

	const bool IsSleeping() const {return m_IsSleeping;}
	void Awake(){m_IsSleeping = false;}
	void PutToSleep(){m_IsSleeping = true;}
	void SetIgnoreFlags(ColliderGroups groupToIgnore){m_GroupsToIgnore.push_back(groupToIgnore);}

	void Update() override;
	void Initialize() override;
	void Draw() const override;

	ColliderComponent(const ColliderComponent& other) = delete;
	ColliderComponent(ColliderComponent&& other) noexcept = delete;
	ColliderComponent& operator=(const ColliderComponent& other) = delete;
	ColliderComponent& operator=(ColliderComponent&& other) noexcept = delete;

private:
	SDL_Rect m_Shape;
	SDL_Rect* m_pIntersect;
	ColliderGroups m_CollisionGroup;
	bool m_HasCollided;
	bool m_IsStatic = false;
	bool m_IsSleeping= false;
	std::vector<ColliderGroups> m_GroupsToIgnore;
	glm::vec2 m_Pivot;
	glm::vec2 m_Offset = {0.f,0.f};
	static std::map<int,std::vector<ColliderComponent*>> m_pColliderMap;
};
}

