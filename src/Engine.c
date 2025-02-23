#include "Engine.h"
#include "Vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

extern bool COLOR_MODE;
extern int W, H; 
extern Vector LIGHT;

char getChar(double brightness)
{
	char* string = ".-^*!/(%&@";
	if (brightness <= 0) return ' ';
	if (brightness >= 1) return string[strlen(string) - 1];
	return string[(int)(brightness * (strlen(string) - 1))];
}

char* getColor(int id)
{
	switch (id)
	{
	case 0: return "\033[0m";	// White
	case 1: return "\x1B[31m";	// Red
	case 2: return "\x1B[32m";	// Green
	case 3: return "\x1B[34m";  // Blue
	case 4: return "\x1B[33m";	// Yellow
	case 5: return "\x1B[35m";	// Purple
	case 6: return "\x1B[36m";	// Cyan
	default: return getColor(0);
	}
}

void drawMap(char* buffer, int* color_buffer)
{
	printf("\033[1;1H");
	if (COLOR_MODE)
	{
		char* output = calloc((W + 1) * H * 8, sizeof(char));

		int index = 0;
		for (int y = 0; y < H; y++)
		{
			for (int x = 0; x < W + 1; x++)
			{
				char c = buffer[y * (W + 1) + x];

				if (x != W && c != ' ')
				{
					char* colorCode = getColor(color_buffer[y * W + x]);

					for (int i = 0; i < (int)strlen(colorCode); i++)
					{
						output[index++] = colorCode[i];
					}
				}
				output[index++] = c;
			}
		}

		printf("%s", output);
	}
	else
	{
		printf("%s", buffer);
	}
}

void getProjection(Vector* p, int* x, int* y)
{
	double z = p->z + 10;
	if (z > 0 && z < .01) z = .01;
	if (z < 0 && z > -.01) z = -.01;
	*x = (int)(p->x / z * 100 + W / 2.0);
	*y = (int)(p->y / z * 100 + H / 2.0);
}

void clearMap(char* buffer)
{
	for (int y = 0; y < H; y++)
	{
		for (int x = 0; x < W; x++)
		{
			buffer[y * (W + 1) + x] = ' ';
		}
		buffer[y * (W + 1) + W] = '\n';
	}
	buffer[H * (W + 1) - 1] = '\0';
}

void clearZBuffer(double** z_buffer)
{
	for (int y = 0; y < H; y++)
	{
		for (int x = 0; x < W; x++)
		{
			z_buffer[y][x] = INFINITY;
		}
	}
}

void clearColorBuffer(int* color_buffer)
{
	for (int i = 0; i < W * H; i++)
	{
		color_buffer[i] = 0;
	}
}

void printAt(char* buffer, double** z_buffer, int* color_buffer, int x, int y, double z, char symbol, int color)
{
	if (x >= 0 && x < W && y >= 0 && y < H)
	{
		if (z < z_buffer[y][x])
		{
			buffer[y * (W + 1) + x] = symbol;
			z_buffer[y][x] = z;
			color_buffer[y * W + x] = color;
		}
	}
}

void setAt(char* buffer, double** z_buffer, int* color_buffer, int x, int y, double z, int color)
{
	printAt(buffer, z_buffer, color_buffer, x, y, z, '#', color);
}


void drawPoint(char* buffer, double** z_buffer, int* color_buffer, Vector* p, int color)
{
	int x = 0;
	int y = 0;
	getProjection(p, &x, &y);
	setAt(buffer, z_buffer, color_buffer, x, y, p->z, color);
}

void drawLine(char* buffer, double** z_buffer, int* color_buffer, Vector* p1, Vector* p2, int color)
{
	int x1 = 0;
	int y1 = 0;
	int x2 = 0;
	int y2 = 0;
	getProjection(p1, &x1, &y1);
	getProjection(p2, &x2, &y2);

	double length = sqrt(pow((double)x1 - x2, 2) + pow((double)y1 - y2, 2));
	double dx = ((double)x2 - x1) / length;
	double dy = ((double)y2 - y1) / length;
	double dz = (p2->z - p1->z) / length;

	double x = x1;
	double y = y1;
	double z = p1->z;

	for (int step = 0; step < length; step++)
	{
		setAt(buffer, z_buffer, color_buffer, (int)x, (int)y, z, color);
		x += dx;
		y += dy;
		z += dz;
	}
}

void _getMinMax(int x1, int y1, int x2, int y2, int y, double* xmin, double* xmax)
{
	if ((y2 <= y && y <= y1) || (y1 <= y && y <= y2))
	{
		if (y2 != y1)
		{
			float x = ((float)y - y1) * (x2 - x1) / (y2 - y1) + x1;
			*xmin = (double)fmin(*xmin, x);
			*xmax = (double)fmax(*xmax, x);
		}
		else
		{
			*xmin = (double)fmin(fmin(*xmin, x1), x2);
			*xmax = (double)fmax(fmax(*xmax, x1), x2);
		}
	}
}

double _get_z(Vector p1, Vector p2, Vector p3, double x, double y)
{
	double denominator = (p2.y - p3.y) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.y - p3.y);
	double w1 = ((p2.y - p3.y) * ((double)x - p3.x) + (p3.x - p2.x) * ((double)y - p3.y)) / denominator;
	double w2 = ((p3.y - p1.y) * ((double)x - p3.x) + (p1.x - p3.x) * ((double)y - p3.y)) / denominator;
	double w3 = 1 - w1 - w2;
	return p1.z * w1 + p2.z * w2 + p3.z * w3;
}

void drawSurface(char* buffer, double** z_buffer, int* color_buffer, Vector* p1, Vector* p2, Vector* p3, int color)
{
	Vector normal = getCrossProduct(*p1, *p2, *p3);
	if (normal.z <= 0)
	{
		normalize(&LIGHT);
		double brightness = -getDotProduct(normal, LIGHT);

		int x1, y1, x2, y2, x3, y3;
		getProjection(p1, &x1, &y1);
		getProjection(p2, &x2, &y2);
		getProjection(p3, &x3, &y3);
		Vector pp1 = { x1, y1, p1->z };
		Vector pp2 = { x2, y2, p2->z };
		Vector pp3 = { x3, y3, p3->z };

		for (int y = (int)fmin(fmin(y1, y2), y3); y < fmax(fmax(y1, y2), y3); y++)
		{
			double xmin = INFINITY;
			double xmax = -INFINITY;
			_getMinMax(x1, y1, x2, y2, y, &xmin, &xmax);
			_getMinMax(x2, y2, x3, y3, y, &xmin, &xmax);
			_getMinMax(x1, y1, x3, y3, y, &xmin, &xmax);
			for (int x = (int)xmin; x < (int)xmax; x++)
			{
				double z = _get_z(pp1, pp2, pp3, (double)x, (double)y);
				printAt(buffer, z_buffer, color_buffer, x, y, z, getChar(brightness), color);
			}
		}
	}
}