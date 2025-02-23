#include "Vector.h"

char getChar(double brightness);

char* getColor(int id);

void drawMap(char* buffer, int* color_buffer);

void getProjection(Vector* p, int* x, int* y);

void clearMap(char* buffer);

void clearZBuffer(double** z_buffer);

void clearColorBuffer(int* color_buffer);

void printAt(char* buffer, double** z_buffer, int* color_buffer, int x, int y, double z, char symbol, int color);

void setAt(char* buffer, double** z_buffer, int* color_buffer, int x, int y, double z, int color);

void drawPoint(char* buffer, double** z_buffer, int* color_buffer, Vector* p, int color);

void drawLine(char* buffer, double** z_buffer, int* color_buffer, Vector* p1, Vector* p2, int color);

void drawSurface(char* buffer, double** z_buffer, int* color_buffer, Vector* p1, Vector* p2, Vector* p3, int color);