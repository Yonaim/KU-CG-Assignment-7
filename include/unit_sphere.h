#pragma once

extern int    gNumVertices;
extern int    gNumTriangles;
extern int   *gIndexBuffer;
extern float *gVertexBuffer;

void create_unit_sphere();
void free_sphere();
