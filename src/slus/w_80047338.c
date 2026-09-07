#include "common.h"

/* Shelf/atlas packer step feeding func_80047270; see 'doc' for full behavior. */
#include "common.h"

typedef struct {
    u8 pad0[4];
    u16 unk4;
    u8 pad1[2];
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
} S_80047338_hdr;

typedef struct {
    u8 pad0[0xC];
    void *unkC;
} S_80047338_rec;

typedef struct {
    s16 unk00;
    s16 unk02;
    s16 unk04;
    s16 unk06;
} S_80047270_hdr;

extern void func_80047270(void *a0, S_80047270_hdr *a1);

extern u16 D_80083164[];

extern u16 D_80081518;
extern u16 D_8008151A;
extern u16 D_8008151C;
extern u16 D_8008151E;

void func_80047338(S_80047338_hdr *arg0, S_80047338_rec *arg1, s32 arg2)
{
    S_80047270_hdr hdr;
    u32 hU;
    s32 h;

    if (D_80083164[0] != D_8008151E) {
        D_8008151C = 0;
        D_8008151A = 0;
        D_80081518 = 0;
        D_8008151E = D_80083164[0];
    }

    h = (arg0->unkA + 3) / 4;
    hdr.unk04 = (s16)h;

    hdr.unk06 = (s16)(arg0->unkB + 1);

    if ((D_8008151A + hdr.unk06) >= 0x100) {
        D_8008151A = 0;
        D_80081518 += D_8008151C;
    }

    hU = (u32)h;

    if ((D_80081518 + h) >= 0x40) {
        /* Both arms reset the same three fields to zero. Retail's exact
         * register schedule (h copied to a scratch register ahead of the
         * D_8008151C compare below) only reproduces with this shape present;
         * collapsing it to a single unconditional reset shifts the
         * gcc-2.7.2-cdk scheduler and drops the copy. Kept verbatim as the
         * byte-matching shape. */
        if (D_8008151C) {
            D_8008151C = 0;
            D_8008151A = 0;
            D_80081518 = 0;
        } else {
            D_8008151C = 0;
            D_8008151A = 0;
            D_80081518 = 0;
        }
    }
    if (D_8008151C < hU) {
        D_8008151C = (u16)h;
    }

    hdr.unk00 = D_80081518 + ((arg0->unk4 << 6) & 0x3C0);
    hdr.unk02 = D_8008151A + ((arg0->unk4 << 4) & 0x100);

    arg0->unk8 = *(u8 *)&D_80081518 << 2;
    arg0->unk9 = *(u8 *)&D_8008151A;
    D_8008151A += hdr.unk06;

    func_80047270((void *)((u8 *)arg1->unkC + arg2), &hdr);
}
