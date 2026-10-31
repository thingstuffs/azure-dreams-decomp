#include "common.h"
#include "dungeon/actor/motion.h"
#include "dungeon/actor.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor/status.h"


extern void spend_actor_mp(ActorRecord *entity, s32 base_reduction);


extern s32 hikewne_action_resume_address[];

/* Selects the state table after a successful target check and applies the flagged offset. */
void select_state_table_with_flagged_offset(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    if (update_actor_movement_to_tile(body, motion, sprite, actor) != 0) {
        spend_actor_mp(actor, 4);
        advance_status_timers(actor);
        if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
            body->unk_8C.address = hikewne_action_resume_address;
            if (g_dungeon_status.flags & 0x80) {
                body->unk_90.parts.high.s = -0x20;
            }
        }
    } else if (g_dungeon_status.flags & 0x80) {
        body->unk_90.parts.high.s = -0x20;
    }
}
