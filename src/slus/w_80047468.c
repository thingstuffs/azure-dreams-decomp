#include "slus/owned_80047468.h"

void func_80047468(S_80047468_arg0 *image, S_80047468_arg1 *source, s32 data_offset)
{
    int vram_x;
    s32 word_width;
    u32 unsigned_width;
    S_80047270_hdr rect;

    if (g_game_work.unk_004 != D_80081526) {
        D_80081524 = 0;
        D_80081522 = 0;
        D_80081520 = 0;
        D_80081526 = g_game_work.unk_004;
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
