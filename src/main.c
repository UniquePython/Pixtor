#include <raylib.h>

#include "pixtor/app.h"

int main(void)
{
    App app = {
        .width = 900,
        .height = 600,
        .title = "Pixtor",
    };

    InitWindow(app.width, app.height, app.title);
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKBLUE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
