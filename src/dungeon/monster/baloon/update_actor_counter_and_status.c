#include "common.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "dungeon/actor/status.h"
#include "shared/sprite_frame_state.h"

s16 try_claim_dungeon_action_slot(ActorRecord *actor);                          /* extern */
s32 apply_camera_offset_and_select_target(void *object_addr, void *source_pos, s32 helper_arg, s32 slot_value); /* extern */


typedef struct S_80175BE0_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x2];
    s16 unk_96;
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x18];
    u16 unk_B4;
} S_80175BE0_1;   /* arg0 in update_actor_counter_and_status */


/* Reset motion and transfer the pending amount after the entity checks pass. */
void update_actor_counter_and_status(S_80175BE0_1 *state, ObjectPosition *motion, SpriteFrameState *unused, ActorRecord *entity) {
    entity->movement_queue_state = (u8) (entity->movement_queue_state & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(entity) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)entity - 0x20, motion, 8, 0x300);
        if ((try_claim_dungeon_action_slot(entity) << 0x10) == 0) {
            state->unk_8C = 0;
            state->unk_9A = 0x18;
            state->unk_9B = 0;
            state->unk_96 = 0;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            state->unk_92 = (u16) (state->unk_92 + ((u16)entity->ground_height));
            state->unk_B4 = (u16) ((u16)entity->ground_height);
            entity->ground_height = 0U;
            state->unk_98 = (u16) (state->unk_98 | 8);
            advance_status_timers(entity);
            entity->pending_turn_updates = (u8) (((u8)entity->pending_turn_updates) - 1);
        }
    }
}
