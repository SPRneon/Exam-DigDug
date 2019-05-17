#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)
#include "BaseComponent.h"

namespace dae
{
	class TransformComponent final : public BaseComponent
	{
		
	public:
		TransformComponent();
		~TransformComponent() override = default;

		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) noexcept = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) noexcept = delete;

		void Initialize() override;
		void Update() override{}
		void Draw() const override{}

		const glm::vec2& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y);
		void SetScale(float xScale, float yScale);
		void SetScale(float scale);
		void SetRotation(float x, float y,  bool euler = true);

		void Translate(float x, float y);
		void Rotate(float x, float y, bool euler = true);

	private:
		glm::vec2 m_Position = glm::vec2(0.f,0.f);
		glm::vec2 m_Scale = glm::vec2(1.f,1.f);
		glm::vec2 m_Rotation = glm::vec2(0.f,0.f);
	};
}
