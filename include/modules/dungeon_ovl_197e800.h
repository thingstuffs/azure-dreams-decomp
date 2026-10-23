#ifndef DUNGEON_OVL_197E800_H
#define DUNGEON_OVL_197E800_H
#include "common.h"
#include "m2c_compat.h"
#include "modules/dungeon_native_abi.h"
#include "modules/dungeon_draw_chain.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/slus_callbacks.h"
typedef struct S_81961A04_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81961A04_1;
typedef struct S_81961A04_3 {
    u8 pad_00[0x38];
    u16 unk_38;
    u16 unk_3A;
    u16 unk_3C;
    u8 pad_3E[0xE];
    s16 unk_4C;
    u8 pad_4E[0x6];
    s16 unk_54;
} S_81961A04_3;
typedef struct {
    u16 x;
    u16 y;
    u16 z;
} Vec3s;
typedef struct {
    u8 pad0[0x30];
    s16 x;
    s16 y;
    s16 z;
    u8 pad36[2];
    s16 cur_x;
    s16 cur_y;
    s16 cur_z;
    u8 pad3e[0xA];
    s16 state;
    u8 pad4a[2];
    s16 timer;
    u8 pad4e[2];
    s16 phase;
    u8 pad52[2];
    s16 step;
} State;
typedef struct {
    u8 pad0[2];
    s16 cur_x;
    u8 pad4[2];
    s16 cur_y;
    u8 pad8[2];
    s16 cur_z;
    u8 intensity;
    u8 padD;
    s16 x;
    u8 pad10[2];
    s16 y;
    u8 pad14[2];
    s16 z;
} Target;
typedef struct S_func_819615E4_0 {
    u8 pad_00[0xC];
    u8 unk_0C;
} S_func_819615E4_0;
typedef struct S_func_819615E4_1 {
    u8 pad_00[2];
    u16 unk_02;
    u8 pad_04[2];
    u16 unk_06;
} S_func_819615E4_1;
typedef struct S_func_819615E4_2 {
    u8 pad_00[0x2A];
    union {
        s16 s16_value;
        u16 u16_value;
    } unk_2A;
    u8 pad_2C[0x5C];
    union {
        s16 s16_value;
        u16 u16_value;
    } unk_88;
} S_func_819615E4_2;
typedef struct S_func_819615E4_3 {
    void *unk_00;
} S_func_819615E4_3;
typedef struct S_func_819615E4_4 {
    u8 pad_00[8];
    void *unk_08;
    u8 pad_0C[0x18];
    u8 unk_24;
    u8 unk_25;
} S_func_819615E4_4;
typedef struct S_func_819615E4_5 {
    s16 unk_00;
} S_func_819615E4_5;
typedef struct S_func_819615E4_6 {
    s16 unk_00;
} S_func_819615E4_6;
typedef struct {
    u8 pad0[8];
    void *field8;
    void *fieldC;
    void *field10;
    u8 pad14[0xC];
    u32 field20;
} TempObj;
typedef struct {
    u8 pad0[2];
    s16 field2;
    u8 pad4[2];
    s16 field6;
    u8 pad8[2];
    s16 fieldA;
} TempBuffer;
typedef struct {
    u8 pad0[8];
    void *field8;
    u8 padC[8];
    s16 field14;
    u8 pad16[6];
    s16 field1C;
    s16 field1E;
} TempChild;
typedef struct {
    u8 pad0[4];
    s16 field4;
    u8 pad6[2];
    s8 field8;
    s8 field9;
    s8 fieldA;
    s8 fieldB;
    u8 padC[4];
    s16 field10;
    s16 field12;
    s16 field14;
    u8 pad16[2];
    s16 field18;
    s16 field1A;
    s16 field1C;
    u8 pad1E[2];
    s16 field20;
    s16 field22;
    s16 field24;
    u8 pad26[2];
    s16 field28;
    s16 field2A;
    s16 field2C;
    u8 pad2E[0x1E];
    s16 field4C;
} TempOutput;
typedef struct S_819613A8_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_819613A8_0;
typedef struct QuadVertex {
    u32 xy;
    u16 z;
    u16 pad;
} QuadVertex;
typedef struct Quad {
    u8 pad_00[0x10];
    QuadVertex v[4];
} Quad;
typedef struct QuadLink {
    u8 pad_00[0xC];
    struct Material *material;
    u8 pad_10[0x10];
    Quad quad;
} QuadLink;
typedef struct Bank56_819611CC_Scratch {
    u8 pad_00[0x20];
    u32 ot_base;
    u8 pad_24[0x4C];
    QuadVertex v[4];
    s32 out_a;
    s32 out_b;
    u8 pad_98[0x28];
    u32 depth;
} Bank56_819611CC_Scratch;
typedef struct Bank56_819611CC_PolyFT4 {
    u32 tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    u8 u0, v0;
    u16 clut;
    s16 x1, y1;
    u8 u1, v1;
    u16 tpage;
    s16 x2, y2;
    u8 u2, v2;
    u16 pad1;
    s16 x3, y3;
    u8 u3, v3;
    u16 pad2;
} Bank56_819611CC_PolyFT4;
typedef struct Texture {
    u8 pad_00[0x4];
    u16 tpage;
    u8 pad_06[0x2];
    u8 u, v, w, h;
} Texture;
typedef struct Material {
    u8 pad_00[0x8];
    Texture *texture;
    u32 color;
} Material;
typedef struct RenderState {
    u8 pad_00[0x8D0];
    u8 *packet;
} RenderState;
typedef struct S_81960CD4_0 {
    u8 pad_00[0x30];
    u32 unk_30;
    u32 unk_34;
    u32 unk_38;
    u8 pad_3C[0x28];
    u32 unk_64;
    u32 unk_68;
    u32 unk_6C;
    u16 unk_70;
    u16 unk_72;
    u16 unk_74;
    u8 pad_76[0x2];
    u16 unk_78;
    u16 unk_7A;
    u16 unk_7C;
    u8 pad_7E[0x2];
    u16 unk_80;
    u16 unk_82;
    u16 unk_84;
    u8 pad_86[0x2];
    u16 unk_88;
    u16 unk_8A;
    u16 unk_8C;
    u8 pad_8E[0xA];
    u16 unk_98;
    u16 unk_9A;
    u16 unk_9C;
    u8 pad_9E[0x2];
    u16 unk_A0;
    u16 unk_A2;
    u16 unk_A4;
    u8 pad_A6[0x2];
    u16 unk_A8;
    u16 unk_AA;
    u16 unk_AC;
    u8 pad_AE[0x2];
    u16 unk_B0;
    u16 unk_B2;
    u16 unk_B4;
} S_81960CD4_0;
typedef struct S_81960CD4_1_pre {
    u16 unk_00;
} S_81960CD4_1_pre;
typedef struct S_81960CD4_1 {
    u8 pad_00[0x10];
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x2];
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u8 pad_1E[0x2];
    u16 unk_20;
    u16 unk_22;
    u16 unk_24;
    u8 pad_26[0x2];
    u16 unk_28;
    u16 unk_2A;
    u16 unk_2C;
    u8 pad_2E[0x1A];
    union { s16 s; u16 u; } unk_48;   /* accessed as both */
    u8 pad_4A[0x2];
    s16 unk_4C;
} S_81960CD4_1;
typedef struct S_81960CD4_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_81960CD4_2;
typedef struct S_81960CD4_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x7];
    u16 unk_16;
    u16 unk_18;
    u8 pad_1A[0x2];
    u16 unk_1C;
    u16 unk_1E;
} S_81960CD4_3;
typedef union {
    s32 w;
    u16 h[2];
    u8 b[4];
} Word;
typedef struct {
    Word f0;
    Word f4;
    Word f8;
    Word fC;
    Word f10;
    Word f14;
    Word f18;
    Word f1C;
    Word f20;
    Word f24;
} Record;
typedef struct {
    u16 index0;
    u16 index1;
    u16 index2;
    u16 index3;
    s32 value8;
    s32 valueC;
    u16 value10;
    u16 value12;
    u16 value14;
} Input;
typedef struct {
    u8 pad0[0x20];
    s32 value;
    u8 pad24[4];
    u16 h28;
    u16 h2A;
    u16 h2C;
    u8 pad2E[0x22];
    s32 w50;
    u8 pad54[0x10];
    s32 w64;
    s32 w68;
    s32 w6C;
    s32 w70;
    u16 h74;
    u16 pad76;
    s32 w78;
    u16 h7C;
    u16 pad7E;
    s32 w80;
    u16 h84;
    u16 pad86;
    s32 w88;
    u16 h8C;
    u16 pad8E;
    s32 w90;
    s32 w94;
} Bank56_8196096C_Scratch;
typedef struct {
    u8 pad0[0x8D0];
    Record *record;
} Root;
typedef struct TableEntry {
    s32 value;
    s32 pad;
} TableEntry;
typedef struct S_81960530_0 {
    u8 pad_00[0x140];
    union { s16 s; u16 u; } unk_140;   /* accessed as both */
    union { s16 s; u16 u; } unk_142;   /* accessed as both */
    s32 unk_144;
    s32 unk_148;
    s32 unk_14C;
    s16 unk_150;
    union { s16 s; u16 u; } unk_152;   /* accessed as both */
    union {
        struct { u32 v; } at00;
        struct { s16 v; } at00u;
        struct { u16 v; } at00p;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_154;   /* overlapping accesses */
    union {
        struct { u32 v; } at00;
        struct { s16 v; } at00u;
        struct { u16 v; } at00p;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_158;   /* overlapping accesses */
    union {
        struct { u32 v; } at00;
        struct { s16 v; } at00u;
        struct { u16 v; } at00p;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_15C;   /* overlapping accesses */
    union {
        struct { u32 v; } at00;
        struct { s16 v; } at00u;
        struct { u16 v; } at00p;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_160;   /* overlapping accesses */
} S_81960530_0;
typedef struct S_81960530_2 {
    u16 unk_00;
    u16 unk_02;
} S_81960530_2;
typedef struct S_81960530_3 {
    u8 pad_00[0x10];
    u16 unk_10;
} S_81960530_3;
typedef struct S_81960530_4 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
    u8 pad_08[0x8];
    u16 unk_10;
    u8 pad_12[0x4];
    u8 unk_16;
    union { u8 u; s8 s; } unk_17;   /* accessed as both */
} S_81960530_4;
typedef struct S_81960530_5 {
    u32 unk_00;
} S_81960530_5;
typedef struct S_81960530_6 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
} S_81960530_6;
typedef struct S_81960530_7 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
} S_81960530_7;
typedef struct S_81960530_8 {
    u8 pad_00[0x4];
    s16 unk_04;
} S_81960530_8;
typedef struct S_81960530_9 {
    u8 pad_00[0x4];
    s16 unk_04;
} S_81960530_9;
typedef struct {
    u16 *tiles;
    u8 pad04[0x10];
    s16 row_shift;
} DungeonMap;
typedef struct S_819602D8_0 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_819602D8_0;
typedef struct S_8196012C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_8196012C_0;
typedef struct S_8196012C_2 {
    u8 pad_00[0x8];
    void * unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    s16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
    s16 unk_22;
} S_8196012C_2;
typedef struct S_8196012C_3 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x2];
    s8 unk_08;
    s8 unk_09;
    s8 unk_0A;
    s8 unk_0B;
    u8 pad_0C[0x40];
    s16 unk_4C;
} S_8196012C_3;
typedef struct DrawChainNode {
    u8 pad_00[8];
    void *position;
    void *render;
    u8 pad_10[8];
    struct DrawChainNode *next; /* header of the next object in the chain */
    u8 pad_1C[4];
} DrawChainNode;
typedef struct DrawChainRender {
    u8 pad_00[6];
    s16 depth;
} DrawChainRender;
typedef struct S_8195FD40_0 {
    u8 pad_00[0x20];
    u32 unk_20;
    u8 pad_24[0xC];
    u32 unk_30;
    u32 unk_34;
    u32 unk_38;
    u8 pad_3C[0x34];
    u32 unk_70;
    u16 unk_74;
    u8 pad_76[0x2];
    u32 unk_78;
    u16 unk_7C;
    u8 pad_7E[0x2];
    u32 unk_80;
    u16 unk_84;
    u8 pad_86[0x2];
    u32 unk_88;
    u16 unk_8C;
    u8 pad_8E[0x32];
    u32 unk_C0;
    u8 pad_C4[0x20];
    s32 unk_E4;
    s32 unk_E8;
    s32 unk_EC;
    u8 pad_F0[0x10];
    u16 unk_100;
    u16 unk_102;
    u16 unk_104;
} S_8195FD40_0;
typedef struct S_8195FD40_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8195FD40_1;
typedef struct S_8195FD40_3 {
    u8 pad_00[0x8];
    u8 * unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} S_8195FD40_3;
