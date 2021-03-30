#include <pgmspace.h>

// c.png
// https://lang-ship.com/tools/image2data/

const uint16_t char_cWidth = 19;
const uint16_t char_cHeight = 19;

// RGB565 Dump(little endian)
const unsigned short char_c[361] PROGMEM = {
    0xAE75, 0xAE75, 0xAE75, 0xAE75, 0x863A, 0x863A, 0x863A, 0x863A, 0x863A, 0x863A, 0x863A, 0x863A, 0x863A, 0x863A, 0x863A, 0x863A, 0xAE75, 0xAE75, 0xAE75, // row 0, 19 pixels
    0xAE75, 0xAE75, 0xAE75, 0x863A, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x863A, 0xAE75, 0xAE75, // row 1, 38 pixels
    0xAE75, 0xAE75, 0x863A, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x863A, 0xAE75, // row 2, 57 pixels
    0xAE75, 0x863A, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x863A, // row 3, 76 pixels
    0x863A, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x863A, 0x863A, 0x863A, 0x863A, 0x863A, 0x863A, 0x863A, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x863A, // row 4, 95 pixels
    0x863A, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x863A, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0x863A, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x863A, // row 5, 114 pixels
    0x863A, 0x2A54, 0x2A54, 0x2A54, 0x863A, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0x863A, 0x2A54, 0x2A54, 0x2A54, 0x863A, // row 6, 133 pixels
    0x863A, 0x2A54, 0x2A54, 0x2A54, 0x863A, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0x863A, 0x863A, 0x863A, 0x863A, // row 7, 152 pixels
    0x863A, 0x2A54, 0x2A54, 0x2A54, 0x863A, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, // row 8, 171 pixels
    0x863A, 0x2A54, 0x2A54, 0x2A54, 0x863A, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, // row 9, 190 pixels
    0x863A, 0x2A54, 0x2A54, 0x2A54, 0x863A, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, // row 10, 209 pixels
    0x863A, 0x2A54, 0x2A54, 0x2A54, 0x863A, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0x863A, 0x863A, 0x863A, 0x863A, // row 11, 228 pixels
    0x863A, 0x2A54, 0x2A54, 0x2A54, 0x863A, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0x863A, 0x2A54, 0x2A54, 0x2A54, 0x863A, // row 12, 247 pixels
    0x863A, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x863A, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0xAE75, 0x863A, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x863A, // row 13, 266 pixels
    0x863A, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x863A, 0x863A, 0x863A, 0x863A, 0x863A, 0x863A, 0x863A, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x863A, // row 14, 285 pixels
    0xAE75, 0x863A, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x863A, // row 15, 304 pixels
    0xAE75, 0xAE75, 0x863A, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x863A, 0xAE75, // row 16, 323 pixels
    0xAE75, 0xAE75, 0xAE75, 0x863A, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x2A54, 0x863A, 0xAE75, 0xAE75, // row 17, 342 pixels
    0xAE75, 0xAE75, 0xAE75, 0xAE75, 0x863A, 0x863A, 0x863A, 0x863A, 0x863A, 0x863A, 0x863A, 0x863A, 0x863A, 0x863A, 0x863A, 0x863A, 0xAE75, 0xAE75, 0xAE75, // row 18, 361 pixels
};
