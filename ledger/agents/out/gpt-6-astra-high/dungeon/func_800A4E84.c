#include "common.h"

typedef struct S_800AA5E4_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
} S_800AA5E4_0;   /* arg0 in func_800AA5E4 */

typedef struct S_800AA5E4_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800AA5E4_1;   /* arg3 in func_800AA5E4 */

typedef struct S_800AA5E4_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
} S_800AA5E4_2;   /* arg2 in func_800AA5E4 */


extern s32 func_8009A3D0();
extern s8 func_8009FB34();
extern s32 func_800A4E2C();
extern s32 func_800AA53C();
typedef struct {
    u8 pad[10];
    u16 counter;
} DungeonState;

extern DungeonState D_80083460;


/* Resets entity state, selects a new position, and increments the dungeon counter. */
void func_800AA5E4(S_800AA5E4_0 *entity, void *unused, void *position, S_800AA5E4_1 *entity_state) {
    s32 tile_mask;
    s32 flags;
    s32 tile_x;
    s32 tile_y;
    void *tile_x_ptr;
    DungeonState *state;

    entity->unk_9A = 4;
    entity->unk_9B = 0;
    entity->unk_8C = 0;
    entity->unk_96 = 0x10;
    entity->unk_98 = entity->unk_98 | 8;
    flags = entity_state->unk_1C | 0x10000;
    entity_state->unk_1C = flags;
    tile_x = ((S_800AA5E4_2 *)position)->unk_24;
    tile_y = ((S_800AA5E4_2 *)position)->unk_25;
    tile_mask = 0x3000;
    if (flags & 0x2000) {
        tile_mask = 0x300;
    }
    func_8009A3D0(tile_x, tile_y, tile_mask);
    tile_x_ptr = (u8 *)position + 0x24;
retry_position:
    if ((s16)func_800A4E2C(tile_x_ptr, (u8 *)position + 0x25) < 0) {
        tile_x_ptr = (u8 *)position + 0x24;
        goto retry_position;
    }
    ((S_800AA5E4_2 *)position)->unk_26 = func_8009FB34(((S_800AA5E4_2 *)position)->unk_24, ((S_800AA5E4_2 *)position)->unk_25);
    func_800AA53C(entity_state);
    state = &D_80083460;
    ASM_KEEP(state);   /* MATCH pin: load-bearing for the whole function shape */
    state->counter = state->counter + 1;
}
