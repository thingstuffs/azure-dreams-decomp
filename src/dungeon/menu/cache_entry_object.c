#include "dungeon/menu_cache.h"
#include "engine/util.h"

/* The decoded bank uses 25 entries; the existing town constructor uses 24. */
MenuEntryObject *allocate_menu_entry_object(s32 resource_id, s32 slot_index, s32 x, s32 y, s32 z)
{
    MenuEntryState *state;
    MenuEntryObject *object;
    void *allocated;
    void *sprite;

    allocated = allocate_flagged_object_node(0);
    object = allocated;
    state = &object->state;
    if (object != 0) {
        if (prepare_cached_menu_entries(state, 25) != 0) {
            sprite = state->display_owner;
            object->node.sprite = sprite;
            state->entry_value = link_cached_menu_entries(state->entries);
            initialize_cached_menu_entry(state, resource_id, slot_index, x, y, z);
            object->node.update_callback = &invoke_cached_menu_callback;
            register_node(object, &draw_tinted_node_sprites_scratch);
            return object;
        }
        release_null_terminated_entries(state->resources);
        object->node.flags |= 0x8000;
        object = 0;
        object_flag_block.flags |= 0x8000;
    }
    return object;
}

void release_menu_entry_object(MenuEntryObject *object)
{
    MenuEntryState *state;
    s32 flags;

    if (object != 0) {
        state = &object->state;
        release_null_terminated_entries(state->resources);
        clear_menu_entries(state->entries);
        release_menu_entry_state(state);
        flags = object_flag_block.flags;
        object->node.flags |= 0x8000;
        object_flag_block.flags = flags | 0x8000;
    }
}

void *allocate_menu_pair_default(void *first, void *second)
{
    return allocate_menu_pair(first, second, 0);
}

void update_menu_panel_colors(MenuPanelState *state)
{
    advance_timed_tagged_stream(state->tagged_stream);
    fade_color_to_gray(state->children->colors[0], 0);
    fade_color_to_gray(state->children->colors[1], 0);
    handle_menu_panel_input(state);
}

void advance_menu_panel_scale(void *record)
{
    MenuPanelUpdateRecord *object = record - 0x10;
    MenuPanelState *state = &object->state;

    state->transform->scale = (state->step << 12) / 5;
    state->step++;
    if (state->step >= 6) {
        object->update = update_menu_panel_colors;
    }
    handle_menu_panel_input(state);
}

/* Object dispatch forwards the original object, motion, sprite and context. */
void invoke_cached_menu_callback(MenuEntryState *state, void *position, void *sprite, void *context)
{
    state->callback(state, position, sprite, context);
}

s32 link_cached_menu_entries(void **entries)
{
    return build_reverse_indexed_chain(entries, menu_entry_link_table, 25);
}

void initialize_cached_menu_entry(MenuEntryState *state, s32 resource_id, s32 slot_index, s32 x, s32 y, s32 z)
{
    initialize_menu_display_templates(state->display_owner, &state->display_template, &state->linked_common, x, y, z);
    clear_cached_menu_entry(state);
    set_cached_menu_entry_resource(state, resource_id, slot_index);
}

s32 prepare_cached_menu_entries(MenuEntryState *state, s32 count)
{
    s32 ready = 0;

    state->entries = realloc_field_0_buffer(state->resources, count, 12);
    if (state->entries != 0) {
        state->entry_common.word0 = menu_entry_common_template.word0;
        state->entry_common.word1 = menu_entry_common_template.word1;
        state->entry_common.word2 = menu_entry_common_template.word2;
        set_entry_common_pointers(state->entries, &state->entry_common, 25);
        ready = 1;
    }
    return ready;
}
