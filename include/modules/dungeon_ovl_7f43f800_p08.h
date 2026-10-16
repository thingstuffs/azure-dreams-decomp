#ifndef DUNGEON_OVL_7F43F800_P08_H
#define DUNGEON_OVL_7F43F800_P08_H
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_func_800AA258_arg2.h"






#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef struct T_801748D0_S_801748D0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} T_801748D0_S_801748D0_0;   /* arg0 in func_801748D0 */


typedef struct T_801748D0_S_801748D0_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} T_801748D0_S_801748D0_2;   /* arg2 in func_801748D0 */

typedef struct T_801748D0_S_801748D0_3 {
    u8 pad_00[0x94];
    u16 unk_94;
    s16 unk_96;
    u8 pad_98[0x6];
    s16 unk_9E;
    u8 pad_A0[0x2];
    s16 unk_A2;
    u8 pad_A4[0x4];
    void * unk_A8;
} T_801748D0_S_801748D0_3;   /* body in func_801748D0 */

typedef struct T_801748D0_S_801748D0_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    union { struct { void * v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    void * unk_0C;
    void * unk_10;
} T_801748D0_S_801748D0_4;   /* obj in func_801748D0 */


typedef struct T_801748D0_S_801748D0_6_pre {
    void * unk_00;
    u8 pad_04[0x14];
} T_801748D0_S_801748D0_6_pre;   /* the 0x18 bytes before body_link in func_801748D0, addressed as body_link[-1] */

typedef struct T_801748D0_S_801748D0_7 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0xC];
    u8 * unk_2C;
} T_801748D0_S_801748D0_7;   /* mesh in func_801748D0 */

typedef struct T_801748D0_S_801748D0_9 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} T_801748D0_S_801748D0_9;   /* anchor in func_801748D0 */

typedef struct T_801748D0_S_801748D0_10 {
    u8 pad_00[0xC];
    void * unk_0C;
} T_801748D0_S_801748D0_10;   /* scratch in func_801748D0 */

typedef struct T_801748D0_S_801748D0_11 {
    u8 pad_00[0x8];
    s32 unk_08;
} T_801748D0_S_801748D0_11;   /* link in func_801748D0 */




typedef struct {
    s16 delta[3];
    u16 pad06;
    u16 pos[3];
    u16 pad0E;
    s32 out0[2];
    s32 out1;
    s32 out2;
} T_801748D0_LocalFrame;

typedef struct {
    s32 w[12];
} T_801748D0_MeshCopy;

extern void func_80047784();
extern s32 findEligibleActorAtTileAndHeight();
extern s32 func_800A2B5C();
extern s32 dungeonAdvanceStatusTimers();
extern s32 dungeonApplyCameraOffsetAndSelectTarget();
extern s32 resolveRecordOrientationOrFallback(s32, void *, s16 *, s16);
extern void * func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_80065420(void *, void *, void *, void *);
extern void dungeonSetRecordIntegerTileCenter(void *, u8, u8);
extern void func_800A56E0(s32);
extern void dungeonReduceActorFoodMeter(void *, s32);
extern void func_800C8788(void *, void *);
extern u8 D_80174EC8;
extern s8 D_800DCECC[];
extern u8 D_80174E88[];
extern u8 D_80174ED0[];
void dungeonStartDirectionalActionAndRecordTile(void *action_state, void *action_context, void *sprite, EntityRec *actor);
void dungeonAdvanceTimedActorVisualEffect(void *effect_state, EntityRec *position, void *source_mesh, EntityRec *actor);
extern void func_80170AD0();
extern void dungeonUpdateActorBehaviorAndDirection();
#endif
