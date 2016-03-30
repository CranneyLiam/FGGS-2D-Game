#pragma once

#include "S2D\S2D.h"

#include <cmath>

using namespace S2D;

class Circle
{
public:
	Circle(Vector2 position, float radius);
	~Circle(void);

	const Vector2& Center() const;
	void Center(const Vector2 center);

	const float& Radius() const;
	void Radius(const float radius);

	bool Intersects(const Rect& rectangle);

private:
	Vector2 _center;
	float _radius;
};

