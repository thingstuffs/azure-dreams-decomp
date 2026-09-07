#include "common.h"

extern u8 *D_80083160;
extern u8 D_801C9E40[16];

extern void func_8006658C(void *, void *);
extern void func_80067E2C(void *, void *);
extern void func_8009DAD8(void *, s32);

void func_8009DF0C(s32 arg0) {
    s32 sp10[2];
    s32 value;
    s32 adjust;
    u8 *root;
    u8 *base;
    u8 *packet2;
    u8 *packet;

    sp10[0] = 0xC00300;
    sp10[1] = 0x400040;
    root = D_80083160;
    adjust = root != D_801C9E40;
    base = root + 0x8B0;
    packet = *(u8 **)(root + 0x8D0);
    *(u8 **)(root + 0x8D0) = packet + 0xC;
    func_80067E2C(packet, *(u8 * volatile *)&D_80083160);
    func_8006658C(base, packet);
    func_8009DAD8(base, arg0);

    packet2 = *(u8 **)(D_80083160 + 0x8D0);
    *(u8 **)(D_80083160 + 0x8D0) = packet2 + 0x10;
    *(s32 *)(packet2 + 4) = 0x60000000;
    *(s8 *)(packet2 + 3) = 3;
    *(s32 *)(packet2 + 8) = sp10[0];
    value = *(s16 *)(packet2 + 0xA);
    if (adjust) {
        value -= 0xE0;
    }
    *(s16 *)(packet2 + 0xA) = value;
    *(s32 *)(packet2 + 0xC) = sp10[1];
    func_8006658C(base, packet2);

    packet = *(u8 **)(D_80083160 + 0x8D0);
    *(u8 **)(D_80083160 + 0x8D0) = packet + 0xC;
    func_80067E2C(packet, &sp10[0]);
    func_8006658C(base, packet);
}
