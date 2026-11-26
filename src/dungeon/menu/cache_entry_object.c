#include "shared/menu_display.h"
#include "town/shop/state.h"
#include "town/shop/monster_status_initialization_g00634.h"
#include "dungeon/menu_cache_stats.h"
#include "engine/graphics.h"
#include "engine/texture.h"
#include "dungeon/menu_cache.h"
#include "engine/util.h"

/* The decoded bank uses 25 entries; the existing town constructor uses 24. */
MenuEntryObject *allocate_menu_entry_object(ActorRecord *actor, s32 slot_index, s32 x, s32 y, s32 z)
{
    ShopFirstCallbackObject *state;
    MenuEntryObject *object;
    void *allocated;
    void *sprite;

    allocated = allocate_flagged_object_node(0);
    object = allocated;
    state = &object->state;
    if (object != 0) {
        if (prepare_menu_entries(state, 25) != 0) {
            sprite = &state->display;
            object->node.sprite = sprite;
            state->display.next = link_menu_entries(state->parts);
            initialize_menu_entry(state, actor, slot_index, x, y, z);
            object->node.update_callback = &invoke_menu_callback;
            register_node(&object->node, draw_tinted_node_sprites_scratch);
            return object;
        }
        release_null_terminated_entries(state->allocations);
        object->node.flags |= 0x8000;
        object = 0;
        object_flag_block.flags |= 0x8000;
    }
    return object;
}

void release_menu_entry_object(MenuEntryObject *object)
{
    ShopFirstCallbackObject *state;
    s32 flags;

    if (object != 0) {
        state = &object->state;
        release_null_terminated_entries(state->allocations);
        release_status_entries(state->parts);
        release_monster_status_request_handles(state);
        flags = object_flag_block.flags;
        object->node.flags |= 0x8000;
        object_flag_block.flags = flags | 0x8000;
    }
}

ObjectNodeHeader *allocate_menu_pair_default(ObjectNodeHeader *owner, s32 position)
{
    return allocate_menu_pair(owner, position, 0);
}

void update_menu_panel_colors(MenuPanelState *state)
{
    advance_timed_tagged_stream(&state->cursor);
    fade_color_to_gray(state->parts[38], 0);
    fade_color_to_gray(state->parts[39], 0);
    poll_item_display_input(state);
}

void advance_menu_panel_scale(MenuPanelState *state)
{
    state->links.display->ramp = (state->step << 12) / 5;
    state->step++;
    if (state->step >= 6) {
        NODE_HEADER(state)->update_callback = update_menu_panel_colors;
    }
    poll_item_display_input(state);
}

void invoke_menu_callback(ShopFirstCallbackObject *state)
{
    state->first_callback(state);
}

ItemMenuPart *link_menu_entries(ItemMenuPart **entries)
{
    return (ItemMenuPart *)build_reverse_indexed_chain((struct S_800491F4 **)entries, menu_entry_link_table, 25);
}

void initialize_menu_entry(ShopFirstCallbackObject *state, ActorRecord *actor, s32 slot_index, s32 x, s32 y, s32 z)
{
    initialize_positioned_display_templates(&state->display, &state->display_template, &state->display_position, x, y, z);
    reset_status_parts(state);
    initialize_status_state(state, actor, slot_index);
}

s32 prepare_menu_entries(ShopFirstCallbackObject *state, s32 count)
{
    s32 ready = 0;

    state->parts = (ItemMenuPart **)rebuild_pointer_pool((s32 *)state->allocations, count, 12);
    if (state->parts != 0) {
        state->resource_position.unk0 = display_vector_defaults.unk0;
        state->resource_position.unk4 = display_vector_defaults.unk4;
        state->resource_position.unk8 = display_vector_defaults.unk8;
        set_menu_part_vectors(state->parts, &state->resource_position, 25);
        ready = 1;
    }
    return ready;
}

/* Each order stops at the first index equal to the entry limit. */
const u8 cached_monster_display_link_table[24] = {
    20, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
    12, 13, 14, 15, 16, 17, 18, 19, 25,
};
const u8 menu_entry_link_table[4] = {24, 21, 22, 25};

ItemMenuPart *link_cached_monster_display_entries(ItemMenuPart **entries)
{
    return (ItemMenuPart *)build_reverse_indexed_chain((struct S_800491F4 **)entries,
                                                       cached_monster_display_link_table, 25);
}
