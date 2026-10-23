#ifndef DUNGEON_RESOURCE06_SLOT0_H
#define DUNGEON_RESOURCE06_SLOT0_H
#include "common.h"
#include "dungeon/actor.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dir_step.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "shared/def_table.h"
#include "shared/object_flags.h"
#include "records/Rec_func_800AB538_arg0.h"
#include "shared/gpu_packets.h"
struct SpriteFrameState;
struct ObjectPosition;

#define U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))
#define NULL 0
typedef struct R06_8017087C_S_8017087C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} R06_8017087C_S_8017087C_0;
typedef struct R06_8017087C_S_8017087C_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} R06_8017087C_S_8017087C_1;
typedef struct R06_8017087C_S_8017087C_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} R06_8017087C_S_8017087C_2;
typedef struct R06_8017087C_S_8017087C_4 {
    u8 pad_00[0x9A];
    u8 unk_9A;
    u8 pad_9B[0x9];
    void * unk_A4;
} R06_8017087C_S_8017087C_4;
typedef struct R06_8017087C_S_8017087C_5 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x4];
    u16 unk_98;
    u8 pad_9A[0x2];
    s8 unk_9C;
    u8 pad_9D[0x1];
    s16 unk_9E;
} R06_8017087C_S_8017087C_5;
typedef struct R06_8017087C_S_8017087C_6 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x90];
    void * unk_98;
} R06_8017087C_S_8017087C_6;
typedef struct R06_8017087C_S_8017087C_7 {
    u8 pad_00[0xC];
    u32 unk_0C;
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x12];
    s32 unk_28;
} R06_8017087C_S_8017087C_7;
typedef struct R06_8017087C_S_8017087C_8 {
    u8 pad_00[0xA4];
    void * unk_A4;
} R06_8017087C_S_8017087C_8;
typedef struct R06_8017087C_S_8017087C_9 {
    u8 pad_00[0x10];
    void * unk_10;
} R06_8017087C_S_8017087C_9;
typedef void (*R06_80170BB8_Callback)(void *, void *, void *, void *);
typedef struct R06_80170BB8_S_80170BB8_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} R06_80170BB8_S_80170BB8_0;
typedef struct R06_80170BB8_S_80170BB8_1 {
    u8 pad_00[0x1C];
    union { u32 u; s32 s; } unk_1C;   
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} R06_80170BB8_S_80170BB8_1;
typedef struct R06_80170BB8_S_80170BB8_2 {
    u8 pad_00[0xC];
    union { u32 u32; u8 u8; } unk_0C;   
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x26];
    u32 unk_3C;
} R06_80170BB8_S_80170BB8_2;
typedef struct R06_80170BB8_S_80170BB8_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u16 unk_04;
} R06_80170BB8_S_80170BB8_3;
typedef struct R06_80170BB8_S_80170BB8_4 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} R06_80170BB8_S_80170BB8_4;
typedef struct R06_8017140C_S_8017140C_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    union { u16 u; s16 s; } unk_92;   
    u8 pad_94[0x4];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x1A];
    union { s16 s; u16 u; } unk_B6;   
    s16 unk_B8;
} R06_8017140C_S_8017140C_0;
typedef struct R06_8017140C_S_8017140C_1 {
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
} R06_8017140C_S_8017140C_1;
typedef struct R06_8017140C_S_8017140C_2 {
    u8 pad_00[0x5];
    u8 unk_05;
    u8 pad_06[0x1E];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} R06_8017140C_S_8017140C_2;
