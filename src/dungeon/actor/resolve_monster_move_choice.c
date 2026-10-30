#include "dungeon/actor.h"
#include "dungeon/player/object/action_state.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor/state.h"

extern void update_actor_status_and_mp(ActorRecord *);
/* func_80171854 keeps its address: bank_9bf000 places the Hikewne direction
 * selector there, but bank_10a3000 rebinds this address into a Grineut helper. */
extern void func_80171854(ActorRecord *, ObjectPosition *, SpriteFrameState *, ActorRecord *);

/* Ask the move selector for an action; force or retry a stored move, rest, or finish the turn. */
s32 resolve_monster_move_choice(ActorRecord *initial, ObjectPosition *position, SpriteFrameState *sprite, s32 force_move) {
    ActorRecord *actor;
    s16 action;
    s32 result;

    actor = initial;
    action = relink_entity_and_clear_high_flag(position, sprite, actor, 3, 6, &actor->unk_9C);
    if (action < 0) {
        return 0;
    }
    if ((force_move << 16) != 0) {
        func_80171854(actor, position, sprite, actor);
        return 0;
    }
    switch (action) {
    case 0:
        actor->action_id.u = 0xE;
        update_actor_status_and_mp(actor);
        return 0;
    case 2:
        func_80171854(actor, position, sprite, actor);
        return 0;
    case 1:
        actor->movement_queue_state &= 0x7F;
        if ((has_pending_dungeon_activity(actor) << 16) != 0) {
            result = 0;
            actor->action_flags &= 0x7FFF;
            return result;
        }
        break;
    }
    actor->movement_queue_state &= 0x7F;
    result = 1;
    if (!(g_dungeon_status.flags & 8)) {
        return result;
    }
    result = 0;
    actor->action_flags &= 0x7FFF;
    return result;
}
