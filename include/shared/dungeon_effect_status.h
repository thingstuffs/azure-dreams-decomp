#ifndef SHARED_DUNGEON_EFFECT_STATUS_H
#define SHARED_DUNGEON_EFFECT_STATUS_H

#include "common.h"

/* The effect initializer clears this byte through signed-char storage; the
 * staged entity loader also writes it. No larger allocation is claimed. */
extern signed char staged_spawn_count;

/* Halfword state shared by actor action and replacement overlays (0x800DCF5E). */
extern s16 actor_action_reset_value;

/* Source words retained by screen and travel effects until their attack runs. */
extern void *linked_effect_chain_attack_event[];
extern void *warp_attack_event;

#endif
