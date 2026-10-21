#ifndef TOWN_PLAYER_TARGET_MOTION_G00547_H
#define TOWN_PLAYER_TARGET_MOTION_G00547_H
/* Move player motion toward target coordinates (G00547). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D0608. */

#include "common.h"

extern void clear_entity_record_fields(void *record);
extern s32 D_800D0608[];
extern s32 D_8009AAB8;
extern u32 D_8009AB74;

/* Functions defined in this translation unit. */
void move_player_toward_target(void *state, void *object);
void approach_player_target_position(void *state, void *motion);

#endif
