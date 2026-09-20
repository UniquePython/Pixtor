#include "pixtor/state/editor.h"
#include "pixtor/canvas.h"
#include "pixtor/appstate.h"
#include "pixtor/app.h"

#include <raylib.h>

#include <stddef.h>

#define TOOLBAR_H 60

#define MIN_CELL_SIZE 2.0f

static Canvas canvas;
static Rectangle viewport;
static float cellSize;
static Vector2 offset;

void EditorEnter(App *app)
{
    canvas = CanvasNew(app->canvasW, app->canvasH, WHITE);

    if (canvas.pixels == NULL)
    {
        ChangeAppState(app, AS_NEW_CANVAS);
        return;
    }

    viewport = (Rectangle){0, TOOLBAR_H, (float)app->width, (float)(app->height - TOOLBAR_H)};

    float fitW = viewport.width / canvas.width;
    float fitH = viewport.height / canvas.height;
    cellSize = fitW < fitH ? fitW : fitH;

    if (cellSize < MIN_CELL_SIZE)
        cellSize = MIN_CELL_SIZE;

    offset.x = viewport.x + (viewport.width - canvas.width * cellSize) / 2.0f;
    offset.y = viewport.y + (viewport.height - canvas.height * cellSize) / 2.0f;
}

void EditorUpdate(App *app) { (void)app; }

void EditorExit(App *app)
{
    (void)app;
    CanvasFree(&canvas);
}

static void DrawCanvas(void)
{
    for (int y = 0; y < canvas.height; y++)
    {
        for (int x = 0; x < canvas.width; x++)
        {
            Rectangle cell = {
                offset.x + x * cellSize,
                offset.y + y * cellSize,
                cellSize,
                cellSize,
            };

            DrawRectangleRec(cell, CanvasGet(&canvas, x, y));
        }
    }
}

void EditorDraw(const App *app)
{
    ClearBackground(app->theme.bg.editor);

    BeginScissorMode((int)viewport.x, (int)viewport.y, (int)viewport.width, (int)viewport.height);
    DrawCanvas();
    EndScissorMode();

    DrawRectangle(0, 0, app->width, TOOLBAR_H, app->theme.bg.toolbar);
}
