#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
s32 func_800A2B5C(void *);                          /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */
M2C_UNK func_800C7930(void *, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
extern M2C_UNK D_80157F30;

s32 func_801543D8(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    u16 temp_v1;

    M2C_FIELD(arg3, u8 *, 0x71) = (u8) (M2C_FIELD(arg3, u8 *, 0x71) & 0x7F);
    temp_v1 = *(u16 *)0x80083462;
    if (!(temp_v1 & 0x2000)) {
        if (((M2C_FIELD(arg3, u16 *, 0x46) & 0x8000) || !(temp_v1 & 8)) && ((func_800A2B5C(arg3) << 0x10) == 0)) {
            func_800C7930(arg3 - 0x20, arg1, 8, 0x300);
            if ((func_800A2B5C(arg3) << 0x10) == 0) {
                M2C_FIELD(arg0, s8 *, 0x9A) = 0x18;
                M2C_FIELD(arg0, s8 *, 0x9B) = 0;
                M2C_FIELD(arg0, s32 *, 0x8C) = 0;
                M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80157F30;
                func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80157F30), 0);
                func_800A4ACC(arg3);
                M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
                return 0;
            }
        }
        /* Duplicate return node #7. Try simplifying control flow for better match */
        return -1;
    }
    return -1;
}
