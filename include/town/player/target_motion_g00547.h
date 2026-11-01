#ifndef TOWN_PLAYER_TARGET_MOTION_G00547_H
#define TOWN_PLAYER_TARGET_MOTION_G00547_H
struct PersonObject;
/* Move player motion toward target coordinates (G00547). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D0608. */

#include "common.h"
#include "shared/position_views.h"

extern s32 player_target_position[];
extern s32 D_8009AAB8;
extern u32 D_8009AB74;

/* Functions defined in this translation unit. */
void move_player_toward_target(UnsignedCountdownView *state, void *object);
void approach_player_target_position(UnsignedCountdownView *state, void *motion);

struct SpriteFrameState;

void set_motion_handler_and_copy_signed_byte(struct PersonObject *record_data, void *placement, struct SpriteFrameState *unused_sprite);

#endif
