#include "pixtor/button.h"

Button ButtonNewSimple(const char *text, Color background, Color foreground, float x, float y, float width, float height)
{
    return ButtonNew(text, background, foreground, background, background, x, y, width, height);
}

Button ButtonNew(const char *text, Color background, Color foreground, Color onHover, Color onPress, float x, float y, float width, float height)
{
    return (Button){
        .text = text,
        .color = {
            .background = background,
            .foreground = foreground,
            .onHover = onHover,
            .onPress = onPress,
        },
        .hitbox = (Rectangle){
            .x = x,
            .y = y,
            .width = width,
            .height = height,
        },
    };
}

bool ButtonIsHovered(const Button *button)
{
    return CheckCollisionPointRec(GetMousePosition(), button->hitbox);
}

bool ButtonIsClicked(const Button *button)
{
    return CheckCollisionPointRec(GetMousePosition(), button->hitbox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

bool ButtonIsHeld(const Button *button)
{
    return CheckCollisionPointRec(GetMousePosition(), button->hitbox) && IsMouseButtonDown(MOUSE_BUTTON_LEFT);
}

void ButtonDraw(const Button *button)
{
    Color color = button->color.background;

    if (ButtonIsHovered(button))
        color = button->color.onHover;

    if (ButtonIsHeld(button))
        color = button->color.onPress;

    DrawRectangleRec(button->hitbox, color);

    int fontSize = 40;
    int textWidth = MeasureText(button->text, fontSize);

    float textX = button->hitbox.x + (button->hitbox.width - textWidth) / 2.0f;
    float textY = button->hitbox.y + (button->hitbox.height - fontSize) / 2.0f;

    DrawText(button->text, (int)textX, (int)textY, fontSize, button->color.foreground);
}
