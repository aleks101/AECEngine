#include "Assets.h"

namespace AEC {
	std::vector<Texture> textures;
	std::vector<Font> fonts;
	std::vector<AudioSound> sounds;
	std::vector<AudioMusic> music;

	bool imgInit = false;
	bool fontInit = false;
	bool audioInit = false;

	bool InitAssets(uint32_t flags) {
		if (IMG_Init(flags) < 0) {
			LOG("Error initializin SDL_Image: ");
			LOG(IMG_GetError());
			return false;
		}
		imgInit = true;

		if (TTF_Init() < 0) {
			LOG("Error initializing SDL_ttf: ");
			LOG(TTF_GetError());
			return false;
		}
		fontInit = true;

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			LOG("SDL_mixer could not initialize! SDL_mixer Error: \n");
			LOG(Mix_GetError());
			return false;
		}
		audioInit = true;

		return true;
	}
	bool AddTexture(SDL_Renderer* ren, const char* textureFile) {
		SDL_Surface* surf = IMG_Load(textureFile);
		if (surf == NULL) {
			LOG("SURF ERROR\n");
			return false;
		}
		SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, surf);
		if (tex == NULL) {
			LOG("TEX ERROR\n");
			return false;
		}
		SDL_FreeSurface(surf);

		textures.push_back(Texture(textureFile, tex));
		return true;
	}
	bool AddFont(const char* fontFile, int size) {
		TTF_Font* font = TTF_OpenFont(fontFile, size);
		if (!font) {
			LOG("Failed to load font: ");
			LOG(TTF_GetError());
			return false;
		}

		fonts.push_back(Font(fontFile, font));
		return true;
	}
	bool AddSound(const char* soundFile) {
		Mix_Chunk* chunk = Mix_LoadWAV(soundFile);
		if (chunk == NULL) {
			LOG("Failed to load beat chunk! SDL_mixer Error: %s\n");
			LOG(Mix_GetError());
			return false;
		}
		sounds.push_back(AudioSound(soundFile, chunk));
		return true;
	}
	bool AddMusic(const char* musicFile) {
		Mix_Music* music_ = Mix_LoadMUS(musicFile);
		if (music_ == NULL)
		{
			LOG("Failed to load beat music! SDL_mixer Error: %s\n");
			LOG(Mix_GetError());
			return false;
		}
		music.push_back(AudioMusic(musicFile, music_));
		return true;
	}

	SDL_Texture* GetTexture(const char* textureFile) {
		for (auto texture : textures)
			if (texture.imageFile == textureFile)
				return texture.texture;
	}
	TTF_Font* GetFont(const char* fontFile) {
		for (auto font : fonts)
			if (font.fontFile == fontFile)
				return font.font;
	}
	Mix_Chunk* GetSound(const char* soundFile) {
		for (auto audio : sounds)
			if (audio.audioFile == soundFile)
				return audio.chunk;
	}
	Mix_Music* GetMusic(const char* musicFile) {
		for (auto audio : music)
			if (audio.audioFile == musicFile)
				return audio.music;
	}

	void CleanTextures() {
		for (auto& texture : textures)
			SDL_DestroyTexture(texture.texture);
		textures.clear();
		IMG_Quit();
	}
	void CleanFonts() {
		for (auto& font : fonts)
			TTF_CloseFont(font.font);
		fonts.clear();
		TTF_Quit();
	}
	void CleanSounds() {
		for (auto& audio : sounds)
			Mix_FreeChunk(audio.chunk);
		sounds.clear();
		Mix_Quit();
	}
	void CleanMusic() {
		for (auto& audio : music)
			Mix_FreeMusic(audio.music);
		music.clear();
		Mix_Quit();
	}
	void CleanEverything() {
		CleanTextures();
		CleanFonts();
		CleanSounds();
		CleanMusic();
	}

}