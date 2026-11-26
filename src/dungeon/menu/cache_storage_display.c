#include "town/shop/shop_window_layout_g00610.h"
#include "engine/graphics.h"
#include "engine/texture.h"
#include "dungeon/menu_cache_close.h"
#include "dungeon/menu_cache_paged.h"
#include "engine/item.h"
#include "engine/util.h"
#include "engine/menu.h"
#include "sdk/libgpu_types.h"
#include "shared/audio_commands.h"
#include "shared/game_work.h"
#include "shared/item_ids.h"
#include "shared/menu_display.h"
#include "slus.h"
#include "slus/item_menu_primary_page_data.h"

static const u8 cached_storage_draw_order[] = {1, 3, 0, 4, 5, 6, 7, 8, 9, 2, 10, 11};

const RECT cached_storage_panel_rectangles[] = {
    {-60, -10, 120, 20},
    {-60, -22, 120, 36},
};

/* Build the draw chain for the eleven storage-display parts. */
ItemMenuPart *link_storage_display_entries(ItemMenuPart **entries)
{
    return (ItemMenuPart *)build_reverse_indexed_chain((struct S_800491F4 **)entries, cached_storage_draw_order, 11);
}

/* Copy the display defaults and set the storage panel position. */
void configure_storage_display_blocks(ItemMenuDisplayLinks *state, StorageDisplayBlock *primary,
                                             ItemMenuDisplayPosition *secondary)
{
    s32 *defaults = display_block_defaults.words;
    DisplayPositionWords *vector = &display_vector_defaults;
    s32 head;
    s32 offset = -60;

    primary->words[0] = display_block_defaults.words[0];
    primary->words[1] = defaults[1];
    primary->words[2] = defaults[2];
    head = display_vector_defaults.unk0;
    primary->words[3] = defaults[3];
    secondary->words.unk0 = head;
    secondary->words.unk4 = vector->unk4;
    secondary->words.unk8 = vector->unk8;
    state->display = &primary->display;
    state->position = secondary;
    state->unk_00 = 0;
    state->display->x = offset;
    state->display->y = offset;
    state->display->depth = 0x200;
    state->position->position.offset_y = 0x30;
    state->display->mode = 4;
}

/* Collect the extra items and select the active storage row. */
void initialize_storage_request(CachedStoragePanel *panel, ObjectNodeHeader *owner)
{
    s32 count;

    panel->owner = owner;
    panel->list = NODE_BODY(owner);
    count = 0;
    if (panel->list->extra_entries[1] != 0) {
        panel->extra_entries[0] = panel->list->extra_entries[1];
        count = 1;
    }
    if (panel->list->extra_entries[0] != 0) {
        panel->extra_entries[count] = panel->list->extra_entries[0];
        count++;
    }
    panel->extra_entry_count = count;
    panel->regular_entry_count = panel->list->count - count;
    panel->selected_extra_index = count - (panel->list->count - panel->list->position);
    panel->enabled = 1;
    get_item_name(panel->extra_entries[panel->selected_extra_index]);
    NODE_HEADER(panel)->update_callback = handle_storage_panel_input;
}

/* Allocate storage parts and give each one the shared position vector. */
s32 prepare_storage_parts(CachedStoragePanel *panel, s32 count)
{
    s32 ready = 0;

    panel->parts = (ItemMenuPart **)rebuild_pointer_pool((s32 *)panel->resources, count, 8);
    if (panel->parts != 0) {
        panel->part_common.unk0 = display_vector_defaults.unk0;
        panel->part_common.unk4 = display_vector_defaults.unk4;
        panel->part_common.unk8 = display_vector_defaults.unk8;
        set_menu_part_vectors(panel->parts, &panel->part_common, 11);
        ready = 1;
    }
    return ready;
}

/* Flag the two displayed objects for each extra-item row for removal. */
void release_storage_components(CachedStoragePanel *panel)
{
    s32 index;

    for (index = 0; index < panel->extra_entry_count; index++) {
        flag_optional_object_for_removal(panel->parts[index + 6]->handler);
        flag_optional_object_for_removal(panel->parts[index + 8]->handler);
    }
}

/* Reopen the linked menu, retrying on the next frame if allocation fails. */
CachedMenuRetryResult try_storage_panel_reopen(CachedStoragePanel *panel)
{
    return (ObjectNodeHeader *)(long)(reopen_menu_pair(panel->owner));
}

void advance_storage_panel_resume(CachedStoragePanel *panel)
{
    if (panel->resume(panel) != 0) {
        NODE_HEADER(panel)->update_callback = panel->saved_update;
    }
}

void reopen_display_from_storage_panel(CachedStoragePanel *panel)
{
    CachedItemList *list;
    void *previous_update;

    release_menu_pair_active_panel(panel->owner);
    list = panel->list;
    list->page = list->position / 10;
    if (reopen_menu_pair(panel->owner) == 0) {
        panel->resume = try_storage_panel_reopen;
        previous_update = NODE_HEADER(panel)->update_callback;
        NODE_HEADER(panel)->update_callback = advance_storage_panel_resume;
        panel->saved_update = previous_update;
    }
}

