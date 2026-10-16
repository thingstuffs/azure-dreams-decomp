#include "modules/dungeon_ovl_1831370.h"

void *dungeonInitializeVariantPacket(ovl_1831370_81811708_Packet *packet, s32 variant) {
    s32 payload;

    packet->unk1 = 0x28;
    payload = D_800294FC;
    packet->unk2 = -0x21;
    packet->unk3 = 5;
    packet->unk4 = payload;
    packet->unkA = (variant == 1) ? 0x42 : 0x5A;
    packet->unkB = 0x16;
    packet->unk0 = 0x80;
    return packet;
}
