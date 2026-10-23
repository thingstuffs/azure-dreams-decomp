#include "common.h"
extern s32 update_actor_defeat_removal(void *, void *, void *, void *);
/* Runs the shared actor defeat and removal sequence and returns its completion result. */
s32 update_troll_defeat_removal_slot_a(void *state, void *position, void *packet, void *entity) { return update_actor_defeat_removal(state, position, packet, entity); }
