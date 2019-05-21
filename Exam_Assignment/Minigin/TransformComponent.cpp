#include "MiniginPCH.h"
#include "TransformComponent.h"
#include "MathHelper.h"


dae::TransformComponent::TransformComponent()
	:m_Position(0,0),
	m_Scale(1,1),
	m_Rotation(0,0)
{
	
}

void dae::TransformComponent::Initialize()
{
	m_IsInitialized = true;
}



void dae::TransformComponent::SetPosition(const float x, const float y)
{
	m_Position.x = x;
	m_Position.y = y;
}

void dae::TransformComponent::SetPosition(glm::vec2 xy)
{
	SetPosition(xy.x,xy.y);
}

void dae::TransformComponent::SetScale(float xScale, float yScale)
{
	m_Scale.x = xScale;
	m_Scale.y = yScale;
}

void dae::TransformComponent::SetScale(glm::vec2 xy)
{
	SetScale(xy.x,xy.y);
}

void dae::TransformComponent::SetScale(float scale)
{
	m_Scale.x = scale;
	m_Scale.y = scale;

}

void dae::TransformComponent::SetRotation(float x, float y, bool euler)
{
	if(euler)
	{
		m_Rotation.x = x;
		m_Rotation.y = y;

	}
	else
	{
		m_Rotation.x = x * (180.f / M_PI);
		m_Rotation.y = y * (180.f / M_PI);
	}
}

void dae::TransformComponent::SetRotation(glm::vec2 xy, bool euler)
{
	Rotate(xy.x,xy.y, euler);
}

void dae::TransformComponent::Translate(float x, float y )
{
	m_Position.x += x;
	m_Position.y += y;

}

void dae::TransformComponent::Translate(int x, int y)
{
	Translate(static_cast<float>(x), static_cast<float>(y));
}

void dae::TransformComponent::Rotate(float x, float y,  bool euler)
{
	if(euler)
	{
		m_Rotation.x += x;
		m_Rotation.y += y;

	}
	else
	{
		m_Rotation.x += x * (180.f / M_PI);
		m_Rotation.y += y * (180.f / M_PI);
	}
}
