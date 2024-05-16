#include "Collision.h"
#include "contact.h"
#include "body.h"
#include "mathf.h"

#include "raymath.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

bool Intersects(Body* body1, Body* body2)
{
	float distance = Vector2Distance(body1->position, body2->position);
	float radius = body1->mass + body2->mass;

	return (distance <= radius);
}

void CreateContacts(Body* bodies, Contact_t** contacts)
{
	for (Body* body1 = bodies; body1; body1 = body1->next)
	{
		for (Body* body2 = body1->next; body2; body2 = body2->next)
		{
			if (body1 == body2) continue;
			if (body1->bodyType != BT_DYNAMIC && body2->bodyType != BT_DYNAMIC) continue;

			if (Intersects(body1, body2))
			{
				Contact_t* contact = GenerateContact(body1, body2);
				AddContact(contact, contacts);
			}
		}
	}
}

Contact_t* GenerateContact(Body* body1, Body* body2)
{
	Contact_t* contact = (Contact_t*)malloc(sizeof(Contact_t));
	assert(contact);

	memset(contact, 0, sizeof(Contact_t));

	contact->body1 = body1;
	contact->body2 = body2;

	Vector2 direction = Vector2Subtract(body1->position, body2->position);
	float distance = Vector2Length(direction);
	if (distance == 0)
	{
		direction = (Vector2){ GetRandomFloatValue(-0.05f, 0.05f), GetRandomFloatValue(-0.05f, 0.05f) };
	}

	float radius = (body1->mass + body2->mass);

	contact->depth = radius - distance;
	contact->normal = Vector2Normalize(direction);
	contact->restitution = (body1->restitution + body2->restitution) * 0.5f;

	return contact;
}

void SeparateContacts(Contact_t* contacts)
{
}

void ResolveContacts(Contact_t* contacts)
{
}
