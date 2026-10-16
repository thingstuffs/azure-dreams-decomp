#ifndef DUNGEON_OVL_18EE800_H
#define DUNGEON_OVL_18EE800_H
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dir_step.h"
#include "shared/dungeon_status.h"
#include "shared/game_work.h"
#include "shared/gpu_packets.h"
#include "shared/object_flags.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "shared/object_node.h"
typedef struct {
    u16 unk0;
    u16 x;
    u16 unk4;
    u16 y;
    u16 unk8;
    u16 z;
} B32_818CFB74_Vec12;
typedef struct {
    u16 x;
    u16 y;
    u16 z;
} B32_818CFB74_ShortVec;
typedef struct {
    s16 x;
    u16 y;
} B32_818CFB74_OffsetPair;
typedef struct {
    B32_818CFB74_OffsetPair entry[8];
} B32_818CFB74_PackedOffsets;
typedef struct {
    u8 bytes[12];
} __attribute__((packed)) B32_818CFB74_PackedTemplate;
typedef struct {
    u8 pad0[8];
    void *unk8;
    u8 padC[8];
    u16 flags14;
} B32_818CFB74_Component;
typedef struct {
    u8 pad0[8];
    void *unk8;
    u32 flagsC;
    u16 field10;
    u8 pad12[2];
    u16 flags14;
    u8 pad16[6];
    u16 scale1C;
    u16 scale1E;
} B32_818CFB74_Graphic;
typedef struct {
    u8 pad0[2];
    s16 step2;
    s16 step4;
    u8 pad6[2];
    s16 active8;
    u8 padA[0xB];
    u8 ownerIndex15;
    u16 variant16;
    u8 pad18[8];
    B32_818CFB74_PackedTemplate template20;
    void *owner2C;
    void *path30;
    void *state34;
    s16 startX38;
    s16 startY3A;
    s16 targetX3C;
    s16 targetY3E;
    u8 pad40[0xC];
    s32 x4C;
    s32 y50;
    s32 dx54;
} B32_818CFB74_SpawnData;
typedef struct B32_818CFB74_Spawned {
    u8 pad0[8];
    B32_818CFB74_Vec12 *position8;
    B32_818CFB74_Graphic *graphicC;
    void (*update10)(void);
    u8 pad14[0xA];
    u16 flags1E;
    B32_818CFB74_SpawnData data20;
} B32_818CFB74_Spawned;
typedef struct {
    void *entity0;
    u16 *flags4;
    u8 unk8;
    u8 index9;
    s16 stateA;
    u8 padC[0x72];
    u16 variant7E;
    u8 pad80[4];
    s16 counter84;
    s16 advance86;
    s16 sentinel88;
    u8 pad8A[0x16];
    u8 valueA0;
    u8 valueA1;
    u8 padA2[6];
    B32_818CFB74_Spawned *spawnA8;
    B32_818CFB74_Vec12 *savedPositionAC;
} B32_818CFB74_State;
typedef struct {
    u8 pad0[8];
    B32_818CFB74_Vec12 *source8;
    B32_818CFB74_Component *componentC;
} B32_818CFB74_EntityHeader;
typedef struct {
    u8 pad0[0x2A];
    u16 flags2A;
    u8 pad2C[0x34];
    void *path60;
    u8 pad64[0xE];
    u8 startX72;
    u8 startY73;
} B32_818CFB74_Entity;
typedef struct {
    u8 pad0[0x24];
    u8 x24;
    u8 y25;
} B32_818CFB74_RoomData;
typedef struct {
    u8 value;
    u8 pad;
} B32_818CFB74_ByteEntry;
typedef struct B32_818CF0E8_S_818CF0E8_0_pre {
    u16 unk_00;
} B32_818CF0E8_S_818CF0E8_0_pre;
typedef struct B32_818CF0E8_S_818CF0E8_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    union { u16 s; s16 u; } unk_04;   /* accessed as both */
    u8 pad_06[0x2];
    s16 unk_08;
    u8 pad_0A[0xB];
    u8 unk_15;
    s16 unk_16;
    u8 pad_18[0x14];
    void * unk_2C;
    void * unk_30;
    void * unk_34;
    s16 unk_38;
    s16 unk_3A;
    s16 unk_3C;
    s16 unk_3E;
    u8 pad_40[0xC];
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
} B32_818CF0E8_S_818CF0E8_0;
typedef struct B32_818CF0E8_S_818CF0E8_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_08;   /* overlapping accesses */
} B32_818CF0E8_S_818CF0E8_1;
typedef struct B32_818CF0E8_S_818CF0E8_2 {
    u8 pad_00[0x2];
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} B32_818CF0E8_S_818CF0E8_2;
typedef struct B32_818CF0E8_S_818CF0E8_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xB];
    s16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} B32_818CF0E8_S_818CF0E8_3;
