#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
M2C_UNK func_8009C93C(void *, void *, s16, M2C_UNK, s32); /* extern */
s32 func_800A0134(s32, void *);                     /* extern */
s32 func_800A04F0(void *, u8, u8, s16);             /* extern */
s32 func_800A2B5C(void *);                          /* extern */
s32 func_800A2CB8(void *, s32);                     /* extern */
M2C_UNK func_800C7930(void *, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
extern M2C_UNK D_80083460;
extern M2C_UNK D_80169258;

s32 func_80166314(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    s32 temp_v0;
    s32 var_v0;

    M2C_FIELD(arg3, u8 *, 0x71) = (u8) (M2C_FIELD(arg3, u8 *, 0x71) & 0x7F);
    if (!(M2C_FIELD(&D_80083460, u16 *, 2) & 0x2000)) {
        temp_v0 = func_800A04F0(arg3, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(arg3, s16 *, 0x2A));
        var_v0 = 0;
        if ((func_800A2CB8(arg3, temp_v0) << 0x10) != 0) {
            var_v0 = -1;
            if (!(M2C_FIELD(&D_80083460, u16 *, 2) & 0x2000)) {
                if (!(M2C_FIELD(arg3, u16 *, 0x46) & 0x8000)) {
                    var_v0 = -1;
                    if (!(M2C_FIELD(&D_80083460, u16 *, 2) & 8)) {
                        goto block_6;
                    }
                    /* Duplicate return node #14. Try simplifying control flow for better match */
                    return var_v0;
                }
block_6:
                var_v0 = 0;
                if ((u32) ((-func_800A0134(temp_v0, arg3) + 0x40) & 0xFFFF) < 0x81U) {
                    var_v0 = -1;
                    if ((func_800A2B5C(arg3) << 0x10) == 0) {
                        func_800C7930(arg3 - 0x20, arg1, 8, 0x300);
                        if ((func_800A2B5C(arg3) << 0x10) != 0) {
                            goto block_9;
                        }
                        M2C_FIELD(arg0, s8 *, 0x9B) = 0;
                        M2C_FIELD(arg0, s32 *, 0x8C) = 0;
                        if (M2C_FIELD(arg0, u16 *, 0x98) & 0x8000) {
                            M2C_FIELD(arg0, s8 *, 0x9A) = 0x17;
                            M2C_FIELD(arg3, s8 *, 0x84) = 0x28;
                            M2C_FIELD(arg3, s8 *, 0x85) = 0x10;
                        } else {
                            M2C_FIELD(arg0, s8 *, 0x9A) = 0x11;
                            M2C_FIELD(arg3, s8 *, 0x84) = 0x7C;
                            M2C_FIELD(arg3, s8 *, 0x85) = 0;
                        }
                        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80169258;
                        func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80169258), 0);
                        M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
                        func_8009C93C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1, 0);
                        var_v0 = 1;
                        /* Duplicate return node #14. Try simplifying control flow for better match */
                        return var_v0;
                    }
                }
                /* Duplicate return node #14. Try simplifying control flow for better match */
                return var_v0;
            }
        }
        return var_v0;
    }
block_9:
    return -1;
}
