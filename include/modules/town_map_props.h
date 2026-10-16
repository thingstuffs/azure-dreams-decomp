#ifndef MODULE_TOWN_MAP_PROPS_H
#define MODULE_TOWN_MAP_PROPS_H
#include "common.h"
#include "m2c_compat.h"
#include "shared/slus_callbacks.h"
#include "shared/object_node.h"
#include "records/Rec_D_80082E80.h"
typedef struct TownPropPosition { s32 unk_00, unk_04, unk_08; } TownPropPosition;
struct S_800BDE7C_0;
struct S_800BDE7C_1;
struct S_800BDFA0_0;
struct TownPropAnimationActor;
struct TownPropAnimationDestination;
struct S_800BE214_0;
struct S_800BE214_2;
void *townCreatePositionedGraphicObject(TownPropPosition *position, s32 object_param, s32 graphics_id);
void *townCreatePositionedVisualObject(TownPropPosition *position, s32 object_data, s32 angle, s32 visual_data);
void func_800BDC98(s16 start_x, s16 start_y, s16 mode, s32 pair_index);
void townFillWrappedFourByFourGrid(s32 start_x, s16 start_y, s32 unused_value);
void townUpdateRecordOutputGrid(struct S_800BDE7C_0 *record, s32 unused_value, struct S_800BDE7C_1 *output, s32 unused_value2);
void townNoOpEffectCallback(void);
void townInitializeRecordVisualState(struct S_800BDFA0_0 *record, s32 unused, s32 value);
void townCopyRecordStateToDestination(struct TownPropAnimationActor *self, s32 unused_value, struct TownPropAnimationDestination *destination);
void townAdvanceActorAnimationPose(struct S_800BE214_0 *actor, struct S_800BE214_2 *pose, Rec_D_80082E80 *animation);
void func_8003DB94(void *destination, void *animation, s16 mode);
void *func_8003FD64(s32 object_type, void *list);
s32 func_8004491C(void *entry, s32 registration_id);
void func_800478B8(void *animation);
s32 townCheckTransformIdentifierAndHook(s32 requested_id);
s32 func_800352FC(void);
s32 func_80064584(s32 angle);
s32 rand(void);
s32 func_80046398(void *group_data, void *position, void *render_data, s32 unused);
void townRandomizePairedObjectMotion(void *pair);
void townAdvanceMotionAndFlagZeroVelocity(void *actor, void *motion, s32 actor_id);
void *memcpy(void *dst, const void *src, u32 n);
/* The caller's historical short arguments are explicit casts in its body.
 * The grid helper's third argument is passed by retail and unused by it. */
#endif
