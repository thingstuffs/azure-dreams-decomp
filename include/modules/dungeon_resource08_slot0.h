#ifndef DUNGEON_RESOURCE08_SLOT0_H
#define DUNGEON_RESOURCE08_SLOT0_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "m2c_compat.h"
#include "shared/def_table.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "records/Rec_func_801736F4_arg0.h"
#include "shared/object_flags.h"

#define NULL 0
typedef s32 R08_8017087C_M2C_UNK;
typedef struct R08_8017087C_S_8017087C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} R08_8017087C_S_8017087C_0;
typedef struct R08_8017087C_S_8017087C_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} R08_8017087C_S_8017087C_1;
typedef struct R08_8017087C_S_8017087C_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} R08_8017087C_S_8017087C_2;
typedef struct R08_8017087C_S_8017087C_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} R08_8017087C_S_8017087C_3;
typedef struct R08_8017087C_S_8017087C_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} R08_8017087C_S_8017087C_4;
typedef void (*R08_80170A50_EntityCallback)(void *, void *, void *, void *);
typedef struct R08_80170A50_S_80170A28_0 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} R08_80170A50_S_80170A28_0;
typedef struct R08_80170A50_S_80170A28_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x68];
    u16 unk_88;
} R08_80170A50_S_80170A28_1;
typedef struct R08_80170A50_S_80170A28_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} R08_80170A50_S_80170A28_2;
typedef struct R08_80170E7C_S_80170E7C_7 {
    void * unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    void * unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} R08_80170E7C_S_80170E7C_7;
