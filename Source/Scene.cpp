#include "Scene.h"

namespace AEC {
	Scene::Scene() {
		m_name = "";
	}
	Scene::Scene(const char* name) {
		m_name = name;
	}
	Scene::Scene(const Scene& scene) : m_cManager(scene.m_cManager), m_gManager(scene.m_gManager){
		m_name = scene.m_name;
		m_isRunning = scene.m_isRunning;
	}
	Scene& Scene::operator=(const Scene& scene) {
		if (this == &scene)
			return *this;
		m_isRunning = scene.m_isRunning;
		m_name = scene.m_name;
		m_gManager = scene.m_gManager;
		m_cManager = scene.m_cManager;
		return *this;
	}

	Scene::~Scene() {
		m_cManager.Clean();
		m_gManager.Clean();
	}
	void Scene::FinishLoad() {
		MonoBehaviourSetup(&m_cManager);
		ArrangeObjectsByLayers(&m_cManager);
	}
	void Scene::Update() {
		if (m_isRunning) {
			MonoBehaviourUpdate(&m_cManager);
		}
		CalcDeltaTime();
	}
	void Scene::ProcessEvents(SDL_Event* event) {
		if (m_isRunning) {
			if (SDL_PollEvent(event)) {
				if (event->type == SDL_QUIT) {
					Quit();
				}
				MonoBehaviourEvent(&m_cManager);
			}
		}
	}
	void Scene::Render(Window* window) {
		RenderObjects(&m_cManager);

		SDL_RenderPresent(window->GetRenderer());
		SDL_RenderClear(window->GetRenderer());
	}
	void Scene::Clean() {
		m_gManager.Clean();
		m_cManager.Clean();
	}
	void Scene::Quit() {
		m_isRunning = false;
	}
	void Scene::Start() {
		m_isRunning = true;
	}
	const std::string Scene::GetName() {
		return m_name;
	}
}