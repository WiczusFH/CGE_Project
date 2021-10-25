#include "Physics.h"
#include <iostream>

bool CheckCollisionAxis(CollisionLine line0, CollisionLine line1)
{
	return line0.position + line0.size >= line1.position && line1.position + line1.size >= line0.position;
}
bool CheckCollision(CollisionBox box0, CollisionBox box1) {
	return CheckCollisionAxis(box0.X, box1.X)&&CheckCollisionAxis(box0.Y, box1.Y);
}
