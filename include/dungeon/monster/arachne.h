#ifndef DUNGEON_RESOURCE12_SLOT0_H
#define DUNGEON_RESOURCE12_SLOT0_H
#include "common.h"
#include "dungeon/actor.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "records/Rec_D_80082E80.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "m2c_compat.h"
#include "shared/def_table.h"
#include "shared/object_flags.h"
#include "records/Rec_func_801736F4_arg0.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "shared/gpu_packets.h"
#include "sdk/libc.h"
#include "sdk/libgpu.h"
#include "dungeon/system.h"
#include "dungeon/player/object.h"
#include "engine/texture.h"
#include "engine/node/allocation.h"
#include "dungeon/actor/status.h"
struct ObjectPosition;

#define NULL 0
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
typedef s32 R12_8017087C_M2C_UNK;



typedef void (*R12_80170A44_EntityCallback)(void *, void *, void *, void *);
typedef struct R12_80170A44_S_80170A28_0 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} R12_80170A44_S_80170A28_0;
typedef struct R12_80170A44_S_80170A28_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x68];
    u16 unk_88;
} R12_80170A44_S_80170A28_1;
typedef struct R12_80170A44_S_80170A28_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} R12_80170A44_S_80170A28_2;
typedef struct R12_80170E70_S_80170E70_0 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x66];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
} R12_80170E70_S_80170E70_0;
typedef struct R12_80170E70_S_80170E70_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} R12_80170E70_S_80170E70_1;

typedef struct R12_801713D4_S_8017139C_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   
    u8 pad_72[0x18];
    union { s16 s; u16 u; } unk_8A;   
} R12_801713D4_S_8017139C_0;
typedef struct R12_801713D4_S_8017139C_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u16 unk_98;
    u8 unk_9A;
} R12_801713D4_S_8017139C_2;
typedef struct R12_801713D4_S_8017139C_3 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} R12_801713D4_S_8017139C_3;

typedef struct R12_801720B4_S_80172628_0 {
    u8 pad_00[0x46];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x28];
    s8 unk_9A;
} R12_801720B4_S_80172628_0;
typedef struct R12_80172290_S_80172290_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { s16 s; u16 u; } unk_96;   
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s32 unk_A0;
} R12_80172290_S_80172290_0;

typedef struct R12_80172654_S_80172654_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } timer;   
    u8 pad_98[0x3];
    union { u8 s; u8 u; } phase;   
} R12_80172654_S_80172654_0;
typedef struct R12_80172654_S_80172654_1 {
    u8 pad_00[0x2A];
    union { u16 s; s16 u; } unk_2A;   
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    s8 unk_6D;
} R12_80172654_S_80172654_1;
typedef struct R12_80172654_S_80172654_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} R12_80172654_S_80172654_3;
typedef struct R12_80172654_S_80172654_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} R12_80172654_S_80172654_4;
typedef struct R12_80172654_S_80172654_5 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0xC];
    u16 unk_20;
} R12_80172654_S_80172654_5;
typedef struct R12_80172654_S_80172654_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x2];
    s32 unk_08;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u16 unk_10;
    u16 unk_12;
} R12_80172654_S_80172654_6;
typedef struct R12_80172AF8_S_80172AF8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} R12_80172AF8_S_80172AF8_0;
typedef struct R12_80172AF8_S_80172AF8_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} R12_80172AF8_S_80172AF8_2_pre;
typedef struct R12_80172AF8_S_80172AF8_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} R12_80172AF8_S_80172AF8_3;

