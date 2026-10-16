#ifndef DUNGEON_OVL_19C088C_H
#define DUNGEON_OVL_19C088C_H
#include "common.h"
#include "m2c_compat.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/entity_height_offsets.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
typedef struct Row_819A088C_S_819A088C_0 {
    u8 pad_00[0x24];
    union { u8 * p; u32 * p2; } unk_24;   /* accessed as both */
    u16 unk_28;
    u8 pad_2A[0xA];
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    u8 pad_40[0x48];
    s32 unk_88;
    s32 unk_8C;
    s32 unk_90;
    u8 pad_94[0x10];
    u16 unk_A4;
    u16 unk_A6;
    u16 unk_A8;
    u8 pad_AA[0x6];
    u16 unk_B0;
    u16 unk_B2;
    u16 unk_B4;
    u8 pad_B6[0x2];
    u16 unk_B8;
    u16 unk_BA;
    u16 unk_BC;
    u8 pad_BE[0x2];
    u16 unk_C0;
    u16 unk_C2;
    u16 unk_C4;
    u8 pad_C6[0x2];
    u16 unk_C8;
    u16 unk_CA;
    u16 unk_CC;
    u8 pad_CE[0x32];
    s32 unk_100;
} Row_819A088C_S_819A088C_0;   /* scratch in func_8002408C */

typedef struct Row_819A088C_S_819A088C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} Row_819A088C_S_819A088C_1;   /* arg1 in func_8002408C */

typedef struct Row_819A088C_S_819A088C_2 {
    u8 pad_00[0xF];
    u8 unk_0F;
    u8 pad_10[0x4];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
} Row_819A088C_S_819A088C_2;   /* arg2 in func_8002408C */

typedef struct Row_819A088C_S_819A088C_3 {
    u8 pad_00[0xB0];
    u32 unk_B0;
    u8 pad_B4[0x81C];
    u8 * unk_8D0;
} Row_819A088C_S_819A088C_3;   /* *(u8 **)D_80083160 in func_8002408C */

typedef struct Row_819A088C_S_819A088C_4 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
    u16 unk_08;
    u16 unk_0A;
    u32 unk_0C;
    u16 unk_10;
    u16 unk_12;
    u32 unk_14;
    u16 unk_18;
    u16 unk_1A;
    u32 unk_1C;
    u16 unk_20;
    u16 unk_22;
} Row_819A088C_S_819A088C_4;   /* packet in func_8002408C */

typedef struct Row_819A088C_S_819A088C_5 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} Row_819A088C_S_819A088C_5;   /* context in func_8002408C */

typedef struct Row_819A088C_S_819A088C_6 {
    u8 pad_00[0xC];
    u32 unk_0C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u8 pad_1C[0x38];
    u16 unk_54;
    u16 unk_56;
    u16 unk_58;
    u16 unk_5A;
    u16 unk_5C;
    u16 unk_5E;
    u16 unk_60;
    u16 unk_62;
    u16 unk_64;
    u16 unk_66;
    u16 unk_68;
    u16 unk_6A;
} Row_819A088C_S_819A088C_6;   /* arg0 in func_8002408C */

typedef struct Row_819A088C_S_819A088C_7 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} Row_819A088C_S_819A088C_7;   /* *global in func_8002408C */

typedef struct {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} Row_819A088C_MATRIX;

/* Transform and queue a visible Gouraud-shaded quad in the ordering table. */
typedef struct Row_819A0D64_GapNode { u8 pad[8]; void *position; void *appearance; } Row_819A0D64_GapNode;

/* Apply the renderer to each node in the linked object chain. */
typedef struct Row_819A0DB8_S_func_819A0DB8_0 {
    u8 pad_00[0x3A];
    u16 unk_3A;
    u8 pad_3C[0x50];
    u8 unk_8C;
    s8 unk_8D;
    u8 pad_8E[0x4];
    u8 unk_92;
    u8 unk_93;
    u8 pad_94[0x1];
    u8 unk_95;
    u8 pad_96[0x2];
    u8 unk_98;
    s8 unk_99;
    u8 pad_9A[0x4];
    u8 unk_9E;
    u8 unk_9F;
    u8 pad_A0[0x1];
    u8 unk_A1;
} Row_819A0DB8_S_func_819A0DB8_0;

