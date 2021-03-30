#ifndef _DG_DRAW_
#define _DG_DRAW_
#include "main.h"

class Draw
{
private:
    const int16_t LINE_WIDTH = 3;
    const int16_t TAB_WIDTH = 64;
    const int16_t WINDOW_WIDTH = 320;
    const int16_t WINDOW_HEIGHT = 240;
    const int16_t PUSH_SPACE = 10;

    const int16_t _eraser_width = 33;
    const int16_t _eraser_height = 50;
    const int16_t _eraser_out = 15;

    const int16_t _pen_width = 18;
    const int16_t _pen_height = 70;
    const int16_t _pen_out = 12;

    const int16_t dot = 4;
    const int16_t e_rato = 3;

    LGFX_Sprite sprite_pen;
    LGFX_Sprite sprite_eraser;
    bool _isDrawPen = true;
    PrintButton *btn_pen;
    PrintButton *btn_eraser;

    int16_t before_x = 0;
    int16_t before_y = 0;
    bool wasPressed = false;

    void drawEraserImage(bool isActive);
    void drawPenImage(bool isActive);
    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
    void drawDot(int16_t x, int16_t y);

public:
    Draw()
    {
        const int16_t tab_start_x = WINDOW_WIDTH - TAB_WIDTH;
        const int16_t btn_width = TAB_WIDTH - LINE_WIDTH * 3;
        const int16_t btn_height = WINDOW_HEIGHT / 2 - LINE_WIDTH * 2;
        btn_eraser = new PrintButton(&lcd, tab_start_x + LINE_WIDTH * 2, LINE_WIDTH, btn_width, btn_height, PUSH_SPACE, true);
        btn_pen = new PrintButton(&lcd, tab_start_x + LINE_WIDTH * 2, WINDOW_HEIGHT / 2 + LINE_WIDTH, btn_width, btn_height, PUSH_SPACE, true);

        btn_eraser->setColor(POK_WHITE, POK_GRAY, POK_DARK_GRAY, POK_BLACK, POK_BLACK, POK_GRAY);
        btn_pen->setColor(POK_WHITE, POK_GRAY, POK_DARK_GRAY, POK_BLACK, POK_BLACK, POK_GRAY);
        btn_eraser->setImage(&sprite_eraser);
        btn_pen->setImage(&sprite_pen);
    };
    ~Draw()
    {
        sprite_pen.deleteSprite();
        sprite_eraser.deleteSprite();
        delete btn_pen;
        delete btn_eraser;
    };
    void setup();
    void update();
    void clear();
};

inline void Draw::setup()
{
    lcd.fillScreen(POK_WHITE);
    // ボタンの設定
    _isDrawPen = true;
    btn_pen->isPushed = true;
    btn_eraser->isPushed = false;

    // ボタンイメージの生成
    sprite_eraser.createSprite(_eraser_width, _eraser_height);
    sprite_pen.createSprite(_pen_width, _pen_height);
    drawEraserImage(btn_eraser->isPushed);
    drawPenImage(btn_pen->isPushed);

    // タブ部分の描画
    lcd.fillRect(WINDOW_WIDTH - TAB_WIDTH, 0, LINE_WIDTH, WINDOW_HEIGHT, POK_DARK_GRAY);
    lcd.fillRect(WINDOW_WIDTH - TAB_WIDTH + LINE_WIDTH, 0, TAB_WIDTH - LINE_WIDTH, WINDOW_HEIGHT, POK_GRAY);
    btn_pen->print();
    btn_eraser->print();
}

inline void Draw::update()
{
    // ボタンの状態取得・変更
    if (btn_pen->wasPress() && !_isDrawPen)
    {
        _isDrawPen = true;
        drawPenImage(true);
        drawEraserImage(false);
        btn_pen->changeState(true);
        btn_eraser->changeState(false);
        buttonVib(75);
    }
    else if (btn_eraser->wasPress() && _isDrawPen)
    {
        _isDrawPen = false;
        drawPenImage(false);
        drawEraserImage(true);
        btn_pen->changeState(false);
        btn_eraser->changeState(true);
        buttonVib(75);
    }

    // ペンの描画処理
    const bool ispressed = M5.Touch.ispressed();
    if (ispressed)
    {
        // 今押されている
        TouchPoint_t pos = M5.Touch.getPressPoint();
        if (wasPressed)
        {
            // 前回も押されていたとき
            int16_t now_x = pos.x;
            int16_t now_y = pos.y;

            // 直線を描画
            Serial.println("beforeDraw");
            drawLine(before_x, before_y, now_x, now_y);
            Serial.println("afterDraw");

            // 押した場所を記録
            if (pos.x > WINDOW_WIDTH - TAB_WIDTH)
                wasPressed = false;
            before_x = pos.x;
            before_y = pos.y;
        }
        else
        {
            // 前回は押されていなかったとき
            // 点を描画
            drawDot(pos.x, pos.y);
            // 押した場所を記録
            if (pos.x < WINDOW_WIDTH - TAB_WIDTH)
            {
                wasPressed = true;
                before_x = pos.x;
                before_y = pos.y;
            }
        }
    }
    else
    {
        // 今は押されていない
        wasPressed = false;
    }
}