typedef struct S_8195FD40_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_04;   /* overlapping accesses */
    u16 unk_08;
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 pad_0E[0x2];
    u16 unk_10;
    u16 unk_12;
    s8 unk_14;
    u8 unk_15;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u8 unk_1C;
    s8 unk_1D;
    u8 pad_1E[0x2];
    u16 unk_20;
    u16 unk_22;
    s8 unk_24;
    s8 unk_25;
} S_8195FD40_4;
typedef struct S_8195FD40_5 {
    u8 pad_00[0x4];
    u16 unk_04;
    u8 pad_06[0x2];
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
    u8 unk_0B;
} S_8195FD40_5;
typedef struct S_8195FD40_6 {
    u32 unk_00;
} S_8195FD40_6;
typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} Motion;
typedef struct {
    u8 pad0[0xC];
    u8 red;
    u8 green;
    u8 blue;
    u8 padF[7];
    u16 x;
    u16 y;
    u8 pad1A[6];
    u16 dx;
    u16 dy;
} Effect;
typedef struct S_8195FB34_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_8195FB34_0;
typedef struct S_8195FB34_2 {
    u8 pad_00[0x8];
    void * unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0xA];
    s16 unk_1C;
    s16 unk_1E;
} S_8195FB34_2;
typedef struct S_8195FB34_3 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x46];
    s16 unk_4C;
} S_8195FB34_3;
typedef struct S_8195F43C_0 {
    u8 pad_00[0x20];
    u8 * unk_20;
    u8 pad_24[0x10];
    u32 unk_34;
    u8 pad_38[0x18];
    s16 unk_50;
    u8 pad_52[0x6];
    s16 unk_58;
    u8 pad_5A[0x16];
    s16 unk_70;
    s16 unk_72;
    s16 unk_74;
    u8 pad_76[0x2];
    s16 unk_78;
    s16 unk_7A;
    s16 unk_7C;
    u8 pad_7E[0x2];
    s16 unk_80;
    s16 unk_82;
    s16 unk_84;
    u8 pad_86[0x2];
    s16 unk_88;
    s16 unk_8A;
    s16 unk_8C;
    u8 pad_8E[0x32];
    u32 unk_C0;
    u8 pad_C4[0x20];
    s32 unk_E4;
    s32 unk_E8;
    s32 unk_EC;
} S_8195F43C_0;
typedef struct S_8195F43C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8195F43C_1;
typedef struct S_8195F43C_2 {
    u16 unk_00;
    u16 unk_02;
} S_8195F43C_2;
typedef struct S_8195F43C_3 {
    u16 unk_00;
    u16 unk_02;
} S_8195F43C_3;
typedef struct S_8195F43C_5 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u32 unk_0C;
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_8195F43C_5;
typedef struct S_8195F43C_6 {
    u8 pad_00[0x2];
    u8 unk_02;
    u8 unk_03;
    u16 unk_04;
    u8 pad_06[0x2];
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
    u8 unk_0B;
} S_8195F43C_6;
typedef struct S_8195F43C_7 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
    union { u16 u; s16 s; } unk_08;   /* accessed as both */
    union { u16 u; s16 s; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x2];
    u16 unk_0E;
    u16 unk_10;
    u16 unk_12;
    u8 unk_14;
    u8 pad_15[0x3];
    u16 unk_18;
    u16 unk_1A;
    u8 pad_1C[0x1];
    u8 unk_1D;
    u8 pad_1E[0x2];
    union { u16 u; s16 s; } unk_20;   /* accessed as both */
    union { u16 u; s16 s; } unk_22;   /* accessed as both */
    u8 unk_24;
    u8 unk_25;
} S_8195F43C_7;
typedef struct {
    u8 pad0[0x48];
    s16 active;
    u8 pad4A[2];
    u16 timer;
} DungeonState;
typedef struct {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 height;
} DungeonOrigin;
typedef struct {
    u8 pad0[0x10];
    u8 red;
    u8 green;
    u8 blue;
} FadeColor;
typedef struct S_8195EF44_5 {
    u8 pad_00[0x38];
    s16 unk_38;
    s16 unk_3A;
    s16 unk_3C;
    u8 pad_3E[0xE];
    s16 unk_4C;
    u8 pad_4E[0x12];
    s16 unk_60;
    s16 unk_62;
} S_8195EF44_5;
typedef struct S_8195EE48_0 {
    u8 pad_00[0x3C];
    s16 unk_3C;
    u8 pad_3E[0xA];
    s16 unk_48;
    u8 pad_4A[0x2];
    s16 unk_4C;
    u8 pad_4E[0x12];
    s16 unk_60;
    s16 unk_62;
} S_8195EE48_0;
typedef struct S_8195EE48_1 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8195EE48_1;
typedef struct S_8195ED3C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0x18];
    s32 unk_2C;
} S_8195ED3C_0;
typedef struct S_8195ED3C_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    union { struct { void * v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x10];
    s16 unk_1C;
    s16 unk_1E;
} S_8195ED3C_1;
typedef struct S_8195ED3C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8195ED3C_2;
typedef struct S_8195EB88_0_pre {
    u16 unk_00;
} S_8195EB88_0_pre;
typedef struct S_8195EB88_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    u8 pad_10[0x30];
    u16 unk_40;
    u16 unk_42;
    union { s16 s; u16 u; } unk_44;   /* accessed as both */
    u8 pad_46[0x2];
    union { s16 s; u16 u; } unk_48;   /* accessed as both */
    s16 unk_4A;
} S_8195EB88_0;
typedef struct S_8195EB88_1 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_8195EB88_1;
typedef struct S_8195EB88_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8195EB88_2;
typedef struct S_8195EB88_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8195EB88_3;
typedef struct S_8195EB88_4 {
    u8 pad_00[0xC];
    union { u8 u8; u32 u32; } unk_0C;   /* accessed as both */
} S_8195EB88_4;
typedef struct S_8195EB88_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_8195EB88_5;
typedef struct CounterView {
    u16 value;
    u16 pad[5];
} CounterView;
typedef struct FlagsView {
    s32 value;
    s32 pad[2];
} FlagsView;
typedef struct S_8002401C_0 {
    union { void * s; u8 * u; } unk_00;   /* accessed as both */
    u8 * unk_04;
    u8 unk_08;
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    void * unk_0C;
    u8 pad_10[0xC];
    union { s16 s; u16 u; } unk_1C;   /* accessed as both */
} S_8002401C_0;
typedef struct S_8002401C_2_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_8002401C_2_pre;
typedef struct S_8002401C_3 {
    u8 pad_00[0xA6];
    u16 unk_A6;
} S_8002401C_3;
typedef struct S_8002401C_4 {
    u16 unk_00;
} S_8002401C_4;
void update_directional_actor_effect(void *object);
void update_brightening_fading_effect(void *effect, S_8195EB88_2 *position, S_8195EB88_4 *primitive);
void *create_brightening_fading_effect(S_8195ED3C_2 *source, s32 offset);
void update_effect_and_spawn_fragments(S_8195EE48_0 *state, S_8195EE48_1 *motion);
void *allocate_map_cell_object(s16 world_x, s16 world_y, s16 world_z, s16 coord_60);
void animate_tile_heights_and_transition(DungeonState *state, DungeonOrigin *origin);
void project_height_grid_object_quad(void *unused, void *origin, u8 *object, s16 tile_x, s16 tile_y);
s32 dispatch_seven_by_seven_tile_grid(void *tile_data, s32 draw_arg_1, s32 draw_arg_2);
void create_animated_tile_grid(s16 x, s16 y, s16 z);
void advance_ballistic_fading_effect(u16 *state, Motion *motion, Effect *effect);
void draw_depth_biased_textured_quad(s32 unused, S_8195FD40_1 *position, S_8195FD40_3 *quad, s16 depth_bias);
s32 draw_linked_object_chain(void *payload, void *position, void *render);
void set_record_pair_to_one(s16 x, s16 y, s16 z, s16 tile_col, s16 tile_row);
void flag_nearby_seven_by_seven_tiles(s32 input_x, s32 center_y);
void restore_saved_map_tile_region(void);
void *select_containing_cell_surface(s32 world_x, s32 world_y, s16 min_height);
void draw_buffered_textured_quad_pair(void *draw_data, s32 draw_mode);
void build_shaded_textured_quad(s32 y_offset, Input *origin, Input *quad_data, s32 draw_depth);
void create_linked_objects(void *quad, S_81960CD4_2 *motion, S_81960CD4_3 *effect);
s32 project_and_queue_semitransparent_quad(Quad *quad, s32 unused, Material *material);
void create_terrain_tile_quad(s16 tile_x, s32 tile_y, S_819613A8_0 *origin);
void interpolate_target_and_finish_transition(State *state, Target *target, S_func_819615E4_0 *color);
void *allocate_nine_position_objects(void *position);
typedef struct Bank56Counter { u16 value; u16 rest[4]; } Bank56Counter;
extern s16 terrain_effect_update_count;
extern void *D_8002732C;
extern void *D_800273C0;
extern u8 D_80027398[];
extern u16 terrain_effect_height_grid[8][8];
extern s32 D_800274DC[7][8];
extern s32 D_800273A8;
extern Bank56Counter brightening_effect_update_count;
s32 draw_linked_lit_meshes(void *, void *, void *);
s32 resolve_record_orientation_or_fallback(void *, void *, void *, s32);
void draw_textured_ellipse(s32, void *, u16, u16);
void CompMatrix(void *, void *, void *);
void PushMatrix();
void PopMatrix(void);
void ReadRotMatrix(void *);
void ScaleMatrix(void *, void *);
void SetRotMatrix(void *);
void SetTransMatrix(void *);
s32 RotAverage4(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
s32 RotTransPers4(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
void RotMatrix(void *, void *);
void AddPrim(void *, void *);
void SetPolyFT4(void *);
s32 rsin(s32);
s32 rcos(s32);
void *find_eligible_entry_at_coordinates(void *, s32, s32);
s32 get_surface_height_at_coordinates(s32, u16);
s32 are_quad_corner_turns_within_half_revolution(void *);
void initialize_timed_motion_step(s32, s32);
s32 func_80069EF8(void);
s16 calculate_planar_heading(s32, s32, s32, s32);
void apply_attack_power_and_element_effects(void *, s32, s32, s32, s32, s32, s32);
void SetDrawArea(void *, void *, ...);
void spawn_blinking_sprite_flash(s16, s16, s16);
#endif
