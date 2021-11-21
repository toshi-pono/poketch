#ifndef _DG_PEDOMETER_
#define _DG_PEDOMETER_
#include "main.h"
#include "img/char_c.h"

class Pedometer
{
private:
    const int16_t button_width = 320 / 3;
    const int16_t button_height = 240 / 3;
    const int16_t button_x = 320 / 3;
    const int16_t button_y = 240 / 2 + 20;
    const int16_t button_pushSpace = 10;

    const int16_t bg_line_width = 8;
    const int16_t bg_topSpace = 4;
    const int16_t bg_bottomSpace = 8;
    const int16_t bg_round = 12;
    const int16_t bg_shift = 15;

    const int16_t font_size = 8;

    // 計算用
    const int16_t number_width = (5 * 3 + 4) * font_size;
    const int16_t number_height = 7.5 * font_size;
    const int16_t bg_width = bg_line_width * 2 + bg_round * 2 + number_width;
    const int16_t bg_height = bg_line_width * 2 + (bg_topSpace + bg_bottomSpace) + number_height;

    const float ACC_RANGE = 0.062F; // 加速度の変化が小さく，うまく歩数をカウントできないときはここを調節する
    const float LOW_PATH = 0.1F;

    float _threshold = 1.10F;
    float _beforeA = 1.0F;
    bool _isUnder = false;
    float _maxA = 0.0F;
    float _minA = 100.0F;
    int16_t _cnt = 0;
    int16_t steps = 0; // 歩数
    bool _isStepsUpdate = true;

    PrintButton *_btn_clear;
    LGFX_Sprite _btn_image;

public:
    Pedometer()
    {
        _btn_clear = new PrintButton(&lcd, button_x, button_y, button_width, button_height, button_pushSpace, false);
        _btn_clear->setColor(POK_WHITE, POK_WHITE, POK_GRAY, POK_BLACK, POK_DARK_GRAY, POK_WHITE);
        // 画像を追加する
        _btn_clear->setImage(&_btn_image);
    }
    ~Pedometer()
    {
        delete _btn_clear;
    }
    void setup();
    void update();
    void clear();
    void background();
};

void Pedometer::setup()
{
    lcd.fillScreen(POK_WHITE);
    _btn_image.createSprite(button_width / 5 * 2 + 2, button_width / 5 * 2 + 2);
    _btn_image.fillScreen(POK_WHITE);
    _btn_image.pushImageRotateZoomWithAA(_btn_image.width() / 2.0F, _btn_image.height() / 2.0F, char_cWidth / 2.0F, char_cHeight / 2.0F, 0, _btn_image.width() / (float)char_cWidth - 0.01F, _btn_image.width() / (float)char_cWidth - 0.01F, char_cWidth, char_cHeight, char_c);

    _btn_clear->print();

    lcd.fillRoundRect((320 - bg_width) / 2, (120 - bg_height) * 2 / 3 + bg_shift, bg_width, bg_height, bg_round + bg_line_width, POK_GRAY);
    lcd.fillRoundRect((320 - bg_width) / 2 + bg_line_width, (120 - bg_height) * 2 / 3 + bg_line_width + bg_shift, bg_width - bg_line_width * 2, bg_height - bg_line_width * 2, bg_round, POK_WHITE);

    // 歩数の描画
    _isStepsUpdate = true;
    update();
}

void Pedometer::update()
{
    if (_btn_clear->checkPress() && steps != 0)
    {
        // クリア
        steps = 0;
        _isStepsUpdate = true;
    }
    // 歩数更新時のみ歩数を描画
    if (_isStepsUpdate)
    {
        _isStepsUpdate = false;
        prn.setParent(&lcd);
        prn.setColor(POK_BLACK, POK_WHITE, POK_DARK_GRAY);
        prn.setFont(1, font_size);
        prn.setCursor((320 - number_width) / 2, (120 - bg_height) * 2 / 3 + bg_line_width + bg_topSpace + bg_shift);
        prn.printText(steps, 5);
    }
}

// 歩数を計測する処理
void Pedometer::background()
{
    // 加速度取得
    float accX, accY, accZ;
    M5.IMU.getAccelData(&accX, &accY, &accZ);
    float nowA = sqrt(accX * accX + accY * accY + accZ * accZ);

    // ローパスフィルタ
    nowA = LOW_PATH * nowA + (1 - LOW_PATH) * _beforeA;

    // 歩数の更新 (基準値を下回る → 上回る となると１歩とカウント)
    if (!_isUnder && nowA < _threshold - ACC_RANGE)
    {
        _isUnder = true;
    }
    if (_isUnder && nowA > _threshold + ACC_RANGE)
    {
        _isUnder = false;
        steps++;
        _isStepsUpdate = true;
        if (steps >= 100000)
        {
            steps = 99999;
            _isStepsUpdate = false;
        }
    }

    // 動的に基準値を計算（50回分の最小と最大の間を利用）
    _minA = min(_minA, nowA);
    _maxA = max(_maxA, nowA);
    _cnt++;
    if (_cnt >= 50)
    {
        _cnt = 0;
        _threshold = (_minA + _maxA) / 2;
        _minA = 100.0F;
        _maxA = 0.0F;
    }
    _beforeA = nowA;
}

void Pedometer::clear()
{
    _btn_image.deleteSprite();
}

#endif // _DG_PEDOMETER_
