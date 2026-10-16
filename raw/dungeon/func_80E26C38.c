#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
s32 func_8009B4B0(void *, s32, s32);                /* extern */
s32 func_800A2B5C(void *);                          /* extern */
s32 func_800A2CB8(void *, s32);                     /* extern */
s32 func_800A44E0(s32, s32, s16, s32);              /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */
s16 func_800BCB04(s32, s32, s16);                   /* extern */
M2C_UNK func_800C7930(void *, s32, M2C_UNK, M2C_UNK); /* extern */
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern M2C_UNK D_8015E4A0;

s32 func_8015A438(void *arg0, s32 arg1, void *arg2, void *arg3) {
    u16 sp10;
    s16 *temp_s0;
    s16 *temp_s6;
    s16 temp_v0;
    s32 temp_fp;
    s32 temp_v0_2;
    s32 var_s5;
    s32 var_v0;
    s32 var_v0_2;
    u16 temp_v1;
    u16 temp_v1_2;
    u8 var_s2;
    u8 var_s3;

    M2C_FIELD(arg3, u8 *, 0x71) = (u8) (M2C_FIELD(arg3, u8 *, 0x71) & 0x7F);
    if (!(*(u16 *)0x80083462 & 0x2000)) {
        var_s5 = 0;
        temp_v1 = ((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 9) & 7;
        temp_fp = temp_v1 * 2;
        var_s3 = M2C_FIELD(arg2, u8 *, 0x24);
        var_s2 = M2C_FIELD(arg2, u8 *, 0x25);
        temp_s6 = temp_fp + &D_8006CCD8;
        M2C_FIELD(arg0, u16 *, 0xB2) = 0U;
        sp10 = temp_v1;
loop_2:
        M2C_FIELD(arg0, u16 *, 0xB2) = (u16) (M2C_FIELD(arg0, u16 *, 0xB2) + 1);
        if ((func_800A44E0(((s16) var_s3 << 6) & 0xFFC0, ((s16) var_s2 << 6) & 0xFFC0, M2C_FIELD(arg3, s16 *, 0x88), sp10 << 9) << 0x10) == 0) {
            temp_s0 = temp_fp + &D_8006CCE8;
            temp_v0 = func_800BCB04(((((s16) var_s3 + *temp_s6) << 6) + 0x20) & 0xFFE0, ((((s16) var_s2 + *temp_s0) << 6) + 0x20) & 0xFFE0, (s16) ((u16) M2C_FIELD(arg3, s16 *, 0x88) - 0x20));
            if ((temp_v0 < 0x201) && ((u32) (((temp_v0 - (u16) M2C_FIELD(arg3, s16 *, 0x88)) + 0x3F) & 0xFFFF) < 0x7FU)) {
                temp_v0_2 = func_8009B4B0(arg3, (var_s3 + (u16) *temp_s6) & 0xFFFF, (var_s2 + (u16) *temp_s0) & 0xFFFF);
                M2C_FIELD(arg3, s32 *, 0x60) = temp_v0_2;
                if ((temp_v0_2 != 0) || (var_s5 += 1, var_s3 += (u16) *temp_s6, var_s2 += (u16) *temp_s0, ((var_s5 < 4) == 0))) {
                    var_v0 = 3;
                    if (var_s5 < 4) {
                        if ((func_800A2CB8(arg3, temp_v0_2) << 0x10) == 0) {
                            return 0;
                        }
                        temp_v1_2 = *(void *)0x80083462;
                        var_v0 = -1;
                        if (!(temp_v1_2 & 0x2000) && ((M2C_FIELD(arg3, u16 *, 0x46) & 0x8000) || (var_v0 = -1, ((temp_v1_2 & 8) == 0)))) {
                            var_v0 = -1;
                            if ((func_800A2B5C(arg3) << 0x10) == 0) {
                                func_800C7930(arg3 - 0x20, arg1, 8, 0x300);
                                var_v0 = -1;
                                if ((func_800A2B5C(arg3) << 0x10) == 0) {
                                    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
                                    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
                                    M2C_FIELD(arg0, s8 *, 0x9A) = 0x17;
                                    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8015E4A0;
                                    func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8015E4A0), 0);
                                    func_800A4ACC(arg3);
                                    M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
                                    return 1;
                                }
                            }
                        }
                        /* Duplicate return node #20. Try simplifying control flow for better match */
                        return var_v0;
                    }
                    /* Duplicate return node #20. Try simplifying control flow for better match */
                    return var_v0;
                }
                goto loop_2;
            }
            var_v0_2 = 3;
            goto block_18;
        }
        var_v0_2 = 2;
block_18:
        M2C_FIELD(arg0, u16 *, 0xB2) = (u16) (M2C_FIELD(arg0, u16 *, 0xB2) - 1);
        return var_v0_2;
    }
    var_v0 = -1;
    return var_v0;
}