typedef struct Row_819A0DB8_S_func_819A0DB8_1 {
    u8 pad_00[0x61B0];
    s16 unk_61B0;
} Row_819A0DB8_S_func_819A0DB8_1;

/* Updates paired fields for the current countdown step and flags completion. */
typedef struct Row_819A0EF0_S_800246F0_0_pre {
    u16 unk_00;
} Row_819A0EF0_S_800246F0_0_pre;   /* the 0x2 bytes before arg0 in func_800246F0, addressed as arg0[-1] */

typedef struct Row_819A0EF0_S_800246F0_0 {
    u8 pad_00[0x3A];
    union { u16 s; s16 u; } unk_3A;   /* accessed as both */
    s16 unk_3C;
} Row_819A0EF0_S_800246F0_0;   /* arg0 in func_800246F0 */

typedef struct Row_819A0EF0_S_800246F0_2 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
} Row_819A0EF0_S_800246F0_2;   /* arg1 in func_800246F0 */

typedef struct Row_819A0EF0_S_800246F0_3 {
    s32 unk_00;
} Row_819A0EF0_S_800246F0_3;   /* D_800814A0 in func_800246F0 */

/* Fade and move the effect, marking it finished when its countdown expires. */
typedef struct Row_819A0FC0_S_func_819A0FC0_0 {
    u8 pad_00[0x3A];
    u16 unk_3A;
    s16 unk_3C;
} Row_819A0FC0_S_func_819A0FC0_0;

typedef struct Row_819A0FC0_S_func_819A0FC0_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} Row_819A0FC0_S_func_819A0FC0_1;

typedef struct Row_819A0FC0_S_func_819A0FC0_2 {
    u16 unk_00;
} Row_819A0FC0_S_func_819A0FC0_2;

// Decrement the fade timer, update the primitive's brightness, and flag completion.
typedef struct Row_819A1034_S_819A1034_0 {
    u8 pad_00[0x3A];
    union { u16 s; s16 u; } unk_3A;   /* accessed as both */
    s16 unk_3C;
} Row_819A1034_S_819A1034_0;   /* base in func_80024834 */

typedef struct Row_819A1034_S_819A1034_1 {
    u8 pad_00[0x61B0];
    s16 unk_61B0;
} Row_819A1034_S_819A1034_1;   /* page in func_80024834 */

typedef struct Row_819A1034_S_819A1034_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    u8 unk_1C;
    u8 unk_1D;
    u8 unk_1E;
} Row_819A1034_S_819A1034_2;   /* p in func_80024834 */

/* Decrement the fade timer, scale four colors, and flag completion at zero. */
typedef struct Row_819A1118_S_819A1118_0_pre {
    u16 unk_00;
} Row_819A1118_S_819A1118_0_pre;   /* the 0x2 bytes before arg0 in func_80024918, addressed as arg0[-1] */

typedef struct Row_819A1118_S_819A1118_0 {
    u8 pad_00[0x3A];
    u16 unk_3A;
    s16 unk_3C;
    s16 unk_3E;
    u8 pad_40[0x14];
    s16 unk_54;
    s16 unk_56;
    s16 unk_58;
    s16 unk_5A;
    s16 unk_5C;
    s16 unk_5E;
    u16 unk_60;
    u16 unk_62;
    u16 unk_64;
    u16 unk_66;
    u16 unk_68;
    u16 unk_6A;
    s16 unk_6C;
    s16 unk_6E;
    s16 unk_70;
    s16 unk_72;
    s16 unk_74;
    s16 unk_76;
} Row_819A1118_S_819A1118_0;   /* arg0 in func_80024918 */

