#include "common.h"

typedef struct S_80025CD8_0 {
    u8 unk_00;
    s8 unk_01;
    s8 unk_02;
    s8 unk_03;
    s32 unk_04;
    u8 pad_08[0x2];
    s8 unk_0A;
    s8 unk_0B;
} S_80025CD8_0;   /* arg0 in func_80025CD8 */



void func_80025CD8(S_80025CD8_0 *arg0) {
    volatile s32 zero[1];
    s32 saved;

    zero[0] = 0;
    arg0->unk_01 = 0x28;
    saved = zero[0];
    arg0->unk_02 = -0x18;
    arg0->unk_03 = 4;
    arg0->unk_0A = 0x30;
    arg0->unk_0B = 0x58;
    arg0->unk_04 = saved;
    arg0->unk_00 |= 0x80;
}
