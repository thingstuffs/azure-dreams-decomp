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

/* Packs a texture into the atlas and passes its data and rectangle to func_80047270. */
void func_80047338(S_80047338_hdr *texture, S_80047338_rec *record, s32 data_offset)
{
    S_80047270_hdr rect;
    u32 unsigned_width;
    s32 width_words;

    if (D_80083164[0] != D_8008151E) {
        D_8008151C = 0;
        D_8008151A = 0;
        D_80081518 = 0;
        D_8008151E = D_80083164[0];
    }

    width_words = (texture->unkA + 3) / 4;
    rect.unk04 = (s16)width_words;

    rect.unk06 = (s16)(texture->unkB + 1);

    if ((D_8008151A + rect.unk06) >= 0x100) {
        D_8008151A = 0;
        D_80081518 += D_8008151C;
    }

    unsigned_width = (u32)width_words;

    if ((D_80081518 + width_words) >= 0x40) {
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
    if (D_8008151C < unsigned_width) {
        D_8008151C = (u16)width_words;
    }

    rect.unk00 = D_80081518 + ((texture->unk4 << 6) & 0x3C0);
    rect.unk02 = D_8008151A + ((texture->unk4 << 4) & 0x100);

    texture->unk8 = *(u8 *)&D_80081518 << 2;
    texture->unk9 = *(u8 *)&D_8008151A;
    D_8008151A += rect.unk06;

    func_80047270((void *)((u8 *)record->unkC + data_offset), &rect);
}
