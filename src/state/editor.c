#include "pixtor/state/editor.h"
#include "pixtor/canvas.h"
#include "pixtor/appstate.h"
#include "pixtor/app.h"

#include <raylib.h>

#include <stddef.h>
#include <stdlib.h>
#include <math.h>

#define TOOLBAR_H 60

#define MIN_CELL_SIZE 2.0f

typedef enum
{
    TOOL_PENCIL,
    TOOL_ERASER,

} Tool;

static Tool tool;
static Color pencilColor;
static Canvas canvas;
static Color canvasBg;
static Rectangle viewport;
static float cellSize;
static Vector2 offset;
static Vector2 lastCell;
static bool painting;

void EditorEnter(App *app)
{
    canvas = CanvasNew(app->canvasW, app->canvasH, BLANK);

    if (canvas.pixels == NULL)
    {
        ChangeAppState(app, AS_NEW_CANVAS);
        return;
    }

    painting = false;
    canvasBg = app->theme.bg.canvas;
    tool = TOOL_PENCIL;
    pencilColor = BLACK;

    viewport = (Rectangle){0, TOOLBAR_H, (float)app->width, (float)(app->height - TOOLBAR_H)};

    float fitW = viewport.width / canvas.width;
    float fitH = viewport.height / canvas.height;
    cellSize = fitW < fitH ? fitW : fitH;

    if (cellSize < MIN_CELL_SIZE)
        cellSize = MIN_CELL_SIZE;

    offset.x = viewport.x + (viewport.width - canvas.width * cellSize) / 2.0f;
    offset.y = viewport.y + (viewport.height - canvas.height * cellSize) / 2.0f;
}

static Vector2 MouseToCell(Vector2 mouse)
{
    return (Vector2){
        floorf((mouse.x - offset.x) / cellSize),
        floorf((mouse.y - offset.y) / cellSize),
    };
}

static void PaintLine(int x0, int y0, int x1, int y1, Color color)
{
    int dx = abs(x1 - x0);
    int dy = -abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;

    while (true)
    {
        CanvasSet(&canvas, x0, y0, color);

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;

        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

static Color CurrentColor(void)
{
    return tool == TOOL_ERASER ? BLANK : pencilColor;
}

void EditorUpdate(App *app)
{
    (void)app;

    if (IsKeyPressed(KEY_P))
        tool = TOOL_PENCIL;
    if (IsKeyPressed(KEY_E))
        tool = TOOL_ERASER;

    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse, viewport))
    {
        Vector2 cell = MouseToCell(mouse);
        Color color = CurrentColor();

        if (painting)
            PaintLine((int)lastCell.x, (int)lastCell.y, (int)cell.x, (int)cell.y, color);
        else
            CanvasSet(&canvas, (int)cell.x, (int)cell.y, color);

        lastCell = cell;
        painting = true;
    }
    else
    {
        painting = false;
    }
}

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
    DrawRectangleRec((Rectangle){offset.x, offset.y, canvas.width * cellSize, canvas.height * cellSize}, canvasBg);

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
