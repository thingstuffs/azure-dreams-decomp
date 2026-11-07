#include "dungeon/monster/u_boat.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"
#include "dungeon/player/object.h"
#include "dungeon/effect.h"


extern struct Ent *prepare_directional_attack();


/* Start the actor action and reset its state when ready, or dispatch the alternate action. */
void begin_actor_action(ActorRecord *state, ObjectPosition *world_pos, SpriteFrameState *sprite, ActorRecord *actor)
{
    if (state->unk_B4.bytes[1] == 0) {
        actor->movement_queue_state &= 0x7F;
        if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 16) == 0)) {
            apply_camera_offset_and_select_target(NODE_HEADER(actor), world_pos, 8, 0x300);
            if ((try_claim_dungeon_action_slot(actor) << 16) == 0) {
                state->unk_8C.word = 0;
                state->action_id = 0x11;
                state->action_phase = 0;
                state->action_timer = 0;
                actor->pending_turn_updates--;
                state->action_state_flags |= 8;
                prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
                actor->unk_84 = 0x7C;
                actor->unk_85 = 0;
                return;
            }
        }
    } else {
        begin_actor_exclusive_action(state, world_pos, sprite, 1, 1);
    }
}
