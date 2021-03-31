#ifndef _print_BUTTON_
#define _print_BUTTON_
#include <M5Core2.h>
#include <LovyanGFX.hpp>

class PrintButton
{
private:
    int32_t _x0;
    int32_t _y0;
    int32_t _lcd_x0;
    int32_t _lcd_y0;
    int32_t _width;
    int32_t _height;
    int32_t _pushSpace;
    bool _isToggle;
    uint16_t _activeColor;
    uint16_t _inactiveColor;
    uint16_t _shadowColor;
    uint16_t _borderColor;
    uint16_t _lineColor;
    uint16_t _backgroundColor;
    static const int32_t lineWidth;
    LGFX_Sprite sprite_button;
    LGFX_Sprite *sprite_btn_image;
    LovyanGFX *_parent;
    bool _wasPressed = false;
    bool isSetImage = false;
    Button *_btn;

public:
    PrintButton(LovyanGFX *parent, int32_t x0, int32_t y0, int32_t width, int32_t height, int32_t pushSpace, bool isToggle = false)
    {
        _x0 = _lcd_x0 = x0;
        _y0 = _lcd_y0 = y0;
        _width = width;
        _height = height;
        _parent = parent;
        _pushSpace = pushSpace;
        _isToggle = isToggle;
        sprite_button.createSprite(_width, _height);
        _btn = new Button(x0, y0, width, height, true, "btn-obj");
    }
    ~PrintButton()
    {
        delete _btn;
        sprite_button.deleteSprite();
    }
    void setLcdPos(int32_t x0, int32_t y0);
    void setImage(LGFX_Sprite *image);
    void setColor(uint16_t activeColor, uint16_t inactiveColor, uint16_t shadowColor, uint16_t borderColor, uint16_t lineColor, uint16_t backgroundColor);
    void changeState(bool state);
    void print();
    bool checkPress();
    bool wasPress();
    bool isPushed = false;
};

inline void PrintButton::setLcdPos(int32_t x0, int32_t y0)
{
    _lcd_x0 = x0;
    _lcd_y0 = y0;
    _btn->x = x0;
    _btn->y = y0;
}

inline void PrintButton::setImage(LGFX_Sprite *image)
{
    sprite_btn_image = image;
    isSetImage = true;
}

inline void PrintButton::changeState(bool state)
{
    isPushed = state;
    print();
}

inline bool PrintButton::wasPress()
{
    return _btn->wasPressed();
}

inline void PrintButton::setColor(uint16_t activeColor, uint16_t inactiveColor, uint16_t shadowColor, uint16_t borderColor, uint16_t lineColor, uint16_t backgroundColor)
{
    _activeColor = activeColor;
    _inactiveColor = inactiveColor;
    _shadowColor = shadowColor;
    _borderColor = borderColor;
    _lineColor = lineColor;
    _backgroundColor = backgroundColor;
}

#endif
