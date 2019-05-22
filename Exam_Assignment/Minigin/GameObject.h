#pragma once
#include <memory>
#include "Texture2D.h"

#include <vector>



namespace dae
{
	class TransformComponent;
	class BaseComponent;
	class Scene;

	class GameObject final
	{
	public:
		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update();
		void Draw() const;
		void Initialize();

		std::shared_ptr<TransformComponent> GetTransform(){return m_pTransform;}
		void AddComponent(std::shared_ptr<BaseComponent> component);
		void RemoveComponent(std::shared_ptr<BaseComponent> component);

		void SetScene(std::shared_ptr<Scene> scene) {m_pScene = scene;}
		std::shared_ptr<Scene> GetScene() const {return m_pScene;}

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
		std::vector<std::shared_ptr<GameObject>> m_pChildren;
		std::shared_ptr<TransformComponent> m_pTransform = nullptr;
		std::vector<std::shared_ptr<BaseComponent>> m_pComponents;
		std::shared_ptr<Scene> m_pScene;
	};
}
