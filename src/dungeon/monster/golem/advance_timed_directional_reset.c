#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct S_80047784 S_80047784;


struct SpriteFrameState;
void select_sprite_entry(void *, s16, s16);         /* extern */
extern u8 golem_frame_set_2;

/* Advance the timer and reset the state and directional sprite after 60 ticks. */
void advance_timed_directional_reset(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor) {
    u16 ticks;

    ticks = body->unk_A4.halves.high.u + 1;
    body->unk_A4.halves.high.u = ticks;
    if ((u32) (ticks & 0xFFFF) >= 0x3DU) {
        u8 *direction_table = &golem_frame_set_2;

        body->unk_A4.halves.high.u = 0x3CU;
        g_dungeon_status.activity_counts.parts.pending_action_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1;
        body->unk_8C.word = 0;
        body->action_id.s = 0x17;
        body->action_phase.s = 0;
        (sprite->frameTable) = direction_table;
        select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)
            + direction_table), 0);
    }
}
