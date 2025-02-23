#include "Vector.h"
#include "Cube.h"
#include "Sphere.h"
#include "Torus.h"
#include "loadFile.h"
#include "Engine.h"

#include <stdlib.h>
#include <stdbool.h>

const int W = 120;
const int H = 30;
const bool COLOR_MODE = true;
Vector LIGHT = { 0, 0, 1 };

int main()
{
	// Init character buffer
	char* buffer = calloc((W + 1) * H, sizeof(char));
	clearMap(buffer);

	// Init z-buffer
	double** z_buffer = calloc(H, sizeof(double*));
	for (int y = 0; y < H; y++) z_buffer[y] = calloc(W, sizeof(double));
	clearZBuffer(z_buffer);

	// Init color buffer
	int* color_buffer = calloc(W * H, sizeof(int));
	clearColorBuffer(color_buffer);

	double dx = .005;
	double dy = .001;
	double dz = -.002;

	int pointsLen = 0;
	int surfacesLen = 0;

	Vector* points;
	int** surfaces;

	initCube(&points, &pointsLen, &surfaces, &surfacesLen, 2);
	while (true)
	{
		for (int i = 0; i < surfacesLen; i++)
		{
			int index1 = surfaces[i][0];
			int index2 = surfaces[i][1];
			int index3 = surfaces[i][2];
			drawSurface(buffer, z_buffer, color_buffer, &points[index1], &points[index2], &points[index3], (int)((double)i / (surfacesLen-1) * 6));
		}
		for (int i = 0; i < pointsLen; i++) rotate(&points[i], dx, dy, dz);

		drawMap(buffer, color_buffer);

		clearMap(buffer);
		clearZBuffer(z_buffer);
		if (COLOR_MODE) clearColorBuffer(color_buffer);
	}
}