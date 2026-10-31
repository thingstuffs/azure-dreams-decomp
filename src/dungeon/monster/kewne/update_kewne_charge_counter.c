#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/monster/kewne.h"
#include "engine/graphics.h"
#include "dungeon/level.h"

typedef struct S_80047784 S_80047784;


typedef struct S_func_809A0B58_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[6];
    u8 *unk_2C;
} S_func_809A0B58_1;



struct SpriteFrameState;
extern u8 kewne_frame_set[9];

/* Advance the counter when unblocked and reset the action when it exceeds 60. */
void update_kewne_charge_counter(ActorRecord *actor_state, ObjectPosition *position, S_func_809A0B58_1 *sprite, ActorRecord *actor) {
    u16 tile_flags;
    u16 counter_value;
    u8 *direction_frames;

    get_offset_map_cell_value_and_flags(sprite->unk_24 - 1, sprite->unk_25,
                  ((u16)actor->facing >> 9) & 7, &tile_flags);
    if (!(tile_flags & 0x8400)) {
        counter_value = actor_state->unk_B0.halves.high.u + 1;
        actor_state->unk_B0.halves.high.u = counter_value;
        if ((u32)(counter_value & 0xFFFF) >= 0x3D) {
            actor_state->unk_B0.halves.high.u = 0x3C;
            g_dungeon_status.activity_counts.parts.pending_action_count =
                (u16)(((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1);
            actor_state->action_id.s = 0x19;
            actor_state->unk_8C.word = 0;
            actor_state->action_phase.s = 0;
            direction_frames = kewne_frame_set;
            sprite->unk_2C = direction_frames;
            select_sprite_entry(sprite,
                          direction_frames[((s32)(g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                          0);
            actor_state->unk_B0.halves.low.u = (u16)actor->facing;
            actor->flags1C = (s32)(actor->flags1C & 0xFFFBFFFF);
            counter_value = actor_state->unk_90.parts.high.u - actor_state->unk_A0.parts.high;
            actor_state->unk_A0.parts.high = 0;
            actor_state->unk_9E.s = 0;
            actor_state->unk_90.parts.high.u = counter_value;
        }
    }
}

