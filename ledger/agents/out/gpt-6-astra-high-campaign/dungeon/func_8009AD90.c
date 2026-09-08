#include "common.h"

extern u8 D_8006CCD8[9];
extern u8 D_8006CCE8[9];
extern void func_8009B25C(void *, s32, s32, s32);

/* Apply direction offsets to the coordinates and update the entity. */
void func_800A04F0(void *entity, s32 x, s32 y, u32 direction) {
    s32 direction_bits;
    u8 *x_offsets;
    s32 direction_offset;

    direction_bits = direction >> 8;
    x_offsets = D_8006CCD8;
    direction_offset = direction_bits & 0xE;
    func_8009B25C(
        entity,
        (*(u16 *)(x_offsets + direction_offset) + x) & 0xFFFF,
        (*(u16 *)(&D_8006CCE8[direction_offset]) + y) & 0xFFFF,
        *(s16 *)((u8 *)entity + 0x88));
}
