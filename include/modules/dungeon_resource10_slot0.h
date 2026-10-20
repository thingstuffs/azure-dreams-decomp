#ifndef DUNGEON_RESOURCE10_SLOT0_H
#define DUNGEON_RESOURCE10_SLOT0_H
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/dir_step.h"
#include "shared/dungeon_status.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_80171CD4_arg0.h"
#include "records/Rec_func_80171CD4_arg1.h"
#include "m2c_compat.h"
#include "shared/sprite_frame_state.h"
#include "shared/def_table.h"
#include "records/Rec_D_80083460.h"
#include "records/Rec_func_80174800_arg0.h"

#define NULL 0
typedef struct R10_8017092C_Scratch {
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
} R10_8017092C_Scratch;
typedef struct R10_8017092C_Packet {
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
} R10_8017092C_Packet;
typedef struct {
    u8 color[3];
    u8 pad03[0x2F];
    s16 scale;
    s16 divisor;
    s16 x;
    s16 y;
    u8 pad3A[6];
    s32 pos[3];
    s32 vel[3];
} R10_80170B0C_Actor;
typedef struct {
    s32 xyz[3];
} R10_80170B0C_Vec3;
typedef struct {
    u8 pad00[0xC];
    s8 color[3];
    u8 pad0F[0xD];
    u16 size0;
    u16 size1;
} R10_80170B0C_Sprite;
typedef struct R10_80170CF8_S_80AC55DC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} R10_80170CF8_S_80AC55DC_0;
typedef struct R10_80170CF8_S_80AC55DC_1 {
    u8 pad_00[0x8];
    void * unk_08;
} R10_80170CF8_S_80AC55DC_1;
typedef struct R10_80170CF8_S_80AC55DC_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    s16 unk_34;
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
} R10_80170CF8_S_80AC55DC_2;
typedef struct R10_80170CF8_S_80AC55DC_4 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} R10_80170CF8_S_80AC55DC_4;
typedef struct R10_80170CF8_S_80AC55DC_5 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} R10_80170CF8_S_80AC55DC_5;
typedef struct R10_80170CF8_S_80AC55DC_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} R10_80170CF8_S_80AC55DC_6;
typedef struct R10_80170F3C_S_80170F3C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} R10_80170F3C_S_80170F3C_0;
typedef struct R10_80170F3C_S_80170F3C_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} R10_80170F3C_S_80170F3C_1;
typedef struct R10_80170F3C_S_80170F3C_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} R10_80170F3C_S_80170F3C_2;
typedef struct R10_80170F3C_S_80170F3C_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} R10_80170F3C_S_80170F3C_3;
typedef struct R10_80170F3C_S_80170F3C_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} R10_80170F3C_S_80170F3C_4;
typedef void (*R10_80171104_ActorCallback)(void *, void *, void *, void *);

typedef struct R10_80171104_S_80171104_1 {
    u8 pad_00[0x1C];
    union { u32 u; s32 s; } unk_1C;   
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x41];
    s8 unk_6D;
    u8 pad_6E[0x1A];
    union { u16 u; s16 s; } unk_88;   
} R10_80171104_S_80171104_1;
typedef struct R10_80171104_S_80171104_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} R10_80171104_S_80171104_2;
typedef struct R10_801717F4_S_801717F4_2 {
    u8 pad_00[0x24];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} R10_801717F4_S_801717F4_2;
