#pragma once

#include <iostream>
#include <unordered_map>
#include "Core.h"

namespace AEC {
	class ComponentManager {
	public:
		ComponentManager();
		ComponentManager(const ComponentManager& manager);
		ComponentManager& operator=(const ComponentManager& manager);
		~ComponentManager();
		template<typename Component>
		void AddComponent(uint32_t gameobject, Component* component) {
			componentStorage[gameobject][sizeof(Component)] = component;
			AEC::NoteComponent<Component>();
		}

		template<typename Component>
		void RemoveComponent(uint32_t gameobject) {
			auto it = componentStorage.find(gameobject);
			if (it != componentStorage.end()) {
				componentStorage[gameobject].erase(sizeof(Component));
				if (componentStorage[gameobject].empty() == true)
					componentStorage.erase(gameobject);
			}
		}
		void RemoveGameObject(uint32_t gameobject) {
			componentStorage.erase(gameobject);
		}
		template<typename Component>
		Component* GetComponent(uint32_t gameobject) {
			auto it = componentStorage.find(gameobject);
			if (it != componentStorage.end()) {
				auto el = componentStorage[gameobject].find(sizeof(Component));
				if (el != componentStorage[gameobject].end()) {
					return (Component*)(el->second);
				}
			}
			return nullptr;
		}

		template<typename Component>
		bool HasComponent(uint32_t gameobject) {
			auto it = componentStorage.find(gameobject);
			if (it != componentStorage.end()) {
				auto el = componentStorage[gameobject].find(sizeof(Component));
				if (el != componentStorage[gameobject].end()) {
					return true;
				}
			}
			return false;
		}
		void Clean() {
			componentStorage.clear();
		}
		std::unordered_map<uint32_t, std::unordered_map<size_t, void*>>& GetStorage() {
			return componentStorage;
		}
	private:
		std::unordered_map<uint32_t, std::unordered_map<size_t, void*>> componentStorage;
	};
}