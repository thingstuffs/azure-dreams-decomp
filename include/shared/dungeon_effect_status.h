#ifndef SHARED_DUNGEON_EFFECT_STATUS_H
#define SHARED_DUNGEON_EFFECT_STATUS_H

/* The effect initializer clears this byte through signed-char storage; the
 * staged entity loader also writes it. No larger allocation is claimed. */
extern signed char staged_spawn_count;

/* Source words retained by screen and travel effects until their attack runs. */
extern void *linked_monster_attack_event[];
extern void *warp_attack_event;

#endif
