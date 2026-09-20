#ifndef THEME_H_
#define THEME_H_

#include <raylib.h>

typedef struct
{
    struct
    {
        Color menu;
    } bg;

    struct
    {
        Color background;
        Color foreground;
        Color onHover;
        Color onPress;
    } button;

} Theme;

#endif
