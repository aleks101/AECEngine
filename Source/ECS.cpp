#include "ECS.h"

namespace AEC {
	ComponentManager::ComponentManager() {

	}
	ComponentManager::ComponentManager(const ComponentManager& manager) :
		componentStorage(manager.componentStorage)
	{
	
	}
	ComponentManager& ComponentManager::operator=(const ComponentManager& manager) {
		if (this == &manager)
			return *this;
		componentStorage = manager.componentStorage;
		return *this;
	}
	ComponentManager::~ComponentManager() {
		for (auto& components : componentStorage) {
			components.second.clear();
		}
		componentStorage.clear();
	}
}