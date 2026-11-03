#include "shared/entity.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "dungeon/effect.h"
#include "dungeon/monster/beldo_large.h"
#include "dungeon/player/object.h"

s32 prepare_directional_attack(void *ptr, s32 value, s16 value_2, s32 value_3, s32 value_4);

/* Clear the entity flag and advance its action when both checks pass. */
void start_actor_attack(ActorRecord *action_state, ObjectPosition *check_arg, s32 action_arg, void *entity) {
    *(u8 *)((s8 *)entity + 0x71) &= 0x7F;
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(entity) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((s8 *)entity - 0x20, check_arg, 8, 0x300);
        if ((try_claim_dungeon_action_slot(entity) << 0x10) == 0) {
            action_state->unk_8C.word = 0;
            action_state->action_id.s = 0x11;
            action_state->action_phase.s = 0;
            *(u8 *)((s8 *)entity + 0x6D) = *(u8 *)((s8 *)entity + 0x6D) - 1;
            prepare_directional_attack(entity, action_arg, *(s16 *)((s8 *)entity + 0x2A), 1, 0);
            *(u8 *)((s8 *)entity + 0x84) = 0x80;
            *(u8 *)((s8 *)entity + 0x85) = 0x20;
        }
    }
}

