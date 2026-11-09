#include "shared/entity.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "dungeon/effect.h"
#include "dungeon/monster/beldo_large.h"
#include "dungeon/player/object.h"

struct Ent *prepare_directional_attack(void *ptr, void *value, s16 value_2, s32 value_3, void *value_4);

/* Clear the entity flag and advance its action when both checks pass. */
void start_actor_attack(ActorRecord *action_state, ObjectPosition *check_arg, void *action_arg, ActorRecord *entity) {
    entity->movement_queue_state &= 0x7F;
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(entity) << 0x10) == 0)) {
        apply_camera_offset_and_select_target(NODE_HEADER(entity), check_arg, 8, 0x300);
        if ((try_claim_dungeon_action_slot(entity) << 0x10) == 0) {
            action_state->unk_8C.word = 0;
            action_state->action_id = 0x11;
            action_state->action_phase = 0;
            entity->pending_turn_updates--;
            prepare_directional_attack(entity, action_arg, entity->facing, 1, 0);
            /* BYTES: unk_84 is declared signed char but retail builds this byte store with li 128; every value-cast spelling ((u8)0x80, -0x80, (signed char)0x80 or plain 0x80) emits li -128, so the store keeps its unsigned view until the field sign is settled. */
            *(u8 *)&entity->unk_84 = 0x80;
            entity->unk_85 = 0x20;
        }
    }
}

