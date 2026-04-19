#include "raylib.h"
#include <vector>


class Bubble {
private:
    float x, y;
    float radius;
    float speed;
    Color color;

public:
    Bubble(float startX, float startY) {
        x = startX;
        y = startY;
        radius = 30.0f;
        speed = 100.0f;
        color = BLUE;
    }


    void Update() {
        y -= speed * GetFrameTime();
    }

    // 畫出泡泡
    void Draw() {
        DrawCircle(x, y, radius, color);
    }

    // 判斷是否被點中
    bool IsClicked(Vector2 mousePos) {
        Vector2 bubbleCenter = { x, y };
        return CheckCollisionPointCircle(mousePos, bubbleCenter, radius);
    }
};

int main() {

    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Click the Bubble - Anti Gravity!");


    std::vector<Bubble> bubbles;
    int score = 0;
    float spawnTimer = 0.0f;

    SetTargetFPS(60);


    while (!WindowShouldClose()) {


        spawnTimer += GetFrameTime();
        if (spawnTimer >= 1.0f) {
            float randomX = GetRandomValue(50, 750);
            float startY = 650.0f;
            bubbles.push_back(Bubble(randomX, startY));
            spawnTimer = 0.0f;
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePos = GetMousePosition();

            for (int i = bubbles.size() - 1; i >= 0; i--) {
                if (bubbles[i].IsClicked(mousePos)) {
                    score += 10;
                    bubbles.erase(bubbles.begin() + i);
                    break;
                }
            }
        }

        for (int i = 0; i < bubbles.size(); i++) {
            bubbles[i].Update();
        }


        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < bubbles.size(); i++) {
            bubbles[i].Draw();
        }

        DrawText(TextFormat("Score: %d", score), 20, 20, 40, BLACK);

        EndDrawing();
    }


    CloseWindow();

    return 0;
}
