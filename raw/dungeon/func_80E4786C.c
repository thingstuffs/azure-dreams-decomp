#include "common.h"
#include "m2c_compat.h"

s32 func_8009A350(s16, s16, s16, u16 *);            /* extern */
s16 func_800BCB04(s32, s32, s16);                   /* extern */
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;

s32 func_8016906C(s16 arg0, s16 arg1, s32 arg2, s16 arg3, s16 *arg4) {
    u16 sp10;
    s16 temp_v0;
    s32 temp_v1;
    s32 var_v0;

    var_v0 = 0;
    if (((func_8009A350(arg0, arg1, arg3, &sp10) << 0x10) != 0) && ((sp10 & 0xB700) || (temp_v1 = arg3 * 2, temp_v0 = func_800BCB04((((arg0 + *(temp_v1 + &D_8006CCD8)) << 6) + 0x20) & 0xFFE0, (((arg1 + *(temp_v1 + &D_8006CCE8)) << 6) + 0x20) & 0xFFE0, (s16) (arg2 - 0x20)), *arg4 = temp_v0, var_v0 = 1, ((temp_v0 < 0x200) == 0)))) {
        var_v0 = 0;
    }
    return var_v0;
}
