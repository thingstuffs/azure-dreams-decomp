/* Complete resident-engine cohort contract; review pending. */
#ifndef DUNGEON_ENGINE_ENTITY_EFFECTS_H
#define DUNGEON_ENGINE_ENTITY_EFFECTS_H
#include "common.h"
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

/* render_floor_items uses one scratchpad workspace. RotTransPers4 consumes the
 * four 8-byte local vertices and writes four packed screen-coordinate pairs;
 * the two matrices and their translations are built by RotMatrix/CompMatrix. */
typedef union FloorItemHalf { u16 u; s16 s; } FloorItemHalf;
typedef struct FloorItemVertex { FloorItemHalf x, y, z; u16 pad; } FloorItemVertex;
typedef struct FloorItemMatrix { u16 m[3][3]; u16 pad; u32 t[3]; } FloorItemMatrix;
typedef struct FloorItemScreen { u16 x, y; } FloorItemScreen;
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
/* POLY_FT4 access widths used while clipping and adjusting texture seams. */
typedef union FloorItemUV {
    s32 word;
    s16 pair;
    struct { u8 u, v; s16 attr; } bytes;
} FloorItemUV;
typedef struct FloorItemQuad {
    s32 tag;
    union { s32 word; struct { u8 r, g, b, code; } bytes; } color;
    struct { FloorItemHalf x, y; FloorItemUV uv; } vertex[4];
} FloorItemQuad;
typedef struct FloorItemScratch {
    /* 0x000 */ u16 world_x, world_y, world_z;
    u8 pad_006[2];
    /* 0x008 */ union { u32 word; u16 low; } tex_u, tex_v, tex_width, tex_height;
    u8 pad_018[8];
    /* 0x020 */ u32 ordering_table;
    u8 pad_024[0x2C];
    /* 0x050 */ FloorItemMatrix transform;
    /* 0x070 */ FloorItemVertex vertices[4];
    /* 0x090 */ u32 depth;
    /* 0x094 */ u32 flags;
    u8 pad_098[0x20];
    /* 0x0B8 */ u16 origin_x, origin_y;
    u8 pad_0BC[4];
    /* 0x0C0 */ u32 sort_depth;
    u8 pad_0C4[0xC];
    /* 0x0D0 */ FloorItemMatrix rotation;
    /* 0x0F0 */ FloorItemScreen screen[4];
    /* 0x100 */ u16 angle_x, angle_y, angle_z;
} FloorItemScratch;

#endif