typedef struct B32_818CF0E8_S_818CF0E8_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x50];
    s32 unk_54;
    u8 pad_58[0x8];
    s32 unk_60;
} B32_818CF0E8_S_818CF0E8_4;
typedef struct B32_818CF0E8_S_818CF0E8_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xE];
    s16 unk_22;
} B32_818CF0E8_S_818CF0E8_5;
typedef struct B32_818CF0E8_S_818CF0E8_6 {
    u8 pad_00[0x2];
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
    union { struct { void * v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_08;   /* overlapping accesses */
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    union { u16 s; u16 u; } unk_14;   /* accessed as both */
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} B32_818CF0E8_S_818CF0E8_6;
typedef struct B32_818CF0E8_S_818CF0E8_7 {
    u8 pad_00[0x60];
    s32 unk_60;
} B32_818CF0E8_S_818CF0E8_7;
typedef struct B32_818CF0E8_S_818CF0E8_8_pre {
    void * unk_00;
    u8 pad_04[0x14];
} B32_818CF0E8_S_818CF0E8_8_pre;
typedef struct B32_818CF0E8_S_818CF0E8_9 {
    u8 pad_00[0x86];
    s16 unk_86;
} B32_818CF0E8_S_818CF0E8_9;
typedef struct {
    u16 h[6];
} B32_818CF0E8_Vec12;
typedef struct B32_818CEDC8_S_818CEDC8_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_08;   /* overlapping accesses */
} B32_818CEDC8_S_818CEDC8_0;
typedef struct B32_818CEDC8_S_818CEDC8_1_pre {
    u16 unk_00;
} B32_818CEDC8_S_818CEDC8_1_pre;
typedef struct B32_818CEDC8_S_818CEDC8_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x2];
    s16 unk_08;
    u8 pad_0A[0x42];
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
} B32_818CEDC8_S_818CEDC8_1;
typedef struct B32_818CEB58_S_818CEB58_0 {
    u8 pad_00[0x8];
    union { void * s; s32 u; } unk_08;   /* accessed as both */
    u8 pad_0C[0x4];
    s32 unk_10;
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
} B32_818CEB58_S_818CEB58_0;
typedef struct B32_818CEB58_S_818CEB58_1 {
    u8 pad_00[0x8];
    void * unk_08;
} B32_818CEB58_S_818CEB58_1;
typedef struct B32_818CEB58_S_818CEB58_2 {
    u8 pad_00[0x2];
    s16 unk_02;
} B32_818CEB58_S_818CEB58_2;
typedef struct B32_818CEB58_S_818CEB58_3 {
    u8 pad_00[0x6];
    s16 unk_06;
} B32_818CEB58_S_818CEB58_3;
typedef struct B32_818CEB58_S_818CEB58_4 {
    u8 pad_00[0x8];
    void * unk_08;
} B32_818CEB58_S_818CEB58_4;
typedef struct B32_818CEB58_S_818CEB58_5 {
    u8 pad_00[0xA];
    s16 unk_0A;
} B32_818CEB58_S_818CEB58_5;
typedef struct B32_818CEB58_S_818CEB58_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} B32_818CEB58_S_818CEB58_6;
typedef struct B32_818CE83C_S_8002403C_1 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x12];
    u8 * unk_18;
    u8 pad_1C[0x4];
    union { u8 * p; u32 * p2; } unk_20;   /* accessed as both */
    u8 pad_24[0x9C];
    u32 unk_C0;
} B32_818CE83C_S_8002403C_1;
typedef struct B32_818CE83C_S_8002403C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} B32_818CE83C_S_8002403C_2;
typedef struct B32_818CE83C_S_8002403C_3 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { u32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
} B32_818CE83C_S_8002403C_3;
typedef struct B32_818CE83C_S_8002403C_4_pre {
    void * unk_00;
    u8 pad_04[0x4];
} B32_818CE83C_S_8002403C_4_pre;
typedef struct B32_818CE83C_S_8002403C_4 {
    u8 pad_00[0x8];
    u32 unk_08;
    u8 pad_0C[0x26];
    s16 unk_32;
} B32_818CE83C_S_8002403C_4;
typedef struct B32_818CE83C_S_8002403C_5 {
    u8 pad_00[0x8];
    u8 * unk_08;
} B32_818CE83C_S_8002403C_5;
typedef struct { u32 addr:24; u32 length:8; } B32_818CE83C_PacketTag;
s32 func_8002403C(void *start_node, void *start_coords);
void func_8002428C(void *object_data, void *source_data);
void func_80024358( void *source, s16 field_34, s32 field_28, s16 field_52, s16 offset_x, s16 offset_y, s16 offset_z);
void func_80024478(void *state, void *position, void *object);
void func_80024578(void *record);
void func_800245C8(void *state, B32_818CEDC8_S_818CEDC8_0 *position, Rec_D_80082E80 *sprite);
void dungeonUpdateChasingStarEffect(void *entity, B32_818CF0E8_S_818CF0E8_1 *pos, B32_818CF0E8_S_818CF0E8_3 *gfx);
void dungeonFollowEntityEffectAndCleanup(B32_818CFB74_State *state, B32_818CFB74_Vec12 *position, B32_818CFB74_Graphic *graphic);
ObjectNodeHeader *func_8003FD64(s32, ObjectNodeHeader **);
s32 func_8004491C(void *, s32, ...);
void func_800478B8(void *);
s32 func_800A56E0(s32);
s16 func_800BCB04(s32, s32, s16);
void func_8003DB94(void *, void *, s32);
extern const B32_818CFB74_PackedOffsets D_80024004;
extern s16 D_80025924[5];
void *func_8003DF74(void *, void *, void *, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);
extern s32 func_80066460(s32, s32, s32, s32);
extern s32 func_80065420(void *, void *, void *, void *);
s32 dungeonCheckLeftTileAndCenterHeight();
extern void dungeonTryApplyConfusionStatus();
extern void func_800542BC();
extern s32 func_800A6D30();
extern s32 dungeonTryTriggerTargetRecordEffect();
extern s32 func_800A4778();
extern s32 func_80069EF8();
#endif