typedef struct R10_80171D7C_S_80171CD4_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   
    u8 pad_72[0x18];
    union { s16 s; u16 u; } unk_8A;   
} R10_80171D7C_S_80171CD4_0;
typedef struct R10_80171D7C_S_80171CD4_4 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} R10_80171D7C_S_80171CD4_4;
typedef struct R10_80171FE8_S_80171C34_1 {
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
} R10_80171FE8_S_80171C34_1;
typedef struct R10_80171FE8_S_80171C34_2 {
    u8 pad_00[0x24];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   
    union { s8 s; u8 u; } unk_26;   
} R10_80171FE8_S_80171C34_2;
typedef struct R10_80171FE8_S_80171C34_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} R10_80171FE8_S_80171C34_3_pre;
typedef struct R10_80171FE8_S_80171C34_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} R10_80171FE8_S_80171C34_3;
typedef struct R10_80171FE8_S_80171C34_5 {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0x2];
    union { s8 s; u8 u; } unk_9C;   
} R10_80171FE8_S_80171C34_5;
typedef struct R10_80171FE8_S_80171C34_7 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} R10_80171FE8_S_80171C34_7;
typedef struct R10_80171FE8_S_80171C34_8 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} R10_80171FE8_S_80171C34_8;
typedef struct R10_80171FE8_DungeonRecord {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} R10_80171FE8_DungeonRecord;
typedef struct R10_80172730_S_80172688_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} R10_80172730_S_80172688_1;
typedef struct R10_8017297C_Ent R10_8017297C_Ent;
typedef struct R10_80172A94_S_80172628_0 {
    u8 pad_00[0x46];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x28];
    s8 unk_9A;
} R10_80172A94_S_80172628_0;
typedef struct R10_80172C54_S_80172C54_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { s16 s; u16 u; } unk_9E;   
    u8 pad_A0[0x4];
    s32 unk_A4;
} R10_80172C54_S_80172C54_0;
typedef struct {
    u8 pad0[0x8C];
    void (*callback)(void *, void *, void *, void *);
} Resource10CallbackState;
typedef struct R10_80173080_S_80173080_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   
    u8 pad_98[0x3];
    u8 unk_9B;
} R10_80173080_S_80173080_0;
typedef struct R10_80173080_S_80173080_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} R10_80173080_S_80173080_3;
typedef struct R10_80173280_S_80173280_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    u16 unk_9E;
} R10_80173280_S_80173280_0;
typedef struct R10_80173280_S_80173280_2 {
    u8 * unk_00;
} R10_80173280_S_80173280_2;
typedef struct R10_80173280_S_80173280_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} R10_80173280_S_80173280_3;
typedef struct R10_80173280_S_80173280_6 {
    u8 pad_00[0xA6];
    u16 unk_A6;
} R10_80173280_S_80173280_6;
typedef struct R10_80173280_S_80173280_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} R10_80173280_S_80173280_7;
typedef struct R10_8017380C_S_8017380C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   
    u8 pad_98[0x3];
    u8 unk_9B;
} R10_8017380C_S_8017380C_0;
typedef struct R10_80173BBC_S_80173D4C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} R10_80173BBC_S_80173D4C_0;
typedef struct R10_80173BBC_S_80173D4C_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
} R10_80173BBC_S_80173D4C_1;
typedef struct R10_80173BBC_S_80173D4C_2 {
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
} R10_80173BBC_S_80173D4C_2;
typedef struct R10_80173F4C_S_801740DC_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} R10_80173F4C_S_801740DC_0;
typedef struct {
    s8 pad_00[0x8C];
    void *unk_8C;
} R10_80174258_Actor;
typedef struct {
    u8 pad_00[0x2C];
    u8 *unk_2C;
} R10_80174258_Entity;
typedef struct {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} R10_80174258_MapObject;
typedef struct R10_8017442C_S_801745BC_0_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} R10_8017442C_S_801745BC_0_pre;
typedef struct R10_8017442C_S_801745BC_0 {
    u8 pad_00[0x5C];
    void * unk_5C;
} R10_8017442C_S_801745BC_0;
typedef struct R10_8017442C_S_801745BC_1_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} R10_8017442C_S_801745BC_1_pre;
typedef struct R10_8017442C_S_801745BC_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x14];
    s8 unk_28;
    u8 pad_29[0x33];
    void * unk_5C;
    u8 pad_60[0x4];
    s16 unk_64;
} R10_8017442C_S_801745BC_1;
typedef struct R10_8017442C_S_801745BC_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} R10_8017442C_S_801745BC_2;
typedef struct R10_8017442C_S_801745BC_3 {
    u8 pad_00[0xA];
    s16 unk_0A;
} R10_8017442C_S_801745BC_3;
typedef struct R10_8017442C_S_801745BC_4 {
    u8 pad_00[0x14];
    s16 unk_14;
    u8 pad_16[0x14];
    u16 unk_2A;
} R10_8017442C_S_801745BC_4;
typedef struct R10_8017442C_S_801745BC_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} R10_8017442C_S_801745BC_5;
typedef struct R10_8017442C_OffsetPair {
    s16 x;
    u16 y;
} R10_8017442C_OffsetPair;
typedef struct R10_8017442C_OffsetTable {
    R10_8017442C_OffsetPair entries[8];
} R10_8017442C_OffsetTable;
typedef struct R10_80174670_S_80174800_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} R10_80174670_S_80174800_0_pre;
typedef struct R10_80174670_S_80174800_0 {
    u8 pad_00[0x5C];
    void * unk_5C;
} R10_80174670_S_80174800_0;
typedef struct R10_80174670_S_80174800_1_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} R10_80174670_S_80174800_1_pre;
typedef struct R10_80174670_S_80174800_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} R10_80174670_S_80174800_2;
typedef struct R10_80174670_S_80174800_3 {
    u8 pad_00[0xA];
    s16 unk_0A;
} R10_80174670_S_80174800_3;
typedef struct R10_80174670_S_80174800_4 {
    u8 pad_00[0x26];
    u8 unk_26;
    u8 pad_27[0x3];
    s16 unk_2A;
    u8 pad_2C[0x58];
    s8 unk_84;
    s8 unk_85;
} R10_80174670_S_80174800_4;
typedef struct R10_80174898_S_80174898_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} R10_80174898_S_80174898_0;
typedef struct R10_80174898_S_80174898_1 {
    u8 pad_00[0xA];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} R10_80174898_S_80174898_1;
