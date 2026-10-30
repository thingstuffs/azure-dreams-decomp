#include "common.h"
#include "engine/graphics.h"
#include "engine/scene.h"
#include "sdk/libgpu.h"
#include "slus.h"

extern void mark_palette_colors_with_high_bit(u16 *entry, s32 groupCount, s32 contiguousMode);
extern s32 relocate_sprite_metadata_pointers(void *object_addr);
extern int patch_sprite_packet_texture_and_palette_ids(void *a0, u16 a1, u16 a2, u16 a3);

/* Uploads image tiles and palettes, updates the object's texture references, and returns the object. */
void *upload_image_tiles(void *object, u16 texture_page, s32 clut_id, s32 alternate_page, s32 image_addr)
{
    s32 palette_addr;

    runtime_upload_image_blocks_vram_offsets_selected_tile_block_indices(image_addr, texture_page, 4);
    palette_addr = get_image_palette_address(image_addr);
    upload_vram_row_and_cache(palette_addr, clut_id, 0x10, 2);
    DrawSync(0);
    mark_palette_colors_with_high_bit(palette_addr, 0x10, 0);
    upload_vram_row_and_cache(palette_addr, clut_id - 0x80, 0x10, 2);
    relocate_sprite_metadata_pointers(object);
    patch_sprite_packet_texture_and_palette_ids(object, texture_page, clut_id, alternate_page);
    return object;
}