inline void Draw::clear()
{
    // スプライトのメモリ解放
    sprite_pen.deleteSprite();
    sprite_eraser.deleteSprite();
}

inline void Draw::drawEraserImage(bool isActive)
{
    // 背景の塗りつぶし
    // HACK: 透過色で対応したい
    if (isActive)
        sprite_eraser.fillScreen(POK_WHITE);
    else
        sprite_eraser.fillScreen(POK_GRAY);

    // 枠線部分の描画
    sprite_eraser.fillRect(0, 0, _eraser_width, _eraser_height - LINE_WIDTH, POK_DARK_GRAY);
    sprite_eraser.fillRect(LINE_WIDTH, _eraser_height - LINE_WIDTH, _eraser_width - LINE_WIDTH * 2, LINE_WIDTH);

    // 中身の色
    if (isActive)
    {
        sprite_eraser.fillRect(LINE_WIDTH, LINE_WIDTH, _eraser_width - LINE_WIDTH * 2, _eraser_height - _eraser_out - LINE_WIDTH * 2, POK_GRAY);
        sprite_eraser.fillRect(LINE_WIDTH, _eraser_height - _eraser_out, _eraser_width - LINE_WIDTH * 2, _eraser_out - LINE_WIDTH, POK_WHITE);
    }
    else
    {
        sprite_eraser.fillRect(LINE_WIDTH, _eraser_height - _eraser_out, _eraser_width - LINE_WIDTH * 2, _eraser_out - LINE_WIDTH, POK_GRAY);
    }
}
inline void Draw::drawPenImage(bool isActive)
{
    // 背景の塗りつぶし
    // HACK: 透過色で対応したい
    if (isActive)
        sprite_pen.fillScreen(POK_WHITE);
    else
        sprite_pen.fillScreen(POK_GRAY);

    // 枠線部分の描画
    sprite_pen.fillRect(0, 0, _pen_width, _pen_height - _pen_out, POK_DARK_GRAY);
    sprite_pen.fillRect(0, _pen_height - _pen_out, LINE_WIDTH, _pen_out / 2);
    sprite_pen.fillRect(_pen_width - LINE_WIDTH, _pen_height - _pen_out, LINE_WIDTH, _pen_out / 2);
    // ペン先の三角形
    const int32_t pen_tri_y = _pen_height - (_pen_out + 1) / 2;
    sprite_pen.fillTriangle(LINE_WIDTH, pen_tri_y, _pen_width - LINE_WIDTH, pen_tri_y, _pen_width / 2, _pen_height);
    // アクティブ時
    if (isActive)
    {
        sprite_pen.fillRect(LINE_WIDTH, LINE_WIDTH, _pen_width - LINE_WIDTH * 2, _pen_height - _pen_out - LINE_WIDTH * 2, POK_GRAY);
    }
}

// 線の描画
inline void Draw::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
{
    drawDot(x0, y0);
    drawDot(x1, y1);
    int16_t x = x0;
    int16_t y = y0;
    if (abs(x0 - x1) > abs(y1 - y0))
    {
        // 傾きの絶対値が1以下のとき
        if (x0 > x1)
        {
            x0, x1 = x1, x0;
            y0, y1 = y1, y0;
        }
        const int16_t dx = abs(x1 - x0);
        const int16_t dy = abs(y1 - y0);
        int16_t dir_y = (y1 - y0 > 0) ? 1 : -1;
        int16_t D = 2 * dy - dx;
        while (x < x1)
        {
            if (D > 0)
            {
                y += dot * dir_y;
                D -= 2 * dx;
            }
            D += 2 * dy;
            x += dot;
            drawDot(x, y);
        }
    }
    else
    {
        // 傾きの絶対値が1以上のとき
        if (y0 > y1)
        {
            x0, x1 = x1, x0;
            y0, y1 = y1, y0;
        }
        // 計算式上で，xとyが入れ替わっていることに注意(y = x を軸として対称移動)
        const int16_t dy = abs(x1 - x0);
        const int16_t dx = abs(y1 - y0);
        int16_t dir_x = (x1 - x0 > 0) ? 1 : -1;
        int16_t D = 2 * dy - dx;
        while (y < y1)
        {
            if (D > 0)
            {
                x += dot * dir_x;
                D -= 2 * dx;
            }
            D += 2 * dy;
            y += dot;
            drawDot(x, y);
        }
    }
}
inline void Draw::drawDot(int16_t x, int16_t y)
{
    if (x > 0 && y > 0 && x < WINDOW_WIDTH - TAB_WIDTH && y < WINDOW_HEIGHT)
    {
        if (_isDrawPen)
        {
            // ペン
            lcd.fillRect(floor(x / dot) * dot, floor(y / dot) * dot, dot, dot, POK_BLACK);
        }
        else
        {
            // 消しゴム
            lcd.fillRect(floor(x / (dot * e_rato)) * dot * e_rato, floor(y / (dot * e_rato)) * dot * e_rato, dot * e_rato, dot * e_rato, POK_WHITE);
        }
    }
    Serial.println("drawDot");
}

#endif