#ifndef _print_NUMBER_
#define _print_NUMBER_
#include <LovyanGFX.hpp>

class PrintNumber
{
private:
    int8_t _type;
    int32_t _size;
    int32_t _x0;
    int32_t _y0;
    uint16_t _textColor;
    uint16_t _backgroundColor;
    uint16_t _shadowColor;
    LovyanGFX *_parent;
    LGFX_Sprite sprite_number;
    void _print(std::vector<std::vector<uint8_t>> data, float wRate, float hRate, bool isShadow);
    static const std::vector<std::vector<std::vector<uint8_t>>> _numberData1;
    static const std::vector<std::vector<std::vector<uint8_t>>> _numberData2;
    static const std::vector<std::vector<std::vector<uint8_t>>> _numberData3;
    static const int32_t _width[3];

public:
    PrintNumber(LovyanGFX *parent);
    void print(int c);
    void printText(int num, int len);
    void setCursor(int32_t x0, int32_t y0);
    void setColor(uint16_t textColor);
    void setColor(uint16_t textColor, uint16_t backgroundColor);
    void setColor(uint16_t textColor, uint16_t backgroundColor, uint16_t shadowColor);
    void setTextPixcel(int32_t size);
    void setFont(int8_t type);
    void setFont(int8_t type, int32_t size);
    void setParent(LovyanGFX *parent) { _parent = parent; }
    void deleteSprite();
};

inline void PrintNumber::setCursor(int32_t x0, int32_t y0)
{
    _x0 = x0;
    _y0 = y0;
}
inline void PrintNumber::setColor(uint16_t textColor)
{
    _textColor = textColor;
}
inline void PrintNumber::setColor(uint16_t textColor, uint16_t backgroundColor)
{
    _textColor = textColor;
    _backgroundColor = backgroundColor;
}
inline void PrintNumber::setColor(uint16_t textColor, uint16_t backgroundColor, uint16_t shadowColor)
{
    _textColor = textColor;
    _backgroundColor = backgroundColor;
    _shadowColor = shadowColor;
}
inline void PrintNumber::deleteSprite()
{
    sprite_number.deleteSprite();
}
inline void PrintNumber::setTextPixcel(int32_t size)
{
    _size = size;
}

// フォントを設定する :(type)
inline void PrintNumber::setFont(int8_t type)
{
    _type = type;
}
// フォントを設定する :(type,size)
inline void PrintNumber::setFont(int8_t type, int32_t size)
{
    _type = type;
    _size = size;
}

#endif
