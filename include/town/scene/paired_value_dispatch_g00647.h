#ifndef TOWN_SCENE_PAIRED_VALUE_DISPATCH_G00647_H
#define TOWN_SCENE_PAIRED_VALUE_DISPATCH_G00647_H
/* Paired value dispatch shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800C3620, PD:town/engine:800D25C0. */

#include "common.h"
#include "shared/object_node.h"
#include "m2c_compat.h"

typedef struct S_800C0C48_0 {
    u8 pad_00[0x10];
    void (*unk_10)();
} S_800C0C48_0;

/* extern */

extern s16 paired_scene_flag_ids[66];
extern s16 scene_resident_flag_ids[66];

void clear_resident_bitmap_bit(s32 flag_id);

/* Functions defined in this translation unit. */
s32 clear_paired_flags_and_install_handler(s32 context, s32 value, s32 options);
void clear_paired_resident_flags(void);

#endif
