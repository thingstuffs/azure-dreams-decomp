/* Update item menu record g01150.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01150 - CL:town/func_800B2100, CL:town/func_800B2150, CL:town/func_800B2264.
 */
#include "town/shop/item/update_item_menu_record_g01150.h"

/* Run the record update sequence and process its stored value. */
void update_item_menu_record(Rec_func_800AF254_arg1 *record) {
    populate_item_menu_lower_entries(record);
    update_item_menu_page_bounds(record);
    populate_current_item_menu_page((struct S_800AF674_0 *)(record));
    populate_item_menu_page_entries(record->unk_A8.as_s32, (void * *)(record));
    item_menu_no_op(record->unk_A8.as_s32, record);
}

/* Positions an indexed entry in a two-column, five-row layout. */
s32 place_selected_item_menu_entry(Rec_func_800AF254_arg1 *entry) {
    s32 x_pos;
    s32 page_slot;

    page_slot = ((S_800AF8B0_2 *)(((Rec_func_800AF254_arg1 *)entry)->unk_00))->unk_18 % 10;
    x_pos = -0xB4;
    if ((page_slot / 5) != 0) {
        x_pos = 0x28;
    }
    entry->unk_10 = 0;
    create_item_menu_display_controller(entry->unk_18, ((S_800AF8B0_2 *)(((Rec_func_800AF254_arg1 *)entry)->unk_00))->unk_18, x_pos,
        ((page_slot % 5) * 0x18) - 0x80,
        ((s32 *)((S_800AF8B0_2 *)(((Rec_func_800AF254_arg1 *)entry)->unk_00))->unk_20)[((S_800AF8B0_2 *)(((Rec_func_800AF254_arg1 *)entry)->unk_00))->unk_18]);
}

/* Store the check result and copy the saved value to the record header on success. */
void store_item_menu_check_result(void *record_data) {
    ((S_800AF96C_2 *)(((S_800AF96C_1 *)record_data)->unk_00))->unk_04 = place_selected_item_menu_entry((Rec_func_800AF254_arg1 *)record_data);
    if (((S_800AF96C_2 *)(((S_800AF96C_1 *)record_data)->unk_00))->unk_04 != 0) {
        ((S_800AF96C_0 *)((u8 *)record_data - 0x10))->unk_00 = (s32) ((S_800AF96C_0 *)((u8 *)record_data
            - 0x10))->unk_14;
    }
}

/* Handles town menu actions, selection movement, and scrolling between bands. */
void update_item_menu_selection(TownObject *obj)
{
    s32 held_buttons;
    s32 move_step;
    s32 next_position;
    s32 next_band;
    TownInner *action_inner;
    TownInner *move_inner;
    TownInner *selection;
    TownInner *refreshed_inner;

    held_buttons = g_game_work.buttons;
    move_step = 0;
    if (held_buttons == 0) {
        return;
    }
    if (obj->enabled == 0) {
        return;
    }
    if (obj->inner->limit == 0) {
        if (((s32)g_game_work.pressed_buttons) & 0x20) {
            SD_Call(0x515);
            set_item_menu_data_pointer(obj->resource);
        }
        return;
    }

    if (((s32)g_game_work.pressed_buttons) & 0x20) {
        SD_Call(0x515);
        set_item_menu_data_pointer(obj->resource);
        return;
    }
    if (((s32)g_game_work.pressed_buttons) & 0x40) {
        SD_Call(0x514);
        obj->inner->handle = place_selected_item_menu_entry((Rec_func_800AF254_arg1 *)obj);
        if (obj->inner->handle != 0) {
            return;
        }
        obj->old_state = *(s32 *)((u8 *)obj - 0x10);
        *(void **)((u8 *)obj - 0x10) = D_800AF96C;
        return;
    } else if (((s32)g_game_work.pressed_buttons) & 0x10) {
        SD_Call(0x503);
        sort_entries_by_category((void *)0x8001029C);
        update_item_menu_record(obj);
        action_inner = obj->inner;
        get_item_name_with_shared_text_table(action_inner->table[action_inner->position]);
        return;
    }

    if (!(held_buttons & 0xF000)) {
        return;
    }
    if (((s32)g_game_work.pressed_buttons) & 0xF000) {
        obj->counter = 0;
        if (((s32)g_game_work.pressed_buttons) & 0x8000)
            move_step = -5;
        else if (((s32)g_game_work.pressed_buttons) & 0x2000)
            move_step = 5;
        else if (((s32)g_game_work.pressed_buttons) & 0x1000)
            move_step = -1;
        else if (((s32)g_game_work.pressed_buttons) & 0x4000)
            move_step = 1;
    } else {
        if (obj->counter >= 5) {
            if (held_buttons & 0x8000)
                move_step = -5;
            else if (held_buttons & 0x2000)
                move_step = 5;
            else if (held_buttons & 0x1000)
                move_step = -1;
            else if (held_buttons & 0x4000)
                move_step = 1;
            obj->counter = *(s32 *)&obj->counter - 1;
        } else {
            obj->counter++;
            return;
        }
    }

    move_inner = obj->inner;
    next_position = advance_index_with_directional_clamp(move_inner->position, move_step, move_inner->limit);
    selection = obj->inner;
    if (next_position >= selection->limit) {
        selection->position = next_position;
        return;
    }
    if (next_position == selection->position) {
        return;
    }
    SD_Call(0x502);
    obj->inner->position = next_position;
    next_band = obj->inner->position / 10;
    set_item_menu_entry_coordinates(obj);
    refreshed_inner = obj->inner;
    get_item_name_with_shared_text_table(refreshed_inner->table[refreshed_inner->position]);
    if (next_band == obj->inner->band) {
        return;
    }
    if (next_band < obj->inner->band) {
        *(s32 *)obj->parts[38]->position = D_800891F4;
    } else {
        *(s32 *)obj->parts[39]->position = D_800891F4;
    }
    obj->inner->band = next_band;
    update_item_menu_record(obj);
}

/* Reset the entity sub-object and its two linked handles, then finalize the update. */
void reset_item_menu_entity_state(void *entity) {
    advance_timed_tagged_stream(entity + 0x1C);
    fade_color_to_gray(((S_800AFD00_1 *)(((Rec_func_800AF254_arg1 *)entity)->unk_A8.as_pv))->unk_98, 0);
    fade_color_to_gray(((S_800AFD00_1 *)(((Rec_func_800AF254_arg1 *)entity)->unk_A8.as_pv))->unk_9C, 0);
    update_item_menu_selection(entity);
}

/* Update the linked value from the current step and advance the state after six steps. */
void advance_item_menu_step(void *object) {
    s32 step;
    s32 nextStep;

    step = ((S_800AFD5C_0 *)((u8 *)object - 0x10))->unk_18;
    ((S_800AFD5C_2 *)(((Rec_func_800AF254_arg1 *)object)->unk_9C))->unk_06 = (s16) ((step << 0xC) / 5);
    nextStep = ((S_800AFD5C_0 *)((u8 *)object - 0x10))->unk_18 + 1;
    ((S_800AFD5C_0 *)((u8 *)object - 0x10))->unk_18 = nextStep;
    if (nextStep < 6) {
    } else {
        ((S_800AFD5C_0 *)((u8 *)object - 0x10))->unk_00 = &D_800AFD00;
    }
    update_item_menu_selection(object);
}
