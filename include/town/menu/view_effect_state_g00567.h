#ifndef TOWN_MENU_VIEW_EFFECT_STATE_G00567_H
#define TOWN_MENU_VIEW_EFFECT_STATE_G00567_H
/* inferred-strong G00567: view_effect_state_g00567; shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A4E6C. */

#include "common.h"
#include "shared/game_work.h"
#include "shared/object_node.h"

typedef struct {
    u8 pad0[0xBC];
    u16 field_BC;
    u16 field_BE;
    u8 pad_C0[8];
    s16 field_C8;
} GlobalState;

typedef struct {
    s16 field_0;
    s16 field_2;
    u16 field_4;
    u16 field_6;
    s32 field_8;
    s16 field_C;
} State;

typedef struct S_800A25CC_0 {
    u8 pad_00[0x10];
    void * unk_10;
} S_800A25CC_0;

typedef struct S_800A25CC_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    u8 pad_0E[0x2];
    s32 unk_10;
    s32 unk_14;
} S_800A25CC_1;

extern s32 func_80064584(s32);
extern s16 func_80065F90(s32, s32);
extern s32 scale_random_to_unsigned_halfword_limit(u32);
extern u8 D_800A2690[9];

/* Functions defined in this translation unit. */
void update_view_driven_state(State *state);
void *allocate_randomized_effect_object(s32 state_value);

#endif
