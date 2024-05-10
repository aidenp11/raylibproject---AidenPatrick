#include "Force.h"
#include "body.h"

void ApplyGravitation(Body* bodies, float strength)
{
	for (Body* body1 = bodies; body1; body1 = body1->next)
	{
		for (Body* body2 = bodies; body2; body2 = body2->next)
		{
			if (body1 == body2) continue;

			Vector2 direction = Vector2Normalize(Vector2Subtract(body1->position, body2->position));
			float distance = Vector2Distance(body1->position, body2->position);

			distance = fmaxf(distance, 1);
			float force = ((body1->mass * body2->mass) / (distance * distance)) * strength;

			direction = Vector2Scale(direction, force);

			ApplyForce(body1, direction, FM_FORCE);
			ApplyForce(body2, Vector2Negate(direction), FM_FORCE);
		}
	}
}
