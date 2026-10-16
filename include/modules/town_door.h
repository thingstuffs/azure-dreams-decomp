#ifndef MODULES_TOWN_DOOR_H
#define MODULES_TOWN_DOOR_H

#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800A0668_arg0.h"
#include "shared/object_flags.h"
#include "shared/runtime_dispatch.h"
#include "shared/sys_flags.h"

typedef struct S_800A0668_1 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800A0668_1;

typedef struct S_800A06A4_0 {
    s32 * unk_00;
    u8 pad_04[0x14];
    s32 unk_18;
    s32 * unk_1C;
    u8 pad_20[0x40];
    s32 * unk_60;
    u8 pad_64[0x14];
    s16 unk_78;
    u8 pad_7A[0x4];
    s16 unk_7E;
    u8 pad_80[0x20];
    s16 unk_A0;
    u8 pad_A2[0x2];
    u8 unk_A4;
} S_800A06A4_0;

typedef struct S_func_800A0708_0 {
    u8 pad_00[0x50];
    void (*unk_50)(void *, void *, void *, s32);
    u8 pad_54[0x44];
    s8 *unk_98;
} S_func_800A0708_0;

typedef struct S_func_800A0708_1 {
    u16 unk_00;
} S_func_800A0708_1;

typedef struct {
    u8 pad00[0x50];
    void *unk50;
    u8 pad54[0x68 - 0x54];
    s16 unk68;
    u8 pad6A[0x72 - 0x6A];
    s16 unk72;
} S800A3088Arg0;

typedef struct {
    u8 pad0[2];
    s16 unk2;
    u8 pad4[2];
    s16 unk6;
} S800A3088Arg2;

typedef struct S_800A08F0_0 {
    u8 pad_00[0x50];
    s32 * unk_50;
    u8 pad_54[0x1A];
    u16 unk_6E;
} S_800A08F0_0;

typedef struct S_800A092C_0 {
    u8 pad_00[0x50];
    s32 * unk_50;
    u8 pad_54[0x18];
    u16 unk_6C;
} S_800A092C_0;

typedef struct S_800A0958_0 {
    u8 pad_00[0x50];
    s32 * unk_50;
    u8 pad_54[0x1A];
    u16 unk_6E;
} S_800A0958_0;

typedef struct Node {
    struct Node *next;
    u8 pad_04[0xC];
    s32 field_10;
    u8 pad_14[0xA];
    u16 flags;
} Node;

typedef struct {
    Node *head;
    s32 pad[2];
} ListHead;

typedef struct {
    u8 pad_00[0x48];
    s32 field_48;
} NodeData;

typedef struct {
    s8 pad[0x50];
    void *unk50;
    s8 pad2[0x18];
    s16 unk6C;
} EntityStruct;

typedef struct S_800A0A54_0 {
    u8 pad_00[0x88];
    s16 unk_88;
} S_800A0A54_0;

typedef struct S_800A0A88_0 {
    u8 pad_00[0x50];
    s32 * unk_50;
    u8 pad_54[0x3C];
    s16 unk_90;
} S_800A0A88_0;

typedef struct S_800A0C30_0 {
    u8 pad_00[0x50];
    s32 * unk_50;
    u8 pad_54[0x1E];
    s16 unk_72;
    u8 pad_74[0x1C];
    s16 unk_90;
} S_800A0C30_0;

typedef struct S_800A0C30_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800A0C30_1;

typedef struct S_800A0CC0_0 {
    u8 pad_00[0x50];
    s32 * unk_50;
} S_800A0CC0_0;

typedef struct S_800A0DAC_0 {
    u8 pad_00[0x50];
    s32 * unk_50;
    u8 pad_54[0x18];
    s16 unk_6C;
    u16 unk_6E;
} S_800A0DAC_0;

typedef struct S_800A0E3C_1 {
    u8 pad_00[0x48];
    s32 unk_48;
} S_800A0E3C_1;

