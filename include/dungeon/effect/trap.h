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

/* Tail of the sprite node created by spawn_source_sprite_effect and advanced by its bouncing callback. */
typedef struct BouncingTrapEffectBody {
    void *source;
    s16 phase;
    u16 ticks_left;
    s16 unk_08;
    s16 floor_height;
} BouncingTrapEffectBody;

/* Delay, state, and entry index for the monster-den sequence callback. */
typedef struct ClampEntryAndCreateEffectNodeBody {
    u8 pad_00[0x4];
    u16 delay_timer;
    u16 state;
    u8 pad_08[0x4];
    s16 entry_index;
} ClampEntryAndCreateEffectNodeBody;
void advance_monster_den_sequence(ClampEntryAndCreateEffectNodeBody *den_event);

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

typedef struct TrapOwnedTimedEffectBody {
    void *owner;
    u8 pad_04[2];
    u16 ticks_remaining;
} TrapOwnedTimedEffectBody;
void advance_go_up_trap_sequence(TrapOwnedTimedEffectBody *trap_state, void *motion_state, void *animation);
void tick_trap_effect_countdown(TrapOwnedTimedEffectBody *effect);

/* Position and direction carried by each segment of the five-part target effect. */
typedef struct FivePartTargetEffectBody {
    u16 x;
    u16 y;
    s16 z;
    u8 direction;
    u8 ticks_remaining;
} FivePartTargetEffectBody;

/* Resource-backed slot whose five-part effect payload begins at +0x20. */
typedef struct FivePartTargetEffectRecord {
    u8 pad_00[0x10];
    u8 *resource;
    u8 pad_14[0xC];
    FivePartTargetEffectBody body;
} FivePartTargetEffectRecord;

void advance_trap_effect_and_process_collisions(FivePartTargetEffectBody *effect);
void tick_byte_timed_trap_effect(FivePartTargetEffectBody *effect);

/* State used by the falling effects installed by create_four_owner_sprite_effects. */
typedef struct FourOwnerSpriteEffectsBody {
    void *target;
    s16 state;
    u16 timer;
    s16 mode;
    union { s16 s; u16 u; } threshold;
    u16 frame_count;
} FourOwnerSpriteEffectsBody;

/* Both retail callers pass 0x10 in the second register; the helper ignores it. */
void apply_mode_selected_trap_mask(ActorRecord *target, s32 unused_mask);

#endif
