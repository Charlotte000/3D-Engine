#include "Vector.h"
#include <math.h>

typedef Vector;

Vector createVector(double x, double y, double z)
{
	Vector v = { x, y, z };
	return v;
}

void normalize(Vector* vec)
{
	double len = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
	vec->x /= len;
	vec->y /= len;
	vec->z /= len;
}

Vector getCrossProduct(Vector vec1, Vector vec2, Vector vec3)
{
	Vector v1 = { vec2.x - vec1.x, vec2.y - vec1.y, vec2.z - vec1.z };
	Vector v2 = { vec3.x - vec1.x, vec3.y - vec1.y, vec3.z - vec1.z };
	normalize(&v1);
	normalize(&v2);

	Vector n = { v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x };
	normalize(&n);
	return n;
}

double getDotProduct(Vector vec1, Vector vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

void rotate(Vector* v, double x, double y, double z)
{
	double newX, newY, newZ;

	// X
	newY = v->y * cos(x) - v->z * sin(x);
	newZ = v->y * sin(x) + v->z * cos(x);
	v->y = newY;
	v->z = newZ;

	// Y
	newX = v->x * cos(y) + v->z * sin(y);
	newZ = -v->x * sin(y) + v->z * cos(y);
	v->x = newX;
	v->z = newZ;

	// Z
	newX = v->x * cos(z) - v->y * sin(z);
	newY = v->x * sin(z) + v->y * cos(z);
	v->x = newX;
	v->y = newY;
}
