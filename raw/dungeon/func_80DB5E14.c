#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
s32 func_800990FC();                                /* extern */
s32 func_80099194(M2C_UNK *, s32);                  /* extern */
M2C_UNK func_80099290(s32);                         /* extern */
s32 func_80099734(void *, s32);                     /* extern */
s32 func_800A05A4(void *, u8, u8, s16, s32);        /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */
M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
M2C_UNK func_800A5720(s32);                         /* extern */
M2C_UNK func_800AD594(void *, M2C_UNK);             /* extern */
M2C_UNK func_800C8A3C(s32, M2C_UNK, M2C_UNK);       /* extern */
extern M2C_UNK D_8014C854;
extern M2C_UNK D_8014CE68;
extern M2C_UNK D_8014F8A4;

void func_8014F614(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 temp_a0;
    s32 temp_v0;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_v0 = func_800990FC();
        func_80099290(func_80099194(&D_8014C854, func_80099734(arg3, temp_v0)));
        func_800A5720(temp_v0);
        M2C_FIELD(arg3, s32 *, 0x60) = func_800A05A4(arg3, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(arg3, s16 *, 0x2A), 0x10);
        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8014F8A4;
        func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8014F8A4), 0);
        func_800A56E0(0x812);
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        return;
    case 1:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            func_800AD594(arg3, 0xC00);
            M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8014CE68;
            *(s32 *)0x8008346C = 0;
            func_800A4ACC(arg3);
            if (M2C_FIELD(arg3, s8 *, 0x6D) == 0) {
                M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
            } else {
                *(void **)0x800E3DE8 = arg3 - 0x20;
            }
            temp_a0 = M2C_FIELD(arg3, s32 *, 0x60);
            if (temp_a0 != 0) {
                func_800C8A3C(temp_a0, 0x10, 0x10);
            }
        }
        return;
    }
}
