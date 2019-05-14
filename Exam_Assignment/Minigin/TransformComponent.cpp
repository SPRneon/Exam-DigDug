#include "MiniginPCH.h"
#include "TransformComponent.h"
#include "MathHelper.h"


dae::TransformComponent::TransformComponent()
	:m_Position(0,0,0),
	m_Scale(1,1,1),
	m_Rotation(0,0,0)
{
	
}

void dae::TransformComponent::Initialize()
{
	m_IsInitialized = true;
}



void dae::TransformComponent::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void dae::TransformComponent::SetScale(float xScale, float yScale, float zScale)
{
	m_Scale.x = xScale;
	m_Scale.y = yScale;
	m_Scale.z = zScale;
}

void dae::TransformComponent::SetScale(float scale)
{
	m_Scale.x = scale;
	m_Scale.y = scale;
	m_Scale.z = scale;
}

void dae::TransformComponent::SetRotation(float x, float y, float z, bool euler)
{
	if(euler)
	{
		m_Rotation.x = x;
		m_Rotation.y = y;
		m_Rotation.z = z;
	}
	else
	{
		m_Rotation.x = x * (180.f / M_PI);
		m_Rotation.y = y * (180.f / M_PI);
		m_Rotation.z = z * (180.f / M_PI);
	}
}

void dae::TransformComponent::Translate(float x, float y, float z)
{
	m_Position.x += x;
	m_Position.y += y;
	m_Position.z += z;
}

void dae::TransformComponent::Rotate(float x, float y, float z, bool euler)
{
	if(euler)
	{
		m_Rotation.x += x;
		m_Rotation.y += y;
		m_Rotation.z += z;
	}
	else
	{
		m_Rotation.x += x * (180.f / M_PI);
		m_Rotation.y += y * (180.f / M_PI);
		m_Rotation.z += z * (180.f / M_PI);
	}
}
