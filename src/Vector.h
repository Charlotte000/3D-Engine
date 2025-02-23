#pragma once

typedef struct Vector
{
	double x;
	double y;
	double z;
} Vector;

Vector createVector(double x, double y, double z);

void normalize(Vector* vec);

Vector getCrossProduct(Vector vec1, Vector vec2, Vector vec3);

double getDotProduct(Vector vec1, Vector vec2);

void rotate(Vector* v, double x, double y, double z);