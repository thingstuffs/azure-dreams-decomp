#include "common.h"

extern s32 D_80082A38[];
extern u8 D_800D381A[];
extern u8 D_800D3C00[];
extern u8 D_800D3950[];

__asm__(".set D_800D3C00, 0x800D3C00");
__asm__(".set D_800D3950, 0x800D3950");

typedef struct Packet {
    s32 handler;
    s32 descriptor;
    s32 pad8;
    s32 padC;
    s32 mode;
    s32 pad14;
    s32 data0;
    s32 data1;
    s32 value0;
    s32 value1;
    s32 base_end;
    s32 arg0;
    s32 arg1;
    s32 arg2;
    s32 arg3;
} Packet;

typedef void (*PacketHandler)(Packet *);

void func_800C0EAC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Packet packet;
    s32 *base = D_80082A38;

    packet.handler = 0x80016000;
    packet.descriptor = 0x80012D70;
    packet.base_end = (s32)&base[18];
    packet.data0 = (s32)D_800D3C00;
    packet.arg0 = arg0;
    packet.arg1 = arg1;
    packet.arg2 = arg2;
    packet.arg3 = arg3;
    packet.mode = D_800D381A[0];
    packet.data1 = (s32)D_800D3950;
    packet.value0 = base[16];
    packet.value1 = base[17];
    (*(PacketHandler *)0x80016000)(&packet);
}
