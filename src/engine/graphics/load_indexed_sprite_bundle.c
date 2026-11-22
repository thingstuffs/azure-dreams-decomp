#include "common.h"
#include "engine/cd.h"
#include "engine/graphics.h"
#include "engine/texture.h"
#include "sdk/libgpu.h"
#include "slus.h"
#include "slus/data.h"

/* Loads and initializes a resource, registers its payload in two VRAM cache slots, and returns its table slot. */
void *load_indexed_sprite_bundle(s32 resource_id) {
    void *payload;
    S_80048C3C_0 *entry;
    S_80048C3C_1 **resource_slot;
    S_80048C3C_1 *resource;
    s32 load_mode;

    load_mode = 6;
    entry = &indexed_sprite_bundle_records[resource_id];
    Control_CD(load_mode, entry->descriptor, 0);
    drain_cd_command_queue();
    resource = entry->resource;
    payload = (u8 *)resource + resource->payload_offset;
    upload_vram_row_and_cache(payload, 0x7A00, resource->width_blocks, 2);
    DrawSync(0);
    set_palette_stp_bits(payload, 1, 1);
    upload_vram_row_and_cache(payload, 0x7980, resource->width_blocks, 2);
    relocate_sprite_metadata_pointers(resource);
    resource_slot = &entry->resource;
    stamp_sprite_part_chain_values(&resource->parts);
    movie_overlay_loaded = 0;
    return resource_slot;
}
