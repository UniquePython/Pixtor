#include <raylib.h>

#include "pixtor/appstate.h"
#include "pixtor/theme.h"
#include "pixtor/app.h"

int main(void)
{
    Theme theme = {
        .bg = {
            .menu = (Color){18, 18, 18, 255},
            .newCanvas = (Color){18, 18, 18, 255},
            .editor = (Color){18, 18, 18, 255},
        },
        .button = {
            .background = (Color){65, 65, 65, 255},
            .foreground = (Color){200, 200, 200, 255},
            .onHover = (Color){90, 90, 90, 255},
            .onPress = (Color){230, 145, 45, 255},
        },
        .textbox = {
            .background = (Color){65, 65, 65, 255},
            .foreground = (Color){200, 200, 200, 255},
            .border = (Color){200, 200, 200, 255},
            .borderFocused = (Color){230, 145, 45, 255},
        },
    };

    App app = {
        .width = 900,
        .height = 600,
        .title = "Pixtor",
        .state = AS_NONE,
        .theme = theme,
    };

    InitWindow(app.width, app.height, app.title);
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    ChangeAppState(&app, AS_MENU);

    while (!WindowShouldClose())
    {
        UpdateApp(&app);

        BeginDrawing();
        DrawApp(&app);
        EndDrawing();
    }

    ChangeAppState(&app, AS_NONE);
    CloseWindow();

    return 0;
}
