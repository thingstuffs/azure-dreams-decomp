#ifndef DUNGEON_OVL_7F0F7800_P07_H
#define DUNGEON_OVL_7F0F7800_P07_H
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct T_80173AD4_S_80173AD4_0 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x6];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x41];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} T_80173AD4_S_80173AD4_0;   /* actor in func_80173AD4 */

typedef struct T_80173AD4_S_80173AD4_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} T_80173AD4_S_80173AD4_1;   /* state in func_80173AD4 */

typedef struct T_80173AD4_S_80173AD4_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0xA];
    u16 unk_A6;
    u8 pad_A8[0x2];
    s16 unk_AA;
} T_80173AD4_S_80173AD4_2;   /* work in func_80173AD4 */

typedef struct T_80173AD4_S_80173AD4_3 {
    u8 pad_00[0x12];
    u16 unk_12;
    u8 pad_14[0x10];
    u8 unk_24;
    u8 unk_25;
} T_80173AD4_S_80173AD4_3;   /* part_b in func_80173AD4 */



extern s32 func_80047784();
extern s32 func_800990FC();
extern s32 func_80099194();
extern void * func_80099290();
extern s32 func_80099734();
extern void func_8009A21C();
extern void func_8009A3D0();
extern s32 func_800A2BDC();
extern s32 func_800A5720();
extern u8 D_80170854[];
extern u8 D_80173FD0[];
void func_80173AD4(void *work_in, void *part_a, void *part_b_in, void *actor);
#endif
