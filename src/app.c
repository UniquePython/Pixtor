#include "pixtor/app.h"
#include "pixtor/state/menu.h"
#include "pixtor/state/newcanvas.h"
#include "pixtor/state/editor.h"

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

    case AS_NEW_CANVAS:
        NewCanvasExit(app);
        break;

    case AS_EDITOR:
        EditorExit(app);
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

    case AS_NEW_CANVAS:
        NewCanvasEnter(app);
        break;

    case AS_EDITOR:
        EditorEnter(app);
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

    case AS_NEW_CANVAS:
        NewCanvasUpdate(app);
        break;

    case AS_EDITOR:
        EditorUpdate(app);
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

    case AS_NEW_CANVAS:
        NewCanvasDraw(app);
        break;

    case AS_EDITOR:
        EditorDraw(app);
        break;
    }
}
