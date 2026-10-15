#include "modules/dungeon_ovl_1830850.h"

void func_80025CD8(ovl_1830850_81810CD8_S_80025CD8_0 *packet) {
    s32 zero;
    s32 payload;

    zero = 0;
    packet->unk_01 = 0x28;
    payload = *(s32 *)&zero;
    packet->unk_02 = -0x18;
    packet->unk_03 = 4;
    packet->unk_0A = 0x30;
    packet->unk_0B = 0x58;
    packet->unk_04 = payload;
    packet->unk_00 |= 0x80;
}
