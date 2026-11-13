#include "common.h"
#include "dungeon/system/random.h"
#include "shared/dungeon_status.h"
#include "dungeon/system.h"
#include "dungeon/item.h"
#include "dungeon/level.h"
#include "dungeon/actor.h"

typedef struct Ent Ent;
typedef struct Pos Pos;
extern Ent *prepare_directional_attack(Ent *, Pos *, u32, s32, Ent *);

/* Reset the entity state and initialize the active dungeon actor. */
s32 begin_actor_attack(ActorRecord *body, ObjectPosition *unused, void *action_param, ActorRecord *actor) {
    body->action_state_flags |= 0x2000;
    prepare_directional_attack((Ent *)actor, action_param, actor->facing, 1, 0);
    if (actor->flags1C & 0x400) {
        actor->facing = actor->facing + (generate_random_value() & 0xE00);
    }
    body->action_id = 0x37;
    body->action_phase = 0;
    body->unk_8C.word = 0;
    g_dungeon_status.active_actor = actor;
    body->unk_A4.halves.high.s = 0;
    process_unflagged_linked_entries_alt(actor->next_actor_header);
    append_packed_action_record(actor, 0x18, 0, 0);
    if (check_action_available_without_nearby_actor() != 0) {
        g_dungeon_status.flags |= 0x80;
    }
    return 0;
}
