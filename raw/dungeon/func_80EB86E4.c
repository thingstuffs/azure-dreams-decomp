#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800478B8(void *);                      /* extern */
M2C_UNK func_800DBA90(void **);                     /* extern */

void func_80173EE4(void *arg0, void *arg1, void *arg2) {
    void *sp10;
    u16 *sp14;
    M2C_UNK sp18;
    M2C_UNK sp1C;
    M2C_UNK sp20;
    M2C_UNK sp24;
    s16 sp28;
    s16 sp2A;
    u16 sp30;
    s16 temp_v1;
    s32 temp_v0;
    u16 temp_v1_2;

    temp_v1 = M2C_FIELD(arg0, s16 *, 0x4C);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_800478B8(arg2);
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
            M2C_FIELD(arg2, s8 *, 4) = 0;
            M2C_FIELD(arg2, s8 *, 5) = 0;
        }
        M2C_FIELD(arg2, s32 *, 0xC) = (s32) (M2C_FIELD(arg2, s32 *, 0xC) + 0xFFE7E7E8);
        if ((u8) M2C_FIELD(arg2, s32 *, 0xC) < 0x30U) {
            M2C_FIELD(arg0, s16 *, 0x4C) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x4C) + 1);
        }
        temp_v1_2 = M2C_FIELD(arg0, u16 *, 8) + 0xA;
        temp_v0 = (s32) (temp_v1_2 << 0x10) >> 0x12;
        M2C_FIELD(arg0, u16 *, 8) = temp_v1_2;
        M2C_FIELD(arg0, s16 *, 4) = (s16) ((s32) -(temp_v0 * temp_v0) >> 4);
        sp10 = arg0 + 4;
        sp14 = &sp30;
        sp18 = M2C_UNALIGNED32(M2C_FIELD(arg0, M2C_UNK *, 0x14));
        sp1C = M2C_UNALIGNED32(M2C_FIELD(arg0, M2C_UNK *, 0x18));
        sp20 = M2C_UNALIGNED32(M2C_FIELD(arg0, M2C_UNK *, 0xC));
        sp24 = M2C_UNALIGNED32(M2C_FIELD(arg0, M2C_UNK *, 0x10));
        sp28 = 1;
        sp2A = 1;
        func_800DBA90(&sp10);
        M2C_FIELD(arg1, u16 *, 2) = sp30;
        M2C_FIELD(arg1, u16 *, 6) = sp32;
        M2C_FIELD(arg1, u16 *, 0xA) = sp34;
        return;
    case 1:
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
        return;
    }
}