/* Advance the cursor stream and fade the indicator before polling buttons. */
void handle_storage_panel_input(CachedStoragePanel *panel)
{
    advance_timed_tagged_stream(&panel->cursor);
    fade_color_to_gray(panel->parts[10], 0);
    poll_storage_panel_input(panel);
}

void locate_storage_cursor(CachedStoragePanel *panel)
{
    panel->parts[2]->position->x = -56;
    panel->parts[2]->position->y = panel->selected_extra_index * 16 + 8;
    panel->parts[3]->position->x = panel->parts[2]->position->x + 56;
    panel->parts[3]->position->y = panel->parts[2]->position->y - 9;
}

/* Move between the extra rows or reopen the regular item display. */
void poll_storage_panel_input(CachedStoragePanel *panel)
{
    GameWork *input;
    s32 delta;
    s32 selection;
    s32 regular_count;

    input = &g_game_work;
    delta = 0;
    if (input->buttons && panel->enabled) {
        if (input->pressed_buttons & 0x40) {
            if (!is_familiar_item(panel->extra_entries[panel->selected_extra_index])) {
                SD_Call(AUDIO_ACCEPT);
            }
            confirm_storage_selection(panel);
        } else if (input->pressed_buttons & 0x20) {
            SD_Call(AUDIO_CANCEL);
            cancel_storage_selection(panel);
        } else if (input->buttons & 0xf000) {
            if (input->pressed_buttons & 0xf000) {
                panel->repeat_ticks = 0;
                if (input->pressed_buttons & 0x8000) {
                    delta = -5;
                } else if (input->pressed_buttons & 0x2000) {
                    delta = 5;
                } else if (input->pressed_buttons & 0x1000) {
                    delta = -1;
                } else if (input->pressed_buttons & 0x4000) {
                    delta = 1;
                }
            } else if (panel->repeat_ticks >= 5) {
                if (input->buttons & 0x8000) {
                    delta = -5;
                } else if (input->buttons & 0x2000) {
                    delta = 5;
                } else if (input->buttons & 0x1000) {
                    delta = -1;
                } else if (input->buttons & 0x4000) {
                    delta = 1;
                }
                panel->repeat_ticks--;
            } else {
                panel->repeat_ticks++;
                return;
            }
            selection = advance_index_with_directional_clamp(panel->list->position, delta, panel->list->count);
            if (selection != panel->list->position) {
                regular_count = panel->regular_entry_count;
                if (selection >= regular_count) {
                    SD_Call(AUDIO_CURSOR_MOVE);
                    panel->list->position = selection;
                    panel->selected_extra_index = selection - panel->regular_entry_count;
                    locate_storage_cursor(panel);
                    get_item_name(panel->extra_entries[panel->selected_extra_index]);
                } else {
                    if (regular_count != 0) {
                        if (delta < -1) {
                            panel->list->position = ((regular_count - 1) / 5) * 5;
                        } else {
                            panel->list->position = selection;
                        }
                    } else {
                        panel->list->position = -1;
                    }
                    SD_Call(AUDIO_CURSOR_MOVE);
                    reopen_display_from_storage_panel(panel);
                }
            }
        }
    }
}

/* Build the panel for the short or tall display and mark its closing command. */
void initialize_storage_rectangle(CachedStoragePanelPacket *packet, s32 height_index)
{
    build_panel_rectangle_packets(packet, (void *)&cached_storage_panel_rectangles[height_index]);
    packet->closing_flags |= 0x80;
}

void cancel_storage_selection(CachedStoragePanel *panel)
{
    CachedItemList *list = panel->list;

    if (list->script_pending == 0) {
        schedule_menu_pair_close(panel->owner);
    } else {
        DungeonItemEntry *selected;

        list->script_pending = 0;
        selected = selected_item_record_alias.item;
        selected->unk_03 &= ~0x40;
        selected_item_record_alias.item = 0;
        selected_item_record_alias.request = 0;
        refresh_storage_panel(panel);
    }
}

void refresh_storage_header(CachedStoragePanel *panel)
{
    if (panel->extra_entry_count != 0) {
        if (panel->list->script_pending == 0) {
            initialize_scaled_entry_cursor(&panel->cursor, &shop_cursor_template,
                                                   (s32 *)panel->parts[2]);
        } else {
            panel->cursor.output = 0;
            panel->parts[2]->handler = cached_fixed_storage_cursor;
        }
    }
}