typedef struct R12_80172AF8_S_80172AF8_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} R12_80172AF8_S_80172AF8_7;
typedef struct R12_80172FE8_S_801730B8_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } timer;   
    u8 pad_98[0x3];
    u8 phase;
} R12_80172FE8_S_801730B8_1;
typedef struct {
    u8 pad0[0x96];
    u16 countdown;
    u8 pad98[3];
    u8 state;
    u8 pad9C[8];
    u16 timer;
} R12_801732EC_EffectState;
typedef struct {
    u8 pad0[4];
    s8 type;
    u8 pad5[7];
    s32 value;
    u16 field10;
    u16 field12;
    u16 flags;
    u8 pad16[0xE];
    u8 x;
    u8 y;
    u8 pad26[6];
    u8 *table;
} R12_801732EC_Entity;
typedef struct {
    u8 pad0[0x14];
    s32 field14;
    u8 pad18[4];
    s32 flags;
    u8 pad20[0xA];
    s16 angle;
} R12_801732EC_Object;
typedef struct R12_8017368C_S_80173358_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} R12_8017368C_S_80173358_0;
typedef struct R12_8017368C_S_80173358_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
} R12_8017368C_S_80173358_1;
typedef struct R12_8017368C_S_80173358_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} R12_8017368C_S_80173358_2;



typedef struct {
    u8 bytes[8];
} R12_80173FDC_Header8;
typedef struct {
    s16 x;
    u16 y;
    s16 z;
    s16 pad;
} R12_80173FDC_GridPoint;
typedef struct {
    R12_80173FDC_GridPoint *points0;
    R12_80173FDC_GridPoint *points1;
    s16 value;
    s16 zero;
    s16 angle;
    s16 pad0E;
    R12_80173FDC_Header8 header;
    s16 count;
    s16 one;
    s32 pad1C;
} R12_80173FDC_WorkDesc;
typedef struct {
    R12_80173FDC_WorkDesc desc;
    R12_80173FDC_GridPoint points[8][8];
} R12_80173FDC_Frame;
typedef struct {
    u8 *ptr;
} R12_80173FDC_RootSlot;
typedef struct {
    u32 tag;
    u32 color0;
    u32 xy0;
    u32 color1;
    u32 xy1;
} R12_80173FDC_LineG2;
typedef struct R12_80173FDC_S_80173FDC_0_pre {
    u8 * unk_00;
    u8 pad_04[0x4];
} R12_80173FDC_S_80173FDC_0_pre;
typedef struct R12_80173FDC_S_80173FDC_0 {
    u8 pad_00[0x10];
    u16 unk_10;
    s16 unk_12;
} R12_80173FDC_S_80173FDC_0;
typedef struct R12_80173FDC_S_80173FDC_1 {
    u8 pad_00[0x8];
    u32 unk_08;
    u8 pad_0C[0x2];
    s16 unk_0E;
} R12_80173FDC_S_80173FDC_1;
typedef struct R12_80173FDC_S_80173FDC_2_pre {
    s16 unk_00;
    u8 pad_02[0xE];
} R12_80173FDC_S_80173FDC_2_pre;
typedef struct R12_80173FDC_S_80173FDC_2 {
    s16 unk_00;
} R12_80173FDC_S_80173FDC_2;
typedef struct R12_80173FDC_S_80173FDC_3 {
    u8 pad_00[0x8D0];
    union { R12_80173FDC_LineG2 * p; u8 * p2; } unk_8D0;   
} R12_80173FDC_S_80173FDC_3;
typedef struct R12_80173FDC_S_80173FDC_4_pre {
    u32 unk_00;
    u8 pad_04[0x1C];
} R12_80173FDC_S_80173FDC_4_pre;
typedef struct R12_80173FDC_S_80173FDC_4 {
    u32 unk_00;
} R12_80173FDC_S_80173FDC_4;
typedef struct R12_80173FDC_S_80173FDC_5 {
    u32 unk_00;
} R12_80173FDC_S_80173FDC_5;
typedef struct R12_80173FDC_S_80173FDC_6 {
    s16 unk_00;
} R12_80173FDC_S_80173FDC_6;
typedef struct R12_80173FDC_S_80173FDC_7 {
    u32 unk_00;
} R12_80173FDC_S_80173FDC_7;
typedef struct R12_80173FDC_S_80173FDC_8 {
    u8 pad_00[0x8];
    u8 * unk_08;
} R12_80173FDC_S_80173FDC_8;
typedef struct R12_8017458C_Entry {
    u8 pad00[6];
    s16 unk06;
    void *unk08;
    struct R12_8017458C_Entry *unk0C;
    u8 pad10[4];
    u16 unk14;
} R12_8017458C_Entry;
typedef struct {
    u8 pad[0x13C];
    s32 value;
} R12_8017458C_Scratchpad;

