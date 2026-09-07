#include "common.h"



typedef s32 M2C_UNK;

typedef struct S_800AA888_3 {
    u8 pad_00[0x60];
    void * unk_60;
} S_800AA888_3;   /* arg3 in func_800AA888 */

typedef struct S_800AA888_4 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_800AA888_4;   /* ((S_800AA888_3 *)arg3)->unk_60 in func_800AA888 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8009A3D0();

typedef struct S_800AA888_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
} S_800AA888_0;   /* arg0 in func_800AA888 */

typedef struct S_800AA888_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800AA888_1;   /* arg2 in func_800AA888 */

typedef struct S_800AA888_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x4A];
    u16 unk_6A;
} S_800AA888_2;   /* arg3 in func_800AA888 */

/* Reset action state, update the tile, and refresh entity flags and data. */
void func_800AA888(S_800AA888_0 *state, void *unused, S_800AA888_1 *position, S_800AA888_2 *entity) {
    u8 tile_x;
    u8 tile_y;
    M2C_UNK update_mask;

    state->unk_9A = 0xB;
    state->unk_9B = 0;
    state->unk_8C = 0;
    tile_x = position->unk_24;
    tile_y = position->unk_25;
    update_mask = 0x3000;
    if (entity->unk_1C & 0x2000) {
        update_mask = 0x300;
    }
    func_8009A3D0(tile_x, tile_y, update_mask);
    state->unk_98 = (u16)(state->unk_98 | 8);
    entity->unk_1C = (s32)(entity->unk_1C & 0xFFFBFFFF);
    state->unk_96 = 0;
    entity->unk_6A = (u16)((S_800AA888_4 *)(((S_800AA888_3 *)entity)->unk_60))->unk_2A;
}
