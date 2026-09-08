#include "common.h"

typedef struct {
    s16 unk00;
    s16 unk02;
    s16 unk04;
    s16 unk06;
} S_80047270_hdr;

extern void func_80047270(void *a0, S_80047270_hdr *a1);
extern u16 D_80083164[8];
extern u16 D_80081520;
extern u16 D_80081522;
extern u16 D_80081524;
extern u16 D_80081526;

typedef struct {
    u8 pad00[4];
    u16 unk04;
    u8 pad06[2];
    s8 unk08;
    s8 unk09;
    u8 unk0A;
    u8 unk0B;
} S_80047468_arg0;

typedef struct {
    u8 pad00[0xC];
    u8 *unk0C;
} S_80047468_arg1;

/* Packs an image into the texture page region at (32, 128), decodes it, and uploads it. */
void func_80047468(S_80047468_arg0 *image, S_80047468_arg1 *source, s32 data_offset)
{
    int vram_x;
    s32 word_width;
    u32 unsigned_width;
    S_80047270_hdr rect;

    if (D_80083164[0] != D_80081526) {
        D_80081524 = 0;
        D_80081522 = 0;
        D_80081520 = 0;
        D_80081526 = D_80083164[0];
    }
    word_width = (image->unk0A + 3) / 4;
    rect.unk04 = (s16)word_width;
    rect.unk06 = image->unk0B + 1;
    if ((D_80081522 + rect.unk06) >= 0x80) {
        D_80081522 = 0;
        D_80081520 += D_80081524;
    }
    unsigned_width = (u32)word_width;
    if ((D_80081520 + word_width) >= 0x20) {
        if (D_80081524) {
            D_80081524 = 0;
            D_80081522 = 0;
            D_80081520 = 0;
        } else {
            D_80081524 = 0;
            D_80081522 = 0;
            D_80081520 = 0;
        }
    }
    if (((u16)D_80081524) < unsigned_width) {
        D_80081524 = (u16)word_width;
    }
    vram_x = (D_80081520 + ((image->unk04 << 6) & 0x3C0)) + 0x20;
    rect.unk00 = vram_x;
    rect.unk02 = (D_80081522 + ((image->unk04 * 0x10) & 0x100)) + 0x80;
    image->unk08 = (s8)((((u8)D_80081520) * 4) - 0x80);
    image->unk09 = (s8)(((u8)D_80081522) + 0x80);
    D_80081522 += rect.unk06;
    func_80047270((void *)(source->unk0C + data_offset), &rect);
}
