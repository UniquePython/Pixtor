#ifndef BUTTON_H_
#define BUTTON_H_

#include <raylib.h>

#include <stdbool.h>

typedef struct
{
    const char *text;

    struct
    {
        Color usual;
        Color onHover;
        Color onPress;
        Color text;

    } color;

    Rectangle hitbox;

} Button;

Button ButtonNewSimple(const char *text, Color color, Color textColor, float x, float y, float width, float height);
Button ButtonNew(const char *text, Color usual, Color onHover, Color onPress, Color textColor, float x, float y, float width, float height);
bool ButtonIsHovered(const Button *button);
bool ButtonIsClicked(const Button *button);
void ButtonDraw(const Button *button);

#endif