typedef struct R12_80174618_S_80174618_0 {
    u8 pad_00[0x24];
    union { u8 * s; u32 * u; } unk_24;   
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
} R12_80174618_S_80174618_0;
typedef struct R12_80174618_S_80174618_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} R12_80174618_S_80174618_1;
typedef struct R12_80174618_S_80174618_2 {
    u8 pad_00[0xC];
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_0C;   
    u8 pad_10[0x4];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
} R12_80174618_S_80174618_2;
typedef struct R12_80174618_S_80174618_4 {
    u8 pad_00[0x64];
    u16 unk_64;
    u16 unk_66;
    u16 unk_68;
    u16 unk_6A;
    u16 unk_6C;
    u16 unk_6E;
} R12_80174618_S_80174618_4;
typedef struct R12_80174618_S_80174618_5 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_00;   
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_04;   
} R12_80174618_S_80174618_5;
typedef struct {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} R12_80174618_MATRIX;
typedef struct {
} R12_80174618_EMPTY_ARG;
typedef struct {
    u32 addr : 24;
    u32 len : 8;
} R12_80174618_P_TAG;
typedef struct R12_80174954_Func800C138CData {
    u8 pad0[8];
    void *context;
    void *data;
} R12_80174954_Func800C138CData;
typedef struct R12_801749A8_S_801748F0_0 {
    u16 unk_00;
    u8 pad_02[0x1A];
    u16 unk_1C;
} R12_801749A8_S_801748F0_0;
typedef struct R12_801749EC_S_801749EC_0 {
    u8 pad_00[0x6];
    s16 unk_06;
} R12_801749EC_S_801749EC_0;
typedef struct R12_801749EC_S_801749EC_1_pre {
    u16 unk_00;
} R12_801749EC_S_801749EC_1_pre;
typedef struct R12_801749EC_S_801749EC_1 {
    u8 pad_00[0x6];
    u16 unk_06;
    s16 unk_08;
    u8 pad_0A[0x2];
    u16 unk_0C;
} R12_801749EC_S_801749EC_1;
typedef struct R12_801749EC_S_801749EC_2_pre {
    u16 unk_00;
} R12_801749EC_S_801749EC_2_pre;
typedef struct R12_801749EC_S_801749EC_2 {
    s16 unk_00;
} R12_801749EC_S_801749EC_2;

typedef struct R12_801749EC_S_801749EC_4 {
    s16 unk_00;
    u16 unk_02;
} R12_801749EC_S_801749EC_4;

typedef struct R12_801749EC_S_801749EC_6 {
    u8 pad_00[0x1A];
    s16 unk_1A;
    s16 unk_1C;
    u8 pad_1E[0x46];
    u16 unk_64;
    u16 unk_66;
    u16 unk_68;
    u16 unk_6A;
    u16 unk_6C;
    u16 unk_6E;
} R12_801749EC_S_801749EC_6;
typedef struct R12_801749EC_S_801749EC_7 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 * unk_10;
} R12_801749EC_S_801749EC_7;

