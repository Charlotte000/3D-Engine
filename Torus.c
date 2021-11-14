#include "Torus.h"
#include "Vector.h"
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

void initTorus(Vector** points, int* pointsLen, int*** surfaces, int* surfacesLen, double radius1, double radius2, int detail)
{
	*pointsLen = detail * detail;
	*points = calloc(*pointsLen, sizeof(Vector));
	for (int j = 0; j < detail; j++)
	{
		double theta = (double)j / detail * PI * 2;
		for (int i = 0; i < detail; i++)
		{
			double fi = (double)i / detail * PI * 2;
			Vector point = {
				(radius2 + radius1 * cos(theta)) * cos(fi),
				(radius2 + radius1 * cos(theta)) * sin(fi),
				radius1 * sin(theta)
			};
			(*points)[j * detail + i] = point;
		}
	}

	*surfacesLen = detail * detail * 2;
	*surfaces = calloc(*surfacesLen, sizeof(int*));
	for (int i = 0; i < *surfacesLen; i++) (*surfaces)[i] = calloc(3, sizeof(int));

	for (int j = 0; j < detail; j++)
	{
		for (int i = 0; i < detail; i++)
		{
			int indexi = (i + 1) % detail;
			int indexj = (j + 1) % detail;
			(*surfaces)[(j * detail + i) * 2][0] = indexi + j * detail;
			(*surfaces)[(j * detail + i) * 2][1] = indexi + indexj * detail;
			(*surfaces)[(j * detail + i) * 2][2] = i + indexj * detail;
			(*surfaces)[(j * detail + i) * 2 + 1][0] = i + j * detail;
			(*surfaces)[(j * detail + i) * 2 + 1][1] = indexi + j * detail;
			(*surfaces)[(j * detail + i) * 2 + 1][2] = i + indexj * detail;
		}
	}
}