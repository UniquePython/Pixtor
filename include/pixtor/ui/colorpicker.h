#ifndef COLORPICKER_H_
#define COLORPICKER_H_

#include "pixtor/ui/button.h"
#include "pixtor/ui/textbox.h"
#include "pixtor/theme.h"

#include <raylib.h>

#include <stdbool.h>

typedef struct
{
    bool open;

    Color original;

    TextBox r;
    TextBox g;
    TextBox b;
    TextBox a;

    Button ok;
    Button cancel;

    Rectangle panel;
    Rectangle preview;

    int labelX;
    float rowY[4];

    struct
    {
        Color panel;
        Color text;
        Color dim;

    } color;

} ColorPicker;

ColorPicker ColorPickerNew(const Theme *theme, int windowW, int windowH);

#endif
