#include "Text.h"

namespace AEC {
	void LText::CreateTexture() {
		SDL_Surface* surf = TTF_RenderText_Solid(m_font, m_text.c_str(), components.color);
		if (!surf) {
			LOG("Failed to render text: ");
			LOG(TTF_GetError());
			LOG("\n");
		}
		if (!components.renderer)
			LOG("renderer error");

		components.texture = SDL_CreateTextureFromSurface(components.renderer, surf);
		if (!components.texture)
			LOG("tex error");
		SDL_QueryTexture(components.texture, NULL, NULL, &components.dest.w, &components.dest.h);
		SDL_FreeSurface(surf);
	}
	void LText::Init(SDL_Renderer* ren, TTF_Font* font, Vec2 pos, SDL_Color color, const char* text) {
		components.renderer = ren;
		components.dest = { (int)pos.x, (int)pos.y };
		components.color = color;
		SetColor();
		m_text = text;
		m_font = font;
	}
	void LText::Init(SDL_Renderer* ren, TTF_Font* font, SDL_Rect rect, SDL_Color color, const char* text) {
		components.renderer = ren;
		components.dest = rect;
		components.source = { 0,0,rect.w,rect.h };
		components.color = color;
		SetColor();
		m_origWidth = rect.w;
		m_origHeight = rect.h;
		m_text = text;
		m_font = font;
	}
	void LText::Setup() {
		CreateTexture();
	}
	void LText::Update() {

	}
	void LText::Render() {
		Texture::Render();
	}
	void LText::Clean() {
		CleanTexture();
	}
	void LText::SetNoChangeText(int indexTo) {

	}
	void LText::SetNoChangeText(std::string newText) {
		m_permaText = newText;
	}
	void LText::ChangeText(std::string _text) {
		if (m_text != (m_permaText + _text)) {
			m_text = m_permaText + _text;
			SDL_DestroyTexture(components.texture);

			CreateTexture();

			m_origWidth = components.dest.w;
			m_origHeight = components.dest.h;
			m_sizePercent = 100;
		}
	}
	void LText::ChangeText(int num) {
		std::string numString = std::to_string(num);
		if (m_text != (m_permaText + numString)) {
			m_text = m_permaText + numString;
			SDL_DestroyTexture(components.texture);

			CreateTexture();

			m_origWidth = components.dest.w;
			m_origHeight = components.dest.h;
			m_sizePercent = 100;
		}
	}
	void LText::ChangeSize(int num) {
		//100 - meaning original size of the text, lower than 100 is smaller text and higher than 100 is bigger text

		int prevSize = m_sizePercent;
		m_sizePercent = num;

		components.dest.w = (m_sizePercent * components.dest.w) / prevSize;
		components.dest.h = (m_sizePercent * components.dest.h) / prevSize;
	}
	void LText::ChangeSizeFor(int num) {
		//100 - meaning original size of the text, lower than 100 is smaller text and higher than 100 is bigger text

		int prevSize = m_sizePercent;
		m_sizePercent += num;

		components.dest.w = (m_sizePercent * components.dest.w) / prevSize;
		components.dest.h = (m_sizePercent * components.dest.h) / prevSize;
	}
	void LText::CleanTexture() {
		SDL_DestroyTexture(components.texture);
		components.texture = nullptr;
	}
}

