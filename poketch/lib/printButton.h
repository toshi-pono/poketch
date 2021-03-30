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
    void setLcdPos(int32_t x0, int32_t y0)
    {
        _lcd_x0 = x0;
        _lcd_y0 = y0;
        _btn->x = x0;
        _btn->y = y0;
    }
    void setImage(LGFX_Sprite *image)
    {
        sprite_btn_image = image;
        isSetImage = true;
    }
    void setColor(uint16_t activeColor, uint16_t inactiveColor, uint16_t shadowColor, uint16_t borderColor, uint16_t lineColor, uint16_t backgroundColor);
    void changeState(bool state)
    {
        isPushed = state;
        print();
    }
    void print();
    bool checkPress();
    bool wasPress();
    bool isPushed = false;
};

inline void PrintButton::print()
{
    // ボタンを描画する
    if (_height < _pushSpace)
        return;
    // HACK: 透過色を設定して，描画する形式に変更する必要がある
    sprite_button.fillScreen(_backgroundColor);
    // 枠の描画
    if (isPushed)
    {
        sprite_button.fillRect(0, _pushSpace, _width, _height - _pushSpace, _borderColor);
        sprite_button.fillRect(lineWidth, _pushSpace + lineWidth, _width - lineWidth * 2, _height - _pushSpace - lineWidth * 2, _activeColor);
    }
    else
    {
        sprite_button.fillRect(0, 0, _width, _height, _borderColor);
        sprite_button.fillRect(lineWidth, lineWidth, _width - lineWidth * 2, _height - _pushSpace - lineWidth * 2, _inactiveColor);
        sprite_button.fillRect(lineWidth, _height - _pushSpace - lineWidth, _width - lineWidth * 2, lineWidth, _lineColor);
        sprite_button.fillRect(lineWidth, _height - _pushSpace, _width - lineWidth * 2, _pushSpace - lineWidth, _shadowColor);
    }
    // イメージの描画
    if (isSetImage)
    {
        int32_t center_x = _width / 2;
        int32_t center_y = (_height - _pushSpace) / 2;
        if (isPushed)
            center_y += 10;

        sprite_btn_image->setPivot(sprite_btn_image->width() / 2, sprite_btn_image->height() / 2);
        // 画像がボタンの内側をはみ出している場合
        if (_width - lineWidth * 2 < sprite_btn_image->width() || _height - lineWidth * 2 - _pushSpace < sprite_btn_image->height())
        {
            // 縮小して描画
            float zoom_x = (_width - lineWidth * 2) / (float)sprite_btn_image->width();
            float zoom_y = (_height - lineWidth * 2 - _pushSpace) / (float)sprite_btn_image->height();
            if (zoom_x <= zoom_y)
            {
                // 横のほうがより縮小しなければならない場合
                sprite_btn_image->pushRotateZoom(&sprite_button, center_x, center_y, 0, zoom_x, zoom_x);
            }
            else
            {
                // 縦のほうがより縮小しなければならない場合
                sprite_btn_image->pushRotateZoom(&sprite_button, center_x, center_y, 0, zoom_y, zoom_y);
            }
        }
        else
        {
            // 普通に描画
            sprite_btn_image->pushRotateZoom(&sprite_button, center_x, center_y, 0, 1, 1);
        }
    }
    sprite_button.pushSprite(_parent, _x0, _y0);
}

// 接触判定
inline bool PrintButton::checkPress()
{
    if (_isToggle)
    {
        // トグルスイッチだった場合: 押したら切り替わる
        if (_btn->wasPressed())
        {
            isPushed = !isPushed;
            print();
        }
        return isPushed;
    }
    else
    {
        // トグルスイッチでない場合: 押している間だけ
        if (isPushed != _btn->isPressed())
        {
            isPushed = _btn->isPressed();
            print();
        }
        return isPushed;
    }
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
const int32_t PrintButton::lineWidth = 3;

#endif
