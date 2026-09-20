#ifndef APP_H_
#define APP_H_

#include "pixtor/appstate.h"

typedef struct App
{
    unsigned int width;
    unsigned int height;
    const char *title;

    AppState state;

} App;

void UpdateApp(App *app);
void DrawApp(const App *app);

#endif
