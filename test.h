#ifndef _TEST_H_
#define _TEST_H_

enum cmos_reg {
    CMOS_REG_SECONDS = 0x00,
    CMOS_REG_MINUTES = 0x02,
    CMOS_REG_HOURS = 0x04,
    CMOS_REG_DAY = 0x07,
    CMOS_REG_MONTH = 0x08,
    CMOS_REG_YEAR = 0x09,
};

enum Color {
    COLOR_BLACK         = 0x0,
    COLOR_BLUE          = 0x1,
    COLOR_GREEN         = 0x2,
    COLOR_AQUA          = 0x3,
    COLOR_RED           = 0x4,
    COLOR_PURPLE        = 0x5,
    COLOR_YELLOW        = 0x6,
    COLOR_WHITE         = 0x7,
    COLOR_GRAY          = 0x8,
    COLOR_LIGHT_BLUE    = 0x9,
    COLOR_LIGHT_GREEN   = 0xA,
    COLOR_LIGHT_AQUA    = 0xB,
    COLOR_LIGHT_RED     = 0xC,
    COLOR_LIGHT_PURPLE  = 0xD,
    COLOR_LIGHT_YELLOW  = 0xE,
    COLOR_BRIGHT_WHITE  = 0xF,
};

#define COLOR(text_color, background_color) ((((uint8_t)COLOR_##background_color) << 4) | ((uint8_t)COLOR_##text_color))

#define DEFAULT_COLOR COLOR(BRIGHT_WHITE, BLACK)


#endif