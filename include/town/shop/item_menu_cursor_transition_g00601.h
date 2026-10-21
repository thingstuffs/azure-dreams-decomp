#ifndef TOWN_SHOP_ITEM_MENU_CURSOR_TRANSITION_G00601_H
#define TOWN_SHOP_ITEM_MENU_CURSOR_TRANSITION_G00601_H
/* Item menu cursor transition declarations (G00601). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B0FD4, CL:town/func_800B10F4. */

#include "common.h"
#include "m2c_compat.h"

#define F(e, t, o) (*(t *)((s8 *)(e) + (o)))

typedef struct S_800AE734_1 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x14];
    void * unk_20;
    u8 pad_24[0x14];
    void * unk_38;
    u8 pad_3C[0x14];
    void * unk_50;
} S_800AE734_1;

typedef struct S_800AE734_2 {
    u8 pad_00[0x4];
    union { void * s; s8 * u; } unk_04;   /* accessed as both */
} S_800AE734_2;

typedef struct S_800AE734_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800AE734_3;

typedef struct S_800AE734_4 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800AE734_4;

typedef struct S_800AE734_5 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800AE734_5;

typedef struct S_800AE734_6 {
    u8 pad_00[0x1];
    s8 unk_01;
    s8 unk_02;
    u8 pad_03[0x5];
    s16 unk_08;
} S_800AE734_6;

typedef struct S_800AE734_7 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_800AE734_7;

typedef struct S_800AE734_8 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_800AE734_8;

typedef struct S_800AE734_9 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_800AE734_9;

typedef struct S_800AE734_0 {
    u8 pad_00[0x28];
    s32 unk_28;
    u8 pad_2C[0xAC];
    s32 unk_D8;
} S_800AE734_0;

/* Functions defined in this translation unit. */
void style_item_menu_entry_records(S_800AE734_0 *collection);
void animate_item_menu_cursor_transition(void *state);

#endif
