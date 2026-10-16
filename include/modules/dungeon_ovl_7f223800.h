#ifndef DUNGEON_OVL_7F223800_H
#define DUNGEON_OVL_7F223800_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"


typedef s32 M2C_UNK;

typedef struct S_8015E854_0 {
    u8 pad_00[0x8];
    void ** unk_08;
    void ** unk_0C;
    void * unk_10;
} S_8015E854_0;   /* objectBase in func_8015E854 */

typedef struct S_8015E854_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8015E854_1;   /* result in func_8015E854 */

typedef struct S_8015E854_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8015E854_2;   /* data08 in func_8015E854 */

typedef struct S_8015E854_3 {
    u8 pad_00[0x10];
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_8015E854_3;   /* data0C in func_8015E854 */

typedef struct S_8015E854_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x7];
    s16 unk_A4;
    s16 unk_A6;
} S_8015E854_4;   /* objectState in func_8015E854 */


extern void func_8015EA8C();
extern u8 D_80161D30[];
extern u8 D_80161D78[];
extern void func_8015EF74();

extern void *func_8003FD64();
extern s32 func_8004491C();
extern s32 func_800A6D30(void);
extern s16 func_800A48F0();
extern void func_800A9C18();
extern s32 func_800AA36C();
extern void func_80044A50();
extern void dungeonRetireTrackedEffectById();

void * func_8015E854(s16 mode, s16 value24, s16 value25, s16 value0A);
#endif
