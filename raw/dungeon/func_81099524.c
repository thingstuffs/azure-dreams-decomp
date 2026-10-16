#include "common.h"
#include "m2c_compat.h"

s32 func_8003DE58(s32, void *, u16 *, M2C_UNK);     /* extern */
M2C_UNK func_80047784(void *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_800478B8(void *);                      /* extern */
extern M2C_UNK D_80163F38;

void func_80162D24(void *arg0, void *arg1, void *arg2) {
    u16 sp10;
    s16 temp_a0;
    u16 temp_v1;
    u16 temp_v1_2;
    void *temp_a1;
    void *temp_v0;

    if (M2C_FIELD(M2C_FIELD(arg0, void **, 8), s32 *, 0x2C) != &D_80163F38) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
        return;
    }
    temp_v0 = M2C_FIELD(arg0, void **, 4);
    M2C_FIELD(arg1, s32 *, 0) = (s32) M2C_FIELD(temp_v0, s32 *, 0);
    M2C_FIELD(arg1, s32 *, 4) = (s32) M2C_FIELD(temp_v0, s32 *, 4);
    M2C_FIELD(arg1, s32 *, 8) = (s32) M2C_FIELD(temp_v0, s32 *, 8);
    M2C_FIELD(arg1, s32 *, 0xC) = (s32) M2C_FIELD(temp_v0, s32 *, 0xC);
    M2C_FIELD(arg1, s32 *, 0x10) = (s32) M2C_FIELD(temp_v0, s32 *, 0x10);
    M2C_FIELD(arg1, s32 *, 0x14) = (s32) M2C_FIELD(temp_v0, s32 *, 0x14);
    temp_a1 = M2C_FIELD(arg0, void **, 8);
    if (func_8003DE58(M2C_FIELD(temp_a1, s32 *, 8), temp_a1, &sp10, 0) != 0) {
        M2C_FIELD(arg1, u16 *, 2) = (u16) (M2C_FIELD(arg1, u16 *, 2) + sp10);
        M2C_FIELD(arg1, u16 *, 6) = (u16) (M2C_FIELD(arg1, u16 *, 6) + sp12);
        M2C_FIELD(arg1, u16 *, 0xA) = (u16) (M2C_FIELD(arg1, u16 *, 0xA) + sp14);
    }
    temp_a0 = M2C_FIELD(arg0, s16 *, 0);
    temp_v1 = M2C_FIELD(arg0, u16 *, 2) + 1;
    M2C_FIELD(arg0, u16 *, 2) = temp_v1;
    switch (temp_a0) {                              /* irregular */
    case 0:
        func_800478B8(arg2);
        temp_v1_2 = M2C_FIELD(arg2, u16 *, 0x14);
        if (temp_v1_2 & 0x6000) {
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (temp_v1_2 | 0x80);
            M2C_FIELD(arg0, u16 *, 2) = 0U;
            M2C_FIELD(arg0, s16 *, 0) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0) + 1);
            return;
        }
        return;
    case 1:
        if ((s16) temp_v1 >= 0x40) {
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xFF7F);
            func_80047784(arg2, 0x38, 0);
            M2C_FIELD(arg0, u16 *, 2) = 0U;
            M2C_FIELD(arg0, s16 *, 0) = 0;
        }
        break;
    }
}