typedef struct R10_80174898_S_80174898_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} R10_80174898_S_80174898_2;
typedef struct R10_80174898_OffsetPair {
    s16 x;
    s16 y;
} R10_80174898_OffsetPair;
typedef struct R10_80174898_OffsetTable {
    R10_80174898_OffsetPair entries[8];
} R10_80174898_OffsetTable;
typedef struct R10_80174BE4_Entry {
    u8 pad00[6];
    s16 unk06;
    void *unk08;
    struct R10_80174BE4_Entry *unk0C;
    u8 pad10[4];
    u16 unk14;
} R10_80174BE4_Entry;
typedef struct {
    u8 pad[0x13C];
    s32 value;
} R10_80174BE4_Scratchpad;
typedef struct {
    u8 pad[0x5218];
    s16 value;
} R10_80174BE4_GlobalPage;
typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} R10_80174C70_LocalVector;
typedef struct {
    R10_80174C70_LocalVector vectors[4];
} __attribute__((packed)) R10_80174C70_LocalTable;
typedef struct R10_80174C70_S_80174C70_0 {
    u8 pad_00[0x18];
    s16 unk_18;
    union { s16 s; u16 u; } unk_1A;   
    u8 pad_1C[0x46];
    s16 unk_62;
} R10_80174C70_S_80174C70_0;
typedef struct R10_80174C70_S_80174C70_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xB];
    union { s16 s; u16 u; } unk_1A;   
} R10_80174C70_S_80174C70_1;
typedef struct R10_80174C70_S_80174C70_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
} R10_80174C70_S_80174C70_2;
typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} R10_80174F24_LocalVector;
typedef struct {
    u32 words[8];
} __attribute__((packed)) R10_80174F24_LocalTable;
typedef struct {
    u32 words[3];
} __attribute__((packed)) R10_80174F24_LocalPacket;
typedef struct R10_80174F24_S_func_80AF3724_0 {
    u8 pad_00[2];
    u16 unk_02;
    u8 pad_04[2];
    u16 unk_06;
    u8 pad_08[2];
    u16 unk_0A;
} R10_80174F24_S_func_80AF3724_0;
typedef struct R10_80174F24_S_func_80AF3724_1 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} R10_80174F24_S_func_80AF3724_1;
typedef struct R10_80174F24_S_func_80AF3724_2 {
    u16 unk_00;
    u16 unk_02;
} R10_80174F24_S_func_80AF3724_2;
typedef struct R10_80174F24_S_func_80AF3724_3 {
    u8 pad_00[8];
    void *unk_08;
    void *unk_0C;
    void *unk_10;
} R10_80174F24_S_func_80AF3724_3;
typedef struct R10_80174F24_S_func_80AF3724_4 {
    u8 pad_00[0x18];
    s16 unk_18;
    s16 unk_1A;
    u8 pad_1C[0xC];
    R10_80174F24_LocalPacket unk_28;
} R10_80174F24_S_func_80AF3724_4;
typedef struct R10_80174F24_S_func_80AF3724_5 {
    union {
        s32 unk_00;
        struct {
            u8 pad_00[2];
            s16 unk_02;
        } unk_02;
    } unk_00;
    union {
        s32 unk_04;
        struct {
            u8 pad_04[2];
            s16 unk_06;
        } unk_06;
    } unk_04;
    u8 pad_08[2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
} R10_80174F24_S_func_80AF3724_5;
typedef struct R10_80174F24_S_func_80AF3724_6 {
    u8 pad_00[8];
    void *unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[6];
    s16 unk_1C;
    s16 unk_1E;
} R10_80174F24_S_func_80AF3724_6;
typedef struct {
    u8 pad0[2];
    u16 flags;
    u8 pad4[6];
    u16 count;
} R10_801751C0_DungeonState;
typedef struct R10_80175398_DungeonCopy3 {
    s32 x;
    s32 y;
    s32 z;
} R10_80175398_DungeonCopy3;
typedef struct R10_80175398_DungeonChild {
    s32 x;
    s32 y;
    s32 z;
} R10_80175398_DungeonChild;
typedef struct R10_80175398_DungeonTail {
    u8 pad0[0x0C];
    u32 color;
    u8 pad10[4];
    u16 flags;
    u8 pad16[6];
    u16 value1c;
    u16 value1e;
} R10_80175398_DungeonTail;
typedef struct R10_80175398_DungeonEffect {
    u8 pad0[8];
    R10_80175398_DungeonChild *child;
    R10_80175398_DungeonTail *tail;
    void *resource;
} R10_80175398_DungeonEffect;
typedef struct R10_80175398_S_80175398_0_pre {
    u16 unk_00;
} R10_80175398_S_80175398_0_pre;
typedef struct R10_80175398_S_80175398_0 {
    u8 pad_00[0x96];
    union { u16 u; s16 s; } unk_96;   
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0xC];
    union { void * p; u8 * p2; } unk_A8;   
    s16 unk_AC;
} R10_80175398_S_80175398_0;
typedef struct R10_80175398_S_80175398_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x16];
    union { u16 u; s16 s; } unk_2A;   
    u8 pad_2C[0x34];
    u8 * unk_60;
    u8 pad_64[0x9];
    s8 unk_6D;
    u8 pad_6E[0x1C];
    u16 unk_8A;
} R10_80175398_S_80175398_1;
typedef struct R10_80175398_S_80175398_2 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x7];
    u8 * unk_0C;
    u32 unk_10;
    u16 unk_14;
    u8 pad_16[0x16];
    u8 * unk_2C;
    u8 pad_30[0x78];
    u8 unk_A8;
    u8 unk_A9;
    u8 unk_AA;
} R10_80175398_S_80175398_2;
typedef struct R10_80175398_S_80175398_3 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} R10_80175398_S_80175398_3;
typedef struct R10_80175398_S_80175398_5_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} R10_80175398_S_80175398_5_pre;
typedef struct R10_80175398_S_80175398_5 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} R10_80175398_S_80175398_5;
typedef struct R10_80175398_S_80175398_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
} R10_80175398_S_80175398_6;
typedef struct R10_80175398_S_80175398_7 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} R10_80175398_S_80175398_7;
extern s32 rand(void);
extern s32 Control_CD();
typedef struct { s16 x; u16 y; } Resource10DirectionOffset;
extern const Resource10DirectionOffset D_80170854[8];
extern const Resource10DirectionOffset D_80170874[8];
s32 func_80065420();
s32 func_80066460();
void func_80067F20();
void func_800478B8();
s32 register_node();
s32 func_8004491C();
void func_8003DB94();
s32 allocate_list_node();
s32 func_8003FD64();
s32 generate_random_value();
s32 set_or_clear_actor_status_slot();
void initialize_actor_sprite_and_animation();
s32 try_move_actor_to_valid_position();
void select_indirect_table_entry();
s32 select_sprite_entry();
s32 func_80047784();
void apply_monster_koyaw_data();
s32 refresh_actor_facing_and_lifecycle();
s16 sample_terrain_surface_height();
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
s32 update_actor_movement_to_tile();
void reduce_actor_food_meter();
s32 advance_status_timers();
s32 check_actor_floor_trap();
s32 func_800644B8();
void set_record_integer_tile_center();
void on_actor_status_updated();
void func_800A9A04();
s32 update_linked_actor_motion();
s32 resolve_attack_damage_and_effects();
s32 play_sound_if_enabled();
s32 get_cd_command_queue_depth();
s32 func_80069EF8();
s32 scan_monster_along_heading();
s32 create_actor_spell_effect();
void begin_actor_display_action();
void apply_clamped_actor_value_delta();
s32 update_actor_defeat_removal();
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
void func_800419EC();
void spawn_radial_particle_burst();
void project_sprite_commands();
void func_800453E0();
s32 func_80064584();
void unlink_node();
void func_80044A50();
void sound_set_cd_cue_parameters();
s32 run_cd_image_commands();
s32 func_80041588();
s32 func_800445E0();
s32 lookup_masked_byte_table();
s32 unlink_entity_node();
s32 decrement_monster_entry_count();
s32 advance_staged_entity_load();
s32 create_status_linked_render_effect();
s32 select_nearby_target_and_initialize_slot();
s32 resolve_actor_floor_trap_once();
s32 propagate_actor_action_flag();
extern u8 D_800DEC70[];
extern u8 D_80175988[];
extern u8 D_801759E8[];
extern u8 D_801759A0[];
extern u8 D_801759B0[];
extern u8 D_801759B8[];
extern u8 D_80175A1C[];
extern u8 D_80175998[];
extern u8 D_801759D0[];
extern u8 D_801759E0[];
extern u8 D_80175980[];
extern u8 D_8006CD00[];
extern u8 D_801759A8[];
extern u8 D_801759C0[];
extern u8 D_801759C8[];
extern u8 D_801759F0[];
extern u8 D_801759D8[];
extern u8 D_80175A18[];
extern u8 D_80175A0C[];
extern u8 D_800DCF5E[];
extern u8 D_80175A84[];
extern u8 D_8003E140[];
extern u8 D_8006CD58[];
extern u8 D_800DCEEC[];
extern u8 D_800DCF5C[];
extern u8 D_8014A000[];
extern u8 D_801759F8[];
extern u8 D_80175A00[];
extern u8 D_80175A80[];
extern u8 D_80175A81[];
s32 func_8017092C(u8 *node_data, u16 *position);
void move_and_shrink_fading_effect(R10_80170B0C_Actor *actor, R10_80170B0C_Vec3 *vec, R10_80170B0C_Sprite *sprite);
void func_80170CF8(
    R10_80170CF8_S_80AC55DC_1 *origin, s16 effect_id, s32 effect_value, s16 duration,
    s32 offset_x, s32 offset_y, s32 offset_z);