typedef struct Row_819A1118_S_819A1118_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0xD];
    u8 unk_1C;
    u8 unk_1D;
    u8 unk_1E;
} Row_819A1118_S_819A1118_1;   /* var_a0 in func_80024918 */

/* Advance effect interpolation, fade its four colors, and flag expiration. */
/* Advance the effect fade and mark it finished when its countdown expires. */
typedef struct {
    u8 pad00[0x3A];
    u16 count;
    s16 divisor;
} Row_819A13D0_Work;

typedef struct {
    u8 pad00[0x0C];
    s8 c0;
    s8 c1;
    s8 c2;
    u8 pad0F[0x0B];
    u16 angle;
} Row_819A13D0_Obj;

/* Decrement the count, update the object angle and components, and flag completion. */
typedef struct Row_819A1450_S_819A1450_0 {
    u8 pad_00[0x3A];
    s16 unk_3A;
    s16 unk_3C;
} Row_819A1450_S_819A1450_0;   /* setup in func_80024C50 */

typedef struct Row_819A1450_S_819A1450_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} Row_819A1450_S_819A1450_1;   /* node in func_80024C50 */

typedef struct Row_819A1450_S_819A1450_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} Row_819A1450_S_819A1450_2;   /* part in func_80024C50 */

typedef struct Row_819A1450_S_819A1450_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
} Row_819A1450_S_819A1450_3;   /* coords in func_80024C50 */

typedef struct Row_819A1450_S_819A1450_4 {
    u8 pad_00[0x36];
    s16 unk_36;
    u8 pad_38[0x4C];
    u16 unk_84;
    u16 unk_86;
    u16 unk_88;
} Row_819A1450_S_819A1450_4;   /* arg0 in func_80024C50 */

typedef struct {
    s16 first;
    u16 second;
} Row_819A1450_LocalEntry;

typedef struct {
    Row_819A1450_LocalEntry entries[8];
} Row_819A1450_LocalTable;

/* Creates an effect at an offset from the source with direction-based motion. */
typedef struct Row_819A1654_Coord {
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[2];
    s16 z;
} Row_819A1654_Coord;

typedef struct Row_819A1654_Sprite {
    u8 pad0[6];
    s16 field6;
    void *data;
    u8 r;
    u8 g;
    u8 b;
    u8 padF;
    s16 field10;
    u8 pad12[2];
    u16 flags;
    s16 field16;
    s16 field18;
    s16 field1A;
    s16 field1C;
    s16 field1E;
} Row_819A1654_Sprite;

typedef struct Row_819A1654_Effect {
    u8 pad0[0xC];
    s32 value0C;
    s32 value10;
    s32 value14;
    s32 value18;
    s32 value1C;
    s32 value20;
    s32 value24;
    s32 value28;
    u8 pad2C[0xE];
    s16 timer3A;
    s16 timer3C;
    s16 mode3E;
    s16 random40;
    u8 pad42[0x12];
    s16 path[18];
} Row_819A1654_Effect;

typedef struct Row_819A1654_Task {
    u8 pad0[8];
    Row_819A1654_Coord *coord;
    Row_819A1654_Sprite *sprite;
    void (*callback)(void);
    u8 pad14[0xC];
    Row_819A1654_Effect effect;
    u8 pad98[0x12];
    u8 data[24];
} Row_819A1654_Task;

typedef struct Row_819A1654_Entity {
    u8 pad0[4];
    u16 *header;
    u8 type;
    u8 pad9;
    s16 state;
    u8 padC[0x20];
    s16 x;
    s16 y;
    s16 z;
    s16 timer;
    u8 pad34[2];
    s16 point_index;
    u8 pad38[2];
    u16 age;
    u8 pad3C[0x18];
    s16 path[24];
    s16 base[3];
} Row_819A1654_Entity;

