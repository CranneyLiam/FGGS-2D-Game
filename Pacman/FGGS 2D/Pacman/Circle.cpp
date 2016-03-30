#include "Circle.h"


Circle::Circle(Vector2 position, float radius)
	: _center(position), _radius(radius)
{
}


Circle::~Circle(void)
{
}

const Vector2& Circle::Center() const
{
	return _center;
}

void Circle::Center(const Vector2 center)
{
	_center = center;
}

const float& Circle::Radius() const
{
	return _radius;
}

void Circle::Radius(const float radius)
{
	_radius = radius;
}

bool Circle::Intersects(const Rect& rectangle)
{
	Vector2 v(MathHelper::Clamp(_center.X, rectangle.X, rectangle.X + rectangle.Width), MathHelper::Clamp(_center.Y, rectangle.Y, rectangle.Y + rectangle.Height));

	Vector2 direction = _center - v;

	float distanceSquared = direction.LengthSquared();

	return ((distanceSquared > 0) && (distanceSquared < _radius * _radius));
}