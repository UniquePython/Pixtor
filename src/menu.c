#include "pixtor/state/menu.h"
#include "pixtor/button.h"
#include "pixtor/theme.h"
#include "pixtor/app.h"

#include <raylib.h>

#define B_WIDTH 70
#define B_HEIGHT 30

static Button new;

void MenuEnter(App *app)
{
    float newx = (app->width / 2) - (B_WIDTH / 2);
    float newy = (app->height / 2) - (B_HEIGHT / 2);

    new = ButtonNew("New", app->theme.button.background, app->theme.button.foreground, app->theme.button.onHover, app->theme.button.onPress, newx, newy, B_WIDTH, B_HEIGHT);
}

void MenuUpdate(App *app)
{
    (void)app;
    return;
}

void MenuDraw(const App *app)
{
    ClearBackground(app->theme.bg.menu);
    ButtonDraw(&new);
}

void MenuExit(App *app)
{
    (void)app;
    return;
}
