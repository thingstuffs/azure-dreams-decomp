#include "common.h"
#include "m2c_compat.h"
extern s32 D_800814A0;
void func_80023FA8(void *actor, void *unused, void *packet) {
    u16 depth;
    M2C_FIELD(packet, u32 *, 0xC) += 0xFFEFEFF0U;
    if (M2C_FIELD(actor, s16 *, 8) != 0) {
        depth = (u16)(M2C_FIELD(packet, u16 *, 0x1E) + 0x120);
        depth -= M2C_FIELD(packet, u8 *, 0xC) >> 3;
        M2C_FIELD(packet, u16 *, 0x1E) = depth;
        M2C_FIELD(packet, u16 *, 0x1C) = depth;
    }
    if (M2C_FIELD(packet, u8 *, 0xC) == 0) {
        M2C_FIELD(actor, u16 *, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
