#ifndef DUNGEON_OVL_7E71D800_H
#define DUNGEON_OVL_7E71D800_H
#include "common.h"
#include "m2c_compat.h"
#include "shared/object_flags.h"
#include "records/Rec_func_800249DC_arg0.h"
#include "shared/game_work.h"
typedef struct Row_818E71DC_S_800249DC_0_pre {
    u16 unk_00;
} Row_818E71DC_S_800249DC_0_pre;   /* the 0x2 bytes before arg0 in func_800249DC, addressed as arg0[-1] */

typedef struct Row_818E71DC_S_800249DC_1 {
    u8 pad_00[0x10];
    s32 unk_10;
} Row_818E71DC_S_800249DC_1;   /* temp_ptr in func_800249DC */

typedef struct Row_818E71DC_S_800249DC_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} Row_818E71DC_S_800249DC_2;   /* arg1 in func_800249DC */

typedef struct Row_818E71DC_S_800249DC_3 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x6];
    union { u8 u8; s32 s32; } unk_0C;   /* accessed as both */
    u8 pad_10[0x4];
    u16 unk_14;
} Row_818E71DC_S_800249DC_3;   /* arg2 in func_800249DC */

/* Advance the target, ease the position toward it, and update visual brightness and flags. */
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))

/* Advances the effect state and frame coordinates, setting flags when its timer expires. */
#ifndef NULL
#define NULL 0
#endif

typedef struct Row_818E747C_S_80024C7C_0 {
    u8 pad_00[0xC];
    u16 unk_0C;
    u16 unk_0E;
    union { s16 s; u16 u; } unk_10;   /* accessed as both */
    u8 pad_12[0x2E];
    u8 unk_40;
    u8 pad_41[0x1];
    u8 unk_42;
    u8 pad_43[0x1];
    u8 unk_44;
    u8 pad_45[0x1];
    u8 unk_46;
    u8 pad_47[0x3];
    u16 unk_4A;
} Row_818E747C_S_80024C7C_0;   /* node in func_80024C7C */

typedef struct Row_818E747C_S_80024C7C_1 {
    void * unk_00;
} Row_818E747C_S_80024C7C_1;   /* global_base in func_80024C7C */

typedef struct Row_818E747C_S_80024C7C_2 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} Row_818E747C_S_80024C7C_2;   /* context in func_80024C7C */

typedef struct Row_818E747C_S_80024C7C_3 {
    union { s32 s; u32 u; } unk_00;   /* accessed as both */
    u32 unk_04;
    u16 unk_08;
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    s16 unk_0E;
    u16 unk_10;
    u16 unk_12;
    s8 unk_14;
    u8 unk_15;
    s16 unk_16;
    s16 unk_18;
    u16 unk_1A;
    u8 unk_1C;
    s8 unk_1D;
    u8 pad_1E[0x2];
    s16 unk_20;
    u16 unk_22;
    s8 unk_24;
    s8 unk_25;
} Row_818E747C_S_80024C7C_3;   /* entry in func_80024C7C */

typedef struct Row_818E747C_S_80024C7C_4 {
    u8 pad_00[0x2];
    s16 unk_02;
} Row_818E747C_S_80024C7C_4;   /* (u8 *)transform_base + lo in func_80024C7C */

typedef struct Row_818E747C_S_80024C7C_5 {
    u8 pad_00[0xB0];
    u32 unk_B0;
} Row_818E747C_S_80024C7C_5;   /* (u8 *)(height4 + (u32)context) in func_80024C7C */

typedef struct Row_818E747C_S_80024C7C_6_pre {
    void * unk_00;
    u8 pad_04[0x4];
} Row_818E747C_S_80024C7C_6_pre;   /* the 0x8 bytes before arg0 in func_80024C7C, addressed as arg0[-1] */

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} Row_818E747C_Point3;

typedef struct {
    s16 x;
    s16 y;
} Row_818E747C_Point2;

/* Draw four jittered textured strips for each node in the linked list. */
typedef struct Row_818E786C_S_8002506C_0 {
    void * unk_00;
} Row_818E786C_S_8002506C_0;   /* arg0 in func_8002506C; pointer addresses record offset 0x14 */

typedef struct Row_818E786C_S_8002506C_1 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} Row_818E786C_S_8002506C_1;   /* temp_a0 in func_8002506C */

typedef struct Row_818E786C_S_8002506C_2 {
    u16 unk_00;
    u16 unk_02;
} Row_818E786C_S_8002506C_2;   /* temp_v1 in func_8002506C */

/* Copy the selected pair of table values into the linked record. */
void func_800478B8(void *visual);
void func_80065770();
s32 func_80069EF8();
s32 func_800666F4();
s32 func_80066640();
s16 func_80066460();
s16 func_8006649C();
extern u8 D_80024004[24];
void func_800249DC(void *motion, Row_818E71DC_S_800249DC_2 *position, Row_818E71DC_S_800249DC_3 *visual);
void func_80024B60(void *effect);
s32 func_80024C7C(void *node_data);
void func_8002506C(void *record_field, s32 pair_index);
#endif
