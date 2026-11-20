#include "common.h"
#include "engine/graphics.h"
#include "engine/scene.h"
#include "engine/texture.h"
#include "sdk/libgpu.h"
#include "slus.h"

/* Uploads image tiles and palettes, updates the object's texture references, and returns the object. */
void *upload_image_tiles(void *object, u16 texture_page, s32 clut_id, s32 alternate_page, s32 image_addr)
{
    s32 palette_addr;

    upload_tile_image_blocks(image_addr, texture_page, 4);
    palette_addr = get_image_palette_address(image_addr);
    upload_vram_row_and_cache(palette_addr, clut_id, 0x10, 2);
    DrawSync(0);
    set_palette_stp_bits(palette_addr, 0x10, 0);
    upload_vram_row_and_cache(palette_addr, clut_id - 0x80, 0x10, 2);
    relocate_sprite_metadata_pointers(object);
    offset_sprite_part_chains(object, texture_page, (u16)clut_id, (u16)alternate_page);
    return object;
}
