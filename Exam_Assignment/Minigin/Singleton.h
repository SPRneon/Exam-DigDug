#pragma once
namespace dae
{
	template <typename T>
	class Singleton
	{
	public:
		static T* GetInstance()
		{
			if(!m_Instance)
			{
			m_Instance = new T();
			}

		return m_Instance;
		}

		static void DestroyInstance()
		{
		delete m_Instance;
		m_Instance = nullptr;
		}

		/*virtual ~Singleton() = default;

		Singleton(const Singleton& other) = delete;
		Singleton(Singleton&& other) = delete;
		Singleton& operator=(const Singleton& other) = delete;
		Singleton& operator=(Singleton&& other) = delete;*/

	

	private:
	static T* m_Instance;
	};
}

template<class T> 
T* dae::Singleton<T>::m_Instance = nullptr;