void populate_storage_panel_rows(CachedStoragePanel *panel)
{
    s32 index = 0;

    if (panel->extra_entry_count > 0) {
        ItemCategory *categories = itemCategoryTable;

        do {
            s32 mode;
            char *text = (char *)(unsigned long)(u32)select_item_data(panel->extra_entries[index], &mode);
            DungeonItemEntry *item = panel->extra_entries[index];
            const ItemRecord *records = categories[item->kind].records;

            if ((records[item->unk_00].flags & 0x800) && (item->unk_03 & 0x40)) {
                mode = 6;
            }
            flag_optional_object_for_removal(panel->parts[index + 6]->handler);
            panel->parts[index + 6]->handler = create_label_glyph_entries(text, mode);
            index++;
        } while (index < panel->extra_entry_count);
    }
}

/* Lay out the storage frame and its extra item rows. */
void initialize_storage_parts(CachedStoragePanel *panel)
{
    s32 index;

    if (panel->extra_entry_count == 1) {
        panel->parts[0]->handler = cached_storage_one_row_frame;
        initialize_storage_rectangle(&panel->packet, 0);
        panel->parts[10]->position->y = 16;
        panel->parts[1]->position->y = 15;
    } else {
        panel->parts[0]->handler = cached_storage_two_row_frame;
        initialize_storage_rectangle(&panel->packet, 1);
        panel->parts[10]->position->y = 24;
        panel->parts[1]->position->y = 27;
    }
    panel->parts[1]->handler = &panel->packet;
    panel->parts[3]->handler = cached_item_secondary_cursor;
    if (panel->regular_entry_count != 0) {
        panel->parts[10]->handler = item_menu_primary_page_data;
    }
    refresh_storage_header(panel);
    locate_storage_cursor(panel);
    index = 0;
    if (index < panel->extra_entry_count) {
        s32 label_y = 136;

        do {
            s32 glyph_style;
            char *text;

            panel->parts[index + 4]->handler = (void *)(unsigned long)(u32)lookup_item_category_mapped_value(
                panel->extra_entries[index]->kind, panel->extra_entries[index]->unk_00);
            text = (char *)(unsigned long)(u32)select_item_data(panel->extra_entries[index], &glyph_style);
            panel->parts[index + 6]->handler = create_label_glyph_entries(text, glyph_style);
            if (panel->extra_entries[index]->kind != ITEM_KIND_FAMILIAR &&
                get_item_category_flags(panel->extra_entries[index]) == 0) {
                panel->parts[index + 8]->handler = create_item_label(panel->extra_entries[index]);
            }
            panel->parts[index + 6]->position->x = 96;
            panel->parts[index + 6]->position->y = label_y;
            panel->parts[index + 4]->position->x = -48;
            panel->parts[index + 4]->position->y = index * 16 + 22;
            panel->parts[index + 8]->position->x = 88;
            panel->parts[index + 8]->position->y = label_y;
            index++;
            label_y += 16;
        } while (index < panel->extra_entry_count);
    }
    populate_storage_panel_rows(panel);
    panel->parts[10]->position->x = -64;
}

ObjectNodeHeader *create_storage_display_node(ObjectNodeHeader *owner)
{
    ObjectNodeHeader *node = allocate_flagged_object_node(0);

    if (node != 0) {
        CachedStoragePanel *panel = NODE_BODY(node);

        if (prepare_storage_parts(panel, 11) != 0) {
            node->sprite = (SpriteFrameState *)&panel->links;
            configure_storage_panel(panel, owner);
            panel->draw_chain = link_storage_display_entries(panel->parts);
            register_node(node, draw_tinted_node_sprites_scratch);
            return node;
        }
        release_null_terminated_entries(panel->resources);
        node->flags |= OBJECT_REMOVE_PENDING;
        node = 0;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    return node;
}

CachedMenuRetryResult open_storage_selection_action(CachedStoragePanel *panel)
{
    CachedItemList *list = panel->list;

    panel->enabled = 0;
    return open_paged_item_menu_with_source(panel->owner, list->position,
            0, -180, -128, panel->extra_entries[panel->selected_extra_index],
            panel->selected_extra_index == 0 && panel->list->extra_entries[1] ? 1 : 2);
}

void confirm_storage_selection(CachedStoragePanel *panel)
{
    if (panel->list->script_pending == 0) {
        if (open_storage_selection_action(panel) == 0) {
            void *previous_update;

            panel->resume = open_storage_selection_action;
            previous_update = NODE_HEADER(panel)->update_callback;
            NODE_HEADER(panel)->update_callback = advance_storage_panel_resume;
            panel->saved_update = previous_update;
        }
    } else {
        DungeonMenuItemSelection *selection = &selected_item_record_alias;
        DungeonItemEntry *selected = selection->item;

        selection->secondary_item = panel->extra_entries[panel->selected_extra_index];
        selected->unk_03 &= ~0x40;
        finish_menu_pair_cleanup(panel->owner);
    }
}

void configure_storage_panel(CachedStoragePanel *panel, ObjectNodeHeader *owner)
{
    initialize_storage_request(panel, owner);
    configure_storage_display_blocks(&panel->links, &panel->display, &panel->position);
    initialize_storage_parts(panel);
}
