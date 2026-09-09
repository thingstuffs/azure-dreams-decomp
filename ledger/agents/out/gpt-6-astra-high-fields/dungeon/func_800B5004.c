#include "common.h"

/* Externals (never defined here -- the overlay gate's linker resolves them). */
extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 D_800BA384;
extern s32 D_800BA6B8;

typedef struct S_func_800BA764_0 {
    u8 pad_00[0x8];
    void *unk_08;
    u8 pad_0C[0x4];
    s32 *unk_10;
    u8 pad_14[0x3C];
    s32 unk_50;
} S_func_800BA764_0;

typedef struct S_func_800BA764_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_func_800BA764_1;

/* Creates an object at the tile center with the supplied Z coordinate and user data. */
void *func_800BA764(u16 tile_x, u16 tile_y, s16 coord_z, s32 user_data) {
    S_func_800BA764_0 *object;
    S_func_800BA764_1 *position;
    u32 tile_x_u32;
    u32 tile_y_u32;

    object = func_8003FC64(0x202);
    if (object != 0) {
        object->unk_10 = &D_800BA6B8;
        func_8004491C(object, &D_800BA384);
        position = object->unk_08;
        tile_x_u32 = (u32)tile_x & 0xFFFFU;
        position->unk_02 = (tile_x_u32 * 64) + 0x20;
        tile_y_u32 = (u32)tile_y & 0xFFFFU;
        position->unk_06 = (tile_y_u32 * 64) + 0x20;
        position->unk_0A = coord_z;
        object->unk_50 = user_data;
    }
    return object;
}