Text::Text(SDL_Renderer* ren, Vec2 pos, TTF_Font* _font, std::string _text, SDL_Color _color) : Object({0,0,0,0}) {
	m_ren = ren;
	m_dest.x = pos.x;
	m_dest.y = pos.y;
	m_text = _text;
	m_color = _color;
	m_font = _font;
	m_permaText = "";

	CreateText();
	m_origWidth = m_dest.w;
	m_origHeight = m_dest.h;
	m_sizePercent = 100;
	SetDest(m_dest);
}
Text::Text(const Text& obj) : Object(obj.m_dest), m_text(obj.m_text), m_permaText(obj.m_permaText), m_color(obj.m_color), m_font(obj.m_font), 
	m_origWidth(obj.m_origWidth), m_origHeight(obj.m_origHeight), m_sizePercent(obj.m_sizePercent) {
	CenterObj(obj.m_playerRect);
	m_ren = obj.m_ren;
	m_tex = obj.m_tex;
}
Text::~Text() {
}
Text& Text::operator=(const Text& obj) {
	m_text = obj.m_text;
	m_permaText = obj.m_permaText;
	m_color = obj.m_color;
	m_font = obj.m_font;
	m_sizePercent = obj.m_sizePercent;
	m_origWidth = obj.m_origWidth;
	m_origHeight = obj.m_origHeight;

	m_ren = obj.m_ren;
	m_dest = obj.m_dest;
	m_tex = obj.m_tex;

	return *this;
}
void Text::Render() {
	if (m_ren != nullptr && m_tex != nullptr)
		SDL_RenderCopy(m_ren, m_tex, NULL, &m_dest);
}
void Text::Update() {

}
SDL_Rect* Text::GetDest() {
	return &m_dest;
}
SDL_Rect* Text::GetSrc() {
	return &m_src;
}
SDL_Rect* Text::GetScreen() {
	return &m_screen;
}
void Text::CreateText() {
	SDL_Surface* surf = TTF_RenderText_Solid(m_font, m_text.c_str(), m_color);
	if (!surf) {
	LOG("Failed to render text: ");
	LOG(TTF_GetError());
	LOG("\n");
	}
	if (!m_ren)
		LOG("renderer error");

	m_tex = SDL_CreateTextureFromSurface(m_ren, surf);
	if (!m_tex)
		LOG("tex error");
	SDL_QueryTexture(m_tex, NULL, NULL, &m_dest.w, &m_dest.h);
	SetDest(m_dest);
	SDL_FreeSurface(surf);
}
void Text::ChangeText(std::string _text) {
	if (m_text != (m_permaText + _text)) {
		m_text = m_permaText + _text;
		SDL_DestroyTexture(m_tex);

		CreateText();

		m_origWidth = m_dest.w;
		m_origHeight = m_dest.h;
		m_sizePercent = 100;
	}
}
void Text::ChangeText(int num) {
	std::string numString = std::to_string(num);
	if (m_text != (m_permaText + numString)) {
		m_text = m_permaText + numString;
		SDL_DestroyTexture(m_tex);

		CreateText();

		m_origWidth = m_dest.w;
		m_origHeight = m_dest.h;
		m_sizePercent = 100;
	}
}
void Text::SetNoChangeText(int indexTo) {

}
void Text::SetNoChangeText(std::string newText) {
	m_permaText = newText;
}
void Text::ChangeColor(SDL_Color color) {
	m_color = color;
	SDL_SetTextureColorMod(m_tex, m_color.r, m_color.g, m_color.b);
}
void Text::ChangeSize(int num) {
	//100 - meaning original size of the text, lower than 100 is smaller text and higher than 100 is bigger text

	int prevSize = m_sizePercent;
	m_sizePercent = num;

	SDL_Rect dest = *GetDest();

	dest.w = (m_sizePercent * m_dest.w) / prevSize;
	dest.h = (m_sizePercent * m_dest.h) / prevSize;

	SetDest(dest);
}
void Text::ChangeSizeFor(int num) {
	//100 - meaning original size of the text, lower than 100 is smaller text and higher than 100 is bigger text

	int prevSize = m_sizePercent;
	m_sizePercent += num;

	SDL_Rect dest = *GetDest();

	dest.w = (m_sizePercent * m_dest.w) / prevSize;
	dest.h = (m_sizePercent * m_dest.h) / prevSize;

	SetDest(dest);
}
void Text::CleanTexture() {
	SDL_DestroyTexture(m_tex);
	m_tex = nullptr;
}