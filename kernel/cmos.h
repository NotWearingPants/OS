#include "common.h"
#include "../test.h"

// enum cmos_reg {
//     CMOS_REG_SECONDS = 0x00,
//     CMOS_REG_MINUTES = 0x02,
//     CMOS_REG_HOURS = 0x04,
//     CMOS_REG_DAY = 0x07,
//     CMOS_REG_MONTH = 0x08,
//     CMOS_REG_YEAR = 0x09,
// };

uint8_t read_from_cmos(uint8_t reg);
