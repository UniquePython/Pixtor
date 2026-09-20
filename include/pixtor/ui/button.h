#ifndef BUTTON_H_
#define BUTTON_H_

#include <raylib.h>

#include <stdbool.h>

typedef struct
{
    const char *text;

    struct
    {
        Color background;
        Color foreground;
        Color onHover;
        Color onPress;

    } color;

    Rectangle hitbox;

    bool selected;

} Button;

Button ButtonNewSimple(const char *text, Color background, Color foreground, float x, float y, float width, float height);
Button ButtonNew(const char *text, Color background, Color foreground, Color onHover, Color onPress, float x, float y, float width, float height);
bool ButtonIsHovered(const Button *button);
bool ButtonIsClicked(const Button *button);
bool ButtonIsHeld(const Button *button);
void ButtonDraw(const Button *button);

#endif