typedef struct R06_80171964_S_8017169C_0 {
    u8 pad_00[0x1C];
    union { s32 s; u32 u; } unk_1C;   
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   
    u8 pad_72[0x18];
    union { s16 s; u16 u; } unk_8A;   
} R06_80171964_S_8017169C_0;
typedef struct R06_80171964_S_8017169C_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} R06_80171964_S_8017169C_1;
typedef struct R06_80171964_S_8017169C_2 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
} R06_80171964_S_8017169C_2;
typedef struct R06_80171964_S_8017169C_3 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} R06_80171964_S_8017169C_3;
typedef struct R06_80171B1C_S_80171C34_1 {
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
} R06_80171B1C_S_80171C34_1;
typedef struct R06_80171B1C_S_80171C34_2 {
    u8 pad_00[0x24];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   
    union { s8 s; u8 u; } unk_26;   
} R06_80171B1C_S_80171C34_2;
typedef struct R06_80171B1C_S_80171C34_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} R06_80171B1C_S_80171C34_3_pre;
typedef struct R06_80171B1C_S_80171C34_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} R06_80171B1C_S_80171C34_3;
typedef struct R06_80171B1C_S_80171C34_5 {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0x2];
    union { s8 s; u8 u; } unk_9C;   
} R06_80171B1C_S_80171C34_5;
typedef struct R06_80171B1C_S_80171C34_7 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} R06_80171B1C_S_80171C34_7;
typedef struct R06_80171B1C_S_80171C34_8 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} R06_80171B1C_S_80171C34_8;
typedef struct R06_80171B1C_DungeonRecord {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} R06_80171B1C_DungeonRecord;
typedef struct R06_80172428_S_80172428_1 {
    u8 pad_00[0x98];
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
} R06_80172428_S_80172428_1;
typedef struct R06_80172428_Ent R06_80172428_Ent;
typedef struct R06_80172550_S_80172628_0 {
    u8 pad_00[0x46];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x28];
    s8 unk_9A;
} R06_80172550_S_80172628_0;
typedef struct {
    u8 pad0[0x8C];
    void (*callback)(void *, void *, void *, void *);
} Resource06CallbackState;
typedef struct R06_8017278C_S_8017278C_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} R06_8017278C_S_8017278C_0;
typedef struct R06_80172970_S_80172970_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} R06_80172970_S_80172970_0;
typedef struct R06_80172970_S_80172970_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} R06_80172970_S_80172970_2_pre;
typedef struct R06_80172970_S_80172970_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} R06_80172970_S_80172970_3;
typedef struct R06_80172970_S_80172970_4 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} R06_80172970_S_80172970_4;
typedef struct R06_80172DD0_S_80172DD0_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   
    u8 pad_98[0x3];
    u8 unk_9B;
} R06_80172DD0_S_80172DD0_1;
typedef struct R06_801734B0_S_801734B0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} R06_801734B0_S_801734B0_0;
typedef struct R06_801734B0_S_801734B0_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
} R06_801734B0_S_801734B0_1;
typedef struct R06_801734B0_S_801734B0_2 {
    u8 pad_00[0x1C];
    union { u32 s; s32 u; } unk_1C;   
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} R06_801734B0_S_801734B0_2;
typedef struct R06_801734B0_S_801734B0_5 {
    u8 pad_00[0x92];
    u16 unk_92;
    u8 pad_94[0x22];
    u16 unk_B6;
    u16 unk_B8;
} R06_801734B0_S_801734B0_5;
typedef struct R06_801738E0_S_801738E0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0x1A];
    u16 unk_B6;
    u16 unk_B8;
} R06_801738E0_S_801738E0_0;
typedef struct R06_801738E0_S_801738E0_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} R06_801738E0_S_801738E0_1;
typedef struct R06_801738E0_S_801738E0_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} R06_801738E0_S_801738E0_2;
typedef struct R06_801738E0_S_801738E0_3 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} R06_801738E0_S_801738E0_3;
typedef struct R06_801738E0_S_801738E0_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} R06_801738E0_S_801738E0_4;
typedef struct {
    s8 pad_00[0x8C];
    void *unk_8C;
} R06_80173C34_Actor;
typedef struct {
    u8 pad_00[0x2C];
    u8 *unk_2C;
} R06_80173C34_Entity;
typedef struct {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} R06_80173C34_MapObject;
typedef struct R06_80173E08_Entry {
    u8 pad00[6];
    s16 unk06;
    void *unk08;
    struct R06_80173E08_Entry *unk0C;
    u8 pad10[4];
    u16 unk14;
} R06_80173E08_Entry;
typedef struct {
    u8 pad[0x13C];
    s32 value;
} R06_80173E08_Scratchpad;
typedef struct {
    u8 pad[0x5218];
    s16 value;
} R06_80173E08_GlobalPage;
typedef struct R06_80173E94_OrderingTag { u32 addr : 24; u32 count : 8; } R06_80173E94_OrderingTag;
typedef struct R06_80173E94_S_80173E94_1 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x12];
    u8 * unk_18;
    u8 pad_1C[0x4];
    union { u8 * p; u32 * p2; } unk_20;   
    u8 pad_24[0x9C];
    u32 unk_C0;
} R06_80173E94_S_80173E94_1;
typedef struct R06_80173E94_S_80173E94_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} R06_80173E94_S_80173E94_2;
typedef struct R06_80173E94_S_80173E94_3 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   
    union {
        struct { u32 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
        struct { u8 pad[0x3]; u8 v; } at03;
    } unk_04;   
} R06_80173E94_S_80173E94_3;
typedef struct R06_80173E94_S_80173E94_4_pre {
    void * unk_00;
    u8 pad_04[0x4];
} R06_80173E94_S_80173E94_4_pre;
typedef struct R06_80173E94_S_80173E94_4 {
    u8 pad_00[0x8];
    u32 unk_08;
    u8 pad_0C[0x26];
    s16 unk_32;
} R06_80173E94_S_80173E94_4;
typedef struct R06_80173E94_S_80173E94_5 {
    u8 pad_00[0x8];
    u8 * unk_08;
} R06_80173E94_S_80173E94_5;
typedef struct R06_801740E4_S_801740E4_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} R06_801740E4_S_801740E4_0;
typedef struct R06_801740E4_S_801740E4_1 {
    u16 unk_00;
    u8 pad_02[0x14];
    s16 unk_16;
    u8 pad_18[0x1C];
    s16 unk_34;
} R06_801740E4_S_801740E4_1;
typedef struct R06_801740E4_S_801740E4_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} R06_801740E4_S_801740E4_2;
typedef struct R06_80174214_S_80174214_0 {
    u8 pad_00[0x8];
    union { void * s; s32 u; } unk_08;   
    u8 pad_0C[0x4];
    s32 unk_10;
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
} R06_80174214_S_80174214_0;
typedef struct R06_80174214_S_80174214_1 {
    u8 pad_00[0x8];
    void * unk_08;
} R06_80174214_S_80174214_1;
typedef struct R06_80174214_S_80174214_2 {
    u8 pad_00[0x2];
    s16 unk_02;
} R06_80174214_S_80174214_2;
typedef struct R06_80174214_S_80174214_3 {
    u8 pad_00[0x6];
    s16 unk_06;
} R06_80174214_S_80174214_3;
typedef struct R06_80174214_S_80174214_4 {
    u8 pad_00[0x8];
    void * unk_08;
} R06_80174214_S_80174214_4;
typedef struct R06_80174214_S_80174214_5 {
    u8 pad_00[0xA];
    s16 unk_0A;
} R06_80174214_S_80174214_5;
typedef struct R06_80174214_S_80174214_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} R06_80174214_S_80174214_6;
typedef struct R06_80174334_S_80174334_0 {
    u8 pad_00[0xC];
    union { s32 s32; u16 u16; } unk_0C;   
    union { s32 s32; u16 u16; } unk_10;   
    union { s32 s32; u16 u16; } unk_14;   
    union { s32 s32; u16 u16; } unk_18;   
    u8 pad_1C[0x8];
    union { u8 * p; u32 * p2; } unk_24;   
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
} R06_80174334_S_80174334_0;
typedef struct R06_80174334_S_80174334_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} R06_80174334_S_80174334_1;
typedef struct R06_80174334_S_80174334_2 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 pad_0C[0x3];
    u8 unk_0F;
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
} R06_80174334_S_80174334_2;
typedef struct R06_80174334_S_80174334_4 {
    u8 pad_00[0x4];
    u32 unk_04;
    u32 unk_08;
    u32 unk_0C;
    u32 unk_10;
    u8 pad_14[0x50];
    u16 unk_64;
    u16 unk_66;
    u16 unk_68;
    u16 unk_6A;
    u16 unk_6C;
    u16 unk_6E;
    u16 unk_70;
    u16 unk_72;
    u16 unk_74;
    u16 unk_76;
    u16 unk_78;
    u16 unk_7A;
} R06_80174334_S_80174334_4;
typedef struct R06_80174334_S_80174334_5 {
    u32 unk_00;
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   
    union { u16 u; s16 s; } unk_08;   
    union { u16 u; s16 s; } unk_0A;   
    u16 unk_0C;
    u16 unk_0E;
    u32 unk_10;
    u16 unk_14;
    u16 unk_16;
    union { u16 u16; u8 u8; } unk_18;   
    u16 unk_1A;
    u32 unk_1C;
    u16 unk_20;
    u16 unk_22;
    union { struct { u16 v; } at00; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   
    u8 pad_26[0x2];
    u32 unk_28;
    union { u16 u; s16 s; } unk_2C;   
    union { u16 u; s16 s; } unk_2E;   
    union {
        struct { u16 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_30;   
} R06_80174334_S_80174334_5;
typedef struct R06_80174334_S_80174334_6 {
    u8 pad_00[0x4];
    u16 unk_04;
    u16 unk_06;
} R06_80174334_S_80174334_6;
typedef struct {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} R06_80174334_MATRIX;
typedef struct R06_8017489C_Func800C138CData {
    u8 pad0[8];
    void *context;
    void *data;
} R06_8017489C_Func800C138CData;
typedef struct R06_801748F0_S_801748F0_0 {
    u16 unk_00;
    u8 pad_02[0x1A];
    u16 unk_1C;
} R06_801748F0_S_801748F0_0;
typedef struct R06_80174934_S_80174934_0 {
    u8 pad_00[0x16];
    union { s16 s; u16 u; u16 p; } unk_16;   
    u8 pad_18[0x2];
    union { s16 s; u16 u; } unk_1A;   
    u8 pad_1C[0x2];
    s16 unk_1E;
    u16 unk_20;
    u8 pad_22[0x42];
    s16 unk_64;
    s16 unk_66;
} R06_80174934_S_80174934_0;
typedef struct R06_80174934_S_80174934_1 {
    u8 pad_00[0x1A];
    s16 unk_1A;
    s16 unk_1C;
    u8 pad_1E[0x4A];
    s16 unk_68;
    u8 pad_6A[0x4];
    s16 unk_6E;
    u8 pad_70[0x4];
    s16 unk_74;
    u8 pad_76[0x4];
    s16 unk_7A;
} R06_80174934_S_80174934_1;
typedef struct R06_80174934_S_80174934_2 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
} R06_80174934_S_80174934_2;
typedef struct R06_80174934_S_80174934_3 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 * unk_08;
    u8 pad_0C[0x4];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} R06_80174934_S_80174934_3;
typedef struct R06_80174934_S_80174934_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} R06_80174934_S_80174934_4;
typedef struct R06_80174934_Vec3w {
    s32 x;
    s32 y;
    s32 z;
} R06_80174934_Vec3w;
typedef struct R06_80174934_Rows {
    u8 pad[0x64];
    u16 row[4][3];
} R06_80174934_Rows;
typedef struct {
    s32 x;
    s32 y;
    s32 z;
} R06_80174E78_Vec3i;
typedef struct {
    u8 pad_00[0x0C];
    u8 field_0C;
    u8 field_0D;
    u8 field_0E;
    u8 pad_0F;
    u16 field_10;
    u8 pad_12[2];
    u16 field_14;
    u8 pad_16[6];
    s16 field_1C;
    s16 field_1E;
} R06_80174E78_Prim;
typedef struct {
    u8 pad_00[4];
    u8 field_04;
    u8 field_05;
    u8 field_06;
    u8 pad_07[0x13];
    s16 field_1A;
    u16 field_1C;
    u8 pad_1E[0x46];
    s16 field_64;
    s16 field_66;
    s16 field_68;
    s16 field_6A;
    s16 field_6C;
    s16 field_6E;
    s16 field_70;
    s16 field_72;
    s16 field_74;
    s16 field_76;
    s16 field_78;
    s16 field_7A;
} R06_80174E78_Sub;
typedef struct {
    u8 pad_00[8];
    R06_80174E78_Vec3i *vec;
    R06_80174E78_Prim *prim;
    void (*callback)(void);
    u8 pad_14[0x0C];
    R06_80174E78_Sub sub;
} R06_80174E78_Entity;
typedef struct {
    u8 pad_00[0x96];
    u16 field_96;
} R06_80174E78_Source;
typedef struct {
    u8 pad0[2];
    u16 flags;
    u8 pad4[6];
    u16 count;
} R06_80175068_DungeonState;
typedef struct R06_80175270_S_80175270_0_pre {
    u16 unk_00;
} R06_80175270_S_80175270_0_pre;
typedef struct R06_80175270_S_80175270_0 {
    u8 pad_00[0x96];
    union { s16 s; u16 u; } unk_96;   
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x1E];
    s16 unk_BA;
} R06_80175270_S_80175270_0;
typedef struct R06_80175270_S_80175270_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x8];
    u32 unk_1C;
    u8 pad_20[0xA];
    union { u16 u; s16 s; } unk_2A;   
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x1C];
    u16 unk_8A;
} R06_80175270_S_80175270_1;
typedef struct R06_80175270_S_80175270_2 {
    u8 pad_00[0x8];
    s32 * unk_08;
    union { void * p; s32 i; } unk_0C;   
    union { void * p; s32 i; } unk_10;   
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x88];
    u8 unk_A8;
    u8 unk_A9;
    u8 unk_AA;
} R06_80175270_S_80175270_2;
typedef struct R06_80175270_S_80175270_3 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} R06_80175270_S_80175270_3;
typedef struct R06_80175270_S_80175270_6_pre {
    void * unk_00;
    u8 pad_04[0x10];
} R06_80175270_S_80175270_6_pre;
typedef struct R06_80175270_S_80175270_6 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} R06_80175270_S_80175270_6;
typedef struct R06_80175270_S_80175270_7 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0x16];
    u8 * unk_2C;
} R06_80175270_S_80175270_7;
typedef struct R06_80175270_S_80175270_8 {
    u8 pad_00[0xA];
    u16 unk_0A;
} R06_80175270_S_80175270_8;
typedef struct R06_80175270_S_80175270_9 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} R06_80175270_S_80175270_9;
typedef struct R06_80175270_S_80175270_10 {
    u8 unk_00;
} R06_80175270_S_80175270_10;
extern int abs(int);
s32 rand();
extern s32 rand(void);
extern void *memcpy(void *, const void *, u32);
extern s32 Control_CD();
s32 allocate_list_node();
s32 func_8003FD64();
s32 register_node();
s32 func_8004491C();
s32 generate_random_value();
s32 set_or_clear_actor_status_slot();
void initialize_actor_sprite_and_animation();
s32 select_sprite_entry();
s32 func_80047784();
void texture_set_the_active_entries_matching_id_in_type_n_2_table_slots();
s32 try_move_actor_to_valid_position();
void process_effect_block_entries();
s32 func_80170A7C();
void select_indirect_table_entry();
void advance_sprite_animation_and_textures();
s32 func_800644B8();
s32 func_80069EF8();
void apply_monster_koyaw_data();
s32 refresh_actor_facing_and_lifecycle();
s16 sample_terrain_surface_height();
s32 check_entity_relation();
s32 find_active_rect_containing_point();
s32 test_neighbor_position_relation();
s32 get_rounded_facing_and_rounding_flag(s16, s16, s16, s16, u16 *);
s32 can_entity_gain_level();
void update_actor_status_and_mp();
void begin_pushed_actor_move();
s32 begin_ready_actor_directional_action();
s32 advance_actor_pending_action();
void begin_actor_move_to_target_facing();
s32 reset_actor_action_state();
s32 process_selected_actor_record();
void begin_actor_spell_action();
s32 cycle_map_cell_flags();
s32 update_map_cell_flags_with_item_limit();
s32 update_actor_proximity_flag();
s32 find_adjacent_actor();
s32 probe_directional_neighbor();
s32 get_actor_height_difference();
s32 check_diagonal_side_height();
s32 select_actor_route_target();
s32 check_directional_move_and_terrain();
s32 prepare_directional_attack();
s32 try_claim_dungeon_action_slot();
u32 check_entity_interaction_compatibility();
s32 apply_camera_offset_and_select_target();
s32 has_pending_dungeon_activity();
s32 relink_entity_and_clear_high_flag();
s32 advance_status_timers();
s32 update_actor_movement_to_tile();
s32 spend_actor_mp();

