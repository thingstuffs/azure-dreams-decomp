#include "common.h"
#include "m2c_compat.h"

s32 func_8009A350(s16, s16, s16, u16 *);            /* extern */
s32 func_8009A540(s32, s16, s16, s16);              /* extern */
s16 func_800BCB04(s32, s32, s16);                   /* extern */
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;

s32 func_80018304(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    u16 sp10;
    s16 temp_v0;
    s16 temp_v0_2;
    s32 temp_v1;
    s32 var_v0;

    temp_v0 = arg2 - 0x20;
    if (((func_8009A540(arg3 & 0xFFFF, arg0, arg1, temp_v0) << 0x10) != 0) && ((func_8009A350(arg0, arg1, arg3, &sp10) << 0x10) != 0)) {
        temp_v1 = arg3 * 2;
        if (!(sp10 & 0x8400)) {
            temp_v0_2 = func_800BCB04((((s32) ((arg0 + *(temp_v1 + &D_8006CCD8)) << 0x10) >> 0xA) + 0x20) & 0xFFE0, (((s32) ((arg1 + *(temp_v1 + &D_8006CCE8)) << 0x10) >> 0xA) + 0x20) & 0xFFE0, temp_v0);
            if (temp_v0_2 < 0x200) {
                if (arg2 >= temp_v0_2) {
                    return 2;
                }
                var_v0 = 1;
                if ((temp_v0_2 - arg2) >= 0x21) {
                    goto block_7;
                }
                /* Duplicate return node #8. Try simplifying control flow for better match */
                return var_v0;
            }
        }
    }
block_7:
    var_v0 = 0;
    return var_v0;
}