void *func_80170F3C(s16 flags, s16 kind_id, s16 variant, s32 spawn_value);
void update_actor_callbacks_animation_and_ground(u8 *actor, u8 *motion, u8 *object);
void func_801717F4(void *actor_arg, void *context_arg, void *sprite_arg, EntityRec *entity_arg);
void func_80171D7C(void *movement, void *motion, void *entity, void *path_state);
void func_80171FE8(void *move_data, void *context, void *position_data, void *actor_data);
void func_80172730(void *actor_state, void *action_state, void *sprite, void *orientation);
s32 func_801727B8(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, SpriteFrameState *sprite, EntityRec *actor);
void func_8017297C(void *action_state, void *action_context, void *sprite, EntityRec *actor);
s32 func_80172A94(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg);
void func_80172BD8(void *entity_arg, s32 unused, s32 check_arg, s32 actor_arg);
void func_80172C54(void *action, EntityRec *motion, void *sprite, EntityRec *actor);
void func_8017301C(Resource10CallbackState *state, void *entity, void *position, void *graphic);
void advance_timed_attack_animation_and_damage(void *action, void *motion, void *sprite, EntityRec *actor);
void advance_actor_spell_effect_sequence(void *actor, EntityRec *motion, void *tile_arg, EntityRec *action);
void func_8017380C(void *action, EntityRec *motion, void *entity, EntityRec *actor);
void func_80173B24(void *state, void *motion, void *position, void *actor);
void func_80173B44(void *state, void *motion, void *position, void *actor);
void func_80173B64(void *state, void *motion, void *position, void *actor);
void func_80173B84(Resource10CallbackState *state, void *motion, void *position, void *actor);
void func_80173BBC(void *action, void *context, void *sprite_in, void *actor_in);
void func_80173F4C(void *actor_in, s32 actor_index, void *target, void *entity_in);
void func_80174258(R10_80174258_Actor *actor, s32 action, R10_80174258_Entity *entity, R10_80174258_MapObject *map_object);
void advance_boss_command_stream(Resource10CallbackState *state, void *entity, void *position, void *graphic);
void func_80174384(Resource10CallbackState *state, void *motion, void *position, void *actor);
void create_positioned_sprite_effect(Resource10CallbackState *state, void *motion, void *position, void *actor);
void func_801743F4(Resource10CallbackState *state, void *motion, void *position, void *actor);
void resolve_linked_attack_hits_and_particle_bursts(void *node, s32 target_x, s32 target_y, s32 target_height);
void prepare_directional_attacks_for_neighbor_entities(void *node, s32 tile_x, s32 tile_y, s16 target_height);
void select_actor_target_and_advance_status(void *action_state, s32 effect_arg, void *anim_state, EntityRec *actor);
void advance_directional_attack_sequence(void *action, void *position, void *sprite, EntityRec *entity);
s32 func_80174BE4(void *initial_payload, s32 entry_data, R10_80174BE4_Entry *entry, s32 unused);
void update_effect_motion_and_brightness(void *effect, void *motion, void *render);
void spawn_randomized_oscillating_effect(s32 unused, R10_80174F24_S_func_80AF3724_0 *origin, void *unused_record, void *unused_actor);
void func_801751C0(void *entity_data, s32 unused_1, s32 unused_2, void *other_data);
void func_8017526C(u8 *task, void *context, u8 *input);
void advance_actor_transition_and_restore_facing(void *transition, void *position, Rec_D_80082E80 *record, void *actor);
void func_80175910(Resource10CallbackState *state, void *motion, void *position, void *actor);
void func_80175948(Resource10CallbackState *state, void *motion, void *position, void *actor);
#endif
