// poketchの共通ファイル
#include "main.h"

// Wifi接続関連
#include <WiFi.h>
#include <time.h>
#include "src/lib/ntp.h"
char ssid[] = "**********";
char pass[] = "**********";

// 時計
#include "dgClock.h"
static DgClock dgClock;

// メモ帳
#include "draw.h"
static Draw draw;

// 万歩計
#include "pedometer.h"
static Pedometer pedometer;

// コイントス
#include "coinToss.h"
static CoinToss cointoss;

// 起動時のモード
static int watchMode = WATCH_CLOCK;

void setup()
{
    M5.begin(true, true, true, true);
    M5.IMU.Init(); // 万歩計用
    Serial.begin(115200);
    lcd.init();
    lcd.setColorDepth(16);
    lcd.setBrightness(128);
    randomSeed(analogRead(0));
    // かっこいい感じのロード画面を作りたい
    connectWifi();
    delay(1000);
    Serial.println("modeInit");
    modeInit(watchMode);
}

void loop()
{
    M5.update();
    // ページ送り
    if (M5.BtnA.wasPressed())
    {
        modeClear(watchMode);
        watchMode--;
        if (watchMode < 0)
            watchMode = WATCH_MODE_NUM - 1;
        modeInit(watchMode);
        buttonVib(75);
    }
    else if (M5.BtnC.wasPressed())
    {
        modeClear(watchMode);
        watchMode++;
        if (watchMode >= WATCH_MODE_NUM)
            watchMode = 0;
        modeInit(watchMode);
        buttonVib(75);
    }

    // main
    modeUpdate(watchMode);

    // バックグラウンド処理
    pedometer.background();

    // 遅延
    delay(16);
}

// 機能の初期化
void modeInit(int mode)
{
    switch (mode)
    {
    case WATCH_CLOCK:
        dgClock.setup();
        break;
    case WATCH_DRAW:
        draw.setup();
        break;
    case WATCH_PEDOMETER:
        pedometer.setup();
        break;
    case WATCH_COINTOSS:
        cointoss.setup();
        break;
    }
}
// ページのメイン処理
void modeUpdate(int mode)
{
    switch (mode)
    {
    case WATCH_CLOCK:
        dgClock.update();
        break;
    case WATCH_DRAW:
        draw.update();
        break;
    case WATCH_PEDOMETER:
        pedometer.update();
        break;
    case WATCH_COINTOSS:
        cointoss.update();
        break;
    }
}
// 機能のクリア
void modeClear(int mode)
{
    switch (mode)
    {
    case WATCH_CLOCK:
        dgClock.clear();
        break;
    case WATCH_DRAW:
        draw.clear();
        break;
    case WATCH_PEDOMETER:
        pedometer.clear();
        break;
    case WATCH_COINTOSS:
        cointoss.clear();
        break;
    }
}

// ロード画面を作るまでここに置いておく
//wifiに接続する
void connectWifi()
{
    lcd.fillScreen(BLACK);
    lcd.setTextSize(2);
    lcd.setTextColor(WHITE, BLACK);
    int con_count = 0;
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        lcd.print(".");
        con_count++;
        if (con_count >= 20)
        {
            break;
        }
    }
    if (con_count < 20)
    {
        lcd.print("\nWiFi connected.");
        setNTP2RTC();
    }
    else
    {
        lcd.print("\nWiFi did not connect.");
    }
}