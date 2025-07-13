#pragma once

#include "GameObjectManager.h"
#include "ECS.h"
#include "Window.h"
#include "TimeD.h"

namespace AEC {
	class Scene
	{
	public:
		Scene();
		Scene(const char* name);
		Scene(const Scene& scene);
		Scene& operator=(const Scene& scene);
		~Scene();

		void FinishLoad();
		void Update();
		void ProcessEvents(SDL_Event* event);
		void Render(Window* window);
		void Clean();

		void Quit();
		void Start();
		const std::string GetName();
		const bool IsRunning() {
			return m_isRunning;
		}
	public:
		GameObjectManager m_gManager;
		ComponentManager  m_cManager;
	private:
		bool m_isRunning = false;
		std::string m_name;
	};
}