#include "shared/menu_display.h"
#include "town/shop/shop_window_layout_g00610.h"
#include "town/data.h"
#include "engine/texture.h"
#include "dungeon/menu_cache.h"
#include "dungeon/menu_cache_close.h"
#include "dungeon/menu_cache_familiar_prompt.h"
#include "dungeon/menu_cache_paged.h"
#include "engine/item.h"
#include "engine/menu.h"
#include "engine/util.h"
#include "sdk/libgpu_types.h"
#include "shared/audio_commands.h"
#include "shared/game_state.h"
#include "shared/game_work.h"
#include "shared/item_ids.h"
#include "slus.h"
#include "slus/card_selection_display_data.h"
#include "slus/item_menu_primary_page_data.h"
#include "slus/sort_rank_81540.h"
#include "town/shop/item.h"

static const u8 cached_item_marker_parts[4] = {36, 37};

const RECT cached_item_panel_rectangle = {194, 6, 126, 86};

/* Fill the ten label slots from the current page. */
void populate_item_labels(ItemMenuPart **parts, MenuPanelState *display)
{
    ItemMenuPart **output_slot;
    DungeonItemEntry *entry;
    s32 entry_index;
    s32 slot;

    slot = 26;
    output_slot = &parts[26];
    entry_index = display->list->page * 10;
    while (1) {
        slot++;
        if (entry_index >= display->visible_count) {
            break;
        }
        entry = display->list->entries[entry_index];
        entry_index++;
        (*output_slot)->handler = create_item_label(entry);
        output_slot++;
        if (slot >= 36) {
            break;
        }
    }
}

/* Place both cursors on the selected slot in the two-column grid. */
void position_item_cursors(MenuPanelState *display)
{
    s32 slot;
    s32 column;

    slot = display->list->position % 10;
    column = slot / 5;
    display->parts[4]->position->x = (column << 7) - 0x38;
    display->parts[4]->position->y = ((slot - column * 5) << 4) + 8;
    display->parts[5]->position->x = display->parts[4]->position->x + 0x38;
    display->parts[5]->position->y = display->parts[4]->position->y - 9;
}

/* Draw the current page icons and clear any unused slots. */
void populate_item_icons(MenuPanelState *display)
{
    s32 entry_index;
    s32 slot_index;
    DungeonItemEntry *entry;
    void *icon;

    entry_index = display->list->page * 10;
    slot_index = 6;
    while (1) {
        if (entry_index >= display->visible_count) {
            break;
        }
        entry = display->list->entries[entry_index];
        icon = (void *)(unsigned long)(u32)lookup_item_category_mapped_value(entry->kind, entry->unk_00);
        entry_index++;
        display->parts[slot_index]->handler = icon;
        slot_index++;
        if (slot_index >= 16) {
            break;
        }
    }
    while (slot_index < 16) {
        display->parts[slot_index]->handler = 0;
        slot_index++;
    }
}

/* Refresh page bounds, labels, icons and indicators. */
void refresh_item_page(MenuPanelState *display)
{
    populate_item_icons(display);
    update_item_page_bounds(display);
    populate_item_page_text(display);
    populate_item_labels(display->parts, display);
    populate_item_page_indicators(display->parts, display);
}

/* Refresh the page and update the label for the selected item. */
void redraw_item_selection(MenuPanelState *display)
{
    refresh_item_cursor_pair(display);
    populate_item_icons(display);
    populate_item_page_text(display);
    update_item_page_bounds(display);
    populate_item_labels(display->parts, display);
    populate_item_page_indicators(display->parts, display);
    get_item_name(display->list->entries[display->list->position]);
}

/* Attach the owning list and set the visible range before opening the display. */
void initialize_item_request(MenuPanelState *display, CachedItemListNode *owner)
{
    s32 count;

    display->owner = owner;
    display->list = &owner->list;
    display->enabled = 1;
    count = display->list->count - display->list->excluded_count;
    display->visible_count = count;
    if (count != 0) {
        display->last_visible_page = (count - 1) / 10;
    }
    NODE_HEADER(display)->update_callback = advance_menu_panel_scale;
}

