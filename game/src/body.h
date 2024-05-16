#pragma once
#include "raylib.h"
#include "raymath.h"

typedef enum BodyType
{
	BT_STATIC,
	BT_KINEMATIC,
	BT_DYNAMIC
} BodyType;

typedef enum
{
	FM_FORCE,
	FM_IMPULSE,
	FM_VELOCITY
} ForceMode;

typedef struct Body
{
	BodyType bodyType;
	// force -> acceleration -> velocity -> position
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	Vector2 force;

	float mass;
	float inverseMass;
	float gravityScale;
	float damping;

	float restitution;

	struct Body* next;
	struct Body* prev;
} Body;

inline void ApplyForce(Body* body, Vector2 force, ForceMode forceMode)
{
	if (body->bodyType != BT_DYNAMIC)
	{
		return;
	}

	switch (forceMode)
	{
	case FM_FORCE:
		body->force = Vector2Add(body->force, force);
		break;
	case FM_IMPULSE:
		body->velocity = Vector2Scale(force, body->inverseMass);
		break;
	case FM_VELOCITY:
		body->velocity = force;
		break;
	}

	//body->force = Vector2Add(body->force, force);

}

inline void ClearForce(Body* body)
{
	body->force = Vector2Zero();
}

void Step(Body* body, float timeStep);