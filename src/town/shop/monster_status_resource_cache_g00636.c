/* Initialize and refresh monster status resource cache. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B956C, CL:town/func_800B958C, CL:town/func_800B95F4, CL:town/func_800B9634, CL:town/func_800B97F4. */
#include "sdk/libgpu_types.h"
#include "town/shop/monster_status_resource_cache_g00636.h"
#include "town/shop.h"
#include "town/shop/state.h"
#include "slus.h"
#include "town/shop/stat_panel_callbacks_api.h"

/* Initialize an entry with a mode-dependent value offset and a fixed data offset. */
void fill_cd_read_descriptor(s32 mode, s32 value_base, MonsterStatusCdDescriptor *entry, s32 data_base) {
    s32 entry_value;

    entry_value = value_base + 0x42E6;
    if (mode == 0) {
        entry_value = value_base + 0x42DB;
    }
    entry->sector = entry_value;
    entry->data_word = (s32) (data_base + 0x80800000);
}

/* Returns a mapped code for the object, or its fallback value when the code is zero. */
s32 get_monster_status_species_code(ActorRecord *object) {
    s32 code = object->species;

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
void set_monster_status_cd_read_target(ShopFirstCallbackObject *object) {
    object->transfer_data = 0x8002B800;
    fill_cd_read_descriptor(object->slot_index, object->species_code,
                  &object->read_descriptor, (s32)0x8002B800);
}

/* Clear the texture's rectangle with zeroed image data. */
void clear_monster_status_texture(SpritePartCommand *texture) {
    RECT rect;
    void *clear_data;

    clear_data = alloc_gpu_scratch_ring(0x200);
    bzero(clear_data, 0x200);
    DrawSync(0);

    rect.x = (texture->data.texture.u0 >> 2)
    + ((texture->tpage << 6) & 0x3C0);
    rect.y = ((texture->tpage << 4) & 0x100)
    + texture->data.texture.v0;
    rect.w = texture->data.texture.width >> 2;
    rect.h = texture->data.texture.height;

    LoadImage(&rect, clear_data);
    DrawSync(0);
}

/* Invalidates changed cached state and starts the corresponding CD operations. */
s32 queue_monster_status_reload(ShopFirstCallbackObject *state) {
    s32 state_code;
    s16 *cache_row;
    s16 *cached_state;

    state->species_code = (s16)get_monster_status_species_code(state->actor);
    state_code = get_enabled_record_flag_priority(state->actor);
    state->palette_index = state_code;
    if (state_code == 3) {
        state->palette_index = 0;
    }
    if (release_monster_status_request_handles(state) != 0) {
        *((state->slot_index * 2) + display_resource_cache_keys) = -1;
    }
    cached_state = (state->slot_index * 2) + display_resource_cache_keys;
    if ((cached_state[0] != state->species_code)
        || (cached_state[1] != state->palette_index)) {
        cached_state[0] = -1;
        cache_row = &display_resource_cache_keys[state->slot_index * 2];
        cache_row[1] = -1;
        clear_monster_status_texture(state->texture);
        state->read_descriptor.sector = 0;
        set_monster_status_cd_read_target(state);
        state->read_handle = Control_CD(6, &state->read_descriptor, NULL);
        /* The command stores its callback context in a 32-bit payload word. */
        state->completion_handle = Control_CD(0xFF, complete_display_transfer, (s32)(unsigned long)state);
        return 1;
    }
    return 0;
}
