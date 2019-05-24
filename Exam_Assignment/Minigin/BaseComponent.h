#pragma once
#include "GameObject.h"

namespace dae{
class BaseComponent 
{
public:
	BaseComponent();
	virtual ~BaseComponent() = default;

	GameObject* GetGameObject() const { return m_pGameObject; }
	std::shared_ptr<TransformComponent> GetTransform() const;

	bool IsInitialized() const {return m_IsInitialized;}

private:
	BaseComponent(const BaseComponent& other) = delete;
	BaseComponent(BaseComponent&& other) noexcept = delete;
	BaseComponent& operator=(const BaseComponent& other) = delete;
	BaseComponent& operator=(BaseComponent&& other) noexcept = delete;
protected:
	friend class GameObject;

	virtual void Initialize() = 0;
	virtual void Update() =0;
	virtual void Draw() const =0;
	GameObject* m_pGameObject = nullptr;
	bool m_IsInitialized = false;



};
}

