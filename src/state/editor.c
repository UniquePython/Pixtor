#include "pixtor/state/editor.h"
#include "pixtor/canvas.h"
#include "pixtor/ui/button.h"
#include "pixtor/ui/colorpicker.h"
#include "pixtor/ui/checker.h"
#include "pixtor/appstate.h"
#include "pixtor/app.h"

#include <raylib.h>

#include <stddef.h>
#include <stdlib.h>
#include <math.h>

#define TOOLBAR_H 60

#define TOOL_BTN_W_PAD 10
#define TOOL_BTN_H 44
#define TOOLBAR_PAD 10

#define SWATCH_SIZE 36
#define SWATCH_LABEL_SIZE 30
#define SWATCH_LABEL_GAP 8
#define SWATCH_GROUP_GAP 24

#define MIN_CELL_SIZE 2.0f

typedef enum
{
    TOOL_PENCIL,
    TOOL_ERASER,

} Tool;

typedef enum
{
    PICK_PENCIL,
    PICK_BG,

} PickTarget;

static Button pencilBtn;
static Button eraserBtn;

static Tool tool;
static Color pencilColor;
static Canvas canvas;
static Color canvasBg;
static Rectangle viewport;
static float cellSize;
static Vector2 offset;
static Vector2 lastCell;
static bool painting;

static ColorPicker picker;
static PickTarget pickTarget;
static Rectangle pencilSwatch;
static Rectangle bgSwatch;

static float penLabelX;
static float bgLabelX;
static float labelY;

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

    float btnY = (TOOLBAR_H - TOOL_BTN_H) / 2.0f;

    float pW = MeasureText("Pencil", BUTTON_FONT_SIZE) + 2 * TOOL_BTN_W_PAD;
    pencilBtn = ButtonNew("Pencil", app->theme.button.background, app->theme.button.foreground,
                          app->theme.button.onHover, app->theme.button.onPress,
                          TOOLBAR_PAD, btnY, pW, TOOL_BTN_H);

    float eW = MeasureText("Eraser", BUTTON_FONT_SIZE) + 2 * TOOL_BTN_W_PAD;
    eraserBtn = ButtonNew("Eraser", app->theme.button.background, app->theme.button.foreground,
                          app->theme.button.onHover, app->theme.button.onPress,
                          TOOLBAR_PAD + pW + TOOLBAR_PAD, btnY, eW, TOOL_BTN_H);

    float fitW = viewport.width / canvas.width;
    float fitH = viewport.height / canvas.height;
    cellSize = fitW < fitH ? fitW : fitH;

    if (cellSize < MIN_CELL_SIZE)
        cellSize = MIN_CELL_SIZE;

    offset.x = viewport.x + (viewport.width - canvas.width * cellSize) / 2.0f;
    offset.y = viewport.y + (viewport.height - canvas.height * cellSize) / 2.0f;

    picker = ColorPickerNew(&app->theme, app->width, app->height);

    float swatchY = (TOOLBAR_H - SWATCH_SIZE) / 2.0f;
    labelY = (TOOLBAR_H - SWATCH_LABEL_SIZE) / 2.0f;
    float x = eraserBtn.hitbox.x + eraserBtn.hitbox.width + SWATCH_GROUP_GAP;

    penLabelX = x;
    x += MeasureText("Pen", SWATCH_LABEL_SIZE) + SWATCH_LABEL_GAP;
    pencilSwatch = (Rectangle){x, swatchY, SWATCH_SIZE, SWATCH_SIZE};
    x += SWATCH_SIZE + SWATCH_GROUP_GAP;

    bgLabelX = x;
    x += MeasureText("BG", SWATCH_LABEL_SIZE) + SWATCH_LABEL_GAP;
    bgSwatch = (Rectangle){x, swatchY, SWATCH_SIZE, SWATCH_SIZE};
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

static bool RectClicked(Rectangle rect)
{
    return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), rect);
}

void EditorUpdate(App *app)
{
    (void)app;

    if (IsKeyPressed(KEY_P))
        tool = TOOL_PENCIL;
    if (IsKeyPressed(KEY_E))
        tool = TOOL_ERASER;

    if (!picker.open)
    {
        if (RectClicked(pencilSwatch))
        {
            pickTarget = PICK_PENCIL;
            ColorPickerOpen(&picker, pencilColor);
        }
        else if (RectClicked(bgSwatch))
        {
            pickTarget = PICK_BG;
            ColorPickerOpen(&picker, canvasBg);
        }

        if (ButtonIsClicked(&pencilBtn))
            tool = TOOL_PENCIL;
        if (ButtonIsClicked(&eraserBtn))
            tool = TOOL_ERASER;
    }

    bool wasOpen = picker.open;

    Color chosen;
    if (ColorPickerUpdate(&picker, &chosen))
    {
        if (pickTarget == PICK_PENCIL)
            pencilColor = chosen;
        else
            canvasBg = chosen;
    }

    if (wasOpen)
        return;

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
    Rectangle canvasRect = {offset.x, offset.y, canvas.width * cellSize, canvas.height * cellSize};
    Rectangle visible = GetCollisionRec(canvasRect, viewport);

    if (visible.width > 0 && visible.height > 0)
        DrawChecker(visible, 12, (Vector2){offset.x, offset.y});

    DrawRectangleRec(canvasRect, canvasBg);

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

static void DrawSwatch(Rectangle swatch, Color color, const App *app)
{
    DrawChecker(swatch, 8, (Vector2){swatch.x, swatch.y});
    DrawRectangleRec(swatch, color);
    DrawRectangleLinesEx(swatch, 2.0f, app->theme.button.foreground);
}

void EditorDraw(const App *app)
{
    ClearBackground(app->theme.bg.editor);

    BeginScissorMode((int)viewport.x, (int)viewport.y, (int)viewport.width, (int)viewport.height);
    DrawCanvas(app);
    EndScissorMode();

    DrawRectangle(0, 0, app->width, TOOLBAR_H, app->theme.bg.toolbar);

    pencilBtn.selected = (tool == TOOL_PENCIL);
    eraserBtn.selected = (tool == TOOL_ERASER);

    ButtonDraw(&pencilBtn);
    ButtonDraw(&eraserBtn);

    DrawText("Pen", (int)penLabelX, (int)labelY, SWATCH_LABEL_SIZE, app->theme.button.foreground);
    DrawSwatch(pencilSwatch, pencilColor, app);

    DrawText("BG", (int)bgLabelX, (int)labelY, SWATCH_LABEL_SIZE, app->theme.button.foreground);
    DrawSwatch(bgSwatch, canvasBg, app);

    ColorPickerDraw(&picker, app->width, app->height);
}
