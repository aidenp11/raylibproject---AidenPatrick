#include "body.h"
#include "mathf.h"
#include "World.h"

#include "raylib.h"
#include "raymath.h"

#include <stdlib.h>
#include <assert.h>

#define MAX_BODIES 100

void UpdateAndDrawBodies()
{
	Body* body = bodies;
	Vector2 position = GetMousePosition();

	while (body)
	{
		if (body->position.y < 0 || body->position.y > 720)
		{
			body = body->next;
			DestroyBody(body->prev);
		}


		if (body->position.x == 0 || body->position.y == 0)
		{
			body->position = position;
		}

		if (body->velocity.x == 0 || body->velocity.y == 0)
		{
			body->velocity.x = GetRandomFloatValue(-5, 5);
			body->velocity.y = GetRandomFloatValue(-5, 5);
		}

		body->position = Vector2Add(body->position, body->velocity);

		DrawCircle((int)body->position.x, (int)body->position.y, 10, GREEN);

		body = body->next;
	}
}

int main(void)
{
	InitWindow(1200, 720, "Physics Engine");
	SetTargetFPS(60);

	// game loop
	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();
		float fps = (float)GetFPS();

		Vector2 position = GetMousePosition();
		if (IsMouseButtonDown(0)) {
			if (bodyCount < MAX_BODIES) {
				CreateBody();
			}
		}

		UpdateAndDrawBodies();

		BeginDrawing();
		ClearBackground(BLACK);
		//stats
		DrawText(TextFormat("FPS: %.2f (%.2f ms)", fps, 1000 / fps), 10, 10, 20, WHITE);
		DrawText(TextFormat("FRAME: %.4f", dt), 10, 30, 20, WHITE);

		DrawCircle((int)position.x, (int)position.y, 10, WHITE);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}