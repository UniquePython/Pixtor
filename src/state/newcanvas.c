#include "pixtor/state/newcanvas.h"
#include "pixtor/ui/textbox.h"
#include "pixtor/theme.h"
#include "pixtor/app.h"

#include <raylib.h>

static TextBox width;

void NewCanvasEnter(App *app)
{
    width = TextBoxNew(app->theme.textbox.background, app->theme.textbox.foreground,
                       app->theme.textbox.border, app->theme.textbox.borderFocused,
                       350, 250, 200, 50);
}

void NewCanvasUpdate(App *app)
{
    (void)app;
    TextBoxUpdate(&width);
}

void NewCanvasExit(App *app) { (void)app; }

void NewCanvasDraw(const App *app)
{
    ClearBackground(app->theme.bg.newCanvas);
    DrawText("New Canvas", 20, 20, 40, RAYWHITE);
    TextBoxDraw(&width);
}
