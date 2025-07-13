#include "MonoBehaviour.h"

namespace AEC {
	int MonoBehaviour::highestLayer = 0;
	int MonoBehaviour::lowestLayer = 20;
	SDL_Renderer* MonoBehaviour::GetRenderer() { return m_renderer; }
	void MonoBehaviour::SetRenderer(SDL_Renderer* ren) {
		m_renderer = ren;
	}
	void MonoBehaviour::SetLayer(int i) {
		if (i < 0)
			i = 0;
		if (i > 20)
			i = 20;
		m_layer = i;
		if (m_layer > highestLayer)
			highestLayer = m_layer;
		if (m_layer < lowestLayer)
			lowestLayer = m_layer;
	}
	int MonoBehaviour::GetLayer() {
		return m_layer;
	}
	int MonoBehaviour::GetHighestLayer() {
		return highestLayer;
	}
	int MonoBehaviour::GetLowestLayer() {
		return lowestLayer;
	}
	void MonoBehaviour::EventProcess() {

	}
	void MonoBehaviour::Clean() {

	}
}