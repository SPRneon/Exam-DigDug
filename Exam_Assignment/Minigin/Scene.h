#pragma once
#include "SceneManager.h"
#include <string>

namespace dae
{
	class GameObject;
	class Scene  : public std::enable_shared_from_this<Scene>
	{
		friend class SceneManager;
	public:
		void Add(const std::shared_ptr<GameObject>& object);
		void Remove(const std::shared_ptr<GameObject>& object);
		virtual ~Scene() = default;
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void MarkForReset(){m_MarkedForReset = true;}
		virtual void ResetScene() = 0;
	protected:
		virtual void Update() = 0;
		virtual void PostUpdate() =0;
		virtual void Draw() const = 0;
		virtual void PostDraw() const = 0;
		virtual void Initialize() = 0;
		

		explicit Scene(const std::string& name);
		bool m_MarkedForReset = false;
	
		
private:
		std::string mName{};
		void RootUpdate();
		void RootDraw();
		void RootInitialize();

		
		std::vector < std::shared_ptr<GameObject>> mObjects{};

		static unsigned int idCounter; 
	};

}
