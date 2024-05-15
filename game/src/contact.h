#pragma once
#include "raylib.h"

typedef struct Contact
{
	struct ncBody* body1;
	struct ncBody* body2;

	float restitution;
	float depth;
	Vector2 normal;

	struct Contact* next;
} Contact_t;

void AddContact(Contact_t* contact, Contact_t** contacts);
void DestroyAllContacts(Contact_t** contacts);
