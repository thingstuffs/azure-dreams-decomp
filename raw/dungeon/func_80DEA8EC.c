#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
s32 func_8009B4B0(void *, s32, s32);                /* extern */
s32 func_800A2B5C(void *);                          /* extern */
s32 func_800A44E0(s32, s32, s16, s32);              /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */
s32 func_800A5690();                                /* extern */
s16 func_800BCB04(s32, s32, s16);                   /* extern */
M2C_UNK func_800C77D0(void *, s32, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_800C7930(void *, s32, M2C_UNK, M2C_UNK); /* extern */
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern M2C_UNK D_8016E558;

s32 func_8016C0EC(void *arg0, s32 arg1, void *arg2, void *arg3) {
    void *sp10;
    s16 temp_v0;
    s32 temp_s0;
    s32 temp_v1_2;
    s32 var_v0;
    u16 *temp_s0_2;
    u16 *temp_s2;
    u16 temp_v1;
    u8 temp_s3;
    u8 temp_s4;
    void *temp_t0;

    M2C_FIELD(arg3, u8 *, 0x71) = (u8) (M2C_FIELD(arg3, u8 *, 0x71) & 0x7F);
    temp_v1 = *(u16 *)0x80083462;
    if (!(temp_v1 & 0x2000)) {
        if ((M2C_FIELD(arg3, u16 *, 0x46) & 0x8000) || (var_v0 = -1, ((temp_v1 & 8) == 0))) {
            var_v0 = -1;
            if ((func_800A2B5C(arg3) << 0x10) == 0) {
                temp_t0 = arg3 - 0x20;
                sp10 = temp_t0;
                func_800C7930(temp_t0, arg1, 8, 0x300);
                if ((func_800A2B5C(arg3) << 0x10) != 0) {
                    goto block_5;
                }
                temp_s3 = M2C_FIELD(arg2, u8 *, 0x24);
                temp_s4 = M2C_FIELD(arg2, u8 *, 0x25);
                temp_s0 = ((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 9) & 7;
                var_v0 = 0;
                if ((func_800A44E0(temp_s3 << 6, temp_s4 << 6, M2C_FIELD(arg3, s16 *, 0x88), temp_s0 << 9) << 0x10) == 0) {
                    temp_v1_2 = temp_s0 * 2;
                    temp_s2 = temp_v1_2 + &D_8006CCD8;
                    temp_s0_2 = temp_v1_2 + &D_8006CCE8;
                    var_v0 = 0;
                    if (func_8009B4B0(arg3, (temp_s3 + *temp_s2) & 0xFFFF, (temp_s4 + *temp_s0_2) & 0xFFFF) == 0) {
                        var_v0 = 0;
                        if ((func_800A5690() << 0x10) != 0) {
                            temp_v0 = func_800BCB04((((temp_s3 + (s16) *temp_s2) << 6) + 0x20) & 0xFFE0, (((temp_s4 + (s16) *temp_s0_2) << 6) + 0x20) & 0xFFE0, (s16) ((u16) M2C_FIELD(arg3, s16 *, 0x88) - 0x20));
                            var_v0 = 0;
                            if (temp_v0 < 0x201) {
                                var_v0 = 0;
                                if ((s16) (temp_v0 - (u16) M2C_FIELD(arg3, s16 *, 0x88)) >= -0x3F) {
                                    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
                                    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
                                    M2C_FIELD(arg0, s8 *, 0x9A) = 0x17;
                                    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8016E558;
                                    func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8016E558), 0);
                                    func_800A4ACC(arg3);
                                    M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
                                    func_800C77D0(sp10, arg1, 8, 0x300);
                                    var_v0 = 1;
                                }
                            }
                        }
                    }
                }
                /* Duplicate return node #12. Try simplifying control flow for better match */
                return var_v0;
            }
        }
        return var_v0;
    }
block_5:
    return -1;
}
