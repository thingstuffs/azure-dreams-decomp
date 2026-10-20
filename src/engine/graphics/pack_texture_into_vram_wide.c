#include "slus/owned_80047338.h"

#include "slus/owned_80047338.h"

void pack_texture_into_vram_wide(S_80047338_hdr *texture, S_80047338_rec *record, s32 data_offset)
{
    S_80047270_hdr rect;
    u32 unsigned_width;
    s32 width_words;

    if (g_game_work.unk_004 != wide_texture_pack_generation) {
        wide_texture_pack_column_width = 0;
        wide_texture_pack_y = 0;
        wide_texture_pack_x = 0;
        wide_texture_pack_generation = g_game_work.unk_004;
    }

    width_words = (texture->unkA + 3) / 4;
    rect.unk04 = (s16)width_words;

    rect.unk06 = (s16)(texture->unkB + 1);

    if ((wide_texture_pack_y + rect.unk06) >= 0x100) {
        wide_texture_pack_y = 0;
        wide_texture_pack_x += wide_texture_pack_column_width;
    }

    unsigned_width = (u32)width_words;

    if ((wide_texture_pack_x + width_words) >= 0x40) {
        if (wide_texture_pack_column_width) {
            wide_texture_pack_column_width = 0;
            wide_texture_pack_y = 0;
            wide_texture_pack_x = 0;
        } else {
            wide_texture_pack_column_width = 0;
            wide_texture_pack_y = 0;
            wide_texture_pack_x = 0;
        }
    }
    if (wide_texture_pack_column_width < unsigned_width) {
        wide_texture_pack_column_width = (u16)width_words;
    }

    rect.unk00 = wide_texture_pack_x + ((texture->unk4 << 6) & 0x3C0);
    rect.unk02 = wide_texture_pack_y + ((texture->unk4 << 4) & 0x100);

    texture->unk8 = *(u8 *)&wide_texture_pack_x << 2;
    texture->unk9 = *(u8 *)&wide_texture_pack_y;
    wide_texture_pack_y += rect.unk06;

    decode_upload_image_from_wrapping_buffer((void *)((u8 *)record->unkC + data_offset), &rect);
}
u16 wide_texture_pack_x = 0;
u16 wide_texture_pack_y = 0;
u16 wide_texture_pack_column_width = 0;
u16 wide_texture_pack_generation = 0;
