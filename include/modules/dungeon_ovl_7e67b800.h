#ifndef DUNGEON_OVL_7E67B800_H
#define DUNGEON_OVL_7E67B800_H
#include "common.h"
#include "m2c_compat.h"
#include "shared/gpu_packets.h"
#include "shared/game_work.h"
typedef struct Row_81989558_S_80024D58_Point {
    s16 unk_00;
    s16 unk_02;
    u16 unk_04;
    u8 pad_06[0x2];
} Row_81989558_S_80024D58_Point;   /* source_points / rotated_points entry (8 bytes) in func_80024D58 */

typedef struct Row_81989558_S_80024D58_Obj {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x6];
    s32 unk_0C;
} Row_81989558_S_80024D58_Obj;   /* obj in func_80024D58 */

typedef struct Row_81989558_S_80024D58_RingParam {
    u8 pad_00[0x10];
    u16 unk_10;
    u16 unk_12;
} Row_81989558_S_80024D58_RingParam;   /* ring_params entry (6 bytes apart) in func_80024D58 */

typedef struct Row_81989558_S_80024D58_Pair {
    s32 unk_00;
    s32 unk_04;
} Row_81989558_S_80024D58_Pair;   /* r1 / r1b in func_80024D58 */

typedef struct Row_81989558_S_80024D58_11_pre {
    void * unk_00;
    u8 pad_04[0x4];
} Row_81989558_S_80024D58_11_pre;   /* the 0x8 bytes before arg0 in func_80024D58, addressed as arg0[-1] */

typedef struct Row_81989558_Blk8 {
    s32 w0;
    s32 w1;
} __attribute__((packed)) Row_81989558_Blk8;

typedef struct Row_81989558_Params {
    void *f510;
    void *f514;
    s16 f518;
    s16 f51A;
    u16 f51C;
    u8 pad0E[2];
    Row_81989558_Blk8 blk;
    s16 f528;
    s16 f52A;
    u8 pad1C[4];
    s32 f530;
    s32 f534;
} Row_81989558_Params;

typedef struct Row_81989558_Frame {
    u8 space[1280];
    Row_81989558_Params p;
} Row_81989558_Frame;

/* Address of cell (row, col) of the 16 x 16 grid of 4-byte points. */
static __inline__ u8 *grid_cell(u8 *grid, s32 row, s32 col)
{
    grid += row << 6;
    col <<= 2;
    return grid + col;
}

/* Build a textured quad grid for each object in the linked list. */
void dungeonTransformRotatedVertices();
void func_80065420();
void func_800666F4();
void func_80066640();
s16 func_80066460();
s16 func_8006649C();

s32 func_80024D58(void *node);
#endif
