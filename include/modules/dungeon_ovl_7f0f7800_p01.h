#ifndef DUNGEON_OVL_7F0F7800_P01_H
#define DUNGEON_OVL_7F0F7800_P01_H
#include "common.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"


typedef void (*T_80170AA4_EntityCallback)(void *, void *, void *, void *);



typedef struct T_80170AA4_S_80170AA4_0 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xD];
    s16 unk_12;
    union { u16 n; u16 v; } unk_14;   /* accessed as both */
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} T_80170AA4_S_80170AA4_0;   /* arg2 in func_80170AA4 */

typedef struct T_80170AA4_S_80170AA4_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} T_80170AA4_S_80170AA4_1;   /* entity in func_80170AA4 */

typedef struct T_80170AA4_S_80170AA4_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} T_80170AA4_S_80170AA4_2;   /* arg1 in func_80170AA4 */

extern void func_80042984();
extern void selectIndirectTableEntry();
extern void func_800478B8();
extern void dungeonApplyMonsterKoyawData();
extern void func_800A56E0();
extern s32 dungeonRefreshActorFacingAndLifecycle();
extern void func_800AA36C();
extern s32 func_800BCB04();
extern T_80170AA4_EntityCallback D_80174018[];
void dungeonUpdateEntityCallbacksDirectionalAnimationMovementGroundContact(void *actor, T_80170AA4_S_80170AA4_2 *motion, void *part);
extern void func_80170F68();
#endif
