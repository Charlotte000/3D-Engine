#include "Sphere.h"
#include "Vector.h"
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

void initSphere(Vector** points, int* pointsLen, int*** surfaces, int* surfacesLen, double radius, int detail)
{
	*pointsLen = detail * detail;
	*points = calloc(*pointsLen, sizeof(Vector));

	for (int b = 0; b < detail; b++)
	{
		for (int c = 0; c < detail; c++)
		{
			float i = (float)b / detail * PI * 2;
			float j = (float)c / detail * PI * 2;
			Vector p = { radius * cos(i) * sin(j), radius * sin(i) * sin(j), radius * cos(j) };
			(*points)[b * detail + c] = p;
		}
	}

	*surfacesLen = detail * detail * 2;
	*surfaces = calloc(*surfacesLen, sizeof(int*));
	for (int i = 0; i < *surfacesLen; i++) (*surfaces)[i] = calloc(3, sizeof(int));

	for (int x = 0; x < detail; x++)
	{
		for (int y = 0; y < detail; y++)
		{
			(*surfaces)[(x * detail + y) * 2][0] = y * detail + x;
			(*surfaces)[(x * detail + y) * 2][1] = y * detail + (x + 1) % detail;
			(*surfaces)[(x * detail + y) * 2][2] = (y + 1) % detail * detail + x;
			(*surfaces)[(x * detail + y) * 2 + 1][0] = (y + 1) % detail * detail + x;
			(*surfaces)[(x * detail + y) * 2 + 1][1] = y * detail + (x + 1) % detail;
			(*surfaces)[(x * detail + y) * 2 + 1][2] = (y + 1) % detail * detail + (x + 1) % detail;
		}
	}

}