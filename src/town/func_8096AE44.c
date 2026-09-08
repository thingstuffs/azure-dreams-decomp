#include "common.h"

typedef struct S_801232DC_0 {
    void * unk_00;
} S_801232DC_0;   /* *var_a1 in func_801232DC */

typedef struct S_801232DC_1 {
    void * unk_00;
    void * unk_04;
    union { struct { void * v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
} S_801232DC_1;   /* object in func_801232DC */

typedef struct S_801232DC_2 {
    u8 pad_00[0x4];
    void * unk_04;
} S_801232DC_2;   /* *var_a2 in func_801232DC */

typedef struct S_801232DC_3 {
    void * unk_00;
    void * unk_04;
} S_801232DC_3;   /* *var_a1_2 in func_801232DC */

typedef struct S_801232DC_4 {
    void * unk_00;
} S_801232DC_4;   /* object_base[0x61] in func_801232DC */

typedef struct S_801232DC_5 {
    u8 pad_00[0x8];
    void * unk_08;
} S_801232DC_5;   /* *var_a0_2 in func_801232DC */

typedef struct S_801232DC_6 {
    u8 pad_00[0x8];
    union { u16 s; s16 u; } unk_08;   /* accessed as both */
    u16 unk_0A;
} S_801232DC_6;   /* ((S_801232DC_1 *)object)->unk_04 in func_801232DC */

typedef struct S_801232DC_7 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_801232DC_7;   /* ((S_801232DC_2 *)(*var_a2))->unk_04 in func_801232DC */

typedef struct S_801232DC_8 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_801232DC_8;   /* ((S_801232DC_3 *)(*var_a1_2))->unk_04 in func_801232DC */

typedef struct S_801232DC_9 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_801232DC_9;   /* ((S_801232DC_5 *)(*var_a0_2))->unk_08 in func_801232DC */

typedef struct S_801232DC_10 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_801232DC_10;   /* ((S_801232DC_1 *)object)->unk_08.at00.v in func_801232DC */



typedef struct TownInitialPosition {
    void *data;
    volatile u16 x;
    volatile u16 y;
} TownInitialPosition;

extern void func_80123238(void);
extern TownInitialPosition D_80126AF8[5];
extern s8 D_80128614[];
extern void *D_80129728[];
extern s8 D_801331D0[];

/* Initialize town object data, grid positions, and display dimensions. */
void func_801232DC(void)
{
    s32 object_index;
    TownInitialPosition *initial_pos;
    s8 *group_data;
    s8 *entry_data;
    s16 detail_y;
    s32 row_offset;
    s32 row;
    s32 column_offset;
    s32 column;
    s32 object_offset;
    register s32 initial_index ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s32 group_index;
    register s32 entry_index ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s32 display_index;
    s32 final_width;
    register s32 final_x ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u16 initial_y;
    S_801232DC_1 *object;
    void **display_slot;
    void **initial_slot;
    void **entry_slot;
    void **group_slot;

    object_index = 0x1C;
    func_80123238();
    initial_index = 0;
    {
        void **object_base;
        object_base = D_80129728;
        initial_slot = &object_base[0x1C];
    }
    initial_pos = D_80126AF8;
    do {
        ((S_801232DC_0 *)(*initial_slot))->unk_00 = initial_pos->data;
        object = *initial_slot;
        initial_index += 1;
        ((S_801232DC_6 *)(object->unk_04))->unk_08.s = initial_pos->x;
        object_index += 1;
        object = *initial_slot;
        initial_y = initial_pos->y;
        initial_pos += 1;
        ((S_801232DC_6 *)(object->unk_04))->unk_0A = initial_y;
        initial_slot += 1;
    } while (initial_index < 5);

    group_index = 0;
    group_data = D_801331D0;
    {
        void **object_base;
        object_base = D_80129728;
        ASM_KEEP(object_base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        object_offset = object_index << 2;
        group_slot = (void **)(object_offset + (u32)object_base);
    }
    do {
        object = *group_slot;
        column_offset = group_index >> 3;
        object->unk_00 = group_data;
        object = *group_slot;
        column_offset <<= 7;
        ((S_801232DC_6 *)(object->unk_04))->unk_08.u = column_offset + 0x38;
        row_offset = (group_index & 7) * 0x12;
        ((S_801232DC_7 *)(((S_801232DC_2 *)(*group_slot))->unk_04))->unk_0A = row_offset + 0x2C;
        group_slot += 1;
        ((S_801232DC_7 *)(((S_801232DC_2 *)(*group_slot))->unk_04))->unk_08 = column_offset + 0x3E;
        object_index += 3;
        object = *group_slot;
        detail_y = row_offset + 0x30;
        object = object->unk_04;
        group_slot += 1;
        object->unk_08.at02.v = detail_y;
        group_data += 0xC;
        ((S_801232DC_7 *)(((S_801232DC_2 *)(*group_slot))->unk_04))->unk_08 = column_offset + 0x44;
        group_index += 1;
        ((S_801232DC_7 *)(((S_801232DC_2 *)(*group_slot))->unk_04))->unk_0A = detail_y;
        group_slot += 1;
    } while (group_index < 0x10);

    entry_index = 0;
    {
        void **object_base;
        object_base = D_80129728;
        ASM_KEEP(object_base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        object_offset = object_index << 2;
        entry_slot = (void **)(object_offset + (u32)object_base);
    }
    entry_data = D_801331D0;
    do {
        column = entry_index >> 3;
        row = entry_index & 7;
        entry_index += 1;
        ((S_801232DC_3 *)(*entry_slot))->unk_00 = entry_data;
        entry_data += 0xC;
        ((S_801232DC_8 *)(((S_801232DC_3 *)(*entry_slot))->unk_04))->unk_08 = (column << 7) + 0x54;
        ((S_801232DC_8 *)(((S_801232DC_3 *)(*entry_slot))->unk_04))->unk_0A = row * 0x12 + 0x30;
        entry_slot += 1;
    } while (entry_index < 0x10);

    display_index = 0;
    final_width = 0x10;
    final_x = 0xE0;
    {
        void **object_base;
        object_base = D_80129728;
        display_slot = &object_base[0x1C];
        ((S_801232DC_4 *)(object_base[0x61]))->unk_00 = D_80128614;
    }
    do {
        ((S_801232DC_9 *)(((S_801232DC_5 *)(*display_slot))->unk_08))->unk_06 = final_width;
        ASM_KEEP(final_width);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        object = *display_slot;
        display_index += 1;
        ((S_801232DC_10 *)(object->unk_08.at00.v))->unk_08 = final_x;
        display_slot += 1;
    } while (display_index < 0x46);
}

/* MECHANISM: The 24-byte frame keeps only s0, with loop counters/data roles pinned at their ABI seams.
   Block-local v0 bases plus split scaled-index names reproduce each hi/lo and pointer-add order.
   One-use object reloads, ASM_KEEP seams, and held s0 liveness reproduce the retail loop schedules. */
