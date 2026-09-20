#ifndef THEME_H_
#define THEME_H_

#include <raylib.h>

typedef struct
{
    struct
    {
        Color menu;
        Color newCanvas;
        Color editor;
        Color toolbar;
    } bg;

    struct
    {
        Color background;
        Color foreground;
        Color onHover;
        Color onPress;
    } button;

    struct
    {
        Color background;
        Color foreground;
        Color border;
        Color borderFocused;
    } textbox;

} Theme;

#endif
