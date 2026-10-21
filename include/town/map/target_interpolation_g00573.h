#ifndef TOWN_MAP_TARGET_INTERPOLATION_G00573_H
#define TOWN_MAP_TARGET_INTERPOLATION_G00573_H
/* Target interpolation shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A7198, CL:town/func_800A7434, CL:town/func_800A74B0, CL:town/func_800A7588. */

#include "common.h"

typedef struct {
    s32 *unk00;
    s32 *unk04;
    s32 unk08;
    s32 unk0C;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    void (*unk28)(void);
} UnkStruct_800A7434;

typedef struct S_800A4C10_0 {
    void * unk_00;
    void * unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    u8 pad_24[0x4];
    s32 * unk_28;
} S_800A4C10_0;

/* arg0 in restart_or_advance_target_interpolation */
typedef struct S_800A4C10_1 {
    s32 unk_00;
} S_800A4C10_1;

typedef struct S_800A4C10_2 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_800A4C10_2;

/* Functions defined in this translation unit. */
void reset_or_copy_state_values(UnkStruct_800A7434 *state);
void restart_or_advance_target_interpolation(S_800A4C10_0 *state);

#endif
