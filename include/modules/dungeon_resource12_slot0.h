#ifndef DUNGEON_RESOURCE12_SLOT0_H
#define DUNGEON_RESOURCE12_SLOT0_H
#include "common.h"
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

#define NULL 0
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
typedef s32 R12_8017087C_M2C_UNK;
typedef struct R12_8017087C_S_8017087C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} R12_8017087C_S_8017087C_0;
typedef struct R12_8017087C_S_8017087C_1 {
    u8 pad_00[0xA];
    s16 unk_0A;
} R12_8017087C_S_8017087C_1;
typedef struct R12_8017087C_Work {
    u8 pad0[0x13];
    s8 byte13;
    s32 flags14;
    u8 pad18[4];
    s32 flags1c;
    u8 pad20[0x6C];
    void *ptr8c;
    u8 pad90[0xA];
    u8 byte9a;
    u8 pad9b;
    s8 byte9c;
} R12_8017087C_Work;
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
typedef struct R12_80170E70_S_80170E70_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   
    s8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} R12_80170E70_S_80170E70_2;
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
typedef struct R12_8017162C_S_80171C34_1 {
    u8 pad_00[0x12];
    u8 unk_12;
    u8 pad_13[0x1];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { s16 s; u16 u; } unk_2A;   
    u8 pad_2C[0x19];
    u8 unk_45;
    u16 unk_46;
    u8 pad_48[0x25];
    union { u8 u; s8 s; } unk_6D;   
    u8 pad_6E[0x3];
    union { s8 s; u8 u; } unk_71;   
    u8 pad_72[0x16];
    union { u16 u; s16 s; } unk_88;   
} R12_8017162C_S_80171C34_1;
typedef struct R12_8017162C_S_80171C34_2 {
    u8 pad_00[0x24];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   
    union { s8 s; u8 u; } unk_26;   
} R12_8017162C_S_80171C34_2;
typedef struct R12_8017162C_S_80171C34_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} R12_8017162C_S_80171C34_3_pre;
typedef struct R12_8017162C_S_80171C34_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} R12_8017162C_S_80171C34_3;
typedef struct R12_8017162C_S_80171C34_5 {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0x2];
    union { s8 s; u8 u; } unk_9C;   
} R12_8017162C_S_80171C34_5;
typedef struct R12_8017162C_S_80171C34_7 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} R12_8017162C_S_80171C34_7;
typedef struct R12_8017162C_S_80171C34_8 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} R12_8017162C_S_80171C34_8;
typedef struct R12_8017162C_DungeonRecord {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} R12_8017162C_DungeonRecord;
typedef struct R12_80171F9C_Ent R12_80171F9C_Ent;
typedef struct R12_801720B4_S_80172628_0 {
    u8 pad_00[0x46];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x28];
    s8 unk_9A;
} R12_801720B4_S_80172628_0;
typedef struct R12_801721F8_S_801724A8_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_90;   
} R12_801721F8_S_801724A8_0;
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
typedef struct {
    u8 pad0[0x8C];
    void (*callback)(void *, void *, void *, void *);
} Resource12CallbackState;
typedef struct R12_80172654_S_80172654_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   
    u8 pad_98[0x3];
    union { u8 s; u8 u; } unk_9B;   
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
    union { s16 s; u16 u; } unk_96;   
    u8 pad_98[0x3];
    u8 unk_9B;
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
    s8 pad_00[0x8C];
    void *unk_8C;
} R12_80173D64_Actor;
typedef struct {
    u8 pad_00[0x2C];
    u8 *unk_2C;
} R12_80173D64_Entity;
typedef struct {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} R12_80173D64_MapObject;
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
typedef struct {
    u8 pad[0x5218];
    s16 value;
} R12_8017458C_GlobalPage;
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
typedef struct R12_801749EC_S_801749EC_3 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
} R12_801749EC_S_801749EC_3;
typedef struct R12_801749EC_S_801749EC_4 {
    s16 unk_00;
    u16 unk_02;
} R12_801749EC_S_801749EC_4;
typedef struct R12_801749EC_S_801749EC_5 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
} R12_801749EC_S_801749EC_5;
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
typedef struct R12_801749EC_S_801749EC_8 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} R12_801749EC_S_801749EC_8;
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
typedef struct R12_801749EC_S_801749EC_16 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} R12_801749EC_S_801749EC_16;
typedef struct R12_801749EC_S_801749EC_17 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} R12_801749EC_S_801749EC_17;
typedef struct R12_801749EC_S_801749EC_18 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} R12_801749EC_S_801749EC_18;
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
typedef struct {
    u8 pad0[2];
    u16 flags;
    u8 pad4[6];
    u16 count;
} R12_8017526C_DungeonState;
typedef struct R12_80175470_S_80175470_0_pre {
    u16 unk_00;
} R12_80175470_S_80175470_0_pre;
typedef struct R12_80175470_S_80175470_0 {
    u8 pad_00[0x96];
    union { u16 u; s16 s; } unk_96;   
    u8 pad_98[0x3];
    union { u8 n; u8 v; } unk_9B;   
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
s32 allocate_list_node();
s32 func_8003FD64();
s32 register_node();
s32 func_8004491C();
s32 generate_random_value();
s32 set_or_clear_actor_status_slot();
void initialize_actor_sprite_and_animation();
s32 try_move_actor_to_valid_position();
void select_indirect_table_entry();
void func_800478B8();
void apply_monster_koyaw_data();
s32 refresh_actor_facing_and_lifecycle();
s16 sample_terrain_surface_height();
s32 select_sprite_entry();
s32 func_80047784();
s32 check_entity_relation();
s32 find_active_rect_containing_point();
s32 compare_monster_neighbor_values();
s32 get_rounded_facing_and_rounding_flag();
s32 can_entity_gain_level();
void update_actor_status_and_food();
void begin_pushed_actor_move();
s32 begin_ready_actor_directional_action();
s32 advance_actor_pending_action();
void begin_actor_move_to_target_facing();
s32 reset_actor_action_state();
s32 process_selected_actor_record();
void begin_actor_spell_action();
s32 cycle_map_cell_flags();
s32 update_map_cell_flags_with_item_limit();
s32 check_movement_clearance_and_height();
s32 update_actor_proximity_flag();
s32 find_valid_monster_neighbor();
s32 place_actor_at_directional_neighbor();
s32 get_actor_height_difference();
s32 check_diagonal_side_height();
s32 rebuild_monster_reachable_tiles();
s32 prepare_directional_attack();
s32 try_claim_dungeon_action_slot();
u32 check_entity_interaction_compatibility();
s32 apply_camera_offset_and_select_target();
s32 has_pending_dungeon_activity();
s32 relink_entity_and_clear_high_flag();
s32 advance_status_timers();
s32 update_actor_movement_to_tile();
void reduce_actor_food_meter();
s32 check_actor_floor_trap();
void set_record_integer_tile_center();
s32 on_actor_status_updated();
s32 func_800A9A04();
s32 update_linked_actor_motion();
s32 resolve_record_orientation_or_fallback();
s32 resolve_attack_damage_and_effects();
s32 play_sound_if_enabled();
s32 get_cd_command_queue_depth();
s32 scan_monster_along_heading();
s32 create_actor_spell_effect();
void create_two_row_object_group();
void begin_actor_display_action();
void apply_clamped_actor_value_delta();
void unlink_entity_node();
void distribute_experience_and_report_gains();
s32 detach_record_and_update_slot_state();
void announce_familiar_defeat();
s32 update_actor_hop_and_shrink();
s32 advance_actor_removal();
s32 update_actor_hop_and_grow();
s32 get_entity_effect_value();
s32 func_80042900();
void clear_slots_of_type();
void func_80042B68();
s32 get_tile_chebyshev_distance();
s32 has_pending_actor_or_turn_action();
s32 update_actor_transform_from_parent();
s32 update_thrown_actor_travel();
s32 interpolate_actor_to_terrain_tile();
s32 update_spinning_actor_fall();
s32 update_actor_fade_in();
s32 func_800644B8();
s32 func_80064584();
void func_80065770();
s32 func_80065F90();
s32 func_80066460();
void func_80066640();
void func_800667D0();
void func_80067F20();
void transform_rotated_vertices();
void project_sprite_commands();
void func_800453E0();
void func_80064840();
void func_800649A0();
void func_80064A40();
void func_80064AE0();
void func_80064BC0();
void func_80064CF0();
void func_80064D80();
s32 func_80065590();
void func_80065820();
void unlink_node();
void func_80044A50();
void func_8003DB94();
void sound_set_cd_cue_parameters();
void run_cd_image_commands();
void func_80041588();
s32 func_800445E0();
s32 lookup_masked_byte_table();
s32 func_80069EF8();
void decrement_monster_entry_count();
s32 advance_staged_entity_load();
s32 create_status_linked_render_effect();
s32 select_nearby_target_and_initialize_slot();
s32 resolve_actor_floor_trap_once();
s32 propagate_actor_action_flag();
extern u8 D_80175A54[];
extern u8 D_80175A9C[];
extern u8 D_80175AAC[];
extern u8 D_80175A5C[];
extern u8 D_80175A8C[];
extern u8 D_80175A94[];
extern u8 D_80175A4C[];
extern u8 D_8006CD00[];
extern u8 D_80175A64[];
extern u8 D_80175A6C[];
extern u8 D_80175A74[];
extern u8 D_800E3DE8[];
extern u8 D_80175AA4[];
extern u8 D_80175B20[];
extern u8 D_800DCF5E[];
extern u8 D_80175B28[];
extern u8 D_8003E140[];
extern u8 D_8006CD58[];
extern u8 D_800DCEEC[];
extern u8 D_800DCF5C[];
extern u8 D_8014A000[];
extern u8 D_80175B0C[];
extern u8 D_80175B14[];
extern u8 D_80175B24[];
extern u8 D_80175B25[];
void *func_8017087C(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c);
void create_directional_template_effect(void *entity, R12_80170A44_S_80170A28_2 *motion, void *part);
void update_actor_state_and_select_target(void *entity, void *context, void *sprite, void *actor);
void advance_actor_path_script_step(void *controller, void *context, void *entity, void *path_state);
void func_8017162C(void *move_data, void *context, void *position_data, void *actor_data);
void advance_linked_actor_motion_script(void *object, void *unused, void *display, void *orientation);
s32 func_80171DD8(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, SpriteFrameState *sprite, EntityRec *actor);
void select_and_start_target_action(void *action_state, void *action_context, void *sprite, EntityRec *actor);
s32 func_801720B4(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg);
void func_801721F8(R12_801721F8_S_801724A8_0 *state, s32 context, s32 source, s32 target);
void complete_actor_arc_movement(void *action, void *motion, void *map_actor, void *actor);
void check_boss_effect_threshold(Resource12CallbackState *state, void *entity, void *position, void *graphic);
void advance_action_and_spawn_effect(void *action, void *motion, void *entity, void *actor);
void advance_actor_motion_and_wait(void *action, void *transform, void *sprite, EntityRec *actor);
void func_80172FE8(R12_80172FE8_S_801730B8_1 *action, EntityRec *motion, SpriteFrameState *entity, void *source);
void advance_entity_fade_effect(R12_801732EC_EffectState *effect, void *unused, R12_801732EC_Entity *entity, R12_801732EC_Object *object);
void advance_familiar_defeat_sequence(void *state, void *motion, void *position, void *actor);
void func_80173634(void *state, void *motion, void *position, void *actor);
void func_80173654(Resource12CallbackState *state, void *motion, void *position, void *actor);
void func_8017368C(void *in_controller, void *in_context, void *sprite, void *in_actor);
void func_80173A28(void *controller, void *context, void *sprite, EntityRec *entity);
void func_80173D64(R12_80173D64_Actor *actor, s32 action, R12_80173D64_Entity *entity, R12_80173D64_MapObject *map_object);
void func_80173E2C(Resource12CallbackState *state, void *entity, void *position, void *graphic);
void func_80173E90(Resource12CallbackState *state, void *motion, void *position, void *actor);
void func_80173EC8(Resource12CallbackState *state, void *motion, void *position, void *actor);
void func_80173F00(Resource12CallbackState *state, void *motion, void *position, void *actor);
void dim_effect_after_delay(void *effect);
s32 build_linked_curved_wireframe_grid(u8 *node, s32 next_node, s32 callback_arg2);
s32 func_8017458C(void *initial_payload, s32 entry_data, R12_8017458C_Entry *entry, s32 unused);
void transform_and_queue_line_packets(R12_80174618_S_80174618_4 *endpoints, R12_80174618_S_80174618_1 *position, void *render_params, s16 depth_bias);
s32 func_80174954(void *initial_state, void *context, void *data);
void update_turning_fade_effect_and_model(void *record_data);
void build_animated_spherical_wireframe(void *effect, void *origin, void *tint);
void create_offset_effect(void *source_arg, void *spawn_pos_arg, void *unused_context);
void func_8017526C(void *entity_data, s32 unused_1, s32 unused_2, void *other_data);
void fade_effect_to_neutral(void *entity_data, void *unused, void *source_data);
void advance_effect_sequence_and_restore_actor(void *sequence, void *position, SpriteFrameState *record, void *actor);
void func_801759DC(Resource12CallbackState *state, void *motion, void *position, void *actor);
void func_80175A14(Resource12CallbackState *state, void *motion, void *position, void *actor);
#endif
