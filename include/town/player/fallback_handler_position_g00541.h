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
extern IntVector3 computed_position;

extern IntVector3 *town_overlap_origin;

/* Functions defined in this translation unit. */
void dispatch_fallback_position(TownPlayerRecord *entry, ObjectPosition *forwarded_a, void *forwarded_b);
void clear_town_overlap_origin(void);
void compute_fallback_position_offset(TownPlayerRecord *object, ObjectPosition *offset, void *resources);
void *lookup_entry_by_byte_index(struct SpriteFrameState *object, u8 *values, s32 index);
void *get_nested_table_entry_data(SpriteFrameState *record, s32 row_index, s32 entry_index, s32 unused);

#endif
