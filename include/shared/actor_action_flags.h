#ifndef SHARED_ACTOR_ACTION_FLAGS_H
#define SHARED_ACTOR_ACTION_FLAGS_H

/* ActorRecord.action_flags (+0x46), distinct from action callback flags (+0x98).
 * Selection sets the pending bit; completed movement clears it. The low 14
 * bits select the action in the monster behavior dispatchers. */
#define ACTOR_ACTION_PENDING 0x8000
#define ACTOR_ACTION_CLEAR_PENDING_MASK 0x7FFF
#define ACTOR_ACTION_CODE_MASK 0x3FFF

#endif
