#ifndef DUNGEON_ACTOR_DEPTH_STRIP_PROJECTION_G00337_H
#define DUNGEON_ACTOR_DEPTH_STRIP_PROJECTION_G00337_H
/* Depth strip projection shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800AA854. */

#include "common.h"
#include "shared/game_work.h"

typedef struct State_80083160 {
    char pad0[0x8d0];
    s32 value;
} State_80083160;

typedef struct Arg0_800AFBFC {
    char pad0[6];
    u8 value;
} Arg0_800AFBFC;

typedef struct Arg2_800AFBFC {
    char pad0[8];
    void *temp;
    char padc[3];
    u8 byte;
    char pade[4];
    u16 flags;
} Arg2_800AFBFC;

typedef struct ScratchHeader_800AFBFC {
    u8 pad0[0x20];
    void *state_data;
    u8 pad24[0xf4];
    void *segment_data;
} ScratchHeader_800AFBFC;

typedef struct S_800AFFB4_0 {
    u8 pad_00[0x8];
    union { s16 s; u16 u; } unk_08;   /* accessed as both */
} S_800AFFB4_0;

/* arg0 in project_depth_strips_and_quads */
typedef struct S_800AFFB4_1 {
    u8 pad_00[0x8];
    union { s32 s32; u16 u16; } unk_08;   /* accessed as both */
    s32 unk_0C;
    union { s32 s32; u16 u16; } unk_10;   /* accessed as both */
    union { s32 s32; u16 u16; } unk_14;   /* accessed as both */
    u8 pad_18[0x8];
    s32 unk_20;
    u8 pad_24[0x50];
    u16 unk_74;
    u8 pad_76[0x6];
    u16 unk_7C;
    u8 pad_7E[0x6];
    u16 unk_84;
    u8 pad_86[0x6];
    u16 unk_8C;
    u8 pad_8E[0x2];
    union { s32 s32; u16 u16; } unk_90;   /* accessed as both */
    u8 pad_94[0x5C];
    union {
        struct { u16 v; } at00;
        struct { s32 v; } at00u;
        struct { s16 v; } at00p;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_F0;   /* overlapping accesses */
    union {
        struct { u16 v; } at00;
        struct { s32 v; } at00u;
        struct { s16 v; } at00p;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_F4;   /* overlapping accesses */
    union {
        struct { u16 v; } at00;
        struct { s32 v; } at00u;
        struct { s16 v; } at00p;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_F8;   /* overlapping accesses */
    union {
        struct { u16 v; } at00;
        struct { s32 v; } at00u;
        struct { s16 v; } at00p;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_FC;   /* overlapping accesses */
    u8 pad_100[0x18];
    s32 unk_118;
} S_800AFFB4_1;

/* arg2 in project_depth_strips_and_quads */
typedef struct S_800AFFB4_2_pre {
    s8 unk_00;
    s8 unk_01;
    s8 unk_02;
    u8 pad_03[0x1];
    s32 unk_04;
    u8 pad_08[0x4];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u8 pad_14[0x4];
    s8 unk_18;
    s8 unk_19;
    s8 unk_1A;
    u8 pad_1B[0x1];
    s32 unk_1C;
    u8 pad_20[0x4];
    s8 unk_24;
    s8 unk_25;
    s8 unk_26;
    u8 pad_27[0x1];
    s16 unk_28;
    s16 unk_2A;
    u8 pad_2C[0x8];
    s8 unk_34;
    s8 unk_35;
    s8 unk_36;
    u8 pad_37[0x1];
    s16 unk_38;
    s16 unk_3A;
    u8 pad_3C[0x4];
    s8 unk_40;
    s8 unk_41;
    s8 unk_42;
    u8 pad_43[0x1];
    s32 unk_44;
    u8 pad_48[0x4];
} S_800AFFB4_2_pre;

/* the near quad of the strip packet: StripPacket.near_quad, at packet_buffer + 4 */
typedef struct S_800AFFB4_2 {
    s8 unk_00;
    s8 unk_01;
    s8 unk_02;
    u8 pad_03[0x1];
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x4];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s32 unk_10;
} S_800AFFB4_2;

/* the far quad of the strip packet: StripPacket.far_quad, at packet_buffer + 0x50 */
typedef struct StripPacket {
    u8 pad_00[0x4];
    S_800AFFB4_2_pre near_quad;
    S_800AFFB4_2 far_quad;
} StripPacket;

/* packet_buffer: the two quads of one strip */
typedef struct StripQuad {
    u8 pad_00[0xC];
    s32 uv0;
    u8 pad_10[0x8];
    union { s32 word; u8 u; } uv1;   /* accessed as both */
    u8 pad_1C[0x8];
    union { s16 half; struct { u8 u; u8 v; } b; } uv2;   /* accessed as both */
    u8 pad_26[0xA];
    union { s16 half; struct { u8 u; u8 v; } b; } uv3;   /* accessed as both */
} StripQuad;

/* one 0x34-byte quad of the strip packet */
typedef struct S_800AFFB4_3 {
    s16 unk_00;
    u16 unk_02;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    u8 pad_08[0x4];
} S_800AFFB4_3;

/* texture entry data, 4 bytes into a TwelveByteEntry */
typedef struct TwelveByteEntry {
    u8 bytes[12];
} TwelveByteEntry;

extern s32 rsin(s32 value);
extern s32 rcos(s32 value);
extern s32 func_80065610();
extern void AddPrim();
extern void SetPolyGT4();

/* Functions defined in this translation unit. */
s32 process_circular_segments(Arg0_800AFBFC *shape, s32 unused, Arg2_800AFBFC *segment);
s32 project_depth_strips_and_quads(S_800AFFB4_0 *origin, void *unused, S_800AFFB4_1 *render_data_in, u8 *packet_buffer, s16 texture_arg);

#endif
