#ifndef TOWN_PLAYER_FALLBACK_HANDLER_POSITION_G00541_H
#define TOWN_PLAYER_FALLBACK_HANDLER_POSITION_G00541_H
/* G00541: shared declarations for fallback handler position. */
/* Original-file evidence (G00541): inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800991C4, CL:town/func_800992D0, CL:town/func_800992FC. */

#include "common.h"
#include "shared/vector.h"

typedef struct {
    s32 unk0;
    s32 unk4;
} Unk99108;

typedef struct Record {
    u8 flags;
    u8 pad1;
    s8 scale;
    s8 height;
} Record;

extern s32 town_position_callback_address[3];
extern s32 D_800D04A4[];
extern s32 D_800D04B8[];
extern Record *find_flagged_record_by_id(void *entry, u32 target_id);
extern s32 rcos(s32 angle);
extern s32 rsin(s32 angle);
extern IntVector3 D_800D0AE4;
extern IntVector3 computed_position;

extern IntVector3 *town_overlap_origin;

/* Functions defined in this translation unit. */
void dispatch_to_matching_fallback_handler_using_sentinel_terminated_key_lists(Unk99108 *entry, s32 forwarded_a, s32 forwarded_b, s32 *match_cursor);
void clear_global_80100_d_20(void);
void compute_the_based_position_offset_publishes_resulting_vector(void *object, IntVector3 *offset, void *resources);
s32 call_an_indexed_byte_s_signed_field_callee_80096_a_5_c(void *object, u8 *values, s32 index);
s32 get_second_word_indexed_entry_in_s_nested_table(void *record, s32 row_index, s32 entry_index, s32 unused);

#endif
