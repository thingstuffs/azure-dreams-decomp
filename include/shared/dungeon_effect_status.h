#ifndef SHARED_DUNGEON_EFFECT_STATUS_H
#define SHARED_DUNGEON_EFFECT_STATUS_H

/* The effect initializer clears this byte through signed-char storage; the
 * staged entity loader also writes it. No larger allocation is claimed. */
extern signed char staged_spawn_count;

#endif