typedef struct S_800A0F10_0 {
    u8 pad_00[0x10];
    u16 unk_10;
} S_800A0F10_0;

s32 townCheckDoorStatusInverted(void *object);
void townInitializeDoorVariant(void *record_data, s32 initial_value);
void townHandleDoorCheckResult(S_func_800A0708_0 *object, void *callback_arg, s32 callback_data);
void townInstallNextDoorHandler(void *object, s32 unused_value, s32 update_context, u8 unused_flags);
void townEmitDoorPositionEffect(S800A3088Arg0 *entity, s32 action, S800A3088Arg2 *position);
void townOpenDoorToTarget(void *object, void *context);
void townDoorNoOp(void);
void townAdvanceDoorOpenAngle(S_800A08F0_0 *door);
void townTickDoorOpenCountdown(S_800A092C_0 *state);
void townAdvanceDoorCloseAngle(S_800A0958_0 *door);
void *townFindDoorKeyedNode(s32 requested_value);
void door_open_demo_set_sub(s32 door_id, s16 demo_angle);
void door_open_demo_set(s32 script_context);
void door_atari_on_off(s32 door_id, s16 collision_enabled);
void into_dn_door_demo_set(void);
void townTriggerDoorInteractionEffect(void *actor, void *target, void *position);
void townChangeDoorMap(void *map_source, s32 *map_table);
void townAdvanceDoorStep(void *entity);
void townSelectTowerEntryHandlerByItemCount(S_800A0C30_0 *script_state, void *unused_context, S_800A0C30_1 *event_params);
void townSetDoorHandlerIfReady(S_800A0CC0_0 *object, s32 value_1, s32 value_2, s32 value_3);
void townUpdateDoorCompletionState(u8 *object, s32 unused, s32 state_id, s32 state_arg);
void townAdvanceDoorStateCounter(S_800A0DAC_0 *state, s32 unused, s32 context_a, s32 context_b);
void townTickDoorCountdown(Rec_func_800A0668_arg0 *object, S_800A0E3C_1 *source, s32 update_arg_a, s32 update_arg_b);
void into_dn_door_jobs(void);
s32 townCheckDoorInputAndAngle(Rec_func_800A0668_arg0 *object, s32 test_value);

extern void func_80033D08(void *);
extern s32 townClassifyObjectAgainstBounds(void *, void *);
extern s32 townCreateObjectWithSharedData(void *input_first, s32 input_second, s32 input_third, u8 input_fourth);
extern void townInitializePlayerEntityCallbacks(s32 entity_id, s32 x, s32 y);
extern void func_8009A8EC(s16 actor_value, s16 position_value_1, s16 position_value_2);
extern s32 change_map();
extern s32 get_player_homerank();
extern s32 func_800B28A0();
extern s16 townCreateObjectsDescendingByCount();
s32 townCountConsecutiveNonzeroEntriesUpTwenty();
void townSetPlayerBlockValue();
s32 func_800352FC(void);
s16 townInitializeObjectItemsInReverse(void *ptr, s32 stateId, s16 currentState);
void townNoOpCallbackA(void *ptr, s32 stateId, s32 stateArg);
void loadIndexedResourcePackage(s32 value);
void soundSetCdCueParameters(s32 value0, s32 value1, s32 value2, s32 value3);
void SD_Call(s32 value);
extern void townDecreaseValueAndAdvanceCounter();
extern void townProcessTerminatedShopIds(void);
extern void clearResidentBitmapBit(s32 a0);
extern void townApplyBuildingPendingUpdates(void);
extern void townDispatchConditionalTablePairs(void);
s32 townGetSmallestSignedOverlapAxisAmountTwoIntersectingBoxes();

extern s32 D_800D09E0;
extern ListHead D_80081498;
extern s32 D_800D4404;
extern u8 D_80100B70[];
extern s32 D_8006CD58[];
extern s16 D_8008146C;
extern s32 D_800834B8;
extern s32 D_80091260;
extern s32 D_80091528;
extern s32 D_800CFCB4;

#endif