/* Initialize the request and attach its display blocks and parts. */
void configure_item_display(MenuPanelState *display, CachedItemListNode *owner)
{
    initialize_item_request(display, owner);
    initialize_item_menu_linked_blocks(&display->links, &display->display, &display->display_position);
    initialize_item_parts(display);
}

/* Allocate the display parts and assign their common position data. */
s32 prepare_item_parts(MenuPanelState *display, s32 count)
{
    s32 ready = 0;

    display->parts = (ItemMenuPart **)rebuild_pointer_pool((s32 *)display->part_resources, count, 12);
    if (display->parts != 0) {
        display->part_common.unk0 = display_vector_defaults.unk0;
        display->part_common.unk4 = display_vector_defaults.unk4;
        display->part_common.unk8 = display_vector_defaults.unk8;
        set_menu_part_vectors(display->parts, &display->part_common, 40);
        ready = 1;
    }
    return ready;
}

/* Initialize the entry render packets and position each group. */
void initialize_item_parts(MenuPanelState *object)
{
    MenuPanelState *obj = object;
    s32 slot_index;

    for (slot_index = 0; slot_index < 2; slot_index++) {
        obj->parts[slot_index]->handler = item_menu_slot_handler_address;
        obj->parts[slot_index]->position->x = slot_index << 7;
    }

    initialize_item_menu_panel_rectangle(obj->panel);

    for (slot_index = 2; slot_index < 4; slot_index++) {
        obj->parts[slot_index]->handler = obj->panel;
        obj->parts[slot_index]->position->x = (slot_index - 2) << 7;
    }

    position_item_cursors(obj);
    layout_item_menu_upper_pair_columns(obj->parts);
    layout_item_menu_lower_item_columns(obj->parts);
    position_item_menu_side_indicators(obj->parts);
    layout_item_menu_lower_pair_columns(obj->parts);
    redraw_item_selection(obj);
}

/* Start the display in its open state and install its steady-state update. */
CachedItemDisplayNode *create_open_item_display(ObjectNodeHeader *owner)
{
    CachedItemDisplayNode *object;

    object = create_item_display(owner);
    if (object != 0) {
        object->header.update_callback = update_menu_panel_colors;
        object->state.links.display->ramp = 0x1000;
    }
    return object;
}

