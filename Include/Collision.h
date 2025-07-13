#pragma once

#include <SDL.h>
#include <iostream>
#include "Vec2.h"

namespace AEC {
	namespace collision {
		bool CheckCollisionAABB(const SDL_Rect A, const SDL_Rect B);
		bool CheckCollisionX(const SDL_Rect A, const SDL_Rect B);
		bool CheckCollisionY(const SDL_Rect A, const SDL_Rect B);
		bool CheckCollisionPoint(const SDL_Rect A, const Vec2 B);
		bool CheckCollisionRectCircle(const SDL_Rect A, const Vec2 pos, const float radius, int accuracy);
	}
}