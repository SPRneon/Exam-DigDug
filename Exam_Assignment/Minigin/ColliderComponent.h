#pragma once
#include "BaseComponent.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

namespace dae{
class ColliderComponent :
	public BaseComponent
{
public:
	ColliderComponent();
	virtual ~ColliderComponent() override;

	


	void Update() override;
	void Initialize() override;
	void Draw() const override;

	ColliderComponent(const ColliderComponent& other) = delete;
	ColliderComponent(ColliderComponent&& other) noexcept = delete;
	ColliderComponent& operator=(const ColliderComponent& other) = delete;
	ColliderComponent& operator=(ColliderComponent&& other) noexcept = delete;

private:
	
};
}

