#include "TimeD.h"
#include <SDL.h>

namespace AEC {
	float s_prevTime = 0;
	float deltaTime = 0;

	void CalcDeltaTime() {
		float currTime = SDL_GetTicks();
		deltaTime = (currTime - s_prevTime) / 1000;
		s_prevTime = currTime;
	}
	float DeltaTime() {
		return deltaTime;
	}
}