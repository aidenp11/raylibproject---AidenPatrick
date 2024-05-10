#include "body.h"
#include "mathf.h"
#include "World.h"
#include "Integrator.h"
#include "Force.h"
#include "editor.h"
#include "render.h"

#include "raylib.h"
#include "raymath.h"

#include <stdlib.h>
#include <assert.h>

#define MAX_BODIES 100

static int mb = 0;
EditorData editorData;
int main(void)
{
	InitWindow(1200, 720, "Physics Engine");
	InitEditor();
	SetTargetFPS(60);

	gravity = (Vector2){ 0, 100 };

	// game loop
	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();
		float fps = (float)GetFPS();

		Vector2 position = GetMousePosition();
		ncScreenZoom += GetMouseWheelMove() * 0.2f;

		UpdateEditor(position);

		if (!ncEditorIntersect && IsMouseButtonDown(0)) {
			mb = 0;
			for (int i = 0; i < 1; i++)
			{

				Body* body = CreateBody(ConvertScreenToWorld(position), GetRandomFloatValue(editorData.massMinBarValue, editorData.massMaxSliderValue), editorData.bodyType);
				body->damping = editorData.damping;
				body->gravityScale = editorData.GravityScale;

				AddBody(body);
				//ApplyForce(body, (Vector2) { GetRandomFloatValue(GetRandomValue(-500, 0), GetRandomValue(0, 500)), GetRandomFloatValue(GetRandomValue(-600, 0), GetRandomValue(0, 600)) }, FM_VELOCITY);
			}
		}

		if (!ncEditorIntersect && IsMouseButtonDown(1)) {
			mb = 1;
			for (int i = 0; i < 1; i++)
			{

				Body* body = CreateBody(ConvertScreenToWorld(position), GetRandomFloatValue(editorData.massMinBarValue, editorData.massMaxSliderValue), editorData.bodyType);
				body->damping = editorData.damping;
				body->gravityScale = editorData.GravityScale;

				AddBody(body);
				//ApplyForce(body, (Vector2) { GetRandomFloatValue(-250, 250), GetRandomFloatValue(-250, 250) }, FM_VELOCITY);
			}
		}

		if (!ncEditorIntersect && IsMouseButtonDown(2)) {
			mb = 2;
			for (int i = 0; i < 1; i++)
			{

				Body* body = CreateBody(ConvertScreenToWorld(position), GetRandomFloatValue(editorData.massMinBarValue, editorData.massMaxSliderValue), editorData.bodyType);
				body->damping = editorData.damping;
				body->gravityScale = editorData.GravityScale;

				AddBody(body);//GetRandomFloatValue(2, 10);
				//ApplyForce(body, (Vector2) { GetRandomFloatValue(GetRandomValue(-250, 0), GetRandomValue(0, 250)), GetRandomFloatValue(-250, 50) }, FM_VELOCITY);
			}
		}

		Body* body = bodies;
		switch (mb)
		{
		case 0:

			ApplyGravitation(body, editorData.GravitationValue);
			for (Body* body = bodies; body; body = body->next)
			{
				Step(body, dt);
			}

			//body = bodies;
			//while (body)
			//{
			//	Step(body, dt);
			//	body = body->next;
			//}

			BeginDrawing();
			ClearBackground(BLACK);

			//stats
			DrawText(TextFormat("FPS: %.2f (%.2f ms)", fps, 1000 / fps), 10, 10, 20, WHITE);
			DrawText(TextFormat("FRAME: %.4f", dt), 10, 30, 20, WHITE);

			//DrawCircle((int)position.x, (int)position.y, 10, WHITE);

			//body = bodies;
			for (Body* body = bodies; body; body = body->next)
			{
				Vector2 screen = ConvertWorldToScreen(body->position);
				DrawCircle((int)screen.x, screen.y, body->mass, (Color) { GetRandomFloatValue(0, 255), GetRandomFloatValue(0, 255), GetRandomFloatValue(0, 255), 255 });
				DrawCircle((int)screen.x + GetRandomFloatValue(-10, 10), screen.y + GetRandomFloatValue(-10, 10), ConvertWorldToPixel(body->mass - 1), WHITE);
				DrawCircle((int)screen.x + GetRandomFloatValue(-10, 10), screen.y + GetRandomFloatValue(-10, 10), ConvertWorldToPixel(body->mass - 1), YELLOW);
				DrawCircle((int)screen.x + GetRandomFloatValue(-10, 10), screen.y + GetRandomFloatValue(-10, 10), ConvertWorldToPixel(body->mass - 1), WHITE);
			}

			DrawEditor(position);
			break;
		case 1:
			ApplyGravitation(body, -30);
			for (Body* body = bodies; body; body = body->next)
			{
				Step(body, dt);
			}

			//body = bodies;
			//while (body)
			//{
			//	Step(body, dt);
			//	body = body->next;
			//}

			BeginDrawing();
			ClearBackground(BLACK);

			//stats
			DrawText(TextFormat("FPS: %.2f (%.2f ms)", fps, 1000 / fps), 10, 10, 20, WHITE);
			DrawText(TextFormat("FRAME: %.4f", dt), 10, 30, 20, WHITE);

		//	DrawCircle((int)position.x, (int)position.y, 10, WHITE);

			//body = bodies;
			for (Body* body = bodies; body; body = body->next)
			{
				Vector2 screen = ConvertWorldToScreen(body->position);
				DrawLineEx((Vector2) {screen.x, screen.y }, Vector2Add((Vector2) { screen.x, screen.y }, (Vector2) {
					GetRandomFloatValue(-5, 5), GetRandomFloatValue(-5, 5)
				}), ConvertWorldToPixel(body->mass), (Color) { GetRandomFloatValue(150, 255), GetRandomFloatValue(100, 255), GetRandomFloatValue(50, 255), 255 });
			}

			DrawEditor(position);
			break;
		case 2:
			ApplyGravitation(body, -30);
			for (Body* body = bodies; body; body = body->next)
			{
				Step(body, dt);
			}

			//body = bodies;
			//while (body)
			//{
			//	Step(body, dt);
			//	body = body->next;
			//}

			BeginDrawing();
			ClearBackground(BLACK);

			//stats
			DrawText(TextFormat("FPS: %.2f (%.2f ms)", fps, 1000 / fps), 10, 10, 20, WHITE);
			DrawText(TextFormat("FRAME: %.4f", dt), 10, 30, 20, WHITE);

			//DrawCircle((int)position.x, (int)position.y, 10, WHITE);

			//body = bodies;
			for (Body* body = bodies; body; body = body->next)
			{
				Vector2 screen = ConvertWorldToScreen(body->position);
				DrawCircle(screen.x, screen.y, ConvertWorldToPixel(body->mass + 8), (Color) { 255, 100, 0, GetRandomFloatValue(10, 175) });
				DrawCircle(screen.x, screen.y, ConvertWorldToPixel(body->mass), (Color) { 255, 255, 255, GetRandomFloatValue(10, 175) });
			}

			DrawEditor(position);
			break;
		}


		/*while (body)
		{
			DrawCircle((int)body->position.x, (int)body->position.y, body->mass, GREEN);
			body = body->next;
		}*/

		EndDrawing();
	}
	CloseWindow();

	return 0;
}