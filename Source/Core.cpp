#include "Core.h"
#include "GameObjectManager.h"
#include "ECS.h"

namespace AEC {
	std::vector<size_t> notedMonoBehaviourComponents;
	std::vector<RenderInfo> gameObjectsInLayerOrder;
	SDL_Texture* layeredTextures[20];

	void InitializeLayeredTextures() {

	}
	void DeleteGameObject(AEC::GameObjectManager* gManager, AEC::ComponentManager* cManager, uint32_t id) {
		std::vector<gInfo>& gameObjects = gManager->GetGameObjects();
		if (id >= 0 && id < gameObjects.size()) {
			auto it = gameObjects.begin();
			gameObjects.erase(it + id);
			cManager->RemoveGameObject(id);
		}
	}
	bool IsComponentBaseOfMonoBehaviour(size_t componentSize) {
		if (!notedMonoBehaviourComponents.empty()) {
			for (size_t size : notedMonoBehaviourComponents) {
				if (size == componentSize) {
					return true;
				}
			}
		}
		return false;
	}
	void MonoBehaviourSetup(ComponentManager* manager) {
		for (const auto& pair1 : manager->GetStorage()) {
			for (const auto& pair2 : pair1.second) {
				if (IsComponentBaseOfMonoBehaviour(pair2.first)) {
					MonoBehaviour* pt = (MonoBehaviour*)(pair2.second);
					pt->Setup();
				}
			}
		}
	}
	void MonoBehaviourUpdate(ComponentManager* manager) {
		MonoBehaviour* pt = nullptr;
		for (const auto& pair1 : manager->GetStorage()) {
			for (const auto& pair2 : pair1.second) {
				if (IsComponentBaseOfMonoBehaviour(pair2.first)) {
					pt = (MonoBehaviour*)(pair2.second);
					pt->Update();
				}
			}
		}
	}
	void MonoBehaviourEvent(ComponentManager* manager) {
		MonoBehaviour* pt = nullptr;
		for (const auto& pair1 : manager->GetStorage()) {
			for (const auto& pair2 : pair1.second) {
				if (IsComponentBaseOfMonoBehaviour(pair2.first)) {
					pt = (MonoBehaviour*)(pair2.second);
					pt->EventProcess();
				}
			}
		}
	}
	void ArrangeObjectsByLayers(ComponentManager* manager) {
		MonoBehaviour* pt = nullptr;
		RenderInfo info;
		gameObjectsInLayerOrder.clear();
		for (int i = MonoBehaviour::GetLowestLayer(); i <= MonoBehaviour::GetHighestLayer(); i++) {
			for (const auto& pair1 : manager->GetStorage()) {
				for (const auto& pair2 : pair1.second) {
					if (IsComponentBaseOfMonoBehaviour(pair2.first)) {
						pt = (MonoBehaviour*)(pair2.second);
						if (pt->GetLayer() == i) {
							info.id = pair1.first;
							info.component = pair2.first;
							gameObjectsInLayerOrder.push_back({ pair1.first, pair2.first });
						}
					}
				}
			}
		}
	}
	void RenderObjects(ComponentManager* manager) {
		if (gameObjectsInLayerOrder.empty() == false) {
			MonoBehaviour* pt = nullptr;
			RenderInfo info;
			for (int i = 0; i < gameObjectsInLayerOrder.size(); i++) {
				info = gameObjectsInLayerOrder[i];
				pt = (MonoBehaviour*)(manager->GetStorage()[info.id][info.component]);
				pt->Render();
			}
		}
	}
}