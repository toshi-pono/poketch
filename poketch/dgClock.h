#ifndef _DG_CLOCK_
#define _DG_CLOCK_
#include "main.h"

// 画像データ
#include "./img/bottom.h"

class DgClock
{ // 時刻モードのコントローラー
private:
    RTC_TimeTypeDef _time;
    int oldMinutes;
    LGFX_Sprite sprite_clock;
    static const int16_t _size;
    static const int16_t _x0;
    static const int16_t _y0;

public:
    DgClock() { oldMinutes = -1; }
    void setup();
    void update();
    void clear();
};

const int16_t DgClock::_size = 12;
const int16_t DgClock::_x0 = 34;
const int16_t DgClock::_y0 = 50;

inline void DgClock::setup()
{
    lcd.fillScreen(POK_WHITE);
    lcd.pushImage(0, 240 - imgHeight, imgWidth, imgHeight, img);
    sprite_clock.createSprite(_size * 21, _size * 9);
    sprite_clock.fillScreen(POK_WHITE);
    // 中央のポッチ
    sprite_clock.fillRect(_size * 10, _size * 2, _size, _size, POK_DARK_GRAY);
    sprite_clock.fillRect(_size * 10, _size * 6, _size, _size, POK_DARK_GRAY);
    // 時刻などの初期描画
    oldMinutes = -1;
    update();
}
inline void DgClock::update()
{
    M5.Rtc.GetTime(&_time);
    if (oldMinutes != _time.Minutes)
    {
        prn.setParent(&sprite_clock);
        prn.setColor(POK_DARK_GRAY, POK_WHITE);
        prn.setFont(0, _size);
        // 時間
        prn.setCursor(0, 0);
        prn.printText(_time.Hours, 2);
        // 分
        prn.setCursor(_size * 12, 0);
        prn.printText(_time.Minutes, 2);
        sprite_clock.pushSprite(&lcd, _x0, _y0);
        oldMinutes = _time.Minutes;
    }
}
inline void DgClock::clear()
{
    // スプライトのメモリ解放
    sprite_clock.deleteSprite();
}

#endif