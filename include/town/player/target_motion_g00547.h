#include "shared/town_object.h"
#ifndef TOWN_PLAYER_TARGET_MOTION_G00547_H
#define TOWN_PLAYER_TARGET_MOTION_G00547_H
struct ObjectPosition;
struct TownObjectRecord;
/* Move player motion toward target coordinates (G00547). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D0608. */

#include "common.h"
#include "shared/position_views.h"

extern s32 player_target_position[];
extern s32 D_8009AAB8;
extern u32 D_8009AB74;

/* Functions defined in this translation unit. */
void move_player_toward_target(UnsignedCountdownView *state, struct ObjectPosition *object);
void approach_player_target_position(UnsignedCountdownView *state, struct ObjectPosition *motion);

struct SpriteFrameState;

void set_motion_handler_and_copy_signed_byte(TownObjectRecord *record_data, struct ObjectPosition *placement, struct SpriteFrameState *unused_sprite);

#endif
