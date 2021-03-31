#ifndef _COINTOSS_
#define _COINTOSS_
#include "main.h"

// 画像データ
#include "img/coin.h"

class CoinToss
{
private:
    int16_t _anim_cnt;
    bool _isAnimation;
    int16_t _bottom_count;

    const int16_t _coin_width = 320 / 5 * 2;
    const int16_t _bottom = 240 - 5 - _coin_width / 2;
    const float _rebound = 0.7F;
    const float _gravityAcc = 1.7F;
    const float _vy_0 = 17.0F;

    float _coin_vy = 0.0F;

    int16_t _coin_y;
    int16_t coinStatus = 0; // 0: Front 1: mid 2: Back

    Button *btn_coin;

    LGFX_Sprite sprite_center;
    void drawCoin(int16_t type);

public:
    CoinToss()
    {
    }
    ~CoinToss()
    {
    }
    void setup();
    void update();
    void clear();
};

void CoinToss::setup()
{
    // 背景の描画
    lcd.fillScreen(POK_WHITE);
    // 背景の横線
    lcd.fillRect(0, 240 / 2, 320, 10, POK_GRAY);
    lcd.fillRect(0, 240 / 2 + 10 + 3, 320, 6);
    lcd.fillRect(0, 240 / 2 + 10 + 3 + 6 + 3, 320, 2);

    _anim_cnt = 0;
    _isAnimation = false;
    _coin_y = _bottom;
    sprite_center.createSprite(_coin_width, 240);
    drawCoin(coinStatus);
}

void CoinToss::update()
{
    const int16_t frame = 2;
    // ボタンのクリック判定
    if (!_isAnimation && M5.BtnB.wasPressed())
    {
        _isAnimation = true;
        // コイントスの結果を決定
        coinStatus = (random(2) == 0) ? 0 : 2;

        _coin_y = _bottom;
        _coin_vy = _vy_0;
        _bottom_count = 0;
        _anim_cnt = coinStatus * frame;
    }

    if (_isAnimation)
    {
        // コインの位置を変更
        _coin_y -= (int16_t)_coin_vy;
        _coin_vy -= _gravityAcc;
        if (_coin_y > _bottom)
        {
            _coin_y = _bottom;
            _coin_vy *= -_rebound;
            _bottom_count++;
        }
        if (_bottom_count >= 4)
        {
            // 最終結果を表示してアニメーション終了
            _isAnimation = false;
            _anim_cnt = coinStatus * frame;
        }

        // コインを描画
        drawCoin(_anim_cnt / frame);
        _anim_cnt++;
        _anim_cnt %= 3 * frame;
    }
}
void CoinToss::clear()
{
    sprite_center.deleteSprite();
}

void CoinToss::drawCoin(int16_t type)
{
    type %= 3;
    const float img_w = coin_imageWidth / 2.0F;
    const float img_h = coin_imageHeight / 2.0F;
    const float zoom = _coin_width / (float)coin_imageWidth - 0.1F;
    sprite_center.fillScreen(POK_WHITE);
    // 背景の横線
    sprite_center.fillRect(0, 240 / 2, sprite_center.width(), 10, POK_GRAY);
    sprite_center.fillRect(0, 240 / 2 + 10 + 3, sprite_center.width(), 6);
    sprite_center.fillRect(0, 240 / 2 + 10 + 3 + 6 + 3, sprite_center.width(), 2);

    // コインの描画
    if (type == 0)
    {
        // 表面
        sprite_center.pushImageRotateZoomWithAA(sprite_center.width() / 2.0F, _coin_y, img_w, img_h, 0, zoom, zoom, coin_imageWidth, coin_imageHeight, coin_front_image, WHITE);
    }
    else if (type == 1)
    {
        // 中間
        sprite_center.pushImageRotateZoomWithAA(sprite_center.width() / 2.0F, _coin_y, img_w, img_h, 0, zoom, zoom, coin_imageWidth, coin_imageHeight, coin_mid_image, WHITE);
    }
    else
    {
        // 裏面
        sprite_center.pushImageRotateZoomWithAA(sprite_center.width() / 2.0F, _coin_y, img_w, img_h, 0, zoom, zoom, coin_imageWidth, coin_imageHeight, coin_back_image, WHITE);
    }
    sprite_center.pushSprite(&lcd, (320 - sprite_center.width()) / 2, 0);
}

#endif