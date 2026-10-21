#ifndef TOWN_MENU_PRIMITIVE_SCALE_EFFECT_G00581_H
#define TOWN_MENU_PRIMITIVE_SCALE_EFFECT_G00581_H
/* inferred-strong G00581: primitive_scale_effect_g00581; shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AA1AC, CL:town/func_800AA268. */

#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A7950_0 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_800A7950_0;

/* arg2 in update_scale_effect_and_advance */
typedef struct S_800A7950_1 {
    u8 pad_00[0x6C];
    s16 unk_6C;
    u8 pad_6E[0x22];
    s16 unk_90;
} S_800A7950_1;

extern u8 D_800A79F0[12];

/* Functions defined in this translation unit. */
void update_scale_effect_and_advance(S_800A7950_1 *state, void *context, S_800A7950_0 *scale);
void initialize_neutral_primitive(void *object, void *unused, void *primitive);

#endif
