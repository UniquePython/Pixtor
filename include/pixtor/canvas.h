#ifndef CANVAS_H_
#define CANVAS_H_

#include <raylib.h>

#include <stdbool.h>

typedef struct
{
    int width;
    int height;
    Color *pixels;

} Canvas;

Canvas CanvasNew(int width, int height, Color fill);
void CanvasFree(Canvas *canvas);
bool CanvasInBounds(const Canvas *canvas, int x, int y);
Color CanvasGet(const Canvas *canvas, int x, int y);
void CanvasSet(Canvas *canvas, int x, int y, Color color);

#endif
