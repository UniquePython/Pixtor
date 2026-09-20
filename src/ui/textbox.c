#include "pixtor/ui/textbox.h"

TextBox TextBoxNew(Color background, Color foreground, Color border, Color borderFocused, float x, float y, float width, float height)
{
    return (TextBox){
        .buf = {0},
        .len = 0,
        .focused = false,
        .color = {
            .background = background,
            .foreground = foreground,
            .border = border,
            .borderFocused = borderFocused,
        },
        .hitbox = (Rectangle){x, y, width, height},
    };
}

void TextBoxUpdate(TextBox *tb)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        tb->focused = CheckCollisionPointRec(GetMousePosition(), tb->hitbox);

    if (!tb->focused)
        return;

    int c = GetCharPressed();
    while (c > 0)
    {
        if (c >= '0' && c <= '9' && tb->len < TEXTBOX_MAX_LEN)
        {
            tb->buf[tb->len] = (char)c;
            tb->len++;
            tb->buf[tb->len] = '\0';
        }

        c = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && tb->len > 0)
    {
        tb->len--;
        tb->buf[tb->len] = '\0';
    }
}

void TextBoxDraw(const TextBox *tb)
{
    DrawRectangleRec(tb->hitbox, tb->color.background);

    Color border = tb->focused ? tb->color.borderFocused : tb->color.border;
    DrawRectangleLinesEx(tb->hitbox, 2.0f, border);

    int fontSize = 30;
    int textX = (int)tb->hitbox.x + 10;
    int textY = (int)(tb->hitbox.y + (tb->hitbox.height - fontSize) / 2.0f);

    DrawText(tb->buf, textX, textY, fontSize, tb->color.foreground);

    if (tb->focused && ((int)(GetTime() * 2.0) % 2 == 0))
    {
        int cursorX = textX + MeasureText(tb->buf, fontSize) + 2;
        DrawRectangle(cursorX, textY, 2, fontSize, tb->color.foreground);
    }
}

int TextBoxGetInt(const TextBox *tb)
{
    int value = 0;

    for (int i = 0; i < tb->len; i++)
        value = value * 10 + (tb->buf[i] - '0');

    return value;
}
