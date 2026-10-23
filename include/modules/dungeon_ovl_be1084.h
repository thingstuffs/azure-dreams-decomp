#ifndef MODULE_DUNGEON_OVL_BE1084_H
#define MODULE_DUNGEON_OVL_BE1084_H
#include "shared/gpu_packets.h"
#include "dungeon/monster/death.h"
#include "common.h"
#include "shared/game_work.h"



typedef struct Scratch {
    u8 pad0[4];
    u16 in0;
    u16 in1;
    u16 in2;
    u8 pad0A[0x12];
    u8 *current;
    u8 pad20[4];
    u8 *table;
    u8 pad28[0xA8];
    u16 out0;
    u16 padD2;
    u16 out1;
    u8 padD4[0x2A];
    s32 index;
} Scratch;

typedef struct Packet {
    u8 pad0[3];
    u8 code;
    union {
        u32 link;
        struct {
            u8 r;
            u8 g;
            u8 b;
            u8 command;
        } color;
    } data;
} Packet;

extern s32 RotTransPers(void *, void *, void *, void *);
extern s32 GetTPage(s32, s32, s32, s32);
extern void SetDrawMode(void *, s32, s32, u16, s32);

/* Project linked points and queue their tile and draw-mode packets for rendering. */
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"
#include "shared/object_links.h"
#include "shared/object_payload.h"
#include "shared/position_views.h"

typedef struct S_80BC1264_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
} S_80BC1264_0;   /* arg1 in func_80170A64 */

   /* the 0x2 bytes before arg0 in func_80170A64, addressed as arg0[-1] */

typedef struct S_80BC1264_1 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x1];
    union {
        struct { s8 v; } at00;
        struct { s32 v; } at00u;
        struct { u8 pad[0x1]; s8 v; } at01;
        struct { u8 pad[0x2]; s8 v; } at02;
    } unk_04;   /* overlapping accesses */
    s32 unk_08;
    u8 pad_0C[0x26];
    s16 unk_32;
    u8 pad_34[0x2];
    s16 unk_36;
    s16 unk_38;
    u8 pad_3A[0x6];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
} S_80BC1264_1;   /* arg0 in func_80170A64 */


#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)


/* Advance the effect motion, fade its color, and flag it near its target or when faded out. */
typedef struct { s32 x,y,z,dx,dy,dz; } EffectMotion;
typedef struct {
 u8 red,green,blue,pad03;
 union {struct {u8 red,green,blue,pad;} color;s32 packed;} current;
 s32 output;
 u8 pad0c[0x26];
 s16 remaining,total;
} FadeEffect;
/* Advance and damp motion; scale the current color by the remaining lifetime. */

typedef struct S_80BC1528_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80BC1528_0;   /* obj in func_80170D28 */

   /* saved_arg0 in func_80170D28 */

typedef struct S_80BC1528_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    u8 pad_34[0x2];
    u16 unk_36;
    u16 unk_38;
    u16 unk_3A;
    u8 pad_3C[0x4];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
} S_80BC1528_2;   /* tail in func_80170D28 */

   /* ((S_80BC1528_0 *)obj)->unk_08 in func_80170D28 */

   /* ((S_80BC1528_1 *)saved_arg0)->unk_08 in func_80170D28 */


extern void *allocate_list_node(s32, void *);
extern void *func_8003FD64(s32, void *);
extern void register_node();
extern void func_8004491C();

/* Creates an offset effect and initializes its motion back toward the parent. */

   /* held_arg0 in func_80170F2C */

typedef struct S_80BC172C_3 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80BC172C_3;   /* temp_v0 in func_80170F2C */

   /* ((S_80BC172C_2 *)held_arg0)->unk_08 in func_80170F2C */

typedef struct S_80BC172C_5 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80BC172C_5;   /* ((S_80BC172C_3 *)temp_v0)->unk_08 in func_80170F2C */

typedef struct S_80BC172C_6 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_80BC172C_6;   /* ((S_80BC172C_3 *)temp_v0)->unk_0C in func_80170F2C */


extern s32 rand(void);

typedef struct S_80BC172C_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80BC172C_0;   /* temp_v0 in func_80170F2C */

typedef struct S_80BC172C_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    s16 unk_34;
} S_80BC172C_1;   /* temp_s0 in func_80170F2C */

/* Spawn an effect at an offset from its parent with randomized motion. */



typedef struct S_80BC1880_0 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0xB];
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} S_80BC1880_0;   /* arg2 in func_80171080 */

   /* the 0x2 bytes before arg0 in func_80171080, addressed as arg0[-1] */

typedef struct S_80BC1880_1 {
    u8 pad_00[0x2];
    u8 unk_02;
    u8 unk_03;
    u8 unk_04;
    u8 pad_05[0x15];
    union { s16 s; u16 u; } unk_1A;   /* accessed as both */
    s16 unk_1C;
} S_80BC1880_1;   /* arg0 in func_80171080 */

   /* arg1 in func_80171080 */



typedef struct StackWork {
    u16 xyz[3];
    u16 pad;
    s64 out18;
    s32 out20;
    s32 out24;
} StackWork;

/* Update the effect's transform, color, and depth, and flag it when its lifetime expires. */
s32 build_projected_tile_packets(u8 *,u16 *);

void advance_damped_motion_and_fade_effect(FadeEffect *,EffectMotion *);
/* Compatibility for registered relink copies pending LL4 removal. */
typedef ObjectPayloadView S_80BC172C_2;

/* Compatibility for registered relink copies pending LL4 removal. */
typedef MovingPosition S_80BC172C_4;

/* Compatibility for registered relink copies pending LL4 removal. */
typedef ObjectRetirementFlags S_80BC1880_1_pre;

/* Compatibility for registered relink copies pending LL4 removal. */
typedef MovingPosition S_80BC1880_2;

#endif
