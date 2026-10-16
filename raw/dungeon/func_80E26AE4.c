#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
s16 func_800A0818(u8, u8, u8, u8, M2C_UNK *);       /* extern */
s32 func_800A2B5C(void *);                          /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */
M2C_UNK func_800C77D0(void *, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_800C7930(void *, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
extern M2C_UNK D_8015E4A0;

void func_8015A2E4(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    M2C_UNK sp18;
    void *temp_s3;
    void *temp_v0;

    M2C_FIELD(arg3, u8 *, 0x71) = (u8) (M2C_FIELD(arg3, u8 *, 0x71) & 0x7F);
    if (!(*(u16 *)0x80083462 & 0x2008)) {
        temp_s3 = arg3 - 0x20;
        if ((func_800A2B5C(arg3) << 0x10) == 0) {
            func_800C7930(temp_s3, arg1, 8, 0x300);
            if ((func_800A2B5C(arg3) << 0x10) == 0) {
                temp_v0 = M2C_FIELD(M2C_FIELD(arg3, void **, 0x60), void **, -0x14);
                M2C_FIELD(arg3, s16 *, 0x2A) = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(temp_v0, u8 *, 0x24), M2C_FIELD(temp_v0, u8 *, 0x25), &sp18);
                M2C_FIELD(arg0, s8 *, 0x9A) = 0x17;
                M2C_FIELD(arg0, s8 *, 0x9B) = 0;
                M2C_FIELD(arg0, s32 *, 0x8C) = 0;
                M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8015E4A0;
                func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8015E4A0), 0);
                func_800A4ACC(arg3);
                M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
                M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 8);
                func_800C77D0(temp_s3, arg1, 8, 0x300);
            }
        }
    }
}
