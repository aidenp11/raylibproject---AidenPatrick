#pragma once
#include "body.h"
#include "raymath.h"

inline void ExplicitEuler(Body* body, float timestep)
{
	body->position = Vector2Add(body->position, Vector2Scale(body->velocity, timestep));
	body->velocity = Vector2Add(body->velocity, Vector2Scale(body->acceleration, timestep));
}

inline void SemiImplicitEuler(Body* body, float timestep)
{
	body->velocity = Vector2Add(body->velocity, Vector2Scale(body->acceleration, timestep));
	body->position = Vector2Add(body->position, Vector2Scale(body->velocity, timestep));
}