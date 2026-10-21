#ifndef TOWN_PLAYER_PENDING_RECORD_VALUES_G00577_H
#define TOWN_PLAYER_PENDING_RECORD_VALUES_G00577_H
/* Apply pending values to flagged player records (G00577). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A8BC8, CL:town/func_800A8C3C, CL:town/func_800A8C68, PD:town/engine:80100E2C. */

#include "common.h"
#include "m2c_compat.h"





typedef struct {
    u16 active;
    u16 pad;
    u32 data;
} TownRecord;

extern struct S_80082EA8 {
    s32 ***p;
    s32 pad[2];
} D_80082EA8;
/* extern */
extern s8 ***loaded_town_resource_attributes;

extern s32 D_80100E2C[3];

/* Functions defined in this translation unit. */
s32 lookup_signed_index_value(s32 index);
void set_flagged_record_values(TownRecord *record, s32 entryValue);
void apply_pending_indexed_value(s32 index, s32 value);
void apply_pending_table_entry(s32 index, s32 entryValue);

#endif
