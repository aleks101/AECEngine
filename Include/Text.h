#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

#include "MonoBehaviour.h"
#include "Object.h"
#include "Log.h"

namespace AEC {
	struct RenderComponents {
		//RenderComponents(){}
		//RenderComponents(const RenderComponents& obj) {
		//	renderer = obj.renderer;
		//	texture = obj.texture;
		//	dest = obj.dest;
		//	source = obj.source;
		//	color = obj.color;
		//	alpha = obj.alpha;
		//	blendMode = obj.blendMode;
		//}
		//RenderComponents& operator=(const RenderComponents& obj) {
		//	if (this == &obj)
		//		return *this;
		//	renderer = obj.renderer;
		//	texture = obj.texture;
		//	dest = obj.dest;
		//	source = obj.source;
		//	color = obj.color;
		//	alpha = obj.alpha;
		//	blendMode = obj.blendMode;
		//	return *this;
		//}
		SDL_Renderer* renderer = nullptr;
		SDL_Texture* texture = nullptr;

		SDL_Rect dest = { 0,0,0,0 };
		SDL_Rect source = { 0,0,0,0 };

		SDL_Color color = { 0,0,0,0 };
		int alpha = 255;
		SDL_BlendMode blendMode;
	};
}

namespace AEC {
	class Texture {
	public:
		Texture() {

		}
		~Texture() {

		}
		Texture(const Texture& obj) {
			components = obj.components;
		}
		Texture& operator=(const Texture& obj) {
			if (this == &obj)
				return *this;
			components = obj.components;
			return *this;
		}
		virtual void SetColor() {
			SDL_SetTextureColorMod(components.texture, components.color.r, components.color.g, components.color.b);
		}
		virtual void SetAlpha() {
			SDL_SetTextureAlphaMod(components.texture, components.alpha);
		}
		virtual void SetBlendMode() {
			SDL_SetTextureBlendMode(components.texture, components.blendMode);
		}
		virtual void Render() {
			if (components.renderer != nullptr && components.texture != nullptr) {
				SDL_RenderCopy(components.renderer, components.texture, &components.source, &components.dest);
			}
		}
		RenderComponents components;
	};
}

namespace AEC {
	class LText : public MonoBehaviour, public Texture {
	private:
		void CreateTexture();
	public:
		void Init(SDL_Renderer* ren, TTF_Font* font, Vec2 pos, SDL_Color color, const char* text);
		void Init(SDL_Renderer* ren, TTF_Font* font, SDL_Rect rect, SDL_Color color, const char* text);
		
		void Setup();
		void Update();
		void Render();
		void Clean();

		virtual void SetNoChangeText(int indexTo);
		virtual void SetNoChangeText(std::string newText);
		virtual void ChangeText(std::string _text);
		virtual void ChangeText(int num);
		virtual void CleanTexture();
		void ChangeSize(int num);
		void ChangeSizeFor(int num);

		std::string GetText() const { return m_text; }
	protected:
		std::string m_text = "";
		std::string m_permaText = "";
		TTF_Font* m_font = nullptr;

		int m_origWidth = 0, m_origHeight = 0;
		int m_sizePercent = 100;
	};
}


class Text : public Object
{

private:
	void CreateText();
public:
	Text(){}
	Text(SDL_Renderer* ren, Vec2 pos, TTF_Font* _font, std::string _text, SDL_Color _color);
	Text(const Text& text);
	virtual ~Text();
	Text& operator=(const Text& obj);

	void Render();
	virtual void Update();

	SDL_Rect* GetDest();
	SDL_Rect* GetSrc();
	SDL_Rect* GetScreen();

	virtual void CleanTexture();

	virtual void SetNoChangeText(int indexTo);
	virtual void SetNoChangeText(std::string newText);
	virtual void ChangeText(std::string _text);
	virtual void ChangeText(int num);
	void ChangeColor(SDL_Color color);
	void ChangeSize(int num);
	void ChangeSizeFor(int num);

	std::string GetText() const { return m_text; }
protected:
	std::string m_text;
	std::string m_permaText;
	SDL_Color m_color;
	TTF_Font* m_font;

	int m_origWidth, m_origHeight;
	int m_sizePercent;
};

