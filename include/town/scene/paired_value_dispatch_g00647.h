#ifndef TOWN_SCENE_PAIRED_VALUE_DISPATCH_G00647_H
#define TOWN_SCENE_PAIRED_VALUE_DISPATCH_G00647_H
/* Paired value dispatch shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800C3620, PD:town/engine:800D25C0. */

#include "common.h"
#include "shared/object_node.h"
#include "m2c_compat.h"

typedef struct S_800C0C48_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
} S_800C0C48_0;

/* extern */
extern M2C_UNK D_800C0C28;
extern s16 D_800D253C[66];
extern s16 D_800D25C0[66];
void set_resident_bitmap_bit(s16 value);

void clear_resident_bitmap_bit(s32 flag_id);

/* Functions defined in this translation unit. */
s32 run_setup_and_get_object_handler(s32 context, s32 value, s32 options);
void dispatch_paired_table_values(void);
void process_paired_arrays_until_terminator(void);

#endif
