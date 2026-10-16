#ifndef DUNGEON_OVL_C4709C_H
#define DUNGEON_OVL_C4709C_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef unsigned long uptr;

typedef struct S_8015E89C_0 {
    u8 pad_00[0x10];
    void * unk_10;
} S_8015E89C_0;   /* init_root in func_8015E89C */

typedef struct S_8015E89C_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} S_8015E89C_1;   /* object in func_8015E89C */

typedef struct S_8015E89C_2 {
    u8 pad_00[0x8];
    union { struct { void * v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    void * unk_0C;
} S_8015E89C_2;   /* (void *)temp_t0 in func_8015E89C */

typedef struct S_8015E89C_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x2];
    s32 unk_28;
    void * unk_2C;
} S_8015E89C_3;   /* part in func_8015E89C */

typedef struct S_8015E89C_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x4];
    u16 unk_98;
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x1];
    s16 unk_9E;
    u8 pad_A0[0x8];
    s16 unk_A8;
} S_8015E89C_4;   /* stable_object in func_8015E89C */

typedef struct S_8015E89C_5 {
    u8 pad_00[0xA4];
    void * unk_A4;
} S_8015E89C_5;   /* outer in func_8015E89C */

typedef struct S_8015E89C_6 {
    u8 pad_00[0x2];
    s16 unk_02;
    u16 unk_04;
    s16 unk_06;
    u8 pad_08[0x90];
    void * unk_98;
} S_8015E89C_6;   /* entry in func_8015E89C */

typedef struct S_8015E89C_7 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x16];
    s32 unk_28;
} S_8015E89C_7;   /* item in func_8015E89C */

typedef struct S_8015E89C_8 {
    u8 pad_00[0xA4];
    void * unk_A4;
} S_8015E89C_8;   /* outer_base in func_8015E89C */

typedef struct S_8015E89C_9 {
    u8 pad_00[0x10];
    void * unk_10;
} S_8015E89C_9;   /* outer_child in func_8015E89C */


extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800A6D30();
extern void func_800A48F0(void *, s32, s32);
extern void func_800A9C18(void *, void *, void *, s16);
extern void func_800AA36C(void *, void *, void *, void *);
extern void func_80047784(void *, s32, s32);
extern void func_800478E8(void *, void *, s32);

extern s16 D_80083228;
extern u8 D_800D71A8[];
extern u8 D_800D78C0[];
extern u8 D_8015EBB8[];
extern u8 D_8015F3A8[];
extern u8 D_80162494[];
extern u8 D_801624FC[];

/* Allocates and initializes an object and its child display items. */

void *func_8015E89C(s32 kind, s32 part_x, s32 part_y, s32 initial_value);
#endif
