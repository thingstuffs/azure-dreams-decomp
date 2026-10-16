#ifndef DUNGEON_OVL_FA1070_H
#define DUNGEON_OVL_FA1070_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"


typedef s32 M2C_UNK;

typedef struct S_8014C870_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8014C870_0;   /* obj in func_8014C870 */

typedef struct S_8014C870_1 {
    u8 pad_00[0x13];
    s8 unk_13;
} S_8014C870_1;   /* work in func_8014C870 */

typedef struct S_8014C870_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8014C870_2;   /* part_a in func_8014C870 */

typedef struct S_8014C870_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_8014C870_3;   /* part_b in func_8014C870 */

typedef struct S_8014C870_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_8014C870_4;   /* actor in func_8014C870 */


typedef struct Work {
    u8 pad14[0x14];
    s32 flags14;
    u8 pad18[4];
    s32 flags1c;
} Work;

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800A6D30(void);
extern void func_800A48F0(void *, s32, s32);
extern void func_800A9C18(void *, void *, void *, s16);
extern void func_800AA36C(void *, void *, void *, void *);
extern void func_8014CA3C();
extern void dispatchDungeonActorBehaviorAndFacing();
extern u8 D_80150194[];
extern u8 D_801501DC[];

void * dungeonCreateActorWithKindParts(s16 kind_flags, s16 grid_x, s16 grid_y, s16 part_value);
#endif
