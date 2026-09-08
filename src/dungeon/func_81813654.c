#include "common.h"

extern u32 D_80029548;
extern u32 D_8002954C;

/* Initializes four drawing packets from coordinates and returns the last packet. */
void *func_80028654(void *packet, void *coords) {
    register u32 packet_type ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *coord_bytes = (u8 *)coords;

    *(u32 *)((u8 *)packet + 4) = D_8002954C;
    *((u8 *)packet + 1) = 0x48;
    *((u8 *)packet + 2) = coord_bytes[0];
    do { *((u8 *)packet + 3) = coord_bytes[2]; } while (0);
    *((u8 *)packet + 0xA) = coord_bytes[4];
    *((u8 *)packet + 0xB) = coord_bytes[6];

    packet = (u8 *)packet + 0xC;

    *(u32 *)((u8 *)packet + 4) = D_8002954C;
    *((u8 *)packet + 1) = 0x48;
    *((u8 *)packet + 2) = coord_bytes[0];
    *((u8 *)packet + 3) = coord_bytes[2];
    *((u8 *)packet + 0xA) = coord_bytes[4] + 1;
    *((u8 *)packet + 0xB) = coord_bytes[6] + 1;

    packet = (u8 *)packet + 0xC;

    *(u32 *)((u8 *)packet + 4) = D_80029548;
    *((u8 *)packet + 1) = 0x48;
    *((u8 *)packet + 2) = coord_bytes[0];
    *((u8 *)packet + 3) = coord_bytes[2];
    *((u8 *)packet + 0xA) = coord_bytes[4];
    *((u8 *)packet + 0xB) = coord_bytes[6];
    packet_type = 3;
    ASM_KEEP(packet_type);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    *((u8 *)packet + 0) = packet_type;

    packet = (u8 *)packet + 0xC;

    *(u32 *)((u8 *)packet + 4) = D_80029548;
    *((u8 *)packet + 1) = 0x48;
    *((u8 *)packet + 2) = coord_bytes[0];
    *((u8 *)packet + 3) = coord_bytes[2];
    *((u8 *)packet + 0xA) = coord_bytes[4] + 1;
    *((u8 *)packet + 0xB) = coord_bytes[6] + 1;
    *((u8 *)packet + 0) = packet_type;
    return packet;
}
