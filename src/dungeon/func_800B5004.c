#include "common.h"

/* Externals (never defined here -- the overlay gate's linker resolves them). */
extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 D_800BA384;
extern s32 D_800BA6B8;

#define FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

/* Creates an object at the tile center with the supplied Z coordinate and user data. */
void *func_800BA764(u16 tile_x, u16 tile_y, s16 coord_z, s32 user_data) {
    void *object;
    void *position;
    u32 tile_x_u32;
    u32 tile_y_u32;

    object = func_8003FC64(0x202);
    if (object != 0) {
        FIELD(object, s32 **, 0x10) = &D_800BA6B8;
        func_8004491C(object, &D_800BA384);
        position = FIELD(object, void **, 8);
        tile_x_u32 = (u32)tile_x & 0xFFFFU;
        FIELD(position, s16 *, 2) = (tile_x_u32 * 64) + 0x20;
        tile_y_u32 = (u32)tile_y & 0xFFFFU;
        FIELD(position, s16 *, 6) = (tile_y_u32 * 64) + 0x20;
        FIELD(position, s16 *, 0xA) = coord_z;
        FIELD(object, s32 *, 0x50) = user_data;
    }
    return object;
}