/* Release the item parts and clear the selected panel slot. */
ObjectNodeHeader *release_item_display(ObjectNodeHeader *node)
{
    MenuPanelState *panel;

    if (node != 0) {
        panel = NODE_BODY(node);
        release_null_terminated_entries(panel->part_resources);
        clear_item_menu_entry_groups(panel->parts);
        node->flags |= OBJECT_REMOVE_PENDING;
        node = 0;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    return node;
}

/* Restore the current page and re-enable item selection. */
void resume_item_display(ObjectNodeHeader *node)
{
    MenuPanelState *panel = NODE_BODY(node);
    CachedItemList *list = panel->list;

    list->page = list->position / 10;
    position_item_cursors(panel);
    refresh_item_cursor_graphics(panel);
    refresh_item_page(panel);
    panel->enabled = 1;
}

void refresh_item_cursor_graphics(MenuPanelState *panel)
{
    if (panel->visible_count != 0) {
        if (panel->list->script_pending == 0) {
            initialize_scaled_entry_cursor(&panel->cursor, &shop_cursor_template,
                                                   (s32 *)panel->parts[4]);
        } else {
            panel->cursor.output = 0;
            panel->parts[4]->handler = cached_fixed_storage_cursor;
        }
    }
}

void refresh_item_cursor_pair(MenuPanelState *panel)
{
    if (panel->visible_count != 0) {
        refresh_item_cursor_graphics(panel);
        panel->parts[5]->handler = cached_item_secondary_cursor;
    }
}

void populate_item_page_text(MenuPanelState *display)
{
    s32 index;
    s32 part = 16;
    ItemCategory *categories;

    clear_item_menu_entry_groups(display->parts);
    index = display->list->page * 10;
    categories = itemCategoryTable;
    do {
        s32 mode;
        DungeonItemEntry *entry;
        char *text;
        void *label;
        const ItemRecord *records;

        if (index >= display->visible_count) {
            break;
        }
        text = (char *)(unsigned long)(u32)select_item_data(display->list->entries[index], &mode);
        entry = display->list->entries[index];
        records = categories[entry->kind].records;
        if ((records[entry->unk_00].flags & 0x800) && (entry->unk_03 & 0x40)) {
            mode = 6;
        }
        index++;
        label = create_label_glyph_entries(text, mode);
        display->parts[part]->handler = label;
        part++;
    } while (part < 26);
}

void update_item_page_bounds(MenuPanelState *display)
{
    display->parts[38]->handler = display->list->page > 0 ? item_menu_primary_page_data : 0;
    display->parts[39]->handler = display->list->page < display->list->last_page ? card_selection_display_data : 0;
}

void populate_item_page_indicators(ItemMenuPart **parts, MenuPanelState *display)
{
    s32 row;
    s32 index;
    const u8 *marker_parts;

    parts[36]->handler = 0;
    parts[37]->handler = 0;
    row = 0;
    index = display->list->page * 10;
    marker_parts = cached_item_marker_parts;
    do {
        DungeonItemEntry *entry;
        s32 slot;

        if (index >= display->visible_count) {
            break;
        }
        entry = display->list->entries[index];
        if (entry->kind == ITEM_KIND_FAMILIAR && (entry->unk_03 & 0x20)) {
            slot = get_menu_actor_index((ActorRecord *)(unsigned long)(u32)resolve_item_record_slot_value(entry));
            if (slot != 2) {
                SpritePartCommand *marker = get_assigned_familiar_marker(slot);
                /* The indexed offset is the first operand of the address addition. */
                const u8 *marker_part = (const u8 *)(slot + (unsigned long)marker_parts);

                parts[*marker_part]->handler = marker;
                parts[*marker_part]->position->x = (row / 5) * 128 + 56;
                parts[*marker_part]->position->y = (row % 5) * 16 + 22;
            }
        }
        row++;
        index++;
    } while (row < 10);
}

CachedMenuRetryResult retry_item_pair_open(MenuPanelState *display)
{
    return (ObjectNodeHeader *)(long)(reopen_menu_pair(&display->owner->header));
}

void cancel_item_selection(MenuPanelState *display)
{
    CachedItemList *list = display->list;

    if (list->script_pending == 0) {
        schedule_menu_pair_close(&display->owner->header);
    } else {
        DungeonItemEntry *selected;

        list->script_pending = 0;
        selected = selected_item_record_alias.item;
        selected->unk_03 &= ~0x40;
        selected_item_record_alias.item = 0;
        selected_item_record_alias.request = 0;
        refresh_item_cursor_graphics(display);
        refresh_item_page(display);
    }
}

CachedItemDisplayNode *create_item_display(ObjectNodeHeader *owner)
{
    CachedItemDisplayNode *node = allocate_flagged_object_node(0);

    if (node != 0) {
        MenuPanelState *display = &node->state;

        if (prepare_item_parts(display, 40) != 0) {
            node->header.sprite = (SpriteFrameState *)&display->links;
            configure_item_display(display, (CachedItemListNode *)owner);
            display->draw_chain = link_item_display_entries(display->parts);
            register_node(&node->header, draw_tinted_node_sprites_scratch);
            return node;
        }
        release_null_terminated_entries(display->part_resources);
        node->header.flags |= OBJECT_REMOVE_PENDING;
        node = 0;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    return node;
}

CachedMenuRetryResult open_item_display_selection_action(MenuPanelState *display)
{
    s32 row = display->list->position % 10;
    s32 column = row / 5;
    s32 x = column != 0 ? 40 : -180;
    s32 y = (row - column * 5) * 24 - 128;

    display->enabled = 0;
    return open_paged_item_menu(&display->owner->header, display->list->position,
                          0, x, y, display->list->entries[display->list->position]);
}

void advance_item_display_resume(MenuPanelState *display)
{
    if (display->resume(display) != 0) {
        NODE_HEADER(display)->update_callback = display->saved_update;
    }
}

void confirm_item_selection(MenuPanelState *display)
{
    CachedItemList *list = display->list;

    if (list->script_pending == 0) {
        if (open_item_display_selection_action(display) == 0) {
            void *previous_update;

            display->resume = open_item_display_selection_action;
            previous_update = NODE_HEADER(display)->update_callback;
            NODE_HEADER(display)->update_callback = advance_item_display_resume;
            display->saved_update = previous_update;
        }
    } else {
        DungeonMenuItemSelection *selection = &selected_item_record_alias;
        DungeonItemEntry *next = list->entries[list->position];
        DungeonItemEntry *selected = selection->item;

        selection->secondary_item = next;
        selected->unk_03 &= ~0x40;
        finish_menu_pair_cleanup(&display->owner->header);
    }
}

void poll_item_display_input(MenuPanelState *display)
{
    GameWork *input = &g_game_work;
    s32 position = 0;

    if (input->buttons != 0 && display->enabled != 0) {
        if (display->visible_count == 0 && (input->pressed_buttons & 0x20)) {
            SD_Call(AUDIO_CANCEL);
            cancel_item_selection(display);
        }

        if (input->pressed_buttons & 0x20) {
            SD_Call(AUDIO_CANCEL);
            cancel_item_selection(display);
        } else if (input->pressed_buttons & 0x40) {
            if (display->visible_count != 0) {
                SD_Call(AUDIO_ACCEPT);
                confirm_item_selection(display);
            }
        } else if (input->pressed_buttons & 0x10) {
            if (display->visible_count != 0) {
                SD_Call(AUDIO_MENU_CONFIRM);
                sort_entries_by_category(GAME_STATE->item_list);
                refresh_item_page(display);
                get_item_name(display->list->entries[display->list->position]);
            }
        } else if (input->buttons & 0xf000) {
            if (input->pressed_buttons & 0xf000) {
                display->repeat_delay = 0;
                if (input->pressed_buttons & 0x8000) {
                    position = -5;
                } else if (input->pressed_buttons & 0x2000) {
                    position = 5;
                } else if (input->pressed_buttons & 0x1000) {
                    position = -1;
                } else if (input->pressed_buttons & 0x4000) {
                    position = 1;
                }
            } else if (display->repeat_delay >= 5) {
                if (input->buttons & 0x8000) {
                    position = -5;
                } else if (input->buttons & 0x2000) {
                    position = 5;
                } else if (input->buttons & 0x1000) {
                    position = -1;
                } else if (input->buttons & 0x4000) {
                    position = 1;
                }
                display->repeat_delay--;
            } else {
                display->repeat_delay++;
                return;
            }

            position = advance_index_with_directional_clamp(display->list->position, position, display->list->count);
            if ((position >= display->visible_count && display->list->position / 10 == display->last_visible_page)
                || display->visible_count == 0) {
                SD_Call(AUDIO_CURSOR_MOVE);
                display->list->position = display->visible_count;
                release_menu_pair_active_panel(&display->owner->header);
                if (reopen_menu_pair(&display->owner->header) == 0) {
                    void *previous_update;

                    display->resume = retry_item_pair_open;
                    previous_update = NODE_HEADER(display)->update_callback;
                    NODE_HEADER(display)->update_callback = advance_item_display_resume;
                    display->saved_update = previous_update;
                }
            } else {
                position = advance_index_with_directional_clamp(position, 0, display->visible_count);
                if (position != display->list->position) {
                    SD_Call(AUDIO_CURSOR_MOVE);
                    display->list->position = position;
                    position = display->list->position / 10;
                    position_item_cursors(display);
                    get_item_name(display->list->entries[display->list->position]);
                    if (position != display->list->page) {
                        display->list->page = position;
                        refresh_item_page(display);
                    }
                }
            }
        }
    }
}
