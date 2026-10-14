#ifndef DUNGEON_OVL_18E8800_H
#define DUNGEON_OVL_18E8800_H
#include "common.h"
#include "m2c_compat.h"
#include "shared/dir_step.h"
#include "shared/dungeon_status.h"
#include "shared/object_flags.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "modules/dungeon_native_abi.h"
typedef struct B31_818C8FD0_S_func_818C8FD0_1 {
    void *unk_00;
    void *unk_04;
    u8 pad_08[1];
    u8 unk_09;
    union { s16 s16; u16 u16; } unk_0A;
    u8 pad_0C[0x72];
    union { s16 s16; u16 u16; } unk_7E;
    u8 pad_80[2];
    u16 unk_82;
    union { s16 s16; u16 u16; } unk_84;
    s16 unk_86;
    s16 unk_88;
    u8 pad_8A[0x16];
    u8 unk_A0;
    u8 unk_A1;
    u8 pad_A2[6];
    void *unk_A8;
    void *unk_AC;
} B31_818C8FD0_S_func_818C8FD0_1;
typedef struct B31_818C8FD0_S_func_818C8FD0_2 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    union { s32 s32; void *ptr; } unk_60;
    u8 pad_64[0xE];
    s8 unk_72;
    s8 unk_73;
} B31_818C8FD0_S_func_818C8FD0_2;
typedef struct B31_818C8FD0_S_func_818C8FD0_3 {
    u8 pad_00[8];
    void *unk_08;
    void *unk_0C;
    void *unk_10;
    u8 pad_14[0xA];
    u16 unk_1E;
} B31_818C8FD0_S_func_818C8FD0_3;
typedef struct B31_818C8FD0_S_func_818C8FD0_4 {
    union { s32 s32; struct { u8 pad_00[2]; u16 unk_02; } u16; } unk_00;
    union { s32 s32; struct { u8 pad_04[2]; u16 unk_06; } u16; } unk_04;
    union { s32 s32; struct { u8 pad_08[2]; u16 unk_0A; } u16; } unk_08;
} B31_818C8FD0_S_func_818C8FD0_4;
typedef struct B31_818C8FD0_S_func_818C8FD0_5 {
    u8 pad_00[0xC];
    u32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} B31_818C8FD0_S_func_818C8FD0_5;
typedef struct B31_818C8FD0_S_func_818C8FD0_6 {
    u8 pad_00[8];
    void *unk_08;
    u8 pad_0C[8];
    u16 unk_14;
} B31_818C8FD0_S_func_818C8FD0_6;
typedef struct B31_818C8FD0_S_func_818C8FD0_7 {
    u8 pad_00[2];
    union { s16 s16; u16 u16; } unk_02;
    u8 pad_04[4];
    s16 unk_08;
    s16 unk_0A;
    u8 pad_0C[9];
    u8 unk_15;
    u16 unk_16;
    u8 pad_18[0x14];
    void *unk_2C;
    s32 unk_30;
    u8 pad_34[0x24];
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
} B31_818C8FD0_S_func_818C8FD0_7;
typedef struct B31_818C8FD0_S_func_818C8FD0_8 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} B31_818C8FD0_S_func_818C8FD0_8;
typedef struct B31_818C8FD0_S_func_818C8FD0_9 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} B31_818C8FD0_S_func_818C8FD0_9;
typedef struct B31_818C8FD0_S_func_818C8FD0_10 {
    u16 unk_00;
} B31_818C8FD0_S_func_818C8FD0_10;
typedef union B31_818C8FD0_OffsetTable {
    struct { s16 x; u16 y; } pairs[8];
    u8 value[32];
} B31_818C8FD0_OffsetTable;
typedef struct B31_818C8A70_S_818C8A70_0_pre {
    u16 unk_00;
} B31_818C8A70_S_818C8A70_0_pre;
typedef struct B31_818C8A70_S_818C8A70_0 {
    s16 unk_00;
    u16 unk_02;
    u8 pad_04[0x4];
    s16 unk_08;
    u8 pad_0A[0xB];
    u8 unk_15;
    u8 pad_16[0x16];
    void * unk_2C;
    void * unk_30;
    u8 pad_34[0x24];
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
} B31_818C8A70_S_818C8A70_0;
typedef struct B31_818C8A70_S_818C8A70_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x54];
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
} B31_818C8A70_S_818C8A70_1;
typedef struct B31_818C8A70_S_818C8A70_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} B31_818C8A70_S_818C8A70_2;
typedef struct B31_818C8A70_S_818C8A70_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} B31_818C8A70_S_818C8A70_3;
typedef struct B31_818C8A70_S_818C8A70_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} B31_818C8A70_S_818C8A70_4;
typedef struct B31_818C8A70_S_818C8A70_5 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} B31_818C8A70_S_818C8A70_5;
typedef struct B31_818C8A70_S_818C8A70_6 {
    u8 pad_00[0x60];
    s32 unk_60;
} B31_818C8A70_S_818C8A70_6;
typedef struct B31_818C8A70_S_818C8A70_7_pre {
    void * unk_00;
    u8 pad_04[0x14];
} B31_818C8A70_S_818C8A70_7_pre;
typedef struct B31_818C8924_S_818C8924_0_pre {
    u16 unk_00;
} B31_818C8924_S_818C8924_0_pre;
typedef struct {
    u8 pad0[2];
    u16 life;
    u16 timer;
    u8 pad6[0x58 - 6];
    s32 x;
    s32 y;
    s32 z;
    s32 vx;
    s32 vy;
    s32 vz;
} B31_818C8924_EffectState;
typedef struct {
    u8 pad0[0x14];
    u16 flags;
    u8 pad16[6];
    u16 field1C;
    u16 field1E;
} B31_818C8924_EffectObject;
typedef struct B31_818C8824_S_818C8824_0_pre {
    u16 unk_00;
} B31_818C8824_S_818C8824_0_pre;
typedef struct {
    u8 pad0[2];
    u16 life;
    u8 pad4[0x58 - 4];
    s32 x;
    s32 y;
    s32 z;
} B31_818C8824_EffectState;
typedef struct {
    u8 pad0[0x14];
    u16 flags;
    u8 pad16[6];
    u16 field1C;
    u16 field1E;
} B31_818C8824_EffectObject;
void func_80024024(B31_818C8824_EffectState *state, s32 *position, B31_818C8824_EffectObject *object);
void func_80024124(B31_818C8924_EffectState *effect, s32 *position, B31_818C8924_EffectObject *object);
void func_80024270(void *effect, B31_818C8A70_S_818C8A70_4 *position);
void func_800247D0(B31_818C8FD0_S_func_818C8FD0_1 *state, B31_818C8FD0_S_func_818C8FD0_4 *output_pos, B31_818C8FD0_S_func_818C8FD0_5 *part);
void func_8003DB94(void *, void *, s32);
extern const B31_818C8FD0_OffsetTable D_80024004;
extern s16 D_80024D04;
s32 func_800C8CD8();        /* extern */
s32 func_800A6D30();                                /* extern */
s32 func_800A4778();           /* extern */
s32 func_8009D218();            /* extern */
s32 func_80069EF8();                                /* extern */
extern void *func_8003DF74(void *, void *, void *, s32);
#endif
