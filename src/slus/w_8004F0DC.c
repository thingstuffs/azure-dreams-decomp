#include "common.h"

#include "common.h"

/* Inner record pointed to by Slot.unk04; only +8/+0xA (s16 pair) touched. */
typedef struct {
    u8 pad0[8];
    /*0x08*/ s16 unk08;
    /*0x0A*/ s16 unk0A;
} S_8004F0DC_Inner;

/* 0x10-byte slot object living in the host object; ptr at +0, inner* at +4. */
typedef struct {
    /*0x00*/ void *unk00;
    /*0x04*/ S_8004F0DC_Inner *unk04;
} S_8004F0DC_Slot;

/* Host object: seven consecutive Slot* at 0x220..0x238. */
typedef struct {
    u8 pad[0x220];
    /*0x220*/ S_8004F0DC_Slot *unk220;
    /*0x224*/ S_8004F0DC_Slot *unk224;
    /*0x228*/ S_8004F0DC_Slot *unk228;
    /*0x22C*/ S_8004F0DC_Slot *unk22C;
    /*0x230*/ S_8004F0DC_Slot *unk230;
    /*0x234*/ S_8004F0DC_Slot *unk234;
    /*0x238*/ S_8004F0DC_Slot *unk238;
} S_8004F0DC;

/* Initialize seven slots with coordinate pairs and pointers to embedded buffers. */
void func_8004F0DC(S_8004F0DC *host)
{
    S_8004F0DC_Slot *slot;
    void *shared_buffer;
    s16 right_x;
    s16 bottom_y;

    slot = host->unk220;
    slot->unk04->unk08 = 6;
    slot->unk04->unk0A = 0x10;
    slot->unk00 = (u8 *)host + 8;

    slot = host->unk234;
    slot->unk04->unk08 = 0;
    slot->unk04->unk0A = 0;
    slot->unk00 = (u8 *)host + 0x80;

    slot = host->unk238;
    slot->unk04->unk08 = 0x68;
    slot->unk04->unk0A = 0;
    slot->unk00 = (u8 *)host + 0xF8;

    slot = host->unk224;
    right_x = 0xA0;
    bottom_y = 0x70;
    slot->unk04->unk08 = right_x;
    shared_buffer = (u8 *)host + 0x170;
    slot->unk04->unk0A = bottom_y;
    slot->unk00 = shared_buffer;

    slot = host->unk228;
    slot->unk04->unk08 = 0;
    slot->unk04->unk0A = bottom_y;
    slot->unk00 = shared_buffer;

    slot = host->unk22C;
    slot->unk04->unk08 = right_x;
    slot->unk04->unk0A = 0;
    slot->unk00 = shared_buffer;

    slot = host->unk230;
    slot->unk04->unk08 = 0;
    slot->unk04->unk0A = 0;
    slot->unk00 = shared_buffer;
}
