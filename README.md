# poketch

m5stack-core2 上で動作するポケッチ風アプリケーションです．

作るまでの背景や，こんなことしたよっていうのをを書きました↓

https://trap.jp/post/1266/

## DEMO

画面下部の左右ボタンで機能を切り替えることができます。

時計・メモ帳・万歩計

<img src="https://user-images.githubusercontent.com/66683209/113024452-b8330880-91c1-11eb-8f96-e7d941afe026.png" width="200px"> <img src="https://user-images.githubusercontent.com/66683209/113024840-2e376f80-91c2-11eb-95af-bab39496beea.png" width="200px"> <img src="https://user-images.githubusercontent.com/66683209/113025052-6f2f8400-91c2-11eb-8ee0-37d0c3ca7a21.png" width="200px">

コイントス

<img src="https://user-images.githubusercontent.com/66683209/113190548-5e9d0d80-9297-11eb-97b3-69ca546d1fa1.gif" width="200px">

## Usage

poketch.ino の 8,9 行目，

```
char ssid[] = "**********";
char pass[] = "**********";
```

を Wi-Fi の SSID とパスワードに書き換えることで Wi-Fi に接続して ntp サーバーから時刻を取得することができます．
