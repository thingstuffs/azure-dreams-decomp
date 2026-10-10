#ifndef DUNGEON_OVL_183A800_H
#define DUNGEON_OVL_183A800_H
#include "common.h"
#include "modules/dungeon_native_abi.h"
#include "m2c_compat.h"
#include "shared/entity.h"
typedef struct S_8181A800_0 {
    u16 unk_00;
    u8 pad_02[0x2];
    s16 unk_04;
} S_8181A800_0;
typedef struct {
    u8 pad0[2];
    s16 f2;
    s16 f4;
} D8181A8C0Header;
typedef struct {
    u8 pad0[2];
    s16 f2;
    u8 pad4[2];
    s16 f6;
    u8 pad8[2];
    s16 fa;
} D8181A8C0Vector;
typedef struct {
    u8 pad0[6];
    s16 f6;
    u8 pad8[4];
    u8 fc;
    u8 fd;
    u8 fe;
    u8 padf;
    s16 f10;
    s16 f12;
    u16 f14;
    u8 pad16[6];
    s16 f1c;
    s16 f1e;
} D8181A8C0Asset;
typedef struct {
    u8 pad0[8];
    D8181A8C0Vector *field8;
    D8181A8C0Asset *fieldc;
    void *field10;
} D8181A8C0Object;
typedef struct PointPosition {
    u16 pad_00;
    u16 x;
    u16 pad_04;
    u16 y;
    u16 pad_08;
    u16 z;
} PointPosition;
typedef struct PointRecord {
    u8 pad_00[8];
    u32 color;          /* r/g/b/code word copied into the tile */
    u8 pad_0C[0x26];
    s16 brightness;     /* 0x80 = full */
} PointRecord;
typedef struct Scratch800241EC {
    u16 x;
    u16 y;
    u16 z;
    u8 pad06[0x12];
    u8 *cursor;
    u8 pad1C[4];
    u32 *ot;
    u8 pad24[0x6C];
    u32 xy;
    u32 depth;
    u8 pad98[0x28];
    u32 index;
} Scratch800241EC;
typedef struct Packet800241EC {
    u32 tag;
    u8 r;
    u8 g;
    u8 b;
    u8 code;
    u32 data;
} Packet800241EC;
typedef struct MotionState {
    unsigned char pad_00[2];
    u16 frames_left;
    unsigned char pad_04[20];
    s16 mode;
    s16 period;
    u16 tick;
    unsigned char pad_1E[0x3a];
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} MotionState;
typedef struct UpdateFlags {
    unsigned char pad_00[0x14];
    u16 flags;
} UpdateFlags;
typedef struct EffectPosition {
    u16 pad_00;
    s16 x;
    u16 pad_04;
    s16 y;
    u16 pad_08;
    s16 z;
} EffectPosition;
typedef struct SpawnedRecord {
    u8 pad_00[8];
    u32 unk_08;
    u8 pad_0C[4];
    s32 unk_10;
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
} SpawnedRecord;
typedef struct S_8181B078_0_pre {
    u16 unk_00;
} S_8181B078_0_pre;
typedef struct S_8181B078_0 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x18];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    u8 unk_28;
    u8 pad_29[0x37];
    s32 unk_60;
} S_8181B078_0;
typedef struct S_8181B078_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8181B078_1;
typedef struct S_8181B078_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8181B078_2;
typedef struct S_8181B1A0_4 {
    u8 pad_00[0x8];
    void * unk_08;
} S_8181B1A0_4;
typedef struct S_8181B1A0_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8181B1A0_5;
typedef struct S_8181B1A0_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x5C];
    s32 unk_60;
} S_8181B1A0_0;
typedef struct S_8181B1A0_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_8181B1A0_1;
typedef struct S_8181B1A0_2 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8181B1A0_2;
typedef struct S_8181B1A0_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8181B1A0_3;
typedef struct S_80024BE8_0_pre {
    u16 unk_00;
} S_80024BE8_0_pre;
typedef struct S_80024BE8_0 {
    void * unk_00;
    u16 * unk_04;
    u8 pad_08[0x1];
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x6C];
    union { u16 u; s16 s; } unk_78;   /* accessed as both */
    u8 unk_7A;
    s8 unk_7B;
    u8 pad_7C[0x2];
    union { s16 s; u16 u; } unk_7E;   /* accessed as both */
    u8 pad_80[0x2];
    u16 unk_82;
    u16 unk_84;
    union { u16 u; s16 s; } unk_86;   /* accessed as both */
    u8 pad_88[0x1A];
    s8 unk_A2;
    s8 unk_A3;
} S_80024BE8_0;
typedef struct S_80024BE8_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80024BE8_1;
typedef struct S_80024BE8_2 {
    u8 pad_00[0xC];
    union {
        struct { s32 v; } at00;
        struct { s8 v; } at00u;
        struct { u8 pad[0x1]; s8 v; } at01;
        struct { u8 pad[0x2]; s8 v; } at02;
    } unk_0C;   /* overlapping accesses */
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80024BE8_2;
typedef struct S_80024BE8_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80024BE8_3_pre;
typedef struct S_80024BE8_3 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0xE];
    s8 unk_72;
    s8 unk_73;
    u8 pad_74[0x14];
    u16 unk_88;
} S_80024BE8_3;
typedef struct S_80024BE8_4 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80024BE8_4;
typedef struct S_80024BE8_5 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80024BE8_5;
typedef struct S_80024BE8_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024BE8_6;
typedef struct S_80024BE8_7 {
    u8 pad_00[0x88];
    u16 unk_88;
} S_80024BE8_7;
typedef struct S_80024BE8_8 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80024BE8_8;
typedef struct S_80024BE8_9 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} S_80024BE8_9;
typedef struct S_80024BE8_10 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_80024BE8_10;
typedef struct S_80024BE8_11 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80024BE8_11;
typedef struct S_80024BE8_12 {
    u8 pad_00[0x8];
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80024BE8_12;
typedef struct S_80024BE8_13 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_80024BE8_13;
typedef struct S_80024BE8_14 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_80024BE8_14;
typedef struct S_80024BE8_15 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xE];
    s16 unk_22;
} S_80024BE8_15;
typedef struct S_80024BE8_16 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x8];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_80024BE8_16;
typedef struct S_80024BE8_17 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    s32 unk_08;
} S_80024BE8_17;
typedef struct S_80024BE8_18 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_80024BE8_18;
typedef struct S_80024BE8_19 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_80024BE8_19;
typedef struct S_80024BE8_20_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80024BE8_20_pre;
typedef struct S_80024BE8_21 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_80024BE8_21;
typedef struct S_80024BE8_22 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80024BE8_22;
typedef struct S_80024BE8_23_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_80024BE8_23_pre;
typedef struct S_80024BE8_23 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x68];
    u16 unk_88;
} S_80024BE8_23;
typedef struct Pair16 {
    s16 x;
    u16 y;
} Pair16;
typedef struct PathBlock {
    Pair16 entries[8];
} PathBlock;
ObjectNodeHeader *func_8003FC64(s32);
void func_8003DB94(void *, void *, s32);
s32 func_800B8FC8(void *, void *, void *, s32, s32);
u32 func_80065420(void *, void *, void *, void *);
extern s16 D_80025914;
typedef struct S_80045C34 { u8 pad0[6]; s16 unk6; u8 pad1[12]; u16 unk14; } S_80045C34;
s32 func_80045C34(u8 *, s32, S_80045C34 *);
void func_8002404C(void *record_data, void *unused, void *update_data);
void func_800240C0(void *unused_context, void *origin, s32 unused_id, s16 offset_x, s16 offset_y, s16 offset_z);
s32 func_800241EC(PointRecord *first_point, PointPosition *first_position);
void func_8002443C(MotionState *state, s32 *sum, UpdateFlags *flags);
void func_80024604(void *object_data, s16 *position);
void func_80024758(ObjectNodeHeader *parent, s16 field_34, s32 field_28, s16 field_52, s16 offset_x,
                   s16 offset_y, s16 offset_z);
void func_80024878(void *object, S_8181B078_1 *position, S_8181B078_2 *source);
void func_800249A0(void *source, s32 offset_x, s32 offset_y, s32 offset_z, s16 effect_value);
void func_80024B14(void *state_data, s32 unused, void *target);
void func_80024BE8(void *effect, void *motion, void *sprite);
#endif
