#ifndef DUNGEON_OVL_EE706C_H
#define DUNGEON_OVL_EE706C_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef struct S_8015E86C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8015E86C_0;   /* obj in func_8015E86C */

typedef struct S_8015E86C_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8015E86C_1;   /* work in func_8015E86C */

typedef struct S_8015E86C_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8015E86C_2;   /* part_a in func_8015E86C */

typedef struct S_8015E86C_3 {
    u8 pad_00[0x12];
    s16 unk_12;
    u8 pad_14[0x10];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x2];
    s32 unk_28;
    void * unk_2C;
} S_8015E86C_3;   /* part_b in func_8015E86C */

typedef struct S_8015E86C_4 {
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
    u16 unk_A8;
} S_8015E86C_4;   /* actor in func_8015E86C */

typedef struct S_8015E86C_5 {
    u8 pad_00[0xA4];
    void * unk_A4;
} S_8015E86C_5;   /* current in func_8015E86C */

typedef struct S_8015E86C_6 {
    u8 pad_00[0x2];
    s16 unk_02;
    u16 unk_04;
    u16 unk_06;
    u8 pad_08[0x90];
    u32 unk_98;
} S_8015E86C_6;   /* child in func_8015E86C */

typedef struct S_8015E86C_7 {
    u8 pad_00[0xC];
    u32 unk_0C;
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x12];
    u32 unk_28;
} S_8015E86C_7;   /* elem in func_8015E86C */

typedef struct S_8015E86C_8 {
    u8 pad_00[0xA4];
    void * unk_A4;
} S_8015E86C_8;   /* base in func_8015E86C */

typedef struct S_8015E86C_9 {
    u8 pad_00[0x10];
    void * unk_10;
} S_8015E86C_9;   /* ((S_8015E86C_8 *)base)->unk_A4 in func_8015E86C */


extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_800A6D30();
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_80047784();
extern void textureSetTheActiveEntriesMatchingIDInTypeN2TableSlots();
extern void func_800AA36C();

extern void dungeonProcessEffectBlockEntries();
extern void func_8015EB64();
extern void func_8015F1A4();
extern u8 D_8016218C[];
extern u8 D_801621CC[];

void * dungeonCreateActorChildDisplayC(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c);
extern void * dungeonDrawSpriteEffectQuads();
#endif
