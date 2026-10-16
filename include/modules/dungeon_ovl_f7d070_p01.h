#ifndef DUNGEON_OVL_F7D070_P01_H
#define DUNGEON_OVL_F7D070_P01_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"



typedef struct T_80170870_S_80170870_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} T_80170870_S_80170870_0;   /* obj in func_80170870 */

typedef struct T_80170870_S_80170870_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} T_80170870_S_80170870_1;   /* work in func_80170870 */

typedef struct T_80170870_S_80170870_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} T_80170870_S_80170870_2;   /* part_a in func_80170870 */

typedef struct T_80170870_S_80170870_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} T_80170870_S_80170870_3;   /* part_b in func_80170870 */

typedef struct T_80170870_S_80170870_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} T_80170870_S_80170870_4;   /* actor in func_80170870 */



extern void * func_8003FD64();
extern void func_8004491C();
extern s32 func_800A6D30();
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_800AA36C();
extern u8 D_80170A3C[];
extern s32 D_80170E68;
extern u8 D_80174194[];
extern u8 D_801741DC[];
void * func_80170870(s16 kind_flags, s16 x, s16 y, s16 part_value);
#endif
