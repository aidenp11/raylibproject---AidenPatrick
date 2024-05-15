#include "spring.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <raymath.h>

Spring* springs = NULL;
int SpringCount = 0;
Vector2 gravity;

Spring* CreateSpring(struct Body* body1, struct Body* body2, float restLength, float k)
{
	Spring* newSpring = (Spring*)malloc(sizeof(Spring));
	assert(newSpring);

	memset(newSpring, 0, sizeof(newSpring));
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
}
