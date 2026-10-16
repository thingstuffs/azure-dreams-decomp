#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8014D0B8(void *, void *, M2C_UNK);     /* extern */

void func_8014D2C4(void *arg0, void *arg1, M2C_UNK arg2) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x17);
    M2C_FIELD(arg0, u16 *, 0x32) = (u16) (M2C_FIELD(arg0, u16 *, 0x32) - 1);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_8014D0B8(arg0, arg1, arg2);
        func_8014D0B8(arg0, arg1, arg2);
        if ((s16) M2C_FIELD(arg0, u16 *, 0x32) == 0) {
            M2C_FIELD(arg0, u16 *, 0x32) = 0x10U;
            M2C_FIELD(arg0, s16 *, 0x34) = 0x10;
            M2C_FIELD(arg0, u8 *, 0x17) = (u8) (M2C_FIELD(arg0, u8 *, 0x17) + 1);
        }
        M2C_FIELD(arg0, s32 *, 8) = (s32) M2C_FIELD(arg0, u8 *, 0);
        return;
    case 1:
        M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg0, s32 *, 0x40));
        M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg0, s32 *, 0x44));
        M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg0, s32 *, 0x48));
        M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg0, s32 *, 0x40));
        M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg0, s32 *, 0x44));
        M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg0, s32 *, 0x48));
        M2C_FIELD(arg0, s8 *, 5) = (s8) ((s32) (M2C_FIELD(arg0, u8 *, 1) * (s16) M2C_FIELD(arg0, u16 *, 0x32)) / (s16) M2C_FIELD(arg0, s16 *, 0x34));
        M2C_FIELD(arg0, s8 *, 4) = (s8) ((s32) (M2C_FIELD(arg0, u8 *, 0) * (s16) M2C_FIELD(arg0, u16 *, 0x32)) / (s16) M2C_FIELD(arg0, s16 *, 0x34));
        M2C_FIELD(arg0, s8 *, 6) = (s8) ((s32) (M2C_FIELD(arg0, u8 *, 2) * (s16) M2C_FIELD(arg0, u16 *, 0x32)) / (s16) M2C_FIELD(arg0, s16 *, 0x34));
        M2C_FIELD(arg0, s32 *, 8) = (s32) M2C_FIELD(arg0, s8 *, 4);
        if ((s16) M2C_FIELD(arg0, u16 *, 0x32) <= 0) {
            M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
            *(s32 *)0x800814A0 |= 0x8000;
        }
        return;
    }
}
