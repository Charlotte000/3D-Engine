#include "Cube.h"
#include "Vector.h"
#include <stdlib.h>

void initCube(Vector** points, int* pointsLen, int*** surfaces, int* surfacesLen, double size)
{
	*pointsLen = 8;
	*points = calloc(8, sizeof(Vector));
	(*points)[0] = createVector(-size / 2, -size / 2, -size / 2);
	(*points)[1] = createVector(size / 2, -size / 2, -size / 2);
	(*points)[2] = createVector(size / 2, size / 2, -size / 2);
	(*points)[3] = createVector(-size / 2, size / 2, -size / 2);
	(*points)[4] = createVector(-size / 2, -size / 2, size / 2);
	(*points)[5] = createVector(size / 2, -size / 2, size / 2);
	(*points)[6] = createVector(size / 2, size / 2, size / 2);
	(*points)[7] = createVector(-size / 2, size / 2, size / 2);

	*surfacesLen = 12;
	*surfaces = calloc(*surfacesLen, sizeof(int*));
	for (int i = 0; i < 12; i++) (*surfaces)[i] = calloc(3, sizeof(int));
	(*surfaces)[0][0] = 2; (*surfaces)[0][1] = 1; (*surfaces)[0][2] = 0;
	(*surfaces)[1][0] = 0; (*surfaces)[1][1] = 3; (*surfaces)[1][2] = 2;
	(*surfaces)[2][0] = 4; (*surfaces)[2][1] = 5; (*surfaces)[2][2] = 6;
	(*surfaces)[3][0] = 6; (*surfaces)[3][1] = 7; (*surfaces)[3][2] = 4;
	(*surfaces)[4][0] = 0; (*surfaces)[4][1] = 1; (*surfaces)[4][2] = 5;
	(*surfaces)[5][0] = 0; (*surfaces)[5][1] = 5; (*surfaces)[5][2] = 4;
	(*surfaces)[6][0] = 2; (*surfaces)[6][1] = 3; (*surfaces)[6][2] = 6;
	(*surfaces)[7][0] = 7; (*surfaces)[7][1] = 6; (*surfaces)[7][2] = 3;
	(*surfaces)[8][0] = 4; (*surfaces)[8][1] = 3; (*surfaces)[8][2] = 0;
	(*surfaces)[9][0] = 4; (*surfaces)[9][1] = 7; (*surfaces)[9][2] = 3;
	(*surfaces)[10][0] = 1; (*surfaces)[10][1] = 2; (*surfaces)[10][2] = 5;
	(*surfaces)[11][0] = 2; (*surfaces)[11][1] = 6; (*surfaces)[11][2] = 5;
}