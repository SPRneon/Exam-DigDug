#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
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

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);
		void SetScale(float xScale, float yScale, float zScale);
		void SetScale(float scale);
		void SetRotation(float x, float y, float z, bool euler = true);

		void Translate(float x, float y, float z);
		void Rotate(float x, float y, float z, bool euler = true);

	private:
		glm::vec3 m_Position = glm::vec3(0.f,0.f,0.f);
		glm::vec3 m_Scale = glm::vec3(1.f,1.f,1.f);
		glm::vec3 m_Rotation = glm::vec3(0.f,0.f,0.f);
	};
}
