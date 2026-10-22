#ifndef DUNGEON_ACTOR_STATE_IDS_H
#define DUNGEON_ACTOR_STATE_IDS_H

/* Actor +0x9A is a callback-table index. Entry 14 of actor_contact_callbacks
 * selects no_op_actor_dispatch. Use this value only with a proved table;
 * bank-specific callback tables do not all share the same target. */
enum ActorState {
    ACTOR_STATE_NO_OP = 0xE,
};

#endif
