#include "printButton.h"

const int32_t PrintButton::lineWidth = 3;

void PrintButton::print()
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
bool PrintButton::checkPress()
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
