/* Update item menu record g01150.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01150 - CL:town/func_800B2100, CL:town/func_800B2150, CL:town/func_800B2264.
 */
#include "town/shop/item/update_item_menu_record_g01150.h"

/* Run the record update sequence and process its stored value. */
void update_item_menu_record(ItemMenuObject *record) {
    populate_item_menu_lower_entries(record);
    update_item_menu_page_bounds(record);
    populate_current_item_menu_page(record);
    populate_item_menu_page_entries(record->parts, record);
    item_menu_no_op(record->parts, record);
}

/* Disables the menu and opens the selected entry's display controller in a two-column, five-row layout. */
void *place_selected_item_menu_entry(ItemMenuObject *entry) {
    s32 x_pos;
    s32 page_slot;

    page_slot = entry->menu->position % 10;
    x_pos = -0xB4;
    if ((page_slot / 5) != 0) {
        x_pos = 0x28;
    }
    entry->enabled = 0;
    return create_item_menu_display_controller(entry->owner, entry->menu->position, x_pos,
        ((page_slot % 5) * 0x18) - 0x80,
        entry->menu->entries[entry->menu->position]);
}

/* Store the selected-entry display controller and restore the saved update callback once it exists. */
void store_item_menu_check_result(ItemMenuObject *record_data) {
    record_data->menu->display_controller = place_selected_item_menu_entry(record_data);
    if (record_data->menu->display_controller != 0) {
        ITEM_MENU_OBJECT_NODE(record_data)->header.update_callback = record_data->saved_update;
    }
}

/* Handles town menu actions, selection movement, and scrolling between bands. */
void update_item_menu_selection(ItemMenuObject *obj)
{
    s32 held_buttons;
    s32 move_step;
    s32 next_position;
    s32 next_band;
    ItemMenuState *action_inner;
    ItemMenuState *move_inner;
    ItemMenuState *selection;
    ItemMenuState *refreshed_inner;

    held_buttons = g_game_work.buttons;
    move_step = 0;
    if (held_buttons == 0) {
        return;
    }
    if (obj->enabled == 0) {
        return;
    }
    if (obj->menu->count == 0) {
        if ((g_game_work.pressed_buttons) & 0x20) {
            SD_Call(0x515);
            set_item_menu_data_pointer(obj->owner);
        }
        return;
    }

    if ((g_game_work.pressed_buttons) & 0x20) {
        SD_Call(0x515);
        set_item_menu_data_pointer(obj->owner);
        return;
    }
    if ((g_game_work.pressed_buttons) & 0x40) {
        SD_Call(0x514);
        obj->menu->display_controller = place_selected_item_menu_entry(obj);
        if (obj->menu->display_controller != 0) {
            return;
        }
        obj->saved_update = ITEM_MENU_OBJECT_NODE(obj)->header.update_callback;
        ITEM_MENU_OBJECT_NODE(obj)->header.update_callback = D_800AF96C;
        return;
    } else if ((g_game_work.pressed_buttons) & 0x10) {
        SD_Call(0x503);
        sort_entries_by_category((void *)0x8001029C);
        update_item_menu_record(obj);
        action_inner = obj->menu;
        get_item_name_with_shared_text_table(action_inner->entries[action_inner->position]);
        return;
    }

    if (!(held_buttons & 0xF000)) {
        return;
    }
    if ((g_game_work.pressed_buttons) & 0xF000) {
        obj->repeat_delay = 0;
        if ((g_game_work.pressed_buttons) & 0x8000)
            move_step = -5;
        else if ((g_game_work.pressed_buttons) & 0x2000)
            move_step = 5;
        else if ((g_game_work.pressed_buttons) & 0x1000)
            move_step = -1;
        else if ((g_game_work.pressed_buttons) & 0x4000)
            move_step = 1;
    } else {
        if (obj->repeat_delay >= 5) {
            if (held_buttons & 0x8000)
                move_step = -5;
            else if (held_buttons & 0x2000)
                move_step = 5;
            else if (held_buttons & 0x1000)
                move_step = -1;
            else if (held_buttons & 0x4000)
                move_step = 1;
            obj->repeat_delay = *(s32 *)&obj->repeat_delay - 1;
        } else {
            obj->repeat_delay++;
            return;
        }
    }

    move_inner = obj->menu;
    next_position = advance_index_with_directional_clamp(move_inner->position, move_step, move_inner->count);
    selection = obj->menu;
    if (next_position >= selection->count) {
        selection->position = next_position;
        return;
    }
    if (next_position == selection->position) {
        return;
    }
    SD_Call(0x502);
    obj->menu->position = next_position;
    next_band = obj->menu->position / 10;
    set_item_menu_entry_coordinates(obj);
    refreshed_inner = obj->menu;
    get_item_name_with_shared_text_table(refreshed_inner->entries[refreshed_inner->position]);
    if (next_band == obj->menu->page) {
        return;
    }
    if (next_band < obj->menu->page) {
        obj->parts[38]->position->color = D_800891F4;
    } else {
        obj->parts[39]->position->color = D_800891F4;
    }
    obj->menu->page = next_band;
    update_item_menu_record(obj);
}

/* Advance the cursor stream, ease both side indicators toward grey, then handle input. */
void reset_item_menu_entity_state(ItemMenuObject *entity) {
    advance_timed_tagged_stream(&entity->cursor);
    fade_color_to_gray(entity->parts[38], 0);
    fade_color_to_gray(entity->parts[39], 0);
    update_item_menu_selection(entity);
}

/* Ramp the display block open over five steps, then install the steady-state update callback. */
void advance_item_menu_step(ItemMenuObject *object) {
    s32 step;
    s32 nextStep;

    step = object->open_step;
    object->links.display->ramp = (s16) ((step << 0xC) / 5);
    nextStep = object->open_step + 1;
    object->open_step = nextStep;
    if (nextStep < 6) {
    } else {
        ITEM_MENU_OBJECT_NODE(object)->header.update_callback = &item_menu_record_callback;
    }
    update_item_menu_selection(object);
}
