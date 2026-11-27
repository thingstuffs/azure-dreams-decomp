#ifndef TRAP_EFFECTS_CANDIDATE_H
#define TRAP_EFFECTS_CANDIDATE_H
#include "common.h"
#include "shared/dungeon_item_entries.h"
#include "m2c_compat.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/level/trap_request_blocked.h"
typedef struct ActiveEntry { u8 pad0; u8 active; u8 pad2[2]; } ActiveEntry;
typedef struct SecondEntry { u8 pad0[6]; u8 x; u8 y; u8 pad8[10]; u16 value; u8 pad14[4]; } SecondEntry;
extern ActiveEntry floor_objects[32];
extern SecondEntry dungeon_floor_object_positions[32];
extern u8 tile_effect_quad_source[];
extern s32 draw_linked_sprites_clipped(u8 *first_data, struct ObjectPosition *position, SpriteFrameState *value_record);
#endif
