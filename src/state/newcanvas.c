#include "pixtor/state/newcanvas.h"
#include "pixtor/ui/button.h"
#include "pixtor/ui/textbox.h"
#include "pixtor/theme.h"
#include "pixtor/app.h"
#include "pixtor/limits.h"

#include <raylib.h>

#include <stdbool.h>
#include <stddef.h>

#define TITLE_SIZE 64
#define LABEL_SIZE 40

#define BOX_W 200
#define BOX_H 50

#define LABEL_GAP 20
#define ROW_GAP 30

#define CREATE_W 160
#define CREATE_H 60

static TextBox widthBox;
static TextBox heightBox;
static Button create;

static int labelX;
static float widthY;
static float heightY;
static float createY;

static const char *error = NULL;

static bool SizeIsValid(int n)
{
    return n >= CANVAS_MIN_SIZE && n <= CANVAS_MAX_SIZE;
}

void NewCanvasEnter(App *app)
{
    int labelW = MeasureText("Height:", LABEL_SIZE);
    int rowW = labelW + LABEL_GAP + BOX_W;

    labelX = (app->width - rowW) / 2;

    widthY = 220;
    heightY = widthY + BOX_H + ROW_GAP;
    createY = heightY + BOX_H + ROW_GAP + 10;

    float boxX = labelX + labelW + LABEL_GAP;

    widthBox = TextBoxNew(app->theme.textbox.background, app->theme.textbox.foreground,
                          app->theme.textbox.border, app->theme.textbox.borderFocused,
                          boxX, widthY, BOX_W, BOX_H);

    heightBox = TextBoxNew(app->theme.textbox.background, app->theme.textbox.foreground,
                           app->theme.textbox.border, app->theme.textbox.borderFocused,
                           boxX, heightY, BOX_W, BOX_H);

    create = ButtonNew("Create", app->theme.button.background, app->theme.button.foreground,
                       app->theme.button.onHover, app->theme.button.onPress,
                       (app->width - CREATE_W) / 2.0f, createY, CREATE_W, CREATE_H);

    error = NULL;
}

void NewCanvasUpdate(App *app)
{
    TextBoxUpdate(&widthBox);
    TextBoxUpdate(&heightBox);

    if (ButtonIsClicked(&create))
    {
        int w = TextBoxGetInt(&widthBox);
        int h = TextBoxGetInt(&heightBox);

        if (!SizeIsValid(w) || !SizeIsValid(h))
        {
            error = TextFormat("Size must be between %d and %d", CANVAS_MIN_SIZE, CANVAS_MAX_SIZE);
        }
        else
        {
            app->canvasW = w;
            app->canvasH = h;
            ChangeAppState(app, AS_EDITOR);
        }
    }
}

void NewCanvasExit(App *app) { (void)app; }

void NewCanvasDraw(const App *app)
{
    ClearBackground(app->theme.bg.newCanvas);

    int titleW = MeasureText("New Canvas", TITLE_SIZE);
    DrawText("New Canvas", (app->width - titleW) / 2, 60, TITLE_SIZE, ORANGE);

    DrawText("Width:", labelX, (widthY + (BOX_H - LABEL_SIZE) / 2.0f), LABEL_SIZE, RAYWHITE);
    DrawText("Height:", labelX, (heightY + (BOX_H - LABEL_SIZE) / 2.0f), LABEL_SIZE, RAYWHITE);

    TextBoxDraw(&widthBox);
    TextBoxDraw(&heightBox);

    ButtonDraw(&create);

    if (error != NULL)
    {
        int errorW = MeasureText(error, 24);
        DrawText(error, (app->width - errorW) / 2, (createY + CREATE_H + 20), 24, RED);
    }
}
