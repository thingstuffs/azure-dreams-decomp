#include "common.h"

typedef struct MainPacket12 {
    u8 tag;
    u8 code;
    u8 pad2[2];
    s16 x;
    s16 y;
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} MainPacket12;

extern s16 func_80078570(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s16 func_80078640(s32 arg0, s32 arg1);

MainPacket12 *func_8001DA3C(MainPacket12 *packet) {
    MainPacket12 *result;

    packet->code = 0x81;
    packet->x = 0x20;
    packet->y = 0;
    packet++;

    packet->code = 0x80;
    packet->r = 0;
    packet->g = 0;
    packet->b = 0xFF;
    packet->a = 0xFF;
    packet++;

    packet->code = 0x2C;
    packet->x = func_80078570(1, 0, 0x380, 0x100);
    packet->y = func_80078640(0, 0x1F5);
    packet->r = 0;
    packet->g = 0;
    packet->b = 0xA0;
    packet->a = 0x70;
    packet++;

    result = packet + 1;
    packet->r = 0x70;
    packet->g = 0xE0;
    packet->code = 0x80;
    packet->b = 8;
    packet->a = 8;
    packet->tag = 0x80;
    return result;
}
