#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
M2C_UNK func_8009A350(s32, u8, s32, u16 *);         /* extern */
extern M2C_UNK D_80083460;
extern M2C_UNK D_80163EA8;

void func_80160358(void *arg0, void *arg2, void *arg3) {
    u16 sp10;
    u16 temp_v0;
    u16 temp_v1;

    func_8009A350(M2C_FIELD(arg2, u8 *, 0x24) - 1, M2C_FIELD(arg2, u8 *, 0x25), ((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 9) & 7, &sp10);
    if (!(sp10 & 0x8400)) {
        temp_v0 = M2C_FIELD(arg0, u16 *, 0xB2) + 1;
        M2C_FIELD(arg0, u16 *, 0xB2) = temp_v0;
        if ((u32) (temp_v0 & 0xFFFF) >= 0x3DU) {
            M2C_FIELD(arg0, u16 *, 0xB2) = 0x3CU;
            M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) + 1);
            M2C_FIELD(arg0, s8 *, 0x9A) = 0x19;
            M2C_FIELD(arg0, s32 *, 0x8C) = 0;
            M2C_FIELD(arg0, s8 *, 0x9B) = 0;
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80163EA8;
            func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80163EA8), 0);
            M2C_FIELD(arg0, u16 *, 0xB0) = (u16) M2C_FIELD(arg3, u16 *, 0x2A);
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xFFFBFFFF);
            temp_v1 = M2C_FIELD(arg0, u16 *, 0xA2);
            M2C_FIELD(arg0, u16 *, 0xA2) = 0U;
            M2C_FIELD(arg0, s16 *, 0x9E) = 0;
            M2C_FIELD(arg0, u16 *, 0x92) = (u16) (M2C_FIELD(arg0, u16 *, 0x92) - temp_v1);
        }
    }
}
