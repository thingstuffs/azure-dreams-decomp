#include "shared/sprite_frame_state.h"
#include "common.h"
#include "dungeon/actor.h"
#include "dungeon/actor/motion.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "dungeon/actor/status.h"


void spend_actor_mp(ActorRecord *entity, s32 base_reduction);            /* extern */
                /* extern */
void dispatch_monster_move_attack_spell(ActorRecord *, ObjectPosition *, SpriteFrameState *, ActorRecord *);

/* Process an interaction and reset the object's state when the checks allow it. */
void process_interaction_and_reset_state(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor) {
    if (update_actor_movement_to_tile(body, position, sprite, actor) != 0) {
        spend_actor_mp(actor, 5);
        advance_status_timers(actor);
        if ((check_actor_floor_trap(sprite, actor) << 0x10) <= 0) {
            return;
        }
        body->unk_8C.handler = &dispatch_monster_move_attack_spell;
        body->unk_90.value = 0;
    }
    if (g_dungeon_status.flags & 0x80) {
        body->unk_90.parts.high.s = 0;
    }
}
