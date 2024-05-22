#pragma once

typedef struct Spring
{
	struct Body* body1;
	struct Body* body2;
	float restLength;
	float k; // stiffness

	struct Spring* next;
	struct Spring* prev;
} Spring;

extern Spring* springs;

Spring* CreateSpring(struct Body* body1, struct Body* body2, float restLength, float k);
void AddSpring(Spring* Spring);
void DestroySpring(Spring* Spring);
void DestroyAllSprings();
void ApplySpringForce(Spring* Spring);
//void ApplySpringForcePosition(Vector2 position, Body* body, float restLength, float k, float damping);
