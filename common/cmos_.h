#ifndef _CMOS__H_
#define _CMOS__H_

enum cmos_reg {
    CMOS_REG_SECONDS = 0x00,
    CMOS_REG_MINUTES = 0x02,
    CMOS_REG_HOURS = 0x04,
    CMOS_REG_DAY = 0x07,
    CMOS_REG_MONTH = 0x08,
    CMOS_REG_YEAR = 0x09,
};

#endif