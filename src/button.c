#include "button.h"

Button ButtonNewSimple(const char *text, Color color, Color textColor, float x, float y, float width, float height)
{
    return ButtonNew(text, color, color, color, textColor, x, y, width, height);
}

Button ButtonNew(const char *text, Color usual, Color onHover, Color onPress, Color textColor, float x, float y, float width, float height)
{
    return (Button){
        .text = text,
        .color = {
            .usual = usual,
            .onHover = onHover,
            .onPress = onPress,
            .text = textColor,
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

void ButtonDraw(const Button *button)
{
    Color color = button->color.usual;

    if (ButtonIsHovered(button))
        color = button->color.onHover;

    if (ButtonIsClicked(button))
        color = button->color.onPress;

    DrawRectangleRec(button->hitbox, color);

    int fontSize = 20;
    int textWidth = MeasureText(button->text, fontSize);

    float textX = button->hitbox.x + (button->hitbox.width - textWidth) / 2.0f;
    float textY = button->hitbox.y + (button->hitbox.height - fontSize) / 2.0f;

    DrawText(button->text, (int)textX, (int)textY, fontSize, button->color.text);
}
