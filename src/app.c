#include "pixtor/app.h"
#include "pixtor/state/menu.h"

void UpdateApp(App *app)
{
    switch (app->state)
    {
    case AS_MENU:
        MenuUpdate(app);
        break;
    }
}

void DrawApp(const App *app)
{
    switch (app->state)
    {
    case AS_MENU:
        MenuDraw(app);
        break;
    }
}
