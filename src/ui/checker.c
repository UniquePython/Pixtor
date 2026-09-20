#include "pixtor/ui/checker.h"

#include <math.h>

void DrawChecker(Rectangle rect, int tile, Vector2 origin)
{
    Color light = (Color){200, 200, 200, 255};
    Color dark = (Color){150, 150, 150, 255};

    int firstCol = (int)floorf((rect.x - origin.x) / tile);
    int firstRow = (int)floorf((rect.y - origin.y) / tile);
    int lastCol = (int)ceilf((rect.x + rect.width - origin.x) / tile);
    int lastRow = (int)ceilf((rect.y + rect.height - origin.y) / tile);

    for (int row = firstRow; row < lastRow; row++)
    {
        for (int col = firstCol; col < lastCol; col++)
        {
            float x0 = origin.x + col * tile;
            float y0 = origin.y + row * tile;
            float x1 = x0 + tile;
            float y1 = y0 + tile;

            // trim the tile to the rectangle
            if (x0 < rect.x)
                x0 = rect.x;
            if (y0 < rect.y)
                y0 = rect.y;
            if (x1 > rect.x + rect.width)
                x1 = rect.x + rect.width;
            if (y1 > rect.y + rect.height)
                y1 = rect.y + rect.height;

            Color color = (((row + col) % 2) == 0) ? light : dark;
            DrawRectangleRec((Rectangle){x0, y0, x1 - x0, y1 - y0}, color);
        }
    }
}
