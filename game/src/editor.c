#include "editor.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui/src/raygui.h"

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
    editorData.massMinBarValue = 1.0f;
    editorData.massMaxSliderValue = 3.0f;
    editorData.GravitationValue = -30.0f;

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
        GuiSliderBar((Rectangle) { editorData.anchor01.x + 120, editorData.anchor01.y + 24, 120, 16 }, "Damping", NULL, & editorData.damping, -15, 15);
        GuiSliderBar((Rectangle) { editorData.anchor01.x + 120, editorData.anchor01.y + 64, 120, 16 }, "Mass Min", NULL, & editorData.massMinBarValue, 0, 15);
        GuiSliderBar((Rectangle) { editorData.anchor01.x + 120, editorData.anchor01.y + 96, 120, 16 }, "Mass Max", NULL, & editorData.massMaxSliderValue, 0, 15);
        GuiSliderBar((Rectangle) { editorData.anchor01.x + 120, editorData.anchor01.y + 242, 120, 16 }, "Gravitation", NULL, & editorData.GravitationValue, -100, 100);
        GuiSliderBar((Rectangle) { editorData.anchor01.x + 120, editorData.anchor01.y + 282, 120, 16 }, "Gravity Scale", NULL, & editorData.GravityScaleSliderValue, 0, 150);
        if (GuiDropdownBox((Rectangle) { editorData.anchor01.x + 96, editorData.anchor01.y + 136, 120, 24 }, "Dynamic;Kinematic;Static", & editorData.DropdownBox004Active, editorData.DropdownBox004EditMode)) editorData.DropdownBox004EditMode = !editorData.DropdownBox004EditMode;

    }

    DrawTexture(cursorTexture, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, PINK);
}
