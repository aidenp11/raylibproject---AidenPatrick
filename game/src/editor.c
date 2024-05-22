#include "editor.h"
#include "body.h"
#include "render.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui/src/raygui.h"

#define EDITOR_DATA(data) TextFormat("%0.2f", data), &data

bool ncEditorActive = true;
bool ncEditorIntersect = false;
Rectangle editorRect;
Texture2D cursorTexture;

EditorData editorData;

//anchor01 = { 816, 48 };
//
//EditorBoxActive = true;
//massMinBarValue = 50.0f;
//massMaxSliderValue = 0.0f;
//GravitationValue = 0.0f;

void InitEditor()
{
    GuiLoadStyle("raygui/styles/sunny/style_sunny.rgs");
    HideCursor();
    Image image = LoadImage("resources/reticle.png");
    cursorTexture = LoadTextureFromImage(image);
    UnloadImage(image);

    editorData.anchor01 = (Vector2){ 816, 48 };

    editorData.EditorBoxActive = true;
    editorData.massMinBarValue = 2.0f;
    editorData.massMaxSliderValue = 2.0f;
    editorData.GravitationValue = 0.0f;
    editorData.GravityScaleSliderValue = 0.0f;

    editorRect = (Rectangle){ editorData.anchor01.x + 0, editorData.anchor01.y + 0, 304, 616 };
}

void UpdateEditor(Vector2 position)
{
    if (editorData.DropdownBox004Active == 0)
    {
        editorData.bodyType = BT_DYNAMIC;
    }
    else if (editorData.DropdownBox004Active == 1)
    {
        editorData.bodyType = BT_KINEMATIC;
    }
    else
    {
        editorData.bodyType = BT_STATIC;
    }
    if (IsKeyPressed(KEY_TAB)) editorData.EditorBoxActive = !editorData.EditorBoxActive;

    ncEditorIntersect = editorData.EditorBoxActive && CheckCollisionPointRec(position, editorRect);
}

void DrawEditor(Vector2 position)
{
    if (editorData.EditorBoxActive)
    {
        editorData.EditorBoxActive = !GuiWindowBox((Rectangle){ editorData.anchor01.x + 0, editorData.anchor01.y + 0, 304, 616 }, "Editor Box");
        GuiSliderBar((Rectangle) { editorData.anchor01.x + 120, editorData.anchor01.y + 24, 120, 16 }, "Damping", EDITOR_DATA(editorData.damping), -15, 15);
        GuiSliderBar((Rectangle) { editorData.anchor01.x + 120, editorData.anchor01.y + 64, 120, 16 }, "Mass Min", EDITOR_DATA(editorData.massMinBarValue), 0, 15);
        GuiSliderBar((Rectangle) { editorData.anchor01.x + 120, editorData.anchor01.y + 96, 120, 16 }, "Mass Max", NULL, & editorData.massMaxSliderValue, 0, 15);
        GuiSliderBar((Rectangle) { editorData.anchor01.x + 120, editorData.anchor01.y + 242, 120, 16 }, "Gravitation", NULL, & editorData.GravitationValue, -100, 100);
        GuiSliderBar((Rectangle) { editorData.anchor01.x + 120, editorData.anchor01.y + 282, 120, 16 }, "Gravity Scale", NULL, & editorData.GravityScaleSliderValue, -150, 150);
        if (GuiDropdownBox((Rectangle) { editorData.anchor01.x + 96, editorData.anchor01.y + 136, 120, 24 }, "Dynamic;Kinematic;Static", & editorData.DropdownBox004Active, editorData.DropdownBox004EditMode)) editorData.DropdownBox004EditMode = !editorData.DropdownBox004EditMode;

    }

    DrawTexture(cursorTexture, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, PINK);
}

Body* GetBodyIntersect(Body* bodies, Vector2 position)
{
    for (Body* body = bodies; body; body = body->next)
    {
        Vector2 screen = ConvertWorldToScreen(body->position);
        if (CheckCollisionPointCircle(position, screen, ConvertWorldToPixel(body->mass * 0.5f)))
        {
            return body;
        }
    }

    return NULL;
}

void DrawLineBodyToPosition(Body* body, Vector2 position)
{
    Vector2 screen = ConvertWorldToScreen(body->position);
    DrawLine((int)screen.x, (int)screen.y, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, YELLOW);
}
