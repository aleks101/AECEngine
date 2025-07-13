#pragma once

#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Log.h"

struct Texture {
	std::string imageFile;
	SDL_Texture* texture;
	Texture(std::string _imageFile, SDL_Texture* _texture) : imageFile(_imageFile), texture(_texture) {}
};
struct Font {
	std::string fontFile;
	TTF_Font* font;
	Font(std::string _fontFile, TTF_Font* _font) : fontFile(_fontFile), font(_font) {}
};
struct AudioSound {
	std::string audioFile;
	Mix_Chunk* chunk;
	AudioSound(std::string _audioFile, Mix_Chunk* _chunk) : audioFile(_audioFile), chunk(_chunk) {}
};
struct AudioMusic {
	std::string audioFile;
	Mix_Music* music;
	AudioMusic(std::string _audioFile, Mix_Music* _music) : audioFile(_audioFile), music(_music) {}
};

namespace AEC {
	bool InitAssets(uint32_t flags);

	bool AddTexture(SDL_Renderer* ren, const char* textureFile);
	bool AddFont(const char* fontFile, int size);
	bool AddSound(const char* soundFile);
	bool AddMusic(const char* musicFile);

	SDL_Texture* GetTexture(const char* textureFile);
	TTF_Font* GetFont(const char* fontFile);
	Mix_Chunk* GetSound(const char* soundFile);
	Mix_Music* GetMusic(const char* musicFile);

	void CleanTextures();
	void CleanFonts();
	void CleanSounds();
	void CleanMusic();
	void CleanEverything();

}