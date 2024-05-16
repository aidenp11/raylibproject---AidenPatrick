#pragma once
#include "raylib.h"

typedef struct Contact
{
	struct Body* body1;
	struct Body* body2;

	float restitution;
	float depth;
	Vector2 normal;

	struct Contact* next;
} Contact_t;

void AddContact(Contact_t* contact, Contact_t** contacts);
void DestroyAllContacts(Contact_t** contacts);
