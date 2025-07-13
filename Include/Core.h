#pragma once

#include <type_traits>
#include <unordered_map>
#include <vector>

#include "Log.h"
#include "MonoBehaviour.h"

namespace AEC {
	struct RenderInfo {
		uint32_t id;
		size_t component;
	};
	extern std::vector<size_t> notedMonoBehaviourComponents;

	template<typename T>
	void NoteComponent() {
		if (std::is_base_of<MonoBehaviour, T>::value == true) {
			notedMonoBehaviourComponents.push_back(sizeof(T));
		}
	}
	bool IsComponentBaseOfMonoBehaviour(size_t componentSize);

	void InitializeLayeredTextures();

	class ComponentManager;
	class GameObjectManager;

	void MonoBehaviourSetup(ComponentManager* manager);
	void MonoBehaviourUpdate(ComponentManager* manager);
	void MonoBehaviourEvent(ComponentManager* manager);

	void ArrangeObjectsByLayers(ComponentManager* manager);
	void RenderObjects(ComponentManager* manager);

	void DeleteGameObject(GameObjectManager* gManager, ComponentManager* cManager, uint32_t id);
}