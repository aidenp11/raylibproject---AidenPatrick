#include "spring.h"
#include "body.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <raymath.h>

Spring* springs = NULL;
int SpringCount = 0;
Vector2 gravity;

Spring* CreateSpring(Body* body1, Body* body2, float restLength, float k)
{
	Spring* newSpring = (Spring*)malloc(sizeof(Spring));
	assert(newSpring);

	memset(newSpring, 0, sizeof(Spring));
	newSpring->body1 = body1;
	newSpring->body2 = body2;
	newSpring->restLength = restLength;
	newSpring->k = k;

	return newSpring;
}

void AddSpring(Spring* Spring)
{
	assert(Spring);

	Spring->prev = NULL;
	Spring->next = springs;

	if (springs != NULL) {
		springs->prev = Spring;
	}

	springs = Spring;
	SpringCount++;
}

void DestroySpring(Spring* Spring)
{
	assert(Spring);

	if (Spring->prev != NULL) {
		Spring->prev->next = Spring->next;
	}

	if (Spring->next != NULL) {
		Spring->next->prev = Spring->prev;
	}

	if (Spring == springs) {
		springs = Spring->next;
	}

	SpringCount--;
	free(Spring);
}

void ApplySpringForce(Spring* spring)
{
	for (Spring* spring = springs; spring; spring = spring->next)
	{
		Vector2 direction = Vector2Subtract(spring->body1->position, spring->body2->position);
		if (direction.x == 0 && direction.y == 0) continue;

		float length = Vector2Length(direction);
		float x = length - spring->restLength;
		float force = -spring->k * x;

		Vector2 ndirection = Vector2Normalize(direction);

		ApplyForce(spring->body1, Vector2Scale(ndirection, force), FM_FORCE);
		ApplyForce(spring->body2, Vector2Scale(Vector2Negate(ndirection), force), FM_FORCE);
	}
}
