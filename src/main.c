#include <raylib.h>

#include "pixtor/app.h"
#include "pixtor/appstate.h"

int main(void)
{
    App app = {
        .width = 900,
        .height = 600,
        .title = "Pixtor",
        .state = AS_MENU,
    };

    InitWindow(app.width, app.height, app.title);
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    while (!WindowShouldClose())
    {
        UpdateApp(&app);

        BeginDrawing();
        ClearBackground(DARKBLUE);
        DrawApp(&app);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
