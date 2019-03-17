#pragma once
#include "Scenegraph/GameObject.h"

namespace dae{
class BaseComponent
{
public:
	BaseComponent(void);
	virtual ~BaseComponent(void);

	GameObject* GetGameObject() const {return m_pGameObject;}
	bool IsInitialized() const {return m_IsInitialized;}
	TransformComponent* GetTransform() const;

protected:
	friend class GameObject;

	virtual void Initialize() = 0;
	virtual void Update();
	virtual void Draw(void) const;
	GameObject* m_pGameObject;
	bool m_IsInitialized;



};
}