typedef struct R08_80170E7C_S_80170E7C_8 {
    u8 pad_00[0x4];
    s32 unk_04;
} R08_80170E7C_S_80170E7C_8;
typedef struct R08_801715B4_S_80171570_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   
    u8 pad_72[0x18];
    s16 unk_8A;
} R08_801715B4_S_80171570_0;
typedef struct R08_801715B4_S_80171570_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
} R08_801715B4_S_80171570_2;
typedef struct R08_801715B4_S_80171570_3 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} R08_801715B4_S_80171570_3;
typedef struct R08_801717F8_S_80171C34_1 {
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
} R08_801717F8_S_80171C34_1;
typedef struct R08_801717F8_S_80171C34_2 {
    u8 pad_00[0x24];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   
    union { s8 s; u8 u; } unk_26;   
} R08_801717F8_S_80171C34_2;
typedef struct R08_801717F8_S_80171C34_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} R08_801717F8_S_80171C34_3_pre;
typedef struct R08_801717F8_S_80171C34_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} R08_801717F8_S_80171C34_3;
typedef struct R08_801717F8_S_80171C34_5 {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0x2];
    union { s8 s; u8 u; } unk_9C;   
} R08_801717F8_S_80171C34_5;
typedef struct R08_801717F8_S_80171C34_7 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} R08_801717F8_S_80171C34_7;
typedef struct R08_801717F8_S_80171C34_8 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} R08_801717F8_S_80171C34_8;
typedef struct R08_801717F8_DungeonRecord {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} R08_801717F8_DungeonRecord;
typedef struct R08_80172168_Ent R08_80172168_Ent;
typedef struct R08_80172280_S_80172628_0 {
    u8 pad_00[0x46];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x28];
    s8 unk_9A;
} R08_80172280_S_80172628_0;
typedef struct R08_801723C4_S_801724A8_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_90;   
} R08_801723C4_S_801724A8_0;
typedef struct R08_8017245C_S_80172478_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x8];
    s32 unk_A4;
    union { s16 s; u16 u; } unk_A8;   
} R08_8017245C_S_80172478_0;
typedef struct R08_8017245C_S_80172478_2 {
    u8 pad_00[0x1C];
    union { u32 s; s32 u; } unk_1C;   
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} R08_8017245C_S_80172478_2;
typedef struct {
    u8 pad0[0x8C];
    void (*callback)(void *, void *, void *, void *);
} Resource08CallbackState;
typedef struct R08_80172830_S_80172830_0 {
    u8 pad_00[0x90];
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} R08_80172830_S_80172830_0;
typedef struct R08_80172CE8_S_80172CE8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} R08_80172CE8_S_80172CE8_0;
typedef struct R08_80172CE8_S_80172CE8_1_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} R08_80172CE8_S_80172CE8_1_pre;
typedef struct R08_80172CE8_S_80172CE8_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} R08_80172CE8_S_80172CE8_2;
typedef struct R08_80172CE8_S_80172CE8_3 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} R08_80172CE8_S_80172CE8_3;
typedef struct R08_80173234_S_80173234_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   
    u8 pad_98[0x3];
    u8 unk_9B;
} R08_80173234_S_80173234_0;
typedef struct R08_80173234_S_80173234_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} R08_80173234_S_80173234_1;
typedef struct {
    s8 pad_00[0x8C];
    void *unk_8C;
} R08_80173F20_Actor;
typedef struct {
    u8 pad_00[0x2C];
    u8 *unk_2C;
} R08_80173F20_Entity;
typedef struct {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} R08_80173F20_MapObject;
typedef struct R08_801740F4_Entry {
    u8 pad00[6];
    s16 unk06;
    void *unk08;
    struct R08_801740F4_Entry *unk0C;
    u8 pad10[4];
    u16 unk14;
} R08_801740F4_Entry;
typedef struct {
    u8 pad[0x13C];
    s32 value;
} R08_801740F4_Scratchpad;
typedef struct {
    u8 pad[0x5218];
    s16 value;
} R08_801740F4_GlobalPage;
typedef struct {
    u8 pad[0x1A];
    u16 field_1A;
    u16 field_1C;
    u16 field_1E;
} R08_80174180_Object;
typedef struct R08_801741D0_S_801741D0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s8 unk_20;
} R08_801741D0_S_801741D0_0;
typedef struct R08_801741D0_S_801741D0_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} R08_801741D0_S_801741D0_1;
typedef struct R08_801741D0_S_801741D0_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} R08_801741D0_S_801741D0_2;
typedef struct R08_801741D0_S_801741D0_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} R08_801741D0_S_801741D0_3;
typedef struct {
    u32 words[3];
} R08_801741D0_Packed12 __attribute__((packed));
typedef struct R08_801743BC_S_801743BC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0x26];
    s16 unk_3A;
} R08_801743BC_S_801743BC_0;
typedef struct R08_801743BC_S_801743BC_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} R08_801743BC_S_801743BC_1;
typedef struct R08_801743BC_S_801743BC_3 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} R08_801743BC_S_801743BC_3;
typedef struct {
    u8 pad0[2];
    u16 flags;
    u8 pad4[6];
    u16 count;
} R08_80174470_DungeonState;
typedef struct R08_80174648_S_80174648_0_pre {
    u16 unk_00;
} R08_80174648_S_80174648_0_pre;
typedef struct R08_80174648_S_80174648_0 {
    u8 pad_00[0x96];
    union { s16 s; u16 u; } unk_96;   
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x10];
    void * unk_AC;
    s16 unk_B0;
} R08_80174648_S_80174648_0;
typedef struct R08_80174648_S_80174648_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x16];
    union { u16 u; s16 s; } unk_2A;   
    u8 pad_2C[0x34];
    union { void * p; s32 i; } unk_60;   
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x1C];
    u16 unk_8A;
} R08_80174648_S_80174648_1;
typedef struct R08_80174648_S_80174648_2 {
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
} R08_80174648_S_80174648_2;
typedef struct R08_80174648_S_80174648_3 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} R08_80174648_S_80174648_3;
typedef struct R08_80174648_S_80174648_6_pre {
    void * unk_00;
    u8 pad_04[0x10];
} R08_80174648_S_80174648_6_pre;
typedef struct R08_80174648_S_80174648_6 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} R08_80174648_S_80174648_6;
typedef struct R08_80174648_S_80174648_7 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0x16];
    u8 * unk_2C;
} R08_80174648_S_80174648_7;
typedef struct R08_80174648_S_80174648_8 {
    u8 pad_00[0xA];
    u16 unk_0A;
} R08_80174648_S_80174648_8;
typedef struct R08_80174648_S_80174648_9 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} R08_80174648_S_80174648_9;
typedef struct R08_80174648_S_80174648_10 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} R08_80174648_S_80174648_10;
typedef struct R08_80174648_S_80174648_11 {
    u8 unk_00;
} R08_80174648_S_80174648_11;
extern s32 rand(void);
extern int abs(int);
extern void *memcpy(void *, const void *, u32);
extern s32 Control_CD();
s32 func_8003FD64();
s32 func_8004491C();
s32 func_800A6D30();
s32 func_800A48F0();
void func_800A9C18();
s32 func_800AA36C();
void selectIndirectTableEntry();
void func_800478B8();
void dungeonApplyMonsterKoyawData();
s32 dungeonRefreshActorFacingAndLifecycle();
s16 func_800BCB04();
s32 resolveRecordOrientationOrFallback();
void func_80047784();
s32 dungeonCheckEntityRelation();
s32 func_8009FB34();
s32 dungeonCompareMonsterNeighborValues();
s32 dungeonGetRoundedFacingAndRoundingFlag();
s32 func_800A1C58();
void func_800A9A0C();
void dungeonBeginPushedActorMove();
s32 dungeonBeginReadyActorDirectionalAction();
s32 dungeonAdvanceActorPendingAction();
void func_800AA888();
s32 dungeonResetActorActionState();
s32 dungeonProcessSelectedActorRecord();
void dungeonBeginActorSpellAction();
void func_8009A21C();
void func_8009A3D0();
s32 dungeonCheckMovementClearanceAndHeight();
s32 dungeonUpdateActorProximityFlag();
s32 dungeonFindValidMonsterNeighbor();
s32 dungeonPlaceActorAtDirectionalNeighbor();
s32 dungeonGetActorHeightDifference();
s32 dungeonCheckDiagonalSideHeight();
s32 dungeonRebuildMonsterReachableTiles();
s32 dungeonPrepareDirectionalAttack();
s32 func_800A2B5C();
u32 func_800A2CB8();
s32 dungeonApplyCameraOffsetAndSelectTarget();
s32 func_800A2BDC();
s32 dungeonRelinkEntityAndClearHighFlag();
s32 dungeonAdvanceStatusTimers();
s32 dungeonUpdateActorMovementToTile();
void dungeonReduceActorFoodMeter();
s32 dungeonCheckActorFloorTrap();
s32 func_800644B8();
void dungeonSetRecordIntegerTileCenter();
void func_800A9A04();
s32 dungeonUpdateLinkedActorMotion();
s32 dungeonResolveAttackDamageAndEffects();
s32 func_800A56E0();
s32 getCdCommandQueueDepth();
s32 dungeonScanMonsterAlongHeading();
s32 dungeonCreateActorSpellEffect();
void dungeonCreateTwoRowObjectGroup();
void dungeonBeginActorDisplayAction();
void dungeonApplyClampedActorValueDelta();
s32 dungeonUpdateActorDefeatRemoval();
s32 dungeonUpdateActorHopAndShrink();
s32 dungeonAdvanceActorRemoval();
s32 dungeonUpdateActorHopAndGrow();
s32 func_80042900();
void func_80042B68();
s32 dungeonGetTileChebyshevDistance();
s32 func_800A2C34();
s32 func_800AC82C();
s32 dungeonUpdateThrownActorTravel();
s32 dungeonInterpolateActorToTerrainTile();
s32 dungeonUpdateSpinningActorFall();
s32 dungeonUpdateActorFadeIn();
void func_800453E0();
void func_80044A50();
void func_8003DB94();
void soundSetCdCueParameters();
void func_80041588();
s32 func_800445E0();
s32 lookupMaskedByteTable();
s32 func_80069EF8();
void func_8009A028();
void dungeonDecrementMonsterEntryCount();
s32 dungeonAdvanceStagedEntityLoad();
s32 dungeonCreateStatusLinkedRenderEffect();
s32 dungeonSelectNearbyTargetAndInitializeSlot();
s32 dungeonResolveActorFloorTrapOnce();
s32 dungeonPropagateActorActionFlag();
extern u8 D_80174C3C[];
extern u8 D_80174C8C[];
extern u8 D_80174C94[];
extern u8 D_800D79B0[];
extern u8 D_800DEA68[];
extern u8 D_80174C34[];
extern u8 D_80174C44[];
extern u8 D_80174C84[];
extern u8 D_80174C2C[];
extern u8 D_8006CD00[];
extern u8 D_80174C4C[];
extern u8 D_80174C54[];
extern u8 D_80174C5C[];
extern u8 D_800E3DE8[];
extern u8 D_80174C64[];
extern u8 D_80174C6C[];
extern u8 D_80174C7C[];
extern u8 D_80174C74[];
extern u8 D_80174D14[];
extern u8 D_80174D08[];
extern u8 D_800DCF5E[];
extern u8 D_80174D1C[];
extern u8 D_8003E140[];
extern u8 D_8006CD58[];
extern u8 D_800DCEEC[];
extern u8 D_800DCF5C[];
extern u8 D_8014A000[];
extern u8 D_80174CF4[];
extern u8 D_80174CFC[];
extern u8 D_80174D18[];
extern u8 D_80174D19[];
void *func_8017087C(s16 kind_flags, s16 tile_x, s16 tile_y, s16 part_id);
void func_80170A50(void *entity, R08_80170A50_S_80170A28_2 *motion, void *part);
void dungeonUpdateActorBehaviorAndEffect(void *actor, EntityRec *position, SpriteFrameState *object, EntityRec *actor_data);
void func_801715B4(void *action, s32 action_id, void *entity, void *move_state);
void func_801717F8(void *move_data, void *context, void *position_data, void *actor_data);
void func_80171F40(void *object, void *unused, void *display, void *orientation);
s32 dungeonUpdateActorAnimationBehaviorAndFacing(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, SpriteFrameState *sprite, EntityRec *actor);
void func_80172168(void *action_state, void *action_context, void *sprite, EntityRec *actor);
s32 func_80172280(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg);
void func_801723C4(R08_801723C4_S_801724A8_0 *state, s32 context, s32 source, s32 target);
void func_8017245C(void *action, void *motion, void *sprite, void *actor);
void dungeonAdvanceATimedActorAnimationAppliesCompletionEffects(Resource08CallbackState *state, void *entity, void *position, void *graphic);
void dungeonUpdateStagedMovementAndReturnToTile(void *action, EntityRec *motion, void *sprite, EntityRec *actor);
void dungeonUpdateItemActivationAndCleanup(void *action, EntityRec *motion, void *actor, EntityRec *object);
void func_80173234(void *action, void *motion, void *sprite, void *entity);
void func_80173688(void *state, void *motion, void *position, void *actor);
void func_801736A8(void *state, void *motion, void *position, void *actor);
void func_801736C8(void *state, void *motion, void *position, void *actor);
void func_801736E8(Resource08CallbackState *state, void *motion, void *position, void *actor);
void dungeonUpdateObjectOrSelectDirectionalData(void *controller, s32 actor_index, void *sprite, EntityRec *actor);
void func_80173BE4(void *controller, void *context, void *sprite, EntityRec *entity);
void func_80173F20(R08_80173F20_Actor *actor, s32 action, R08_80173F20_Entity *entity, R08_80173F20_MapObject *map_object);
void func_80173FE8(Resource08CallbackState *state, void *entity, void *position, void *graphic);
void func_8017404C(Resource08CallbackState *state, void *motion, void *position, void *actor);
void dungeonCreateFourDirectionalEffects(Resource08CallbackState *state, void *motion, void *position, void *actor);
void func_801740BC(Resource08CallbackState *state, void *motion, void *position, void *actor);
s32 dungeonStartBankActorHitReaction(void *initial_payload, s32 entry_data, R08_801740F4_Entry *entry, s32 unused);
void dungeonAdvanceObjectAngleAndHeight(u16 *record_data, s32 unused, R08_80174180_Object *object);
void dungeonCreateTintedRotatedSprite(s32 unused_0, R08_801741D0_S_801741D0_3 *source_pos, s32 unused_2, s8 green, u8 red_blue);
void dungeonUpdateTimedEffectAndExpire(void *effect, s32 x, s32 y);
void dungeonCreatePositionedSpriteEffect(M2C_UNK unused, EntityRec *source_pos, void *unused_context);
void func_80174470(void *entity_data, s32 unused_1, s32 unused_2, void *other_data);
void func_8017451C(u8 *task, void *context, u8 *input);
void dungeonAdvanceEffectAndChildAnimation(void *effect_state, EntityRec *position, Rec_D_80082E80 *entity, void *actor);
void func_80174BBC(Resource08CallbackState *state, void *motion, void *position, void *actor);
void func_80174BF4(Resource08CallbackState *state, void *motion, void *position, void *actor);
#endif