typedef struct R12_801749EC_S_801749EC_9 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} R12_801749EC_S_801749EC_9;
typedef struct R12_801749EC_S_801749EC_10 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} R12_801749EC_S_801749EC_10;
typedef struct R12_801749EC_S_801749EC_11 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} R12_801749EC_S_801749EC_11;
typedef struct R12_801749EC_S_801749EC_12 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} R12_801749EC_S_801749EC_12;
typedef struct R12_801749EC_S_801749EC_13 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} R12_801749EC_S_801749EC_13;
typedef struct R12_801749EC_S_801749EC_14 {
    u8 pad_00[0x1A];
    s16 unk_1A;
    s16 unk_1C;
    u8 pad_1E[0x46];
    u16 unk_64;
    u16 unk_66;
    u16 unk_68;
    u16 unk_6A;
    u16 unk_6C;
    u16 unk_6E;
} R12_801749EC_S_801749EC_14;
typedef struct R12_801749EC_S_801749EC_15 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 * unk_10;
} R12_801749EC_S_801749EC_15;

typedef struct R12_801749EC_S_801749EC_17 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} R12_801749EC_S_801749EC_17;

typedef struct R12_801749EC_S_801749EC_19 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} R12_801749EC_S_801749EC_19;
typedef struct R12_801749EC_S_801749EC_20 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} R12_801749EC_S_801749EC_20;
typedef struct R12_801749EC_S_801749EC_21 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} R12_801749EC_S_801749EC_21;
typedef struct R12_80175180_S_80175180_0 {
    u8 pad_00[0x8];
    s16 unk_08;
    u16 unk_0A;
    s16 unk_0C;
} R12_80175180_S_80175180_0;
typedef struct R12_80175180_S_80175180_1 {
    u8 pad_00[0x96];
    u16 unk_96;
} R12_80175180_S_80175180_1;
typedef struct R12_80175180_S_80175180_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} R12_80175180_S_80175180_2;
typedef struct R12_80175180_S_80175180_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} R12_80175180_S_80175180_4;
typedef struct R12_80175180_S_80175180_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} R12_80175180_S_80175180_5;

typedef struct R12_80175470_S_80175470_0_pre {
    u16 unk_00;
} R12_80175470_S_80175470_0_pre;
typedef struct R12_80175470_S_80175470_0 {
    u8 pad_00[0x96];
    union { u16 u; s16 s; } timer;   
    u8 pad_98[0x3];
    union { u8 n; u8 v; } phase;   
    u8 pad_9C[0xC];
    void * unk_A8;
    s16 unk_AC;
} R12_80175470_S_80175470_0;
typedef struct R12_80175470_S_80175470_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x16];
    union { u16 u; s16 s; } unk_2A;   
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x1C];
    u16 unk_8A;
} R12_80175470_S_80175470_1;
typedef struct R12_80175470_S_80175470_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    union { void * p; u32 i; } unk_10;   
    u8 pad_14[0x16];
    s16 unk_2A;
} R12_80175470_S_80175470_2;
typedef struct R12_80175470_S_80175470_5_pre {
    void * unk_00;
    u8 pad_04[0x10];
} R12_80175470_S_80175470_5_pre;
typedef struct R12_80175470_S_80175470_5 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} R12_80175470_S_80175470_5;
extern int abs(int);
s32 Control_CD();
void * func_8003FD64(s32 flags, ObjectNodeHeader **list_head);
s32 register_node(ObjectNodeHeader *entry, void *registration_id);
s32 func_8004491C(struct ObjectNodeHeader *entry, void *registration_id);
s32 generate_random_value(void);
void initialize_actor_sprite_and_animation(void *entity, void *position, SpriteFrameState *sprite, s32 init_flags);
void advance_sprite_animation_and_textures(void *entity);
s32 refresh_actor_facing_and_lifecycle();
s16 sample_terrain_surface_height();
void select_sprite_entry(void *object_data, s16 table_index, s16 entry_index);
void func_80047784(void *object_data, s16 table_index, s16 entry_index);
s32 check_entity_relation();
s32 find_active_rect_containing_point(s32 point_x, s32 point_y);
s32 can_entity_gain_level(void *entity);
void update_actor_status_and_mp(ActorRecord *entity);
s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
void cycle_map_cell_flags(s16 x, s16 y, u16 flags);
void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
s32 check_movement_clearance_and_height();
s32 update_actor_proximity_flag(void *source, void *state, s32 lower_limit, s32 upper_limit, s8 *result);
s16 get_actor_height_difference(ActorRecord *left_record, ActorRecord *right_record);
s16 check_diagonal_side_height(s32 direction, s16 tile_x, s16 tile_y, s16 height);
s32 prepare_directional_attack();
s16 try_claim_dungeon_action_slot(ActorRecord *actor);
u32 check_entity_interaction_compatibility();
#include "dungeon/player/object/action_state.h"
struct Entry;
struct ObjectNodeHeader;
struct ObjectNodeHeader;
s32 update_actor_movement_to_tile(void *move_state, void *motion, void *target_tile, ActorRecord *actor);
void spend_actor_mp(ActorRecord *entity, s32 base_reduction);

