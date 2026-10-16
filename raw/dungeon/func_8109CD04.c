#include "common.h"
#include "m2c_compat.h"

s32 func_8009B4B0(void *, s32, s32);                /* extern */
M2C_UNK func_8009C93C(void *, void *, s16, s16, s32); /* extern */
s32 func_800A2B5C(void *);                          /* extern */
s32 func_800A44E0(s32, s32, s16, s32);              /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */
s16 func_800BCB04(s32, s32, s16);                   /* extern */
M2C_UNK func_800C77D0(void *, s32, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_800C7930(void *, s32, M2C_UNK, M2C_UNK); /* extern */
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;

s32 func_8015A504(void *arg0, s32 arg1, void *arg2, void *arg3) {
    u16 sp18;
    s16 *temp_s0;
    s16 *temp_s6;
    s16 temp_v0;
    s32 temp_fp;
    s32 temp_v0_2;
    s32 var_s5;
    s32 var_v0;
    u16 temp_v1;
    u16 temp_v1_2;
    u8 temp_v0_3;
    u8 temp_v1_3;
    u8 var_s2;
    u8 var_s3;

    M2C_FIELD(arg3, u8 *, 0x71) = (u8) (M2C_FIELD(arg3, u8 *, 0x71) & 0x7F);
    temp_v1 = *(u16 *)0x80083462;
    if (!(temp_v1 & 0x2000)) {
        if ((M2C_FIELD(arg3, u16 *, 0x46) & 0x8000) || (var_v0 = -1, ((temp_v1 & 8) == 0))) {
            var_v0 = -1;
            if ((func_800A2B5C(arg3) << 0x10) == 0) {
                func_800C7930(arg3 - 0x20, arg1, 8, 0x300);
                var_s5 = 0;
                if ((func_800A2B5C(arg3) << 0x10) != 0) {
                    goto block_5;
                }
                temp_v1_2 = ((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 9) & 7;
                temp_fp = temp_v1_2 * 2;
                var_s3 = M2C_FIELD(arg2, u8 *, 0x24);
                var_s2 = M2C_FIELD(arg2, u8 *, 0x25);
                temp_s6 = temp_fp + &D_8006CCD8;
                sp18 = temp_v1_2;
                M2C_FIELD(arg0, s16 *, 0xA8) = (s16) var_s3;
                M2C_FIELD(arg0, s16 *, 0xAA) = (s16) var_s2;
loop_8:
                if ((func_800A44E0(((s16) var_s3 << 6) & 0xFFC0, ((s16) var_s2 << 6) & 0xFFC0, M2C_FIELD(arg3, s16 *, 0x88), sp18 << 9) << 0x10) == 0) {
                    temp_s0 = temp_fp + &D_8006CCE8;
                    temp_v0 = func_800BCB04(((((s16) var_s3 + *temp_s6) << 6) + 0x20) & 0xFFE0, ((((s16) var_s2 + *temp_s0) << 6) + 0x20) & 0xFFE0, (s16) ((u16) M2C_FIELD(arg3, s16 *, 0x88) - 0x20));
                    if (temp_v0 < 0x201) {
                        if ((u32) (((temp_v0 - (u16) M2C_FIELD(arg3, s16 *, 0x88)) + 0x3F) & 0xFFFF) < 0x7FU) {
                            temp_v0_2 = func_8009B4B0(arg3, (var_s3 + (u16) *temp_s6) & 0xFFFF, (var_s2 + (u16) *temp_s0) & 0xFFFF);
                            if (temp_v0_2 == 0) {
                                var_s5 += 1;
                                temp_v1_3 = var_s3 + (u16) *temp_s6;
                                var_s3 = temp_v1_3;
                                temp_v0_3 = var_s2 + (u16) *temp_s0;
                                var_s2 = temp_v0_3;
                                M2C_FIELD(arg0, s16 *, 0xAA) = (s16) temp_v0_3;
                                M2C_FIELD(arg0, s16 *, 0xA8) = (s16) temp_v1_3;
                                if (var_s5 >= 8) {

                                } else {
                                    goto loop_8;
                                }
                            } else {
                                M2C_FIELD(arg0, u8 *, 0xAE) = 2U;
                                M2C_FIELD(arg0, s16 *, 0xAC) = (s16) (var_s5 + 1);
                                M2C_FIELD(arg3, s32 *, 0x60) = temp_v0_2;
                            }
                        }
                    }
                }
                M2C_FIELD(arg0, s8 *, 0x9A) = 0x1A;
                M2C_FIELD(arg0, s8 *, 0x9B) = 0;
                M2C_FIELD(arg0, s32 *, 0x8C) = 0;
                M2C_FIELD(arg0, s16 *, 0x96) = 8;
                M2C_FIELD(arg3, s8 *, 0x84) = 0x7E;
                M2C_FIELD(arg3, s8 *, 0x85) = 8;
                func_800A4ACC(arg3);
                M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
                if (M2C_FIELD(arg0, u8 *, 0xAE) == 2) {
                    func_8009C93C(arg3, arg2, (s16) M2C_FIELD(arg3, u16 *, 0x2A), (s16) (var_s5 + 1), M2C_FIELD(arg3, s32 *, 0x60));
                    return 0;
                }
                func_800C77D0(arg3 - 0x20, arg1, 8, 0x300);
                var_v0 = 0;
                /* Duplicate return node #18. Try simplifying control flow for better match */
                return var_v0;
            }
        }
        return var_v0;
    }
block_5:
    return -1;
}
