#include "common.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"





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
void func_800AA5E4(Rec_func_800A9E70_arg0 *entity, void *unused, void *position, Rec_D_800E3D7C *entity_state) {
    s32 tile_mask;
    s32 flags;
    s32 tile_x;
    s32 tile_y;
    void *tile_x_ptr;
    DungeonState *state;

    entity->unk_9A.as_s8 = 4;
    entity->unk_9B.as_s8 = 0;
    entity->unk_8C = 0;
    entity->unk_96.as_s16 = 0x10;
    entity->unk_98 = entity->unk_98 | 8;
    flags = entity_state->unk_1C.as_s32 | 0x10000;
    entity_state->unk_1C.as_s32 = flags;
    tile_x = ((Rec_D_80082E80 *)position)->unk_24;
    tile_y = ((Rec_D_80082E80 *)position)->unk_25;
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
    ((Rec_D_80082E80 *)position)->unk_26.as_s8 = func_8009FB34(((Rec_D_80082E80 *)position)->unk_24, ((Rec_D_80082E80 *)position)->unk_25);
    func_800AA53C(entity_state);
    state = &D_80083460;
    state->counter = state->counter + 1;
}
