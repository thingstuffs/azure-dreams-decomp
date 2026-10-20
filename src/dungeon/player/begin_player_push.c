#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "records/Rec_func_8008ACDC_arg0.h"

typedef struct S_80048A44_Obj S_80048A44_Obj;

typedef struct S_8008CD4C_0 {
    u8 pad_00[0x24];
    u8 unk_24;
    union { u8 s; u8 u; } unk_25;   /* accessed as both */
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_8008CD4C_0;   /* arg2 in begin_player_push */

typedef struct S_8008CD4C_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x5C];
    s16 unk_88;
} S_8008CD4C_2;   /* actor in begin_player_push */

extern void set_sprite_animation_frame(S_80048A44_Obj *obj, s16 frame_group, s16 frame_index, s32 slot_index);
s16 check_tile_entry_at_adjusted_height();
void cycle_map_cell_flags();
void update_map_cell_flags_with_item_limit();
s32 can_push_adjacent_actor();
s32 find_eligible_actor_at_tile_and_height();
void append_packed_action_record();
s32 play_sound_if_enabled();

extern u8 D_800DCFB8[];
extern u8 D_800DD018[];

/* Checks the next tile and updates the actor's movement state and directional animation. */
void begin_player_push(Rec_func_8008ACDC_arg0 *action, s32 context, S_8008CD4C_0 *sprite, S_8008CD4C_2 *actor,
    s16 move_state) {
    s16 state;
    s32 direction_offset;
    s32 next_x;
    s32 next_y;
    s32 target;
    u16 *x_step;
    u16 *y_step;

    ((SpriteFrameState *)sprite)->frameTable = D_800DD018;
    state = move_state;
    action->unk_9A.as_u8 = 0x18;
    action->unk_9B.as_u8 = 0;
    action->unk_8C.as_s32 = 0;

    if ((s16)state != -2) {
        direction_offset = ((actor->unk_2A.s >> 8) & 0xE);
        x_step = (u16 *)((u8 *)dir_step_x + direction_offset);
        next_x = ((SpriteFrameState *)sprite)->unk_24 + *x_step;
        y_step = (u16 *)((u8 *)dir_step_y + direction_offset);
        next_y = ((SpriteFrameState *)sprite)->unk_25 + *y_step;
        target = find_eligible_actor_at_tile_and_height(actor, next_x & 0xFFFF, next_y & 0xFFFF,
                               actor->unk_88);
        if (target != 0) {
            if ((can_push_adjacent_actor(actor, target, (s16)next_x, (s16)next_y,
                               actor->unk_88) << 16) != 0) {
                action->unk_124 = target;
                update_map_cell_flags_with_item_limit(((SpriteFrameState *)sprite)->unk_24,
                              ((SpriteFrameState *)sprite)->unk_25, 0x300);
                ((SpriteFrameState *)sprite)->unk_24 =
                    ((SpriteFrameState *)sprite)->unk_24 + *(u8 *)x_step;
                ((SpriteFrameState *)sprite)->unk_25 =
                    ((SpriteFrameState *)sprite)->unk_25 + *(u8 *)y_step;
                cycle_map_cell_flags(((SpriteFrameState *)sprite)->unk_24,
                              ((SpriteFrameState *)sprite)->unk_25, 0x300);

                actor->unk_1C |= 0x40000000;
                g_dungeon_status.movement_frames_left = 0x20;
                g_dungeon_status.flags |= 8;
                action->unk_9B.as_u8 = 0x10;
                ((SpriteFrameState *)sprite)->frameTable = D_800DCFB8;
                action->unk_96.as_s16 = 4;
                append_packed_action_record(actor, 8, 0, 0);
                play_sound_if_enabled(0x50B);
                check_tile_entry_at_adjusted_height(action, context, sprite, actor);
            }
        }
    }

    set_sprite_animation_frame(
        sprite,
        (*(u8 * *)&((SpriteFrameState *)sprite)->frameTable)
            [((g_game_work.view.camera_rotation.parts.viewAngle + actor->unk_2A.u + 0x100) >> 9) & 7],
        0, 1);
}
