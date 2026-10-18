#ifndef DUNGEON_OVL_191284C_H
#define DUNGEON_OVL_191284C_H
#include "common.h"
#include "m2c_compat.h"
#include "shared/gpu_packets.h"
#include "shared/game_work.h"
#include "modules/dungeon_ovl_190d6a4.h"
/* gv in func_8002404C */

typedef struct Row_818F2800_S_BODY_1 {
    u8 pad_00[0x8];
    u8 * unk_08;
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_0C;   /* overlapping accesses */
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} Row_818F2800_S_BODY_1;   /* state in func_8002404C */

typedef struct Row_818F2800_S_BODY_2 {
    u8 unk_00;
    u8 unk_01;
    u8 pad_02[0x1];
    u8 unk_03;
    u16 unk_04;
    u16 unk_06;
    union {
        struct { u8 v; } at00;
        struct { void * v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
        struct { u8 pad[0x3]; u8 v; } at03;
    } unk_08;   /* overlapping accesses */
} Row_818F2800_S_BODY_2;   /* sp in func_8002404C */

typedef struct Row_818F2800_S_BODY_3 {
    u8 pad_00[0x38];
    s16 unk_38;
    s16 unk_3A;
    s16 unk_3C;
} Row_818F2800_S_BODY_3;   /* root in func_8002404C */

typedef struct Row_818F2800_S_BODY_4 {
    u8 pad_00[0x2];
    u8 unk_02;
} Row_818F2800_S_BODY_4;   /* sq in func_8002404C */

typedef struct Row_818F2800_S_BODY_5 {
    u8 pad_00[0x20];
    s16 unk_20;
    u8 pad_22[0x6];
    s16 unk_28;
    u8 pad_2A[0x6];
    s16 unk_30;
    u8 pad_32[0x6];
    s16 unk_38;
} Row_818F2800_S_BODY_5;   /* rp in func_8002404C */

typedef struct Row_818F2800_S_BODY_6 {
    u8 pad_00[0x20];
    union { s16 s; u16 u; } unk_20;   /* accessed as both */
    u8 pad_22[0x6];
    u16 unk_28;
    u8 pad_2A[0x6];
    u16 unk_30;
    u8 pad_32[0x6];
    u16 unk_38;
} Row_818F2800_S_BODY_6;   /* q in func_8002404C */

typedef struct Row_818F2800_S_BODY_7 {
    u8 pad_m4[0x3];
    s8 len;
    s32 unk_00;
    union { u16 u; s16 s; } unk_04;   /* accessed as both */
    union { u16 u; s16 s; } unk_06;   /* accessed as both */
    s16 unk_08;
    s16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    union { s16 s16; u8 u8; } unk_10;   /* accessed as both */
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    union { struct { s16 v; } at00; struct { u8 pad[0x1]; u8 v; } at01; } unk_18;   /* overlapping accesses */
    u8 pad_1A[0x2];
    union { u16 u; s16 s; } unk_1C;   /* accessed as both */
    union { u16 u; s16 s; } unk_1E;   /* accessed as both */
    union {
        struct { s16 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_20;   /* overlapping accesses */
} Row_818F2800_S_BODY_7;   /* ent in func_8002404C */

   /* gp[0] in func_8002404C */

typedef struct { u8 v; } DmU8;
typedef struct { u16 v; } DmU16;
typedef struct { s16 v; } DmS16;
typedef struct { u32 v; } DmU32;
typedef struct { s32 v; } DmS32;

#define DM_U8(o)  (((DmU8 *)(scratch + (o)))->v)
#define DM_U16(o) (((DmU16 *)(scratch + (o)))->v)
#define DM_S16(o) (((DmS16 *)(scratch + (o)))->v)
#define DM_U32(o) (((DmU32 *)(scratch + (o)))->v)
#define DM_S32(o) (((DmS32 *)(scratch + (o)))->v)

/* Builds textured quad strips and adds visible quads to the ordering table. */
typedef struct Row_818F3098_GapNode { u8 pad[8]; void *position; void *appearance; } Row_818F3098_GapNode;

/* Render each linked effect, using its appearance field as the draw parameter. */
typedef struct {
    u32 addr : 24;
    u32 len : 8;
} Row_818F30EC_P_TAG;

   /* ctx in func_800248EC */

typedef struct Row_818F30EC_S_800248EC_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} Row_818F30EC_S_800248EC_1;   /* input in func_800248EC */

typedef struct Row_818F30EC_S_800248EC_2 {
    u8 pad_00[0x3];
    u8 unk_03;
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
} Row_818F30EC_S_800248EC_2;   /* packet in func_800248EC */

typedef struct Row_818F30EC_S_800248EC_3_pre {
    void * unk_00;
    u8 pad_04[0x4];
} Row_818F30EC_S_800248EC_3_pre;   /* the 0x8 bytes before cur in func_800248EC, addressed as cur[-1] */

typedef struct Row_818F30EC_S_800248EC_3 {
    u8 pad_00[0x8];
    u32 unk_08;
    u8 pad_0C[0x26];
    s16 unk_32;
} Row_818F30EC_S_800248EC_3;   /* cur in func_800248EC */

typedef struct Row_818F30EC_S_800248EC_4 {
    u8 pad_00[0x8];
    void * unk_08;
} Row_818F30EC_S_800248EC_4;   /* next in func_800248EC */

   /* final_ctx in func_800248EC */

typedef struct {
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
} Row_818F30EC_Scratch800248EC;

typedef struct {
    u32 tag;
    u8 r;
    u8 g;
    u8 b;
    u8 code;
    u32 data;
} Row_818F30EC_Packet800248EC;

/* Projects linked points and queues shaded tiles with draw-mode packets. */

s32 func_800644B8(s32);
void func_80064840();
void func_800649A0(void);
void func_80064A40(void);
void func_80064AE0();
void func_80064BC0();
void func_80064CF0();
void func_80064D80();
s32 func_80065590();
void func_80065820();
u32 func_80065420(void *, void *, void *, void *);
s32 func_80066460(s32, s32, s32, s32);
void func_80067F20(void *, s32, s32, s32, s32);

void render_textured_effect_parts(Row_818F2800_S_BODY_3 *geometry, void *position, Row_818F2800_S_BODY_1 *state, s32 depth_offset);
s32 draw_linked_gap_effects(void *state, void *position, void *appearance);
s32 draw_linked_shaded_tiles(void *first_point, void *first_position);
s32 choose_random_sign(void);
#endif
