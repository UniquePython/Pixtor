#include "pixtor/state/editor.h"
#include "pixtor/app.h"

#include <raylib.h>

void EditorEnter(App *app) { (void)app; }
void EditorUpdate(App *app) { (void)app; }
void EditorExit(App *app) { (void)app; }

void EditorDraw(const App *app)
{
    ClearBackground(app->theme.bg.editor);
    DrawText("New Canvas", 20, 20, 40, RAYWHITE);
}
