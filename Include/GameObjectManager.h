#pragma once

#include "GameObject.h"
#include <vector>

namespace AEC {
	class GameObjectManager {
	public:
		GameObjectManager();
		~GameObjectManager();
		GameObjectManager(const GameObjectManager& manager);
		GameObjectManager& operator=(const GameObjectManager& manager);

		uint32_t CreateGameObject();
		uint32_t GetCurrentGameObject();
		void ActivateGameObject(uint32_t id);
		void DeactivateGameObject(uint32_t id);
		void Clean();
		std::vector<gInfo>& GetGameObjects();
	private:
		int m_idCounter = 0;
		std::vector<gInfo> m_gameObjects;
	};
}
