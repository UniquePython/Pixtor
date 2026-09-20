#include "pixtor/canvas.h"
#include "pixtor/limits.h"

#include <stdlib.h>

Canvas CanvasNew(int width, int height, Color fill)
{
    Canvas canvas = {0};

    if (width < CANVAS_MIN_SIZE || width > CANVAS_MAX_SIZE ||
        height < CANVAS_MIN_SIZE || height > CANVAS_MAX_SIZE)
        return canvas;

    canvas.pixels = malloc((size_t)width * (size_t)height * sizeof(Color));
    if (canvas.pixels == NULL)
        return canvas;

    canvas.width = width;
    canvas.height = height;

    for (int i = 0; i < width * height; i++)
        canvas.pixels[i] = fill;

    return canvas;
}

void CanvasFree(Canvas *canvas)
{
    free(canvas->pixels);
    canvas->pixels = NULL;
    canvas->width = 0;
    canvas->height = 0;
}

bool CanvasInBounds(const Canvas *canvas, int x, int y)
{
    return x >= 0 && x < canvas->width && y >= 0 && y < canvas->height;
}

Color CanvasGet(const Canvas *canvas, int x, int y)
{
    if (!CanvasInBounds(canvas, x, y))
        return BLANK;

    return canvas->pixels[y * canvas->width + x];
}

void CanvasSet(Canvas *canvas, int x, int y, Color color)
{
    if (!CanvasInBounds(canvas, x, y))
        return;

    canvas->pixels[y * canvas->width + x] = color;
}
