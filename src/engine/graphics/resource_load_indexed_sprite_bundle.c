#include "common.h"
#include "engine/cd.h"
#include "engine/graphics.h"
#include "engine/texture.h"
#include "sdk/libgpu.h"
#include "slus.h"
#include "slus/data.h"

typedef struct S_80048C3C_0 {
    s32 unk_00;
    void * unk_04;
} S_80048C3C_0;   /* temp_s1 in resource_load_indexed_sprite_bundle */

typedef struct S_80048C3C_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    s32 unk_20;
} S_80048C3C_1;   /* temp_s2 in resource_load_indexed_sprite_bundle */

/* Loads and initializes a resource, registers its payload in two VRAM cache slots, and returns its table slot. */
void *resource_load_indexed_sprite_bundle(s32 resource_id) {
    void *payload;
    s32 entry_offset;
    S_80048C3C_0 *entry2;
    void *entry3;
    void *resource;
    s32 load_mode;

    entry_offset = resource_id * 8;
    load_mode = 6;
    entry2 = (S_80048C3C_0 *)(indexed_sprite_bundle_records + entry_offset);
    Control_CD(load_mode, entry2->unk_00, 0);
    drain_cd_command_queue();
    resource = entry2->unk_04;
    payload = resource + ((S_80048C3C_1 *)resource)->unk_1C;
    upload_vram_row_and_cache(payload, 0x7A00, ((S_80048C3C_1 *)resource)->unk_20, 2);
    DrawSync(0);
    mark_palette_colors_with_high_bit(payload, 1, 1);
    upload_vram_row_and_cache(payload, 0x7980, ((S_80048C3C_1 *)resource)->unk_20, 2);
    relocate_sprite_metadata_pointers(resource);
    entry3 = &entry2->unk_04;
    texture_mark_unprocessed_type_n_2_node_sequences_set_low_six_bits_n_14(resource);
    shared_sprite_resource_loaded = 0;
    return entry3;
}
