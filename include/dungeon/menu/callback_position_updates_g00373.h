#ifndef DUNGEON_MENU_CALLBACK_POSITION_UPDATES_G00373_H
#define DUNGEON_MENU_CALLBACK_POSITION_UPDATES_G00373_H
/* Callback position updates shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800D6EF0, CL:dungeon/func_800D6FC4, CL:dungeon/func_800D70CC, PD:dungeon/engine:800E2934. */

#include "common.h"
#include "m2c_compat.h"

typedef void (*Func)(void *, s32);

typedef struct {
    u8 pad[0xC];
    s32 value;
} GlobalState;

typedef struct S_800DC724_0 {
    u8 pad_00[0x3C];
    void * unk_3C;
    u8 pad_40[0x10];
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
} S_800DC724_0;

/* arg0 in move_indexed_position_and_apply */
typedef struct S_800DC724_1 {
    u16 unk_00;
    u16 unk_02;
} S_800DC724_1;

typedef struct S_800DC724_2 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800DC724_2;

/* holder in move_indexed_position_and_apply */
typedef struct S_800DC724_3 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800DC724_3;

typedef struct S_800DC82C_0 {
    u8 pad_00[0x38];
    s32 * unk_38;
    u8 pad_3C[0x18];
    s32 unk_54;
    u8 pad_58[0x4];
    s32 unk_5C;
} S_800DC82C_0;

typedef struct S_800DC888_0 {
    u8 pad_00[0x38];
    s32 * unk_38;
} S_800DC888_0;

typedef void (*FinalFunc)(void *);

extern Func D_800E2934[];
extern void set_object_value_and_negation(void *, s32);
extern s32 link_indexed_entry_chain(void *, s32);
extern s32 SD_Call();
extern u8 D_800E2924[];

extern GlobalState *dungeon_menu_object;

/* Functions defined in this translation unit. */
void move_value_toward_target(u8 *object_data, s32 unused_coord, s32 unused_y);
void move_indexed_position_and_apply(S_800DC724_0 *state);
void update_state_activity_flags(S_800DC82C_0 *record);
void process_callback_slots_and_object(u8 *object);

#endif
