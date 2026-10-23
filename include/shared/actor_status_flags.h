#ifndef SHARED_ACTOR_STATUS_FLAGS_H
#define SHARED_ACTOR_STATUS_FLAGS_H

#include "shared/actor_property_flags.h"

/* Live bits in ActorRecord.flags1C (+0x1C), changed by status, movement and attachment callbacks.
 * Slot-driven bits are set by apply_entity_action_flags and cleared by end_status_effect_message.
 * Equal numeric bits in flags14 are properties/resistances, not these current-state meanings. */
/* The remaining bits describe movement, attachment and current side.
 * Party membership retains the shared property spelling above. */
enum ActorStatusFlags {
    ACTOR_MP_EMPTY = 0x8, /* MP-exhaustion state gates normal actions/MP spending; feeding clears it when MP is restored */
    ACTOR_PUSH_PENDING = 0x100, /* queued push state consumed and cleared by begin_pushed_actor_move */
    ACTOR_PLAYER_SIDE = 0x2000, /* current side selects 0x300 occupancy rather than 0x3000; distinct from class enablement at actor +0x14 */
    ACTOR_PLAYER_AWARE = 0x20000, /* inferred player-awareness state; action selection tests it and blindness clears it */
    ACTOR_LIFTED = 0x80000, /* carried actor state; target points back to the carrier, release clears this bit */
    ACTOR_CARRYING = 0x100000, /* carrier state; the player keeps the carried actor in PlayerRecord.unk_124 */
    ACTOR_GROUNDED = 0x8000000, /* landing/movement completion state; landing clears it on launch and sets it when the airborne phase ends */
    ACTOR_REFRESH_GROUND = 0x40000000, /* terrain refresh pending; completed tile movement clears it and resamples the ground height */

    ACTOR_BLIND = 0x10, /* active blindness bit for STATUS_BLIND, separate from ACTOR_RESIST_BLIND */
    ACTOR_PARALYZED = 0x20, /* active paralysis bit for STATUS_PARALYSIS, separate from ACTOR_RESIST_PARALYSIS */
    ACTOR_POISONED = 0x40, /* active poison bit for STATUS_POISON; damage is advanced through the status slot timer */
    ACTOR_MAGIC_BOUND = 0x80, /* active magic-bind bit for STATUS_MAGIC_BIND */
    ACTOR_ASLEEP = 0x200, /* active sleep bit for STATUS_SLEEP; action eligibility tests it with paralysis and MP exhaustion */
    ACTOR_CONFUSED = 0x400, /* active confusion bit for STATUS_CONFUSION, separate from ACTOR_RESIST_CONFUSION */
    ACTOR_CURSED = 0x800, /* active curse bit for STATUS_CURSE */
    ACTOR_ANGRY = 0x1000, /* active anger bit; status application and derived actor effects can both set it */
};

/* Keep the unsigned type of the original hexadecimal clear masks. */
#define ACTOR_GROUNDED_CLEAR_MASK 0xF7FFFFFF /* unsigned 32-bit complement of ACTOR_GROUNDED; AND preserves the other flags1C bits */
#define ACTOR_REFRESH_GROUND_CLEAR_MASK 0xBFFFFFFF /* unsigned 32-bit complement of ACTOR_REFRESH_GROUND; AND preserves the other flags1C bits */
#define ACTOR_PLAYER_AWARE_CLEAR_MASK 0xFFFDFFFF /* unsigned 32-bit complement of ACTOR_PLAYER_AWARE; AND preserves the other flags1C bits */
#define ACTOR_LIFTED_CLEAR_MASK 0xFFF7FFFF /* unsigned 32-bit complement of ACTOR_LIFTED; AND preserves the other flags1C bits */
#define ACTOR_CARRYING_CLEAR_MASK 0xFFEFFFFF /* unsigned 32-bit complement of ACTOR_CARRYING; AND preserves the other flags1C bits */

#endif
