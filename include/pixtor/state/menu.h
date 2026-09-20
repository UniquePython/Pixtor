#ifndef STATE_MENU_H_
#define STATE_MENU_H_

typedef struct App App;

void MenuEnter(App *app);
void MenuUpdate(App *app);
void MenuDraw(const App *app);
void MenuExit(App *app);

#endif
