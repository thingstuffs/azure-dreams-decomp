/* Complete resident-engine cohort contract; review pending. */
#ifndef DUNGEON_ENGINE_ENTITY_EFFECTS_H
#define DUNGEON_ENGINE_ENTITY_EFFECTS_H
#include "common.h"
#include "sdk/libgte_matrix.h"
#include "sdk/libgpu_packets.h"
#include "shared/gpu_packets.h"
#include "m2c_compat.h"
#include "shared/dir_step.h"
#include "shared/dungeon_item_entries.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/tile_object.h"
#include "modules/dungeon_engine_entity_effects_fragment_c2fbc.h"
#include "modules/dungeon_engine_entity_effects_abi_views.h"
#include "modules/dungeon_engine_entity_effects_storage.h"

/* Twelve-byte command-source entries advanced by the floor-item renderer. */
typedef struct FloorItemSprite {
    union { u8 u; s8 s; } flags;
    u8 pad_01;
    u8 offset_x, offset_y;
    s16 tpage;
    u16 clut;
    u8 u, v, width, height;
} FloorItemSprite;
typedef struct FloorItemPosition {
    u8 tile_x, tile_y;
    u16 height, ground_height;
    u8 pad_06[2];
    FloorItemSprite *sprite;
} FloorItemPosition;
extern s8 random_pickup_enabled;
extern s16 pickup_event_latch;
#endif
