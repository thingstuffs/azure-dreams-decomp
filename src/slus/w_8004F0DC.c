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

/* Wire seven slot records on the object: each gets a UV-style s16 pair on its
 * inner and a buffer pointer into the object's embedded regions. Order is the
 * retail access order (0x220, 0x234, 0x238, then the 0x224..0x230 quartet that
 * shares the 0x170 buffer). */
void func_8004F0DC(S_8004F0DC *arg0)
{
    S_8004F0DC_Slot *s;
    void *shared;
    s16 x;
    s16 y;

    s = arg0->unk220;
    s->unk04->unk08 = 6;
    s->unk04->unk0A = 0x10;
    s->unk00 = (u8 *)arg0 + 8;

    s = arg0->unk234;
    s->unk04->unk08 = 0;
    s->unk04->unk0A = 0;
    s->unk00 = (u8 *)arg0 + 0x80;

    s = arg0->unk238;
    s->unk04->unk08 = 0x68;
    s->unk04->unk0A = 0;
    s->unk00 = (u8 *)arg0 + 0xF8;

    s = arg0->unk224;
    x = 0xA0;
    y = 0x70;
    s->unk04->unk08 = x;
    shared = (u8 *)arg0 + 0x170;
    s->unk04->unk0A = y;
    s->unk00 = shared;

    s = arg0->unk228;
    s->unk04->unk08 = 0;
    s->unk04->unk0A = y;
    s->unk00 = shared;

    s = arg0->unk22C;
    s->unk04->unk08 = x;
    s->unk04->unk0A = 0;
    s->unk00 = shared;

    s = arg0->unk230;
    s->unk04->unk08 = 0;
    s->unk04->unk0A = 0;
    s->unk00 = shared;
}
