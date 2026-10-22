#ifndef TOWN_SCENE_BUILD_SELECTED_ENTRY_OUTPUT_G01237_H
#define TOWN_SCENE_BUILD_SELECTED_ENTRY_OUTPUT_G01237_H
/* Build selected entry output. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01237 - PR:town/ll34_3e5000_80016000:80017ADC, PR:town/ll34_3e5000_80016000:80017AE8, PR:town/ll34_3e5000_80016000:80017AF4, PR:town/ll34_3e5000_80016000:80017B00, PR:town/ll34_3e5000_80016000:80017B0C, PR:town/ll34_3e5000_80016000:80017B18. */

#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001A86C_0 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_8001A86C_0;

typedef struct {
    u8 pad0[4];
    s16 field4;
    u8 pad6[2];
    s32 field8;
} Record12;

extern void dispatch_records_by_kind(void *, void *);
extern s32 func_8001E670(s32);
extern u8 D_80017ADC;
extern u8 D_80017AE8;
extern u8 D_80017AF4;
extern u8 D_80017B00;
extern u8 D_80017B0C;
extern u8 D_80017B18;
extern u8 D_80017D50;
extern u8 D_80017AD0;
extern u8 D_80017E54[];
extern M2C_UNK D_80017B24;
extern u8 D_80017EA4;
extern u8 D_80017F08;
extern u8 D_80017F44;

/* Shared import declarations; data casts preserve each measured view. */
extern void copy_callback_value_to_destination(void *, void *);
extern u8 town_selection_records[];

/* Functions defined in this translation unit. */
u8 *build_selected_entry_output(s32 selected_index);
void *build_entry_list(s32 entry_index);
void *build_selected_record_buffer(s32 entry_index);
s32 *build_four_record_value_block(void);
s32 *build_two_record_value_block(void);
s32 *build_three_record_value_block(void);

#endif
