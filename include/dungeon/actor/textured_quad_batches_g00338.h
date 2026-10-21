#ifndef DUNGEON_ACTOR_TEXTURED_QUAD_BATCHES_G00338_H
#define DUNGEON_ACTOR_TEXTURED_QUAD_BATCHES_G00338_H
/* Textured quad batches shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800AB480. */

#include "common.h"

typedef struct S_800B06F0_0 {
    u8 pad_00[0x20];
    u8 * unk_20;
    u8 pad_24[0xC];
    u32 unk_30;
    u32 unk_34;
    u32 unk_38;
    u8 pad_3C[0x34];
    s16 unk_70;
    s16 unk_72;
    u16 unk_74;
    u8 pad_76[0x4];
    s16 unk_7A;
    u16 unk_7C;
    u8 pad_7E[0x2];
    s16 unk_80;
    s16 unk_82;
    u16 unk_84;
    u8 pad_86[0x4];
    s16 unk_8A;
    u16 unk_8C;
    u8 pad_8E[0x2A];
    u16 unk_B8;
    u16 unk_BA;
    u8 pad_BC[0x4];
    union { u32 i; u8 * p; } unk_C0;   /* accessed as both */
    u8 pad_C4[0x20];
    u32 unk_E4;
    u32 unk_E8;
    u32 unk_EC;
    union {
        struct { u32 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x2]; u16 v; } at02;
    } unk_F0;   /* overlapping accesses */
    union {
        struct { u32 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x2]; u16 v; } at02;
    } unk_F4;   /* overlapping accesses */
    union {
        struct { u32 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x2]; u16 v; } at02;
    } unk_F8;   /* overlapping accesses */
    u16 unk_FC;
    u16 unk_FE;
    u16 unk_100;
    u16 unk_102;
    u16 unk_104;
} S_800B06F0_0;

/* scratch in transform_linked_quad_batches */
typedef struct S_800B06F0_1 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800B06F0_1;

/* initial_manager in transform_linked_quad_batches */
typedef struct S_800B06F0_2_pre {
    u8 * unk_00;
    u8 pad_04[0x4];
} S_800B06F0_2_pre;

/* the 0x8 bytes before arg0_r in transform_linked_quad_batches, addressed as arg0_r[-1] */
typedef struct S_800B06F0_2 {
    u8 ** unk_00;
    u8 * unk_04;
    u16 unk_08;
} S_800B06F0_2;

/* arg0_r in transform_linked_quad_batches */
typedef struct S_800B06F0_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
    u16 unk_22;
} S_800B06F0_3;

/* arg2_r in transform_linked_quad_batches */
typedef struct S_800B06F0_4 {
    s8 unk_00;
} S_800B06F0_4;

/* current in transform_linked_quad_batches */
typedef struct S_800B06F0_5 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
    u8 pad_0C[0x4];
    s16 unk_10;
    s16 unk_12;
    u8 pad_14[0x4];
    s16 unk_18;
    s16 unk_1A;
    u8 pad_1C[0x4];
    s16 unk_20;
    s16 unk_22;
} S_800B06F0_5;

/* object in transform_linked_quad_batches */
typedef struct S_800B06F0_6 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 * unk_0C;
} S_800B06F0_6;

/* next_manager in transform_linked_quad_batches */
typedef struct S_800B06F0_7 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800B06F0_7;

/* manager in transform_linked_quad_batches */
typedef struct {
    u8 *manager;
    u8 pad[0x9C];
    u32 value;
} GlobalSlot;

typedef struct { u32 entry; } OtSlot;

/* extern */
typedef struct S_800B0BE0_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u16 unk_0E;
    u8 pad_10[0x4];
    s8 unk_14;
    u8 unk_15;
    u16 unk_16;
    u8 pad_18[0x4];
    u8 unk_1C;
    s8 unk_1D;
    u8 pad_1E[0x6];
    s8 unk_24;
    s8 unk_25;
} S_800B0BE0_0;

/* arg3 in submit_textured_quad */
typedef struct S_800B0BE0_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u16 unk_10;
} S_800B0BE0_1;

/* arg1 in submit_textured_quad */
typedef struct S_800B0BE0_2 {
    u8 pad_00[0x4];
    u16 unk_04;
    u16 unk_06;
    u8 unk_08;
    u8 unk_09;
} S_800B0BE0_2;

/* *arg2 in submit_textured_quad */
typedef struct S_800B0BE0_3 {
    u8 pad_00[0x8];
    u8 unk_08;
    u8 pad_09[0x1];
    u8 unk_0A;
} S_800B0BE0_3;

typedef struct S_800B0BE0_4 {
    u8 pad_00[0x9];
    u8 unk_09;
    u8 pad_0A[0x1];
    u8 unk_0B;
} S_800B0BE0_4;

typedef struct S_800B0BE0_5 {
    s8 unk_00;
} S_800B0BE0_5;

extern GlobalSlot D_80083160[];
extern s32 swap_int_values();
extern s32 multiply_rgb_tint_saturated();
extern void *emit_gpu_packets();
extern s32 func_800649A0();
extern s32 func_80064A40();
extern s32 func_80064BC0();
extern s32 func_80064CF0();
extern s32 func_80064D80();
extern s32 func_80065480();
extern s32 func_800654B0();
extern s32 func_80065820();
s32 func_8006658C(void *, void *);
/* extern */
s32 func_800666F4(void *);

extern s32 (*D_800DEFF0[])(s32, void *, void *);

/* Functions defined in this translation unit. */
s32 transform_linked_quad_batches(u8 *initial_batch, s32 initial_dispatch_arg, u8 *initial_params);
void *submit_textured_quad(s32 draw_context, S_800B0BE0_1 *draw_settings, void **texture_cursor, void *primitive);

#endif
