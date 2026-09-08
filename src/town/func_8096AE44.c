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

void func_801232DC(void)
{
    s32 var_s0;
    TownInitialPosition *var_a0;
    s8 *var_t0;
    s8 *var_a2_data;
    s16 temp_a0_2;
    s32 temp_a0;
    s32 temp_a0_3;
    s32 temp_a1;
    s32 temp_v1_2;
    s32 object_offset;
    register s32 var_a3 ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s32 var_a3_2;
    register s32 var_a3_3 ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s32 var_a3_4;
    s32 final_width;
    register s32 final_x ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u16 temp_v1;
    S_801232DC_1 *object;
    void **var_a0_2;
    void **var_a1;
    void **var_a1_2;
    void **var_a2;

    var_s0 = 0x1C;
    func_80123238();
    var_a3 = 0;
    {
        void **object_base;
        object_base = D_80129728;
        var_a1 = &object_base[0x1C];
    }
    var_a0 = D_80126AF8;
    do {
        ((S_801232DC_0 *)(*var_a1))->unk_00 = var_a0->data;
        object = *var_a1;
        var_a3 += 1;
        ((S_801232DC_6 *)(object->unk_04))->unk_08.s = var_a0->x;
        var_s0 += 1;
        object = *var_a1;
        temp_v1 = var_a0->y;
        var_a0 += 1;
        ((S_801232DC_6 *)(object->unk_04))->unk_0A = temp_v1;
        var_a1 += 1;
    } while (var_a3 < 5);

    var_a3_2 = 0;
    var_t0 = D_801331D0;
    {
        void **object_base;
        object_base = D_80129728;
        ASM_KEEP(object_base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        object_offset = var_s0 << 2;
        var_a2 = (void **)(object_offset + (u32)object_base);
    }
    do {
        object = *var_a2;
        temp_a1 = var_a3_2 >> 3;
        object->unk_00 = var_t0;
        object = *var_a2;
        temp_a1 <<= 7;
        ((S_801232DC_6 *)(object->unk_04))->unk_08.u = temp_a1 + 0x38;
        temp_a0 = (var_a3_2 & 7) * 0x12;
        ((S_801232DC_7 *)(((S_801232DC_2 *)(*var_a2))->unk_04))->unk_0A = temp_a0 + 0x2C;
        var_a2 += 1;
        ((S_801232DC_7 *)(((S_801232DC_2 *)(*var_a2))->unk_04))->unk_08 = temp_a1 + 0x3E;
        var_s0 += 3;
        object = *var_a2;
        temp_a0_2 = temp_a0 + 0x30;
        object = object->unk_04;
        var_a2 += 1;
        object->unk_08.at02.v = temp_a0_2;
        var_t0 += 0xC;
        ((S_801232DC_7 *)(((S_801232DC_2 *)(*var_a2))->unk_04))->unk_08 = temp_a1 + 0x44;
        var_a3_2 += 1;
        ((S_801232DC_7 *)(((S_801232DC_2 *)(*var_a2))->unk_04))->unk_0A = temp_a0_2;
        var_a2 += 1;
    } while (var_a3_2 < 0x10);

    var_a3_3 = 0;
    {
        void **object_base;
        object_base = D_80129728;
        ASM_KEEP(object_base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        object_offset = var_s0 << 2;
        var_a1_2 = (void **)(object_offset + (u32)object_base);
    }
    var_a2_data = D_801331D0;
    do {
        temp_v1_2 = var_a3_3 >> 3;
        temp_a0_3 = var_a3_3 & 7;
        var_a3_3 += 1;
        ((S_801232DC_3 *)(*var_a1_2))->unk_00 = var_a2_data;
        var_a2_data += 0xC;
        ((S_801232DC_8 *)(((S_801232DC_3 *)(*var_a1_2))->unk_04))->unk_08 = (temp_v1_2 << 7) + 0x54;
        ((S_801232DC_8 *)(((S_801232DC_3 *)(*var_a1_2))->unk_04))->unk_0A = temp_a0_3 * 0x12 + 0x30;
        var_a1_2 += 1;
    } while (var_a3_3 < 0x10);

    var_a3_4 = 0;
    final_width = 0x10;
    final_x = 0xE0;
    {
        void **object_base;
        object_base = D_80129728;
        var_a0_2 = &object_base[0x1C];
        ((S_801232DC_4 *)(object_base[0x61]))->unk_00 = D_80128614;
    }
    do {
        ((S_801232DC_9 *)(((S_801232DC_5 *)(*var_a0_2))->unk_08))->unk_06 = final_width;
        ASM_KEEP(final_width);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        object = *var_a0_2;
        var_a3_4 += 1;
        ((S_801232DC_10 *)(object->unk_08.at00.v))->unk_08 = final_x;
        var_a0_2 += 1;
    } while (var_a3_4 < 0x46);
}

/* MECHANISM: The 24-byte frame keeps only s0, with loop counters/data roles pinned at their ABI seams.
   Block-local v0 bases plus split scaled-index names reproduce each hi/lo and pointer-add order.
   One-use object reloads, ASM_KEEP seams, and held s0 liveness reproduce the retail loop schedules. */
