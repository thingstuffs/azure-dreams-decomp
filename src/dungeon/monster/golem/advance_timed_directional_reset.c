#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct S_80047784 S_80047784;

typedef struct S_80172334_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0xA];
    u16 unk_A6;
} S_80172334_0;   /* arg0 in advance_timed_directional_reset */

struct SpriteFrameState;
void select_sprite_entry(void *, s16, s16);         /* extern */
extern u8 golem_frame_set_2;

/* Advance the timer and reset the state and directional sprite after 60 ticks. */
void advance_timed_directional_reset(ActorRecord *state, ObjectPosition *unused, SpriteFrameState *sprite, ActorRecord *orientation) {
    u16 ticks;

    ticks = ((S_80172334_0 *)state)->unk_A6 + 1;
    ((S_80172334_0 *)state)->unk_A6 = ticks;
    if ((u32) (ticks & 0xFFFF) >= 0x3DU) {
        u8 *direction_table = &golem_frame_set_2;

        ((S_80172334_0 *)state)->unk_A6 = 0x3CU;
        g_dungeon_status.activity_counts.parts.pending_action_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1;
        ((S_80172334_0 *)state)->unk_8C = 0;
        ((S_80172334_0 *)state)->unk_9A = 0x17;
        ((S_80172334_0 *)state)->unk_9B = 0;
        (sprite->frameTable) = direction_table;
        select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + orientation->facing + 0x100) >> 9) & 7)
            + direction_table), 0);
    }
}
