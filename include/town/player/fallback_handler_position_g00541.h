#ifndef TOWN_PLAYER_FALLBACK_HANDLER_POSITION_G00541_H
#define TOWN_PLAYER_FALLBACK_HANDLER_POSITION_G00541_H

#include "town/player/record.h"
/* shared declarations for fallback handler position. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800991C4, CL:town/func_800992D0, CL:town/func_800992FC. */

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
struct SpriteFrameState;
#include "shared/vector.h"
#include "sdk/libgte.h"


typedef struct Record {
    u8 flags;
    u8 pad1;
    s8 scale;
    s8 height;
} Record;

extern s32 town_position_callback_address[3];
extern void *D_800D04A4[];
extern void *D_800D04B8[];
extern IntVector3 town_fallback_origin;

/* The published box at 0x800D0AFC has three coordinates followed by
 * three extents, initialized to 0x400000 on each axis. */
typedef struct S_800A2A18_1 {
    s32 x, y, z;
    s32 extent_x, extent_y, extent_z;
} TownOverlapBox;

extern TownOverlapBox computed_position;
extern TownOverlapBox *town_overlap_origin;

/* Functions defined in this translation unit. */
void dispatch_fallback_position(TownPlayerRecord *entry, ObjectPosition *forwarded_a, SpriteFrameState *sprite);
void clear_town_overlap_origin(void);
void compute_fallback_position_offset(TownPlayerRecord *object, ObjectPosition *offset, SpriteFrameState *sprite);
void *lookup_entry_by_byte_index(struct SpriteFrameState *object, u8 *values, s32 index);
void *get_nested_table_entry_data(SpriteFrameState *record, s32 row_index, s32 entry_index, s32 unused);

#endif
