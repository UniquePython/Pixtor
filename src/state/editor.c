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
    canvas = CanvasNew(app->canvasW, app->canvasH, app->theme.bg.canvas);

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

static int GridThickness(void)
{
    float raw = cellSize * 0.05f;

    if (raw < 1.0f)
        return 0;

    return (int)(raw + 0.5f);
}

static void DrawGrid_(const App *app)
{
    int thickness = GridThickness();
    if (thickness == 0)
        return;

    float gridW = canvas.width * cellSize;
    float gridH = canvas.height * cellSize;

    for (int x = 0; x <= canvas.width; x++)
    {
        float lineX = offset.x + x * cellSize;
        DrawRectangleRec((Rectangle){lineX - thickness / 2.0f, offset.y, (float)thickness, gridH}, app->theme.grid);
    }

    for (int y = 0; y <= canvas.height; y++)
    {
        float lineY = offset.y + y * cellSize;
        DrawRectangleRec((Rectangle){offset.x, lineY - thickness / 2.0f, gridW, (float)thickness}, app->theme.grid);
    }
}

static void DrawCanvas(const App *app)
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

    DrawGrid_(app);
}

void EditorDraw(const App *app)
{
    ClearBackground(app->theme.bg.editor);

    BeginScissorMode((int)viewport.x, (int)viewport.y, (int)viewport.width, (int)viewport.height);
    DrawCanvas(app);
    EndScissorMode();

    DrawRectangle(0, 0, app->width, TOOLBAR_H, app->theme.bg.toolbar);
}
