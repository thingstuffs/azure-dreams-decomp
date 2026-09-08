#include "common.h"

extern u16 D_8008347E;
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
s32 func_8009A540(s32, u8, u8, s16);
s32 func_8009B25C(void *, u16, u16, s16);
s32 func_800A2CB8(void *, s32);

/* Returns the first valid candidate found while checking eight neighboring positions. */
s32 func_800A03C4(void *entity, u16 x, u16 y) {
    u16 *x_offsets;
    u16 *y_offsets;
    void *entity_data;
    void *entity_ptr;
    u16 origin_x;
    u16 origin_y;
    s32 candidate;
    s32 attempt;
    s32 direction;

    entity_ptr = entity;
    origin_x = x;
    origin_y = y;
    x_offsets = D_8006CCD8;
    y_offsets = D_8006CCE8;
    entity_data = *(void **)((s8 *)entity_ptr - 0x14);
    direction = D_8008347E & 7;
    for (attempt = 0; attempt < 8; attempt++, direction = (direction + 1) & 7) {
        candidate = func_8009B25C(entity_ptr, (origin_x + x_offsets[direction]) & 0xFFFF, (origin_y + y_offsets[direction]) & 0xFFFF, *(s16 *)((s8 *)entity_ptr + 0x88));
        if (candidate != 0 && ((func_800A2CB8(entity_ptr, candidate) << 16) != 0)) {
            if (((func_8009A540(direction, *(u8 *)((s8 *)entity_data + 0x24), *(u8 *)((s8 *)entity_data + 0x25), (s16)((u16)*(s16 *)((s8 *)entity_ptr + 0x88) - 0x20)) << 16) == 0)) {
                continue;
            }
            entity_ptr = entity;
            return candidate;
        }
    }
    return 0;
}
