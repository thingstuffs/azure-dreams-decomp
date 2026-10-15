#ifndef SLUS_JTBL_8004CECC_H
#define SLUS_JTBL_8004CECC_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "common.h"

/* Convert HSV with 0x600 hue units per revolution to RGB bytes. */

u8 *func_8004CECC(u32 hue, s32 saturation, s32 value, u8 *out);

#endif
