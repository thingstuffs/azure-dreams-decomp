#ifndef SHARED_ACTOR_STATUS_FLAGS_H
#define SHARED_ACTOR_STATUS_FLAGS_H

#include "shared/actor_property_flags.h"

/* Active status bits in ActorRecord.flags1C (+0x1C). These are distinct
 * from the resistance bits in flags14 and from sprite/map-cell flags.
 * apply_entity_action_flags sets them for the corresponding status ID;
 * end_status_effect_message clears them when that status ends. */
/* The remaining bits describe movement, attachment and current side.
 * Party membership retains the shared property spelling above. */
enum ActorStatusFlags {
    ACTOR_MP_EMPTY = 0x8,
    ACTOR_PUSH_PENDING = 0x100,
    ACTOR_PLAYER_SIDE = 0x2000,
    ACTOR_PLAYER_AWARE = 0x20000,
    ACTOR_LIFTED = 0x80000,
    ACTOR_CARRYING = 0x100000,
    ACTOR_GROUNDED = 0x8000000,
    ACTOR_REFRESH_GROUND = 0x40000000,

    ACTOR_BLIND = 0x10,
    ACTOR_PARALYZED = 0x20,
    ACTOR_POISONED = 0x40,
    ACTOR_MAGIC_BOUND = 0x80,
    ACTOR_ASLEEP = 0x200,
    ACTOR_CONFUSED = 0x400,
    ACTOR_CURSED = 0x800,
    ACTOR_ANGRY = 0x1000,
};

/* Keep the unsigned type of the original hexadecimal clear masks. */
#define ACTOR_GROUNDED_CLEAR_MASK 0xF7FFFFFF
#define ACTOR_REFRESH_GROUND_CLEAR_MASK 0xBFFFFFFF
#define ACTOR_PLAYER_AWARE_CLEAR_MASK 0xFFFDFFFF
#define ACTOR_LIFTED_CLEAR_MASK 0xFFF7FFFF
#define ACTOR_CARRYING_CLEAR_MASK 0xFFEFFFFF

#endif
