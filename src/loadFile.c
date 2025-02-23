#define _CRT_SECURE_NO_WARNINGS

#include "loadFile.h"
#include "Vector.h"
#include <stdio.h>
#include <stdlib.h>

void _getLength(FILE* file, int* pointsLen, int* surfacesLen)
{
	rewind(file);
	*pointsLen = 0;
	*surfacesLen = 0;
	while (!feof(file))
	{
		char name[100];
		fscanf(file, "%s ", name);
		if (feof(file)) break;
		if (name[0] == 'f' && name[1] == '\0')
		{
			(*surfacesLen)++;
			fscanf(file, "%*d/%*d %*d/%*d %*d/%*d");
		}
		else if (name[0] == 'v' && name[1] == '\0')
		{
			(*pointsLen)++;
			fscanf(file, "%*f %*f %*f");
		}
	}
	rewind(file);
}

void initFile(Vector** points, int* pointsLen, int*** surfaces, int* surfacesLen, char* fileName, double size, Vector origin)
{
	FILE* file = fopen(fileName, "r");
	_getLength(file, pointsLen, surfacesLen);

	*points = calloc(*pointsLen, sizeof(Vector));
	*surfaces = calloc(*surfacesLen, sizeof(int*));
	for (int i = 0; i < *surfacesLen; i++) (*surfaces)[i] = calloc(3, sizeof(int));

	int indexP = 0;
	int indexS = 0;
	while (!feof(file))
	{
		char name[100];
		fscanf(file, "%s ", name);
		if (feof(file)) break;
		if (name[0] == 'v' && name[1] == '\0')
		{
			float x, y, z;
			fscanf(file, "%f %f %f", &x, &y, &z);
			Vector p = { x * size + origin.x, -y * size + origin.y, z * size + origin.z };
			(*points)[indexP++] = p;
		}
		else if (name[0] == 'f' && name[1] == '\0')
		{
			int p1, p2, p3;
			fscanf(file, "%d %d %d", &p1, &p2, &p3);
			(*surfaces)[indexS][2] = p1 - 1;
			(*surfaces)[indexS][1] = p2 - 1;
			(*surfaces)[indexS][0] = p3 - 1;
			indexS++;
		}
	}
	fclose(file);
}