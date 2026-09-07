#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94();        /* extern */
M2C_UNK func_800A56E0();                     /* extern */
extern s16 D_80083228;
extern u8 D_800DD294[];

/* Initializes actor state and selects an animation from the adjusted facing angle. */
void func_80097A68(void *actor, M2C_UNK unused, void *anim, void *facing_source) {
    M2C_FIELD(actor, s8 *, 0x9A) = 0x38;
    M2C_FIELD(actor, s8 *, 0x9B) = 0;
    M2C_FIELD(actor, s32 *, 0x8C) = 0;
    M2C_FIELD(anim, u8 **, 0x2C) = D_800DD294;
    func_8003DB94(anim, M2C_FIELD(D_800DD294, s32 *, ((s32) (D_80083228 + M2C_FIELD(facing_source, s16 *, 0x2A) + 0x100) >> 7) & 0x1C), 0);
    func_800A56E0(0x50A);
    M2C_FIELD(actor, s16 *, 0x96) = 2;
    M2C_FIELD(actor, u16 *, 0xA2) = (u16) (M2C_FIELD(actor, u16 *, 0xA2) & 0xFFEF);
}
