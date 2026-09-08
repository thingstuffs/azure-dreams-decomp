#include "common.h"

typedef struct S_81868E84_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    void * unk_10;
    u8 pad_14[0xC];
    s16 unk_20;
} S_81868E84_0;   /* temp_v0 in func_81868E84 */

typedef struct S_81868E84_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    void * unk_0C;
    s8 unk_10;
} S_81868E84_1;   /* temp_v0_2 in func_81868E84 */

typedef struct S_81868E84_2 {
    u8 pad_00[0x9];
    u8 unk_09;
} S_81868E84_2;   /* arg0 in func_81868E84 */

typedef struct S_81868E84_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81868E84_3;   /* arg1 in func_81868E84 */

typedef struct S_81868E84_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_81868E84_4;   /* temp_v0_3 in func_81868E84 */



extern void *func_8003FC64(s32);
extern u8 D_80024384[];

/* Creates object 0x212 with its owner, initial state, and two copies of the supplied coordinates. */
void func_81868E84(void *owner, S_81868E84_3 *coords) {
    u32 owner_value;
    u16 x;
    u16 y;
    u16 z;
    void *object;
    S_81868E84_1 *state;
    S_81868E84_4 *coord_pairs;

    object = func_8003FC64(0x212);
    if (object != 0) {
        ((S_81868E84_0 *)object)->unk_10 = D_80024384;
        state = object + 0x20;
        ((S_81868E84_0 *)object)->unk_20 = 0;
        state->unk_02 = 0;
        owner_value = ((S_81868E84_2 *)owner)->unk_09;
        state->unk_06 = 0;
        state->unk_08 = 0;
        state->unk_0A = 0;
        state->unk_0C = owner;
        state->unk_10 = 0x40;
        state->unk_04 = owner_value;
        coord_pairs = ((S_81868E84_0 *)object)->unk_08;
        x = coords->unk_02;
        coord_pairs->unk_0E = x;
        coord_pairs->unk_02 = x;
        y = coords->unk_06;
        coord_pairs->unk_12 = y;
        coord_pairs->unk_06 = y;
        z = coords->unk_0A;
        coord_pairs->unk_16 = z;
        coord_pairs->unk_0A = z;
    }
}

/* MECHANISM: Hold owner[9] in a u32 local after the first two zero stores.
   Its live range claims $a0, leaving the allocator result in $a1; u32 avoids
   the redundant andi and collapses the +1-word branch-displacement cascade. */