void func_800A9A04(void *actor);
s32 resolve_record_orientation_or_fallback();
s32 get_cd_command_queue_depth(void);
void create_two_row_object_group(void *payload, s16 value_scale);
void unlink_entity_node();
void * detach_record_and_update_slot_state(void *record);
s32 update_actor_hop_and_shrink(void *animation, void *motion, SpriteFrameState *scale, void *render);

s32 get_entity_effect_value(ActorRecord *entry, s32 effect_id);
s32 func_80042900(ActorRecord *entry, s32 effect_id);
void clear_slots_of_type(ActorRecord *owner, s8 match_type);
void func_80042B68(ActorRecord *owner, s8 match_type);
s32 get_tile_chebyshev_distance();

s32 update_actor_transform_from_parent();
s32 interpolate_actor_to_terrain_tile();
s32 update_spinning_actor_fall();
s32 update_actor_fade_in();
s32 rsin(s32);
s32 rcos(s32);
void func_80065770();
s32 ratan2(s32, s32);
void transform_rotated_vertices(void *transform_data);
void func_800453E0(void *context, void *position, struct Entry *entry, s16 depth_bias);
void * CompMatrix(void *, void *, void *);
void PushMatrix(void);
void PopMatrix(void);
void * ReadRotMatrix(void *);
void * ScaleMatrix(void *, void *);
void SetRotMatrix(void *);
void SetTransMatrix(void *);
s32 RotAverage4();
void * RotMatrix(void *, void *);
void unlink_node();
void func_80044A50(struct ObjectNodeHeader *node);
void select_record_entry_and_value(void *state, void *entries, short index);
void sound_set_cd_cue_parameters(int value_0, int value_1, int value_2, int value_3);
void func_80041588(u32 *stream_ref, u8 *state, s32 execute);
s32 read_stream_cue_start_offset(void);
s32 lookup_masked_byte_table();
void decrement_monster_entry_count(s16 requested_id, s16 requested_type);
s32 create_status_linked_render_effect();
s32 propagate_actor_action_flag(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern u8 arachne_direction_frames[];
extern u8 arachne_alt_direction_frames[];
extern u8 D_80175AAC[];
extern u8 D_80175A5C[];
extern u8 arachne_frame_set[];
extern u8 arachne_reset_frames[];
extern u8 arachne_move_direction_frames[];
extern u8 actor_turn_angle_offsets[];
extern u8 D_80175A64[];
extern u8 D_80175A6C[];
extern u8 D_80175A74[];
extern u8 actor_update_node_cursor[];
extern u8 D_80175AA4[];
extern u8 D_80175B20[];
extern u8 actor_action_reset_value[];
extern u8 D_80175B28[];
extern u8 resource_completion_callback_address[];
extern u8 cd_cue_base[];
extern u8 actor_effect_color_targets[];
extern u8 staged_spawn_count[];
extern u8 dungeon_resource_buffer[];
extern u8 arachne_image_commands[];
extern u8 D_80175B14[];
extern u8 arachne_image_load_done[];
extern u8 arachne_effect_load_done[];
void *spawn_animated_monster(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c);
void create_directional_template_effect(void *entity, R12_80170A44_S_80170A28_2 *motion, void *part);
void update_actor_state_and_select_target(ActorRecord *entity, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *actor);
void advance_actor_path_script_step(void *controller, ObjectPosition *context, void *entity, void *path_state);
void choose_arachne_move(ActorRecord *move_data, ObjectPosition *context, SpriteFrameState *position_data, ActorRecord *actor_data);
void advance_linked_actor_motion_script(void *object, ObjectPosition *unused, void *display, void *orientation);
s32 try_arachne_attack(ActorRecord *action_state, ObjectPosition *motion_param, SpriteFrameState *sprite, ActorRecord *actor);
void select_and_start_target_action(ActorRecord *action_state, ObjectPosition *action_context, void *sprite, ActorRecord *actor);
s32 relink_arachne_path(void *entity_arg, ObjectPosition *primary_context_arg, void *secondary_context_arg, s32 force_state_arg);
void finish_actor_tile_move_then_select_target(ActorRecord *state, ObjectPosition *context, SpriteFrameState *source, ActorRecord *target);
void complete_actor_arc_movement(void *action, void *motion, void *map_actor, void *actor);
void check_boss_effect_threshold(ActorRecord *state, ObjectPosition *entity, SpriteFrameState *position, ActorRecord *graphic);
void advance_action_and_spawn_effect(void *action, void *motion, void *entity, void *actor);
void advance_actor_motion_and_wait(void *action, void *transform, void *sprite, ActorRecord *actor);
void apply_knockback_then_restore_target_selection(R12_80172FE8_S_801730B8_1 *action, ObjectPosition *motion, SpriteFrameState *entity, void *source);
void advance_entity_fade_effect(R12_801732EC_EffectState *effect, void *unused, R12_801732EC_Entity *entity, R12_801732EC_Object *object);
void advance_familiar_defeat_sequence(void *state, void *motion, void *position, void *actor);
void advance_arachne_removal(void *state, void *motion, void *position, void *actor);
void finish_actor_hop_and_grow_then_select_target(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void advance_arachne_status_action(void *in_controller, ObjectPosition *in_context, void *sprite, ActorRecord *in_actor);
void resume_actor_target_selection_after_status_animation(ActorRecord *controller, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);
void update_arachne_parent_motion(ActorRecord *actor, ObjectPosition *action, SpriteFrameState *entity, ActorRecord *map_object);
void finish_thrown_actor_travel_and_floor_trap_then_select_target(ActorRecord *state, ObjectPosition *entity, SpriteFrameState *position, ActorRecord *graphic);
void finish_actor_terrain_interpolation_then_select_target(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void finish_spinning_actor_fall_then_select_target(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void finish_actor_fade_in_then_select_target(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void dim_effect_after_delay(void *effect);
s32 build_linked_curved_wireframe_grid(u8 *node, s32 next_node, s32 unused_2);
s32 project_arachne_sprite_chain(void *initial_payload, s32 entry_data, R12_8017458C_Entry *entry, s32 unused);
void transform_and_queue_line_packets(R12_80174618_S_80174618_4 *endpoints, R12_80174618_S_80174618_1 *position, void *render_params, s16 depth_bias);
s32 queue_line_packets_for_node_chain(void *initial_state, void *context, void *data);
void update_turning_fade_effect_and_model(void *record_data);
void build_animated_spherical_wireframe(void *effect, void *origin, void *tint);
void create_offset_effect(void *source_arg, void *spawn_pos_arg, void *unused_context);
void wait_for_arachne_activity(void *entity_data, ObjectPosition *unused_1, s32 unused_2, void *other_data);
void fade_effect_to_neutral(void *entity_data, void *unused, void *source_data);
void advance_effect_sequence_and_restore_actor(void *sequence, void *position, SpriteFrameState *record, void *actor);
void finish_actor_floor_trap_then_select_target(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void finish_actor_action_flag_propagation_then_select_target(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *position, ActorRecord *actor);
void *spawn_arachne(s16 spawn_flags, s16 tile_x, s16 tile_y, s16 spawn_height);

#endif