s32 update_linked_actor_motion();
s32 resolve_attack_damage_and_effects();
void set_record_integer_tile_center();
s32 play_sound_if_enabled();
s32 get_cd_command_queue_depth();
s32 scan_actor_along_heading();
s32 create_actor_spell_effect();
void begin_actor_display_action();
void apply_clamped_actor_value_delta();
void unlink_entity_node();
void distribute_experience_and_report_gains();
s32 detach_record_and_update_slot_state();
void announce_familiar_defeat();
s32 update_actor_hop_and_shrink();

s32 update_actor_hop_and_grow();
s32 get_entity_effect_value();
s32 func_80042900();
void clear_slots_of_type();
void func_80042B68();
s32 get_tile_chebyshev_distance();
s32 has_pending_actor_or_turn_action();
void on_actor_status_updated();
void func_800A9A04();
s32 update_actor_transform_from_parent();
s32 update_thrown_actor_travel();
s32 interpolate_actor_to_terrain_tile();
s32 update_spinning_actor_fall();
s32 update_actor_fade_in();
void project_sprite_commands();
void func_800453E0();
s32 func_80065420();
s32 func_80066460();
void func_80067F20();
void func_80064840();
void func_800649A0();
void func_80064A40();
void func_80064AE0();
void func_80064BC0();
void func_80064CF0();
void func_80064D80();
s32 func_80065590();
void func_80065820();
void func_8006671C();
s32 func_80064584();
void unlink_node();
void func_80044A50();
void select_record_entry_and_value();
void sound_set_cd_cue_parameters();
void run_cd_image_commands();
void func_80041588();
s32 read_stream_cue_start_offset();
s32 lookup_masked_byte_table();
void decrement_monster_entry_count();
s32 advance_staged_entity_load();
s32 create_status_linked_render_effect();
s32 select_nearby_target_and_initialize_slot(s32 slot_id,struct ObjectPosition *target, s32 target_id, s32 slot_value);
s32 resolve_actor_floor_trap_once();
s32 propagate_actor_action_flag();
extern u8 D_800D71A8[];
extern u8 D_8017586C[];
extern u8 D_80175894[];
extern u8 resident_globals_page[];
extern u8 D_8006CCF8[];
extern u8 D_8017589C[];
extern u8 D_80175874[];
extern u8 D_80175884[];
extern u8 D_8017588C[];
extern u8 actor_turn_angle_offsets[];
extern u8 D_8017587C[];
extern u8 actor_update_node_cursor[];
extern u8 D_8017591C[];
extern u8 D_80175910[];
extern u8 D_800DCF5E[];
extern u8 D_80175928[];
extern u8 D_8003E140[];
extern u8 cd_cue_base[];
extern u8 actor_effect_color_targets[];
extern u8 D_800DCF5C[];
extern u8 D_8014A000[];
extern u8 D_801758FC[];
extern u8 D_80175904[];
extern u8 D_80175920[];
extern u8 D_80175921[];
extern u8 D_80175924[];
void *func_8017087C(s16 kind_flags, s16 tile_x, s16 tile_y, s16 part_id);
void create_anchored_directional_object(u8 *actor, u8 *motion, u8 *entity);
void initialize_destination_state(void *actor, void *actor_context, struct SpriteFrameState *sprite, void *creature);
/* Compatible C89 declaration: the earlier retail call retains incoming a2/a3. The later definition documents all four pointer parameters. */
void update_actor_object_motion();
void choose_flame_move(void *move_data, void *context, struct SpriteFrameState *position_data, void *actor_data);
s32 try_flame_attack(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, struct SpriteFrameState *sprite, ActorRecord *actor);
void update_actor_action_and_direction(void *action_state, void *context, struct SpriteFrameState *sprite, EntityRec *actor);
s32 relink_flame_path(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg);
void finish_actor_tile_move_then_initialize_destination(void *state, s32 unused, s32 source, s32 target);
void finish_linked_actor_motion_and_floor_trap_then_initialize_destination(Resource06CallbackState *state, void *entity, void *position, void *graphic);
void advance_action_through_animation(R06_8017278C_S_8017278C_0 *action, struct ObjectPosition *motion, struct SpriteFrameState *sprite, void *actor);
void start_selected_move_and_reset_action(void *action, struct ObjectPosition *position, struct SpriteFrameState *sprite, ActorRecord *actor);
void update_directional_motion_and_tile(R06_80172DD0_S_80172DD0_1 *action, struct ObjectPosition *motion, struct SpriteFrameState *tile_state, EntityRec *entity);
void fade_sprites_and_remove_entity(void *actor, s32 unused, struct SpriteFrameState *sprite, void *entity);
void reset_record_motion_field_b(Rec_func_800AB538_arg0 *record, void *motion, void *scale, void *render);
void advance_flame_removal(void *state, void *motion, void *position, void *actor);
void grow_hopping_flame(Resource06CallbackState *state, void *motion, void *position, void *actor);
void update_actor_state_by_flags(void *in_actor, void *in_context, struct SpriteFrameState *in_sprite, void *in_entity);
void func_801738E0(void *entity, void *context, struct SpriteFrameState *anim, void *actor);
void update_flame_parent_motion(R06_80173C34_Actor *actor, s32 action, struct SpriteFrameState *entity, R06_80173C34_MapObject *map_object);
void create_randomized_rotated_effect(Resource06CallbackState *state, void *entity, void *position, void *graphic);
void finish_actor_terrain_interpolation_then_initialize_destination(Resource06CallbackState *state, void *motion, void *position, void *actor);
void finish_spinning_actor_fall_then_initialize_destination(Resource06CallbackState *state, void *motion, void *position, void *actor);
void finish_actor_fade_in_then_initialize_destination(Resource06CallbackState *state, void *motion, void *position, void *actor);
s32 project_flame_sprite_chain(void *initial_payload, s32 entry_data, R06_80173E08_Entry *entry, s32 unused);
s32 append_linked_shaded_point_packets(u8 *node, void *vertex_arg);
void advance_randomized_motion_and_complete(void *object_data, R06_801740E4_S_801740E4_0 *position, R06_801740E4_S_801740E4_2 *state);
void advance_actor_action_and_update_status(
    void *source,
    s16 value_34,
    s32 value_28,
    s16 value_52,
    s16 x_offset,
    s16 y_offset,
    s16 z_offset);
void project_and_queue_textured_quad(void *quad, void *position, void *draw_state, s16 depth_bias);
s32 project_textured_quad_chain(void *initial_state, void *context, void *data);
void advance_record_countdown(void *record_data);
void update_fading_four_strip_effect(u8 *effect, R06_80174934_Vec3w *origin, u8 *render_data);
void create_sixteen_segment_ring(R06_80174E78_Source *source, R06_80174E78_Vec3i *center, void *unused_context);
void wait_for_flame_action_slot(void *entity_data, s32 unused_1, s32 unused_2, void *other_data);
void fade_effect_to_neutral_and_finish(void *entity_data, void *unused, void *source_data);
void advance_actor_transition_and_restore_child_angle(void *action, EntityRec *position, struct SpriteFrameState *entity, void *actor);
void finish_actor_floor_trap_then_initialize_destination(Resource06CallbackState *state, void *motion, void *position, void *actor);
void finish_actor_action_flag_propagation_then_initialize_destination(Resource06CallbackState *state, void *motion, void *position, void *actor);
#endif
