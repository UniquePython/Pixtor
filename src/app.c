#include "pixtor/app.h"
#include "pixtor/state/menu.h"

void ChangeAppState(App *app, AppState newState)
{
    if (app->state == newState)
        return;

    switch (app->state)
    {
    case AS_NONE:
        break;

    case AS_MENU:
        MenuExit(app);
        break;
    }

    app->state = newState;

    switch (app->state)
    {
    case AS_NONE:
        break;

    case AS_MENU:
        MenuEnter(app);
        break;
    }
}

void UpdateApp(App *app)
{
    switch (app->state)
    {
    case AS_NONE:
        break;

    case AS_MENU:
        MenuUpdate(app);
        break;
    }
}

void DrawApp(const App *app)
{
    switch (app->state)
    {
    case AS_NONE:
        break;

    case AS_MENU:
        MenuDraw(app);
        break;
    }
}
