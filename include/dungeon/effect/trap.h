/* Complete resident-engine cohort contract. Review pending. */
#ifndef DUNGEON_ENGINE_TRAP_EFFECTS_H
#define DUNGEON_ENGINE_TRAP_EFFECTS_H
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "modules/trap_effects_candidate.h"
#include "shared/dir_step.h"
#include "shared/dungeon_floor.h"
#include "shared/dungeon_item_entries.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/entity_height_offsets.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/tile_object.h"

/* Fade callback body allocated by create_grid_effect_object (flags 2).
 * The cleared phase starts brightening; the constructor seeds four steps. */
typedef union TrapFadeHalf { s16 s; u16 u; } TrapFadeHalf;
typedef struct TrapFadeWork {
    TrapFadeHalf phase;
    TrapFadeHalf frames_left;
    s16 value;
    s16 mode;
} TrapFadeWork;
void fade_trap_color_to_black(TrapFadeWork *fade, void *unused, SpriteFrameState *color);

/* Both retail callers pass 0x10 in the second register; the helper ignores it. */
void apply_mode_selected_trap_mask(void *target, s32 unused_mask);

#endif