typedef struct Row_819A1654_World {
    u8 pad0[0x2A];
    u16 angle;
    u8 pad2C[0x34];
    void *focus;
    u8 pad64[0x32];
    s16 field96;
    u8 pad98[0xE];
    u16 fieldA6;
    u8 fieldA8;
    u8 padA9[0x4B];
    s32 fieldF4;
} Row_819A1654_World;

typedef struct Row_819A1654_GlobalState {
    s32 flags;
    s32 pad4;
    Row_819A1654_World *world;
} Row_819A1654_GlobalState;

typedef struct Row_819A1654_LookupGlobal {
    u8 pad0[6];
    s16 field6;
    void *found;
    u8 padC[8];
    u16 flags;
} Row_819A1654_LookupGlobal;

typedef struct Row_819A1654_ControlGlobal {
    u8 pad0[0xA];
    u16 count;
    s32 active;
} Row_819A1654_ControlGlobal;

typedef struct Row_819A1654_Point {
    s16 x;
    u16 y;
} Row_819A1654_Point;

typedef struct Row_819A1654_PointTable {
    Row_819A1654_Point point[8];
} Row_819A1654_PointTable;

typedef struct Row_819A1654_Blob12 {
    u8 bytes[12];
} __attribute__((packed)) Row_819A1654_Blob12;

typedef struct Row_819A1654_Blob8 {
    u8 bytes[8];
} __attribute__((packed)) Row_819A1654_Blob8;

typedef struct Row_819A1654_Blob24 {
    u8 bytes[24];
} __attribute__((packed)) Row_819A1654_Blob24;

/* Advance the entity effect sequence, spawning particles and trails before cleanup. */
void func_80064840(void *, void *, void *);
void func_800649A0(void);
void func_80064A40(void);
void func_80064AE0(void *);
void func_80064BC0(void *, void *);
void func_80064CF0(void *);
void func_80064D80(void *);
s32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
void func_80065820(void *, void *);
u16 func_80066460(s32, s32, s32, s32);
void func_80067F20(void *, s32, s32, u16, s32);
void func_800478B8(void *);
void func_8004491C();
void func_8003DB94();
s16 rand();
s32 func_8003DF74(void *, void *, void *, s32);
s32 func_80069EF8(void);
s32 func_80053EF0(s32);
void func_800A56E0(s32);
void D_80024C50(void *, void *, void *, s32, s32, s32);



extern const Row_819A1450_LocalTable D_80024034;
extern u8 D_800246F0[];
extern u8 D_800DEC00[];
extern Row_819A1654_GlobalState D_800814A0[];
extern Row_819A1654_LookupGlobal D_80082E80[];
extern s16 D_80082E86[6];
extern u16 D_80082E94[6];
extern Row_819A1654_Coord D_80083780[];

extern const Row_819A1654_PointTable D_80024054[1];
extern Row_819A1654_Blob12 D_80026180[];
extern Row_819A1654_Blob12 D_8002618C[];
extern Row_819A1654_Blob24 D_80026198[];
void func_8002408C(void *quad, void *position, void *render_state, s16 depth_bias);
s32 func_80024564(void *state, void *position, void *appearance);
void func_800245B8(void *object_data);
void func_800246F0(void *effect, Row_819A0EF0_S_800246F0_2 *motion, Rec_D_80082E80 *primitive);
void func_800247C0(Row_819A0FC0_S_func_819A0FC0_0 *fadeState, void *unused, Row_819A0FC0_S_func_819A0FC0_1 *primitive);
void func_80024834(void *fade_data);
void func_80024918(void *effect);
void func_80024B3C(void *effect, s32 unused, void *primitive);
void func_80024BD0(Row_819A13D0_Work *work, s32 unused, Row_819A13D0_Obj *obj);
void func_80024C50(Row_819A1450_S_819A1450_4 *source, s32 unused_1, s32 unused_2, s16 offset_x, s16 offset_y,
                   s16 offset_z);
void func_80024E54(Row_819A1654_Entity *entity, void *saved_context, void *saved_data);
extern u8 D_800261B0[];
#endif
