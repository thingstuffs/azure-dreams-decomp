#ifndef DUNGEON_OVL_7F511800_P03_H
#define DUNGEON_OVL_7F511800_P03_H
#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"


typedef struct T_8017314C_S_8017314C_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} T_8017314C_S_8017314C_1;   /* arg0 in func_8017314C */





#include "shared/object_flags.h"

typedef struct T_80173450_S_80173450_0 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} T_80173450_S_80173450_0;   /* arg0 in func_80173450 */


typedef struct T_80173450_S_80173450_2 {
    u8 pad_00[0xC];
    union { u8 u8; s32 s32; } unk_0C;   /* accessed as both */
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} T_80173450_S_80173450_2;   /* arg2 in func_80173450 */

typedef struct T_80173450_S_80173450_3 {
    u8 pad_00[0x10];
    s32 unk_10;
} T_80173450_S_80173450_3;   /* global in func_80173450 */



extern void dungeonSetRecordIntegerTileCenter();
extern void dungeonBeginActorDisplayAction();
extern void dungeonApplyClampedActorValueDelta();
extern void func_8009A028(void *);
extern void func_8009A3D0(s32, s32, s32);
extern void func_800A2FE0(void *);
extern void func_800A32A4(void *);
extern void func_800A56E0(s32);
extern void dungeonAnnounceFamiliarDefeat(void *);
extern u8 D_80170E7C;
extern u8 D_80174D5C;
void updateDirectionalMotionAndRecenterActor(T_8017314C_S_8017314C_1 *action, EntityRec *motion, Rec_D_80082E80 *actor, void *source);
void fadeAndRemoveEntitySprite(void *action, void *unused, void *sprite, void *entity);
#endif
