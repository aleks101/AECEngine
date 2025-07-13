#pragma once

#include <SDL.h>

namespace AEC {
	class Window
	{
	public:
		Window();
		Window(const Window& obj) = delete;
		void Init(const char* title, const int width, const int height);
		void Init(const char* title, const int width, const int height, uint32_t flags);
		void Render();
		void Quit();

		SDL_Renderer* GetRenderer();
		SDL_Event* GetEvent();
		SDL_Window* GetWindow();
		int GetWindowWidth();
		int GetWindowHeight();
	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Event* ev;
		int width, height;
	};
}