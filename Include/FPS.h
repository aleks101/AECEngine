#pragma once

namespace AEC {
	class FPS
	{
	public:
		static void CalcFPS();
		static int GetFPS();
	private:
		static int fps;
	};
}
