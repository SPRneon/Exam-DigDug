#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include "MathHelper.h"
#include <map>
#include <vector>

std::map<int,std::vector<dae::ColliderComponent*>> dae::ColliderComponent::m_pColliderMap;

dae::ColliderComponent::ColliderComponent(SDL_Rect rect, ColliderGroups collisionGroup,  bool isStatic, bool isSleeping):
	m_Shape(rect),
	m_CollisionGroup(collisionGroup),
	m_HasCollided(false),
	m_IsStatic(isStatic),
	m_IsSleeping(isSleeping),
	m_Pivot(0.f,0.f)
{
	
		
}


dae::ColliderComponent::~ColliderComponent()
{
	
	auto it = std::find(m_pColliderMap.at(static_cast<int>(m_CollisionGroup)).begin(),
	                    m_pColliderMap.at(static_cast<int>(m_CollisionGroup)).end(), this);
	if(it != m_pColliderMap.at(static_cast<int>(m_CollisionGroup)).end())
		m_pColliderMap.at(static_cast<int>(m_CollisionGroup)).erase(it);
}

SDL_Rect* dae::ColliderComponent::CheckCollisions()
{
	SDL_Rect* temp = new SDL_Rect();
	for (auto it = m_pColliderMap.begin(); it != m_pColliderMap.end(); ++it)
	{
		//EXIT if groups is to be ignored
		auto ignoreIt = std::find(m_GroupsToIgnore.begin(), m_GroupsToIgnore.end(), it->first);
		if(ignoreIt != m_GroupsToIgnore.end())
			continue;

		//CHeck if there is any intersection
		for(auto collider : it->second)
		{
			//Check if collider is sleeping ->ignore
			if(collider->IsSleeping())
				continue;



			auto result = SDL_IntersectRect(&m_Shape, collider->GetShape(), temp);
			if(result == SDL_TRUE)
			{	
				m_Collisions.at(collider->m_CollisionGroup) = true;
				return temp;
			}
		}
	}
	//No intersetion detected thus no overlap
	delete temp;
	return nullptr;

}

SDL_Rect* dae::ColliderComponent::WillCollide(glm::vec2 movement)
{
	SDL_Rect testShape = m_Shape;
	testShape.x += static_cast<int>(movement.x);
	testShape.y += static_cast<int>(movement.y);
	SDL_Rect* temp = new SDL_Rect();
	for (auto it = m_pColliderMap.begin(); it != m_pColliderMap.end(); ++it)
	{
		//EXIT if groups is to be ignored
		auto ignoreIt = std::find(m_GroupsToIgnore.begin(), m_GroupsToIgnore.end(), it->first);
		if(ignoreIt != m_GroupsToIgnore.end())
			continue;

		//CHeck if there is any intersection
		for(auto collider : it->second)
		{
			if(collider->IsSleeping())
				continue;
			auto result = SDL_IntersectRect(&testShape, collider->GetShape(), temp);
			if(result == SDL_TRUE)
			{	
				m_Collisions.at(collider->m_CollisionGroup) = true;
				return temp;
			}
		}
	}
	//No intersetion detected thus no overlap
	delete temp;
	return nullptr;
}

const bool dae::ColliderComponent::HasCollidedWith(ColliderGroups groups)
{
	if(m_Collisions.at(groups))
		return m_Collisions.at(groups);

	return false;
}

std::shared_ptr<dae::GameObject> dae::ColliderComponent::GetCollisionObject(ColliderGroups objectFlag)
{
	
}


void dae::ColliderComponent::Update()
{
	m_HasCollided = false;
	for_each(m_Collisions.begin(),m_Collisions.end(),[](auto& it)
	{
		it.second = false;
	});
	
	if(m_IsSleeping)
		return;

	if(!m_IsStatic)
	{
		auto pos = GetTransform()->GetPosition();
		m_Shape.x = static_cast<int>(pos.x + (m_Shape.w * m_Pivot.x) + m_Offset.x);
		m_Shape.y = static_cast<int>(pos.y+ (m_Shape.h * m_Pivot.y) + m_Offset.y);
	}
	if(CheckCollisions())
		m_HasCollided = true;
	else
		m_HasCollided = false;
}

void dae::ColliderComponent::Initialize()
{
	auto it = m_pColliderMap.find(static_cast<int>(m_CollisionGroup));
	if(it != m_pColliderMap.end())
	{
		it->second.push_back(this);
	}
	else
	{
		
		auto vec = std::vector<ColliderComponent*>();
		vec.push_back(this);
		m_pColliderMap.insert_or_assign(static_cast<int>(m_CollisionGroup),vec);
	}
	m_GroupsToIgnore.push_back(m_CollisionGroup);

	auto pos = GetTransform()->GetPosition();
		m_Shape.x = static_cast<int>(pos.x + (m_Shape.w * m_Pivot.x) + m_Offset.x);
		m_Shape.y = static_cast<int>(pos.y+ (m_Shape.h * m_Pivot.y) + m_Offset.y);

	for(auto enumName = ColliderGroups::MIN; enumName<= ColliderGroups::MAX;enumName++)
	{
		m_Collisions.insert_or_assign(enumName,false);
	}


	m_IsInitialized = true;
}

void dae::ColliderComponent::Draw() const
{
	Renderer::GetInstance()->RenderSquare(m_Shape,Colors::red,false);
}

void dae::ColliderComponent::SetRect(SDL_Rect rect)
{
	auto pos = GetTransform()->GetPosition();
	m_Shape.x = static_cast<int>(pos.x + (m_Shape.w * m_Pivot.x) + m_Offset.x);
	m_Shape.y = static_cast<int>(pos.y+ (m_Shape.h * m_Pivot.y) + m_Offset.y);
	m_Shape.w = rect.w;
	m_Shape.h = rect.h;
}

