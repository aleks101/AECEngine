#pragma once

#include <SDL.h>

namespace AEC {
	class MonoBehaviour
	{
	public:
		virtual void Setup() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void EventProcess();
		virtual void Clean();

		SDL_Renderer* GetRenderer();
		void SetRenderer(SDL_Renderer* ren);
		/// <summary>
		/// Order in which layers will be rendered
		/// </summary>
		void SetLayer(int i);
		int GetLayer();
		static int GetHighestLayer();
		static int GetLowestLayer();
	protected:
		SDL_Renderer* m_renderer;
	private:
		int m_layer = 0;
		static int highestLayer;
		static int lowestLayer;
	};
}