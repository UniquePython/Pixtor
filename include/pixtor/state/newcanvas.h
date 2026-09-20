#ifndef STATE_NEWCANVAS_H_
#define STATE_NEWCANVAS_H_

typedef struct App App;

void NewCanvasEnter(App *app);
void NewCanvasUpdate(App *app);
void NewCanvasDraw(const App *app);
void NewCanvasExit(App *app);

#endif
