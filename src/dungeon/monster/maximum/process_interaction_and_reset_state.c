#include "common.h"
#include "dungeon/actor.h"
#include "dungeon/actor/motion.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct S_801722DC_0 {
    u8 pad_00[0x8C];
    void (*unk_8C)(void *, void *, void *, ActorRecord *);
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_90;   /* overlapping accesses */
} S_801722DC_0;   /* arg0 in process_interaction_and_reset_state */


s32 advance_status_timers();                     /* extern */
void spend_actor_mp();            /* extern */
                /* extern */
void dispatch_monster_move_attack_spell(void *controller, void *context, void *entity, ActorRecord *actor_state);

/* Process an interaction and reset the object's state when the checks allow it. */
void process_interaction_and_reset_state(S_801722DC_0 *state, void *context, void *source, ActorRecord *target) {
    if (update_actor_movement_to_tile(state, context, source, target) != 0) {
        spend_actor_mp(target, 5);
        advance_status_timers(target);
        if ((check_actor_floor_trap(source, target) << 0x10) <= 0) {
            return;
        }
        state->unk_8C = &dispatch_monster_move_attack_spell;
        state->unk_90.at00.v = 0;
    }
    if (g_dungeon_status.flags & 0x80) {
        state->unk_90.at02.v = 0;
    }
}
