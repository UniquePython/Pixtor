#ifndef TEXTBOX_H_
#define TEXTBOX_H_

#include <raylib.h>

#include <stdbool.h>

#define TEXTBOX_MAX_LEN 8

typedef struct
{
    char buf[TEXTBOX_MAX_LEN + 1]; // +1 for the '\0' terminator
    int len;
    bool focused;

    struct
    {
        Color background;
        Color foreground;
        Color border;
        Color borderFocused;

    } color;

    Rectangle hitbox;

} TextBox;

TextBox TextBoxNew(Color background, Color foreground, Color border, Color borderFocused, float x, float y, float width, float height);
void TextBoxUpdate(TextBox *tb);
void TextBoxDraw(const TextBox *tb);
int TextBoxGetInt(const TextBox *tb);
void TextBoxSetInt(TextBox *tb, int value);

#endif
