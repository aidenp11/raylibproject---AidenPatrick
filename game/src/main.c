#include "body.h"
#include "mathf.h"
#include "World.h"
#include "Integrator.h"

#include "raylib.h"
#include "raymath.h"

#include <stdlib.h>
#include <assert.h>

#define MAX_BODIES 100

int main(void)
{
	InitWindow(1200, 720, "Physics Engine");
	SetTargetFPS(60);

	gravity = (Vector2){ 0, 30 };

	// game loop
	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();
		float fps = (float)GetFPS();

		Vector2 position = GetMousePosition();
		if (IsMouseButtonDown(0)) {
				Body* body = CreateBody();
				body = CreateBody();
				body->position = position;	
				body->mass = GetRandomFloatValue(3, 20);
				body->inverseMass = 1 / body->mass;
				body->bodyType = BT_DYNAMIC;
				body->damping = 0.5f;
				body->gravityScale = 5.0f;
				ApplyForce(body, (Vector2) { GetRandomFloatValue(-250, 250), GetRandomFloatValue(-250, 250) }, FM_VELOCITY);
		}

		Body* body = bodies;
		while (body)
		{
			//ApplyForce(body, CreateVector2(0, 250), FM_FORCE);
			body = body->next;
		}

		body = bodies;
		while (body)
		{
			Step(body, dt);
			body = body->next;
		}

		BeginDrawing();
		ClearBackground(BLACK);
		//stats
		DrawText(TextFormat("FPS: %.2f (%.2f ms)", fps, 1000 / fps), 10, 10, 20, WHITE);
		DrawText(TextFormat("FRAME: %.4f", dt), 10, 30, 20, WHITE);

		DrawCircle((int)position.x, (int)position.y, 10, WHITE);

		body = bodies;
		while (body)
		{
			DrawCircle((int)body->position.x, (int)body->position.y, body->mass, GREEN);
			body = body->next;
		}

		EndDrawing();
	}
	CloseWindow();

	return 0;
}