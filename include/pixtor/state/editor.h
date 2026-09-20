#ifndef STATE_EDITOR_H_
#define STATE_EDITOR_H_

typedef struct App App;

void EditorEnter(App *app);
void EditorUpdate(App *app);
void EditorDraw(const App *app);
void EditorExit(App *app);

#endif
