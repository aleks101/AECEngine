#include "Collision.h"

namespace AEC {
    namespace collision {
        bool CheckCollisionAABB(const SDL_Rect A, const SDL_Rect B) {
            int leftA = A.x;
            int rightA = A.x + A.w;
            int topA = A.y;
            int bottomA = A.y + A.h;

            int leftB = B.x;
            int rightB = B.x + B.w;
            int topB = B.y;
            int bottomB = B.y + B.h;

            if (rightA > leftB && leftA < rightB && bottomA > topB && topA < bottomB) {
                return true;
            }
            return false;
        }
        bool CheckCollisionX(const SDL_Rect A, const SDL_Rect B) {
            int leftA = A.x;
            int rightA = A.x + A.w;
            int topA = A.y;
            int bottomA = A.y + A.h;

            int leftB = B.x;
            int rightB = B.x + B.w;
            int topB = B.y;
            int bottomB = B.y + B.h;

            if (rightA > leftB && leftA < leftB) {
                return true;
            }
            else if (leftA < rightB && rightA > rightB) {
                return true;
            }
            return false;
        }
        bool CheckCollisionY(const SDL_Rect A, const SDL_Rect B) {
            int leftA = A.x;
            int rightA = A.x + A.w;
            int topA = A.y;
            int bottomA = A.y + A.h;

            int leftB = B.x;
            int rightB = B.x + B.w;
            int topB = B.y;
            int bottomB = B.y + B.h;

            if (topA >= topB && topA <= bottomB) {
                return true;
            }
            else if (bottomA >= topB && bottomA < bottomB) {
                return true;
            }
            return false;

        }
        bool CheckCollisionPoint(const SDL_Rect A, const Vec2 B) {
            if (B.x >= A.x && B.x <= (A.x+A.w) && B.y >= A.y && B.y <= (A.y+A.h)) {
                return true;
            }
            return false;
        }
        bool CheckCollisionRectCircle(const SDL_Rect A, const Vec2 pos, const float radius, int accuracy) {
            accuracy = accuracy < 10 ? 10 : accuracy;
            accuracy = accuracy > 100 ? 100 : accuracy;

            Vec2 point = { 0,0 };
            float kotniPremik = 2 * M_PI / accuracy;
            float kot = 0;

            for (int i = 0; i < accuracy; i++) {
                kot = i * kotniPremik;

                point.x = pos.x + radius * cos(kot);
                point.y = pos.y + radius * sin(kot);

                if (CheckCollisionPoint(A, point))
                    return true;
            }           
            return false;
        }
    }
}