#include "pixtor/ui/colorpicker.h"

#include <raylib.h>

#define CP_TITLE_SIZE 40
#define CP_LABEL_SIZE 30
#define CP_BOX_W 110
#define CP_BOX_H 44
#define CP_PREVIEW_W 120
#define CP_GAP 20
#define CP_ROW_GAP 14
#define CP_PANEL_PAD 24
#define CP_BTN_H 44
#define CP_BTN_TEXT_PAD 10

static int MaxInt(int a, int b)
{
    return a > b ? a : b;
}

ColorPicker ColorPickerNew(const Theme *theme, int windowW, int windowH)
{
    ColorPicker cp = {0};

    // widths of each band
    int labelW = MeasureText("R:", CP_LABEL_SIZE);
    labelW = MaxInt(labelW, MeasureText("G:", CP_LABEL_SIZE));
    labelW = MaxInt(labelW, MeasureText("B:", CP_LABEL_SIZE));
    labelW = MaxInt(labelW, MeasureText("A:", CP_LABEL_SIZE));

    int rowsW = labelW + CP_GAP + CP_BOX_W + CP_GAP + CP_PREVIEW_W;
    int rowsH = 4 * CP_BOX_H + 3 * CP_ROW_GAP;

    int titleW = MeasureText("Color", CP_TITLE_SIZE);

    int cancelW = MeasureText("Cancel", BUTTON_FONT_SIZE) + 2 * CP_BTN_TEXT_PAD;
    int okW = MeasureText("OK", BUTTON_FONT_SIZE) + 2 * CP_BTN_TEXT_PAD;
    int buttonsW = cancelW + CP_GAP + okW;

    // panel size
    int contentW = MaxInt(titleW, MaxInt(rowsW, buttonsW));
    int panelW = contentW + 2 * CP_PANEL_PAD;
    int panelH = CP_PANEL_PAD + CP_TITLE_SIZE + CP_GAP + rowsH + CP_GAP + CP_BTN_H + CP_PANEL_PAD;

    // centered in the window
    cp.panel = (Rectangle){
        (windowW - panelW) / 2.0f,
        (windowH - panelH) / 2.0f,
        (float)panelW,
        (float)panelH,
    };

    float left = cp.panel.x + CP_PANEL_PAD;
    float top = cp.panel.y + CP_PANEL_PAD;

    float rowsTop = top + CP_TITLE_SIZE + CP_GAP;

    float boxX = left + labelW + CP_GAP;

    for (int i = 0; i < 4; i++)
        cp.rowY[i] = rowsTop + i * (CP_BOX_H + CP_ROW_GAP);

    cp.labelX = (int)left;

    cp.r = TextBoxNew(theme->textbox.background, theme->textbox.foreground,
                      theme->textbox.border, theme->textbox.borderFocused,
                      boxX, cp.rowY[0], CP_BOX_W, CP_BOX_H);

    cp.g = TextBoxNew(theme->textbox.background, theme->textbox.foreground,
                      theme->textbox.border, theme->textbox.borderFocused,
                      boxX, cp.rowY[1], CP_BOX_W, CP_BOX_H);

    cp.b = TextBoxNew(theme->textbox.background, theme->textbox.foreground,
                      theme->textbox.border, theme->textbox.borderFocused,
                      boxX, cp.rowY[2], CP_BOX_W, CP_BOX_H);

    cp.a = TextBoxNew(theme->textbox.background, theme->textbox.foreground,
                      theme->textbox.border, theme->textbox.borderFocused,
                      boxX, cp.rowY[3], CP_BOX_W, CP_BOX_H);

    cp.preview = (Rectangle){
        boxX + CP_BOX_W + CP_GAP,
        rowsTop,
        (float)CP_PREVIEW_W,
        (float)rowsH,
    };

    float btnY = rowsTop + rowsH + CP_GAP;
    float btnX = cp.panel.x + (cp.panel.width - buttonsW) / 2.0f;

    cp.cancel = ButtonNew("Cancel", theme->button.background, theme->button.foreground,
                          theme->button.onHover, theme->button.onPress,
                          btnX, btnY, cancelW, CP_BTN_H);

    cp.ok = ButtonNew("OK", theme->button.background, theme->button.foreground,
                      theme->button.onHover, theme->button.onPress,
                      btnX + cancelW + CP_GAP, btnY, okW, CP_BTN_H);

    cp.open = false;
    cp.original = BLANK;

    cp.color.panel = theme->popup.panel;
    cp.color.text = theme->button.foreground;
    cp.color.dim = theme->popup.dim;

    return cp;
}
