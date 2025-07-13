#include "RenderBase.h"

//namespace AEC {
//	int RenderBase::highestLayer = 0;
//	int RenderBase::lowestLayer = 20;
//	SDL_Renderer* RenderBase::GetRenderer() { return m_renderer; }
//	void RenderBase::SetRenderer(SDL_Renderer* ren) {
//		m_renderer = ren;
//	}
//	void RenderBase::SetLayer(int i) {
//		if (i < 0)
//			i = 0;
//		if (i > 20)
//			i = 20;
//		m_layer = i;
//		if (m_layer > highestLayer)
//			highestLayer = m_layer;
//		if (m_layer < lowestLayer)
//			lowestLayer = m_layer;
//	}
//	int RenderBase::GetLayer() {
//		return m_layer;
//	}
//	int RenderBase::GetHighestLayer() {
//		return highestLayer;
//	}
//	int RenderBase::GetLowestLayer() {
//		return lowestLayer;
//	}
//
//}