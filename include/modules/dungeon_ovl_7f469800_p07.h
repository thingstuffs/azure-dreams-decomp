#ifndef DUNGEON_OVL_7F469800_P07_H
#define DUNGEON_OVL_7F469800_P07_H
#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"


typedef struct T_80175050_S_80175050_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} T_80175050_S_80175050_0;   /* arg0 in func_80175050 */

typedef struct T_80175050_S_80175050_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
    u8 pad_27[0x5];
    u8 * unk_2C;
} T_80175050_S_80175050_1;   /* arg2 in func_80175050 */

typedef struct T_80175050_S_80175050_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x1C];
    u8 unk_48;
    u8 pad_49[0x1B];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} T_80175050_S_80175050_2;   /* arg3 in func_80175050 */

typedef struct T_80175050_S_80175050_3 {
    u8 unk_00;
    u8 pad_01[0x9];
    u16 unk_0A;
} T_80175050_S_80175050_3;   /* var_v0 in func_80175050 */

typedef struct T_80175050_S_80175050_4 {
    u8 pad_00[0x9B];
    u8 unk_9B;
} T_80175050_S_80175050_4;   /* state0_arg0 in func_80175050 */




#define func_80171BEC_returning dungeonCreateTrackedAttachmentSprite



#include "records/Rec_func_800AA258_arg2.h"
#include "shared/entity.h"

typedef struct T_80175574_S_80175574_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} T_80175574_S_80175574_0;   /* arg0 in func_80175574 */


typedef struct {
    u8 pad00[0x8c];
    void *field8c;
    u8 pad90[0x0b];
    u8 state9b;
} T_80175574_Obj0;

typedef struct {
    u8 pad00[0x14];
    u16 flags14;
    u8 pad16[0x16];
    u8 *table2c;
} T_80175574_Obj2;

typedef struct {
    u8 pad00[0x1c];
    u32 flags1c;
    u8 pad20[5];
    u8 flag25;
    u8 pad26[4];
    s16 value2a;
    u8 pad2c[0x1c];
    u8 kind48;
    u8 pad49[0x1b];
    s16 value64;
    u8 pad66[7];
    s8 flag6d;
} T_80175574_Obj3;





typedef struct {
    u8 pad00[0x8c];
    void *field8c;
} T_801759A0_Obj0;

typedef struct {
    u8 pad00[0x2c];
    u8 *table2c;
} T_801759A0_Obj2;

typedef struct {
    u8 pad00[0x1c];
    u32 flags1c;
    u8 pad20[5];
    u8 flag25;
    u8 pad26[4];
    s16 value2a;
    u8 pad2c[0x1c];
    u8 kind48;
} T_801759A0_Obj3;



extern s32 func_80042900();
extern void func_80042B68();
extern void func_80047784();
extern s32 dungeonCheckEntityRelation();
extern s16 dungeonGetTileChebyshevDistance();
extern s32 func_800A2C34();
extern s32 func_800A6D30();
extern s32 func_800A9A04();
extern void func_800A9A0C();
extern void dungeonBeginPushedActorMove();
extern s32 dungeonBeginReadyActorDirectionalAction();
extern s32 dungeonAdvanceActorPendingAction();
extern void func_800AA888();
extern void dungeonCreateTrackedAttachmentSprite();
extern s32 func_800AC82C(T_801759A0_Obj0 *, void *, T_801759A0_Obj2 *, T_801759A0_Obj3 *);
extern s32 dungeonCheckActorFloorTrap(T_801759A0_Obj2 *, T_801759A0_Obj3 *);
extern u8 D_80175E54[];
extern u8 D_80175E5C[];
extern u8 D_80175E64[];
extern u8 D_80175E6C[];
extern u8 D_80175E74[];
extern u8 D_80175E7C[];
extern s32 D_80175DC4;
extern s32 D_80175DCC;
extern s32 D_80175DD4;
extern u8 D_80175E24[];
extern u8 D_80175E2C[];
extern u8 D_80175E34[];
void dungeonUpdateActorActivityState(void *task, s32 task_id, void *sprite_in, void *actor_in);
void dungeonUpdateActorActionAnimationState(T_80175574_Obj0 *controller, void *context, T_80175574_Obj2 *animation, T_80175574_Obj3 *actor);
void dungeonUpdateDirectionalActionDisplay(T_801759A0_Obj0 *actor, void *context, T_801759A0_Obj2 *display_arg, T_801759A0_Obj3 *state_arg);
extern void dungeonUpdateActorBehavior();
#endif
