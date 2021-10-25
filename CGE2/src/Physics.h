#pragma once

struct CollisionLine {
	float position;
	float size;
};
struct CollisionBox {
	CollisionLine X;
	CollisionLine Y;
};
bool CheckCollisionAxis(CollisionLine line0, CollisionLine line1);
bool CheckCollision(CollisionBox box0, CollisionBox box1);
