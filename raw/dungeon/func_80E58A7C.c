#include "common.h"
#include "m2c_compat.h"

s8 func_80042518(void *, M2C_UNK);                  /* extern */
s32 func_80042900(void *, M2C_UNK);                 /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
M2C_UNK func_80044A50(void *);                      /* extern */
M2C_UNK func_800956B8(s32, M2C_UNK *, M2C_UNK *, s32); /* extern */
M2C_UNK func_8009A21C(u8, u8, M2C_UNK);             /* extern */
s16 func_800A1BD0(void *);                          /* extern */
M2C_UNK func_800A48F0(void *, M2C_UNK, s8);         /* extern */
M2C_UNK func_800AAA54(void *, M2C_UNK, void *, M2C_UNK *); /* extern */
M2C_UNK func_80156B90(void *, void *, void *, void *); /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80082E80;
extern M2C_UNK D_80083460;
extern M2C_UNK D_80083780;
extern M2C_UNK D_800C6AEC;
extern M2C_UNK D_80152EE4;
extern M2C_UNK D_80158640;

void func_8015627C(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    M2C_UNK var_a2;
    s16 temp_a0;
    s16 temp_v0_2;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_v0;
    s8 temp_v1_3;
    u8 temp_v1;
    u8 temp_v1_2;
    u8 temp_v1_4;
    void *temp_s0;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {                              /* irregular */
    case 0:
        M2C_FIELD(arg0, s16 *, 0x96) = 0x10;
        func_8004491C(arg0 - 0x20, &D_800C6AEC);
        M2C_FIELD(arg2, s32 *, 0xC) = 0x08000000;
        M2C_FIELD(arg2, s16 *, 0x10) = 0x20;
        M2C_FIELD(arg2, u16 *, 0x12) = (u16) (M2C_FIELD(arg2, u16 *, 0x12) - 0x80);
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0xC);
        M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x40000000);
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        /* fallthrough */
    case 1:
        temp_a0 = M2C_FIELD(arg0, s16 *, 0x96);
        if (temp_a0 != 0) {
            temp_v1_2 = (u8) M2C_FIELD(arg2, s32 *, 0xC);
            temp_v1_3 = temp_v1_2 + ((s32) (0x80 - temp_v1_2) / temp_a0);
            M2C_FIELD(arg2, s32 *, 0xC) = temp_v1_3;
            M2C_FIELD(arg2, s8 *, 0xE) = temp_v1_3;
            M2C_FIELD(arg2, s8 *, 0xD) = temp_v1_3;
            M2C_FIELD(arg0, s16 *, 0x96) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x96) - 1);
            return;
        }
block_13:
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        return;
    case 2:
        temp_v1_4 = M2C_FIELD(arg2, u8 *, 0xF);
        temp_s0 = arg0 - 0x20;
        if (temp_v1_4 >= 2U) {
            M2C_FIELD(arg2, u8 *, 0xF) = (u8) (temp_v1_4 - 1);
            return;
        }
        func_80044A50(temp_s0);
        func_8004491C(temp_s0, &D_80045340);
        M2C_FIELD(arg2, s32 *, 0xC) = 0x808080;
        M2C_FIELD(arg2, s16 *, 0x10) = 0;
        M2C_FIELD(arg2, u16 *, 0x12) = (u16) (M2C_FIELD(arg2, u16 *, 0x12) + 0x80);
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xFFF3);
        func_80156B90(temp_s0, arg3 + 0x2A, arg0 + 0x9A, arg0 + 0x98);
        goto block_13;
    case 3:
        M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_80152EE4;
        temp_a0_2 = M2C_FIELD(arg3, s32 *, 0x1C);
        temp_v0 = temp_a0_2 & 0xEFFFFFFF;
        M2C_FIELD(arg3, s32 *, 0x1C) = temp_v0;
        if (!(temp_v0 & 0x400000)) {
            var_a2 = 0x3000;
            if (temp_a0_2 & 0x2000) {
                var_a2 = 0x300;
            }
            func_8009A21C(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), var_a2);
        }
        M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) - 1);
        if (M2C_FIELD(arg3, u8 *, 0x28) == 0) {
            M2C_FIELD(&D_80083460, void **, 0x10) = (void *) (arg3 - 0x20);
            func_800AAA54(arg0, arg1, arg2, &D_80158640);
            return;
        }
        if (M2C_FIELD(arg3, s32 *, 0x14) & 0x4000) {
            if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x10000) {
                temp_v0_2 = func_800A1BD0(arg3);
                if (temp_v0_2 >= 0) {
                    temp_a0_3 = *(s32 *)0x800E3D7C;
                    func_800956B8(temp_a0_3, &D_80083780, &D_80082E80, M2C_FIELD(((temp_v0_2 * 4) + temp_a0_3), s32 *, 0xD0));
                    M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xFFFEFFFF);
                    return;
                }
            } else {
                goto block_25;
            }
        } else {
block_25:
            if ((func_80042900(arg3, 0xA) << 0x10) != 0) {
                func_800A48F0(arg3, 0xA, func_80042518(arg3, 0xA));
            }
            return;
        }
        break;
    }
}
