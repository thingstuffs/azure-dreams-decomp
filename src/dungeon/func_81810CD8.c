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



/* Initialize the packet fields with a zero payload and set flag 0x80. */
void func_80025CD8(S_80025CD8_0 *packet) {
    volatile s32 zero[1];
    s32 payload;

    zero[0] = 0;
    packet->unk_01 = 0x28;
    payload = zero[0];
    packet->unk_02 = -0x18;
    packet->unk_03 = 4;
    packet->unk_0A = 0x30;
    packet->unk_0B = 0x58;
    packet->unk_04 = payload;
    packet->unk_00 |= 0x80;
}
