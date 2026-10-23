/* Initialize and refresh monster status resource cache (G00636). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B956C, CL:town/func_800B958C, CL:town/func_800B95F4, CL:town/func_800B9634, CL:town/func_800B97F4. */
#include "town/shop/monster_status_resource_cache_g00636.h"

/* Initialize an entry with a mode-dependent value offset and a fixed data offset. */
void initialize_mode_offset_entry(s32 mode, s32 value_base, S_800B6CCC_0 *entry, s32 data_base) {
    s32 entry_value;

    entry_value = value_base + 0x42E6;
    if (mode == 0) {
        entry_value = value_base + 0x42DB;
    }
    entry->unk_04 = entry_value;
    entry->unk_00 = (s32) (data_base + 0x80800000);
}

/* Returns a mapped code for the object, or its fallback value when the code is zero. */
s32 get_mapped_object_code(void *object) {
    s32 code = *((u8 *) object + 0x13);

    if (code != 0) {
        if ((get_entity_effect_value(object, 10) << 0x10) != 0) {
            code = 47;
        } else {
            code = normalize_monster_status_species_code(code);
        }
        return code;
    }
    return select_mapped_object_status_code(object);
}

/* Set the object data pointer and initialize its coordinate-based data. */
void initialize_coordinate_entry(void *object) {
    *(void **)((u8 *)object + 0xE0) = (void *)0x8002B800;
    initialize_mode_offset_entry(*(s16 *)((u8 *)object + 8), *(s16 *)((u8 *)object + 0xA),
                  (S_800B6CCC_0 *)((u8 *)object + 0xD8), (s32)0x8002B800);
}

/* Clear the texture's rectangle with zeroed image data. */
void clear_monster_status_texture(void *texture) {
    s16 rect[4];
    void *clear_data;

    clear_data = alloc_gpu_scratch_ring(0x200);
    bzero(clear_data, 0x200);
    DrawSync(0);

    rect[0] = (*(u8 *)((u8 *)texture + 8) >> 2)
    + ((*(u16 *)((u8 *)texture + 4) << 6) & 0x3C0);
    rect[1] = ((*(u16 *)((u8 *)texture + 4) << 4) & 0x100)
    + *(u8 *)((u8 *)texture + 9);
    rect[2] = *(u8 *)((u8 *)texture + 10) >> 2;
    rect[3] = *(u8 *)((u8 *)texture + 11);

    LoadImage(rect, clear_data);
    DrawSync(0);
}

/* Invalidates changed cached state and starts the corresponding CD operations. */
s32 invalidate_cached_state_and_queue_read(void *state) {
    s32 state_code;
    s32 cache_addr;
    CachedObjectCodePair *cached_state;

    ((Rec_func_800B683C_arg0 *)state)->unk_0A = (s16)get_mapped_object_code((void *)((Rec_func_800B683C_arg0 *)state)->unk_04);
    state_code = get_enabled_record_flag_priority(((Rec_func_800B683C_arg0 *)state)->unk_04);
    ((Rec_func_800B683C_arg0 *)state)->unk_10 = state_code;
    if (state_code == 3) {
        ((Rec_func_800B683C_arg0 *)state)->unk_10 = 0;
    }
    if (release_monster_status_request_handles(state) != 0) {
        *((((Rec_func_800B683C_arg0 *)state)->unk_08 * 2) + display_resource_cache_keys) = -1;
    }
    cached_state = (((Rec_func_800B683C_arg0 *)state)->unk_08 * 2) + display_resource_cache_keys;
    if ((cached_state->unk_00 != ((Rec_func_800B683C_arg0 *)state)->unk_0A)
        || (cached_state->unk_02 != ((Rec_func_800B683C_arg0 *)state)->unk_10)) {
        cached_state->unk_00 = -1;
        cache_addr = ((Rec_func_800B683C_arg0 *)state)->unk_08;
        cache_addr <<= 2;
        cache_addr += (s32)display_resource_cache_keys;
        ((S_800B6E3C_2 *)((void *)cache_addr))->unk_02 = -1;
        clear_monster_status_texture((void *)(((Rec_func_800B683C_arg0 *)state)->unk_14));
        ((Rec_func_800B683C_arg0 *)state)->unk_DC = 0;
        initialize_coordinate_entry(state);
        ((Rec_func_800B683C_arg0 *)state)->unk_D0 = Control_CD(6, state + 0xD8, NULL);
        ((Rec_func_800B683C_arg0 *)state)->unk_D4 = Control_CD(0xFF, &D_800B5B20, state);
        return 1;
    }
    return 0;
}
