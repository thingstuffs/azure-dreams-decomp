#include "slus/owned_80047468.h"

#include "slus/owned_80047468.h"
#include "engine/graphics.h"

/* Packs and uploads a texture in a 32-word by 128-row VRAM area, resetting on a generation change. */
void pack_texture_into_vram_narrow(S_80047468_arg0 *image, S_80047468_arg1 *source, s32 data_offset)
{
    int vram_x;
    s32 word_width;
    u32 unsigned_width;
    S_80047270_hdr rect;

    if (g_game_work.unk_004 != narrow_texture_pack_generation) {
        narrow_texture_pack_column_width = 0;
        narrow_texture_pack_y = 0;
        narrow_texture_pack_x = 0;
        narrow_texture_pack_generation = g_game_work.unk_004;
    }
    word_width = (image->unk0A + 3) / 4;
    rect.unk04 = (s16)word_width;
    rect.unk06 = image->unk0B + 1;
    if ((narrow_texture_pack_y + rect.unk06) >= 0x80) {
        narrow_texture_pack_y = 0;
        narrow_texture_pack_x += narrow_texture_pack_column_width;
    }
    unsigned_width = (u32)word_width;
    if ((narrow_texture_pack_x + word_width) >= 0x20) {
        if (narrow_texture_pack_column_width) {
            narrow_texture_pack_column_width = 0;
            narrow_texture_pack_y = 0;
            narrow_texture_pack_x = 0;
        } else {
            narrow_texture_pack_column_width = 0;
            narrow_texture_pack_y = 0;
            narrow_texture_pack_x = 0;
        }
    }
    if (((u16)narrow_texture_pack_column_width) < unsigned_width) {
        narrow_texture_pack_column_width = (u16)word_width;
    }
    vram_x = (narrow_texture_pack_x + ((image->unk04 << 6) & 0x3C0)) + 0x20;
    rect.unk00 = vram_x;
    rect.unk02 = (narrow_texture_pack_y + ((image->unk04 * 0x10) & 0x100)) + 0x80;
    image->unk08 = (s8)((((u8)narrow_texture_pack_x) * 4) - 0x80);
    image->unk09 = (s8)(((u8)narrow_texture_pack_y) + 0x80);
    narrow_texture_pack_y += rect.unk06;
    decode_upload_image_from_wrapping_buffer((void *)(source->unk0C + data_offset), &rect);
}
u16 narrow_texture_pack_x = 0;
u16 narrow_texture_pack_y = 0;
u16 narrow_texture_pack_column_width = 0;
u16 narrow_texture_pack_generation = 0;
