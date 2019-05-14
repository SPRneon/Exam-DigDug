#pragma once
#include "Singleton.h"
#include <string>
#include <vector>

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		template <class T>
		Scene & CreateScene( const std::string& name)
		{
			const type_info& ti = typeid(T);

			if(ti == typeid(Scene))
			{
				//TODO
				//DEBUG LOG SCENE TYPE
				throw std::exception("Cannot add scene of BaseClass <Scene>");
			}

			if(!std::is_base_of<Scene, T>())
			{
				throw std::exception("Have to add a derived Scene of BaseClass <Scene>");
			}
			const auto scene = std::shared_ptr<T>(new T(name));

			const auto it = std::find(mScenes.begin(), mScenes.end(), scene);


				if(it == mScenes.end())
				{
				mScenes.push_back(scene);
				scene->RootInitialize();
				}
			return *scene;
		}

		void Update();
		void Draw();

	private:
		std::vector<std::shared_ptr<Scene>> mScenes;
	};

}
