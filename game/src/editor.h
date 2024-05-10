#pragma once
#include "raylib.h"
#include "body.h"

typedef struct EditorData
{
    Vector2 anchor01;

    bool EditorBoxActive;
    float massMinBarValue;
    float massMaxSliderValue;
    BodyType bodyType;
    float GravitationValue;
    float GravityScale;
    float damping;
    bool DropdownBox004EditMode;
    int DropdownBox004Active;
    float GravityScaleSliderValue;
    
}EditorData;

extern bool ncEditorActive;
extern bool ncEditorIntersect;

void InitEditor();
void UpdateEditor(Vector2 position);
void DrawEditor(Vector2 position);