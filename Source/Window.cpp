#include "Window.h"

namespace AEC {
	Window::Window() {

	}
	void Window::Init(const char* title, int width, int height) {
		this->width = width;
		this->height = height;
		SDL_Init(SDL_INIT_EVERYTHING);
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
		ev = new SDL_Event;
	}
	void Window::Init(const char* title, int width, int height, uint32_t flags) {
		this->width = width;
		this->height = height;
		SDL_Init(flags);
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
		ev = new SDL_Event;
	}
	void Window::Quit() {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
	void Window::Render() {
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
	}
	SDL_Renderer* Window::GetRenderer() {
		return renderer;
	}
	SDL_Event* Window::GetEvent() {
		return ev;
	}
	SDL_Window* Window::GetWindow() {
		return window;
	}
	int Window::GetWindowWidth() {
		return width;
	}
	int Window::GetWindowHeight() {
		return height;
	}
}