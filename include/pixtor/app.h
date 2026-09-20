#ifndef APP_H_
#define APP_H_

#include "pixtor/appstate.h"
#include "pixtor/theme.h"

typedef struct App
{
    unsigned int width;
    unsigned int height;
    const char *title;

    AppState state;

    Theme theme;

} App;

void ChangeAppState(App *app, AppState newState);

void UpdateApp(App *app);
void DrawApp(const App *app);

#endif
