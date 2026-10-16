#ifndef DUNGEON_OVL_7F559800_H
#define DUNGEON_OVL_7F559800_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"


extern u8 D_8016AA58[];
extern s32 D_8016B014;
extern s32 D_8016E20C;
extern s32 D_8016E25C;

extern void *func_8003FD64();
extern void func_8004491C();
extern void func_800A48F0();
extern s32 func_800A6D30();
extern void func_800A9C18();
extern void func_800AA36C();


typedef struct S_8016A878_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 * unk_10;
} S_8016A878_0;   /* temp_v0 in func_8016A878 */

typedef struct S_8016A878_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8016A878_1;   /* var_s0 in func_8016A878 */

typedef struct S_8016A878_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8016A878_2;   /* temp_s4 in func_8016A878 */

typedef struct S_8016A878_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    s32 * unk_2C;
} S_8016A878_3;   /* temp_s2 in func_8016A878 */

typedef struct S_8016A878_4 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_8016A878_4;   /* temp_s5 in func_8016A878 */

/* Allocate and initialize an object with its placement, flags, and runtime state. */

void *func_8016A878(s16 init_flags, s16 tile_x, s16 tile_y, s16 object_id);
#endif
