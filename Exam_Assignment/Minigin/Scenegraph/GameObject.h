#pragma once
#include <memory>


#include "Texture2D.h"
#include "SceneObject.h"

#include <vector>



namespace dae
{
	class TransformComponent;
	class BaseComponent;

	class GameObject : public SceneObject
	{
	public:
		void Update() override;
		void Draw() const override;

		TransformComponent* GetTransform(){return m_pTransform;}
		

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		TransformComponent* m_pTransform;
		std::vector<BaseComponent*> m_pComponents;
		std::shared_ptr<Texture2D> mTexture;
	};
}
