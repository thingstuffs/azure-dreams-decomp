#ifndef TOWN_MENU_INDEXED_OBJECT_STATE_G00569_H
#define TOWN_MENU_INDEXED_OBJECT_STATE_G00569_H
/* inferred-strong G00569: indexed_object_state_g00569; shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A5CF0. */

#include "common.h"
#include "shared/object_node.h"
#include "shared/dungeon_effect_views.h"
#include "shared/object_payload.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} Unk800A5C88;

typedef struct S_800A3450_3 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
    u8 pad_24[0x1E];
    s16 unk_42;
} S_800A3450_3;

extern void *allocate_list_node(s32, void *);
extern u8 D_800A34E0[];
extern u8 D_800A3508[];

/* Functions defined in this translation unit. */
void check_adjusted_input_indices(Unk800A5C88 *input);
void *allocate_object_with_initial_state(EffectInitialState *source_data, s32 initial_value);

#endif
