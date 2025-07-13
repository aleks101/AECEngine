#include "FPS.h"
#include "TimeD.h"

namespace AEC {
	int FPS::fps = 0;

	void FPS::CalcFPS() {
		fps = 1 / (int)DeltaTime();
	}
	int FPS::GetFPS() {
		return fps;
	}
}