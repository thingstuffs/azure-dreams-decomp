#include "shared/entity.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

extern s32 select_sprite_entry();
extern s32 cycle_map_cell_flags();
void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
extern s16 get_rounded_facing_and_rounding_flag();

extern u8 beldo_frame_set_1[8];

typedef struct S_801719C0_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x16];
    u16 unk_88;
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_801719C0_0;   /* arg3 in advance_queued_movement_step */

typedef struct S_801719C0_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x2];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    u8 pad_9B[0x3];
    s16 unk_9E;
    u8 pad_A0[0x2];
    s16 unk_A2;
} S_801719C0_2;   /* arg0 in advance_queued_movement_step */

typedef struct S_801719C0_3 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_801719C0_3;   /* entry in advance_queued_movement_step */

typedef struct S_801719C0_4 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_801719C0_4;   /* (u8 *)arg3 + ((S_801719C0_0 *)arg3)->unk_8A.s in advance_queued_movement_step */

/* Advances a queued movement step and updates position, direction, and timing. */
void advance_queued_movement_step(ActorRecord *motion, ObjectPosition *unused, SpriteFrameState *sprite, ActorRecord *path) {
    s32 tile_mask;
    s32 step_count;
    s32 old_x;
    s32 old_y;
    u8 *step;

    if (((S_801719C0_0 *)path)->unk_71.s <= 0) {
        return;
    }
    if (((S_801719C0_0 *)path)->unk_71.u <= ((S_801719C0_0 *)path)->unk_8A.s) {
        return;
    }

    if (*(u8 **)&sprite->frameTable != beldo_frame_set_1) {
        (sprite->frameTable) = beldo_frame_set_1;
        select_sprite_entry(
            sprite,
            beldo_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + path->facing + 0x100) >> 9) & 7],
            0);
        sprite->frame_ticks = 1;
        ((S_801719C0_2 *)motion)->unk_A2 = 0;
        ((S_801719C0_2 *)motion)->unk_9E = 0;
    }

    step = (u8 *)path + ((S_801719C0_0 *)path)->unk_8A.s;
    if (sprite->tile_x == ((S_801719C0_3 *)step)->unk_74 &&
        sprite->tile_y == ((S_801719C0_3 *)step)->unk_7C) {
        u16 remaining_offset = ((S_801719C0_0 *)path)->unk_88;
        ((S_801719C0_2 *)motion)->unk_92 += 0x20;
        ((S_801719C0_0 *)path)->unk_88 = remaining_offset - 0x20;
        ((S_801719C0_0 *)path)->unk_8A.u++;
    } else {
        old_x = sprite->tile_x;
        old_y = sprite->tile_y;
        tile_mask = 0x3000;
        if (path->flags1C & 0x2000) {
            tile_mask = 0x300;
        }
        update_map_cell_flags_with_item_limit(old_x, old_y, tile_mask);

        sprite->tile_x =
            ((S_801719C0_4 *)((u8 *)path + ((S_801719C0_0 *)path)->unk_8A.s))->unk_74;
        sprite->tile_y =
            ((S_801719C0_4 *)((u8 *)path + ((S_801719C0_0 *)path)->unk_8A.s))->unk_7C;
        ((S_801719C0_0 *)path)->unk_8A.u++;

        cycle_map_cell_flags(sprite->tile_x, sprite->tile_y,
                      (path->flags1C & 0x2000) ? 0x300 : 0x3000);

        path->facing =
            get_rounded_facing_and_rounding_flag(old_x, old_y, sprite->tile_x,
                          sprite->tile_y, (u8 *)motion + 0x98);
    }
    ((S_801719C0_2 *)motion)->unk_9A = 0xF;
    ((S_801719C0_2 *)motion)->unk_8C = 0;
    path->flags1C |= 0x40000000;

    if (g_dungeon_status.flags & 0x80) {
        ((S_801719C0_2 *)motion)->unk_96 = 0;
        return;
    }

    ((S_801719C0_2 *)motion)->unk_96 = 8;
    step_count = ((S_801719C0_0 *)path)->unk_71.u;
    if (step_count > 0) {
        ((S_801719C0_2 *)motion)->unk_96 = 8 / step_count;
    }
}
