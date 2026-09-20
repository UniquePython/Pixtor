#include "pixtor/state/menu.h"
#include "pixtor/button.h"
#include "pixtor/theme.h"
#include "pixtor/app.h"

#include <raylib.h>

#define B_WIDTH 100
#define B_HEIGHT 60

static Button new;

void MenuEnter(App *app)
{
    float newx = (app->width / 2) - (B_WIDTH / 2);
    float newy = (17 * app->height / 30) - (B_HEIGHT / 2);

    new = ButtonNew("New", app->theme.button.background, app->theme.button.foreground, app->theme.button.onHover, app->theme.button.onPress, newx, newy, B_WIDTH, B_HEIGHT);
}

void MenuUpdate(App *app)
{
    if (ButtonIsClicked(&new))
        ChangeAppState(app, AS_NEW_CANVAS);
}

void MenuDraw(const App *app)
{
    ClearBackground(app->theme.bg.menu);

    const char *title = "Pixtor";
    const int fontSize = 128;
    int textWidth = MeasureText(title, fontSize);
    int textX = (app->width - textWidth) / 2;
    int textY = (app->height / 5);
    DrawText(title, textX, textY, fontSize, ORANGE);

    ButtonDraw(&new);
}

void MenuExit(App *app)
{
    (void)app;
    return;
}
