#include "common.h"

typedef struct S_80048C3C_0 {
    s32 unk_00;
    void * unk_04;
} S_80048C3C_0;   /* temp_s1 in resource_load_indexed_sprite_bundle */

typedef struct S_80048C3C_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    s32 unk_20;
} S_80048C3C_1;   /* temp_s2 in resource_load_indexed_sprite_bundle */
void DrawSync(s32);                          /* extern */
s32 Control_CD(s32 event_code, void *event_data, s32 payload);       /* extern */
void drain_cd_command_queue(void);                            /* extern */
void upload_vram_row_and_cache(); /* extern */
s32 relocate_sprite_metadata_pointers();                      /* extern */
void mark_palette_colors_with_high_bit();    /* extern */
void texture_mark_unprocessed_type_n_2_node_sequences_set_low_six_bits_n_14();                      /* extern */
extern u8 D_80071210[];
extern s8 D_80080A89;

/* Loads and initializes a resource, registers its payload in two VRAM cache slots, and returns its table slot. */
void *resource_load_indexed_sprite_bundle(s32 resource_id) {
    void *payload;
    void *entry;
    void *entry2;
    void *entry3;
    void *resource;
    s32 load_mode;

    entry = (void *)(resource_id * 8);
    load_mode = 6;
    entry2 = (u8 *)entry + (u32)D_80071210;
    Control_CD(load_mode, ((S_80048C3C_0 *)entry2)->unk_00, 0);
    drain_cd_command_queue();
    resource = ((S_80048C3C_0 *)entry2)->unk_04;
    payload = resource + ((S_80048C3C_1 *)resource)->unk_1C;
    upload_vram_row_and_cache(payload, 0x7A00, ((S_80048C3C_1 *)resource)->unk_20, 2);
    DrawSync(0);
    mark_palette_colors_with_high_bit(payload, 1, 1);
    upload_vram_row_and_cache(payload, 0x7980, ((S_80048C3C_1 *)resource)->unk_20, 2);
    relocate_sprite_metadata_pointers(resource);
    entry3 = (u8 *)entry2 + 4;
    texture_mark_unprocessed_type_n_2_node_sequences_set_low_six_bits_n_14(resource);
    D_80080A89 = 0;
    return entry3;
}
