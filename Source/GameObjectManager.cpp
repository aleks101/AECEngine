#include "GameObjectManager.h"

namespace AEC {
	GameObjectManager::GameObjectManager() {

	}
	GameObjectManager::~GameObjectManager() {
		Clean();
	}
	GameObjectManager::GameObjectManager(const GameObjectManager& manager) : m_gameObjects(manager.m_gameObjects) {
		m_idCounter = manager.m_idCounter;
	}
	GameObjectManager& GameObjectManager::operator=(const GameObjectManager& manager) {
		if (this == &manager)
			return *this;
		m_idCounter = manager.m_idCounter;
		m_gameObjects = manager.m_gameObjects;
		return *this;
	}
	uint32_t GameObjectManager::CreateGameObject() {
		m_idCounter++;

		m_gameObjects.push_back(gInfo(m_idCounter - 1, true));
		return m_idCounter - 1;
	}
	uint32_t GameObjectManager::GetCurrentGameObject() {
		return m_idCounter - 1;
	}

	void GameObjectManager::ActivateGameObject(uint32_t id) {
		if (id >= 0 && id < m_gameObjects.size()) {
			m_gameObjects[id].active = true;
		}
	}
	void GameObjectManager::DeactivateGameObject(uint32_t id) {
		if (id >= 0 && id < m_gameObjects.size()) {
			m_gameObjects[id].active = false;
		}
	}
	void GameObjectManager::Clean() {
		m_gameObjects.clear();
	}
	std::vector<gInfo>& GameObjectManager::GetGameObjects() {
		return m_gameObjects;
	}
}