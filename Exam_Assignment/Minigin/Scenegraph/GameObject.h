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
		void Initialize() override;

		TransformComponent* GetTransform(){return m_pTransform;}
		void AddComponent(std::shared_ptr<BaseComponent> component);
		void RemoveComponent(std::shared_ptr<BaseComponent> component);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template <class T>
		std::shared_ptr<T> GetComponent()
		{
			const type_info& ti = typeid(T);

			for (auto component : m_pComponents)
			{
			if (component && typeid(*component) == ti)
				return std::dynamic_pointer_cast<T>(component);
			}

			return nullptr;
		}


	private:
		TransformComponent* m_pTransform;
		std::vector<std::shared_ptr<BaseComponent>> m_pComponents;
		std::shared_ptr<Texture2D> mTexture;
	};
}
