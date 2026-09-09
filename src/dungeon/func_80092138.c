#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94();        /* extern */
s32 func_800A6D30(void *, M2C_UNK, void *, void *);   /* extern */
extern s16 D_80083228;
extern u8 D_800DD294[];

void func_80097898(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    /* MATCH: retain retail's a0 table base after the explicit argument call. */
    register u8 *temp ASM_REG("$4");
    /* MATCH: save a2 then a3 before loading the state-byte constant. */
    register void *saved2 ASM_REG("$17") = arg2;
    void *saved = arg3;
    ASM_KEEP_DEP_NV(saved2, saved);
    M2C_FIELD(arg0, s8 *, 0x9A) = 0x39;
    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    if (!(func_800A6D30(arg0, arg1, arg2, arg3) & 3)) {
        M2C_FIELD(saved, s32 *, 0x1C) = (s32) (M2C_FIELD(saved, s32 *, 0x1C) & ~0x620);
    }
    temp = D_800DD294;
    M2C_FIELD(saved2, u8 **, 0x2C) = temp;
    func_8003DB94(saved2, M2C_FIELD(temp, s32 *, ((s32) (D_80083228 + M2C_FIELD(saved, s16 *, 0x2A) + 0x100) >> 7) & 0x1C), 0);
}
