#include "pixtor/state/newcanvas.h"
#include "pixtor/app.h"

#include <raylib.h>

void NewCanvasEnter(App *app) { (void)app; }
void NewCanvasUpdate(App *app) { (void)app; }
void NewCanvasExit(App *app) { (void)app; }

void NewCanvasDraw(const App *app)
{
    ClearBackground(app->theme.bg.newCanvas);
    DrawText("New Canvas", 20, 20, 40, RAYWHITE);
}
