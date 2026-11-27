#include "town.h"
#include "town/menu/motion.h"
#include "engine/item.h"
#include "engine/menu.h"
#include "engine/texture.h"
#include "engine/sprite.h"
#include "engine/util.h"
#include "dungeon/menu_cache.h"
#include "dungeon/menu_cache_paged.h"
#include "engine/node/allocation.h"
#include "dungeon/menu_cache_familiar_prompt.h"
#include "dungeon/menu_cache_fusion.h"
#include "dungeon/menu_cache_linked_actor.h"
#include "dungeon/menu_cache_party_menu.h"
#include "dungeon/menu_cache_selection.h"
#include "shared/item_ids.h"
#include "shared/menu_display.h"
#include "town/shop/item.h"
#include "shared/audio_commands.h"
#include "shared/game_work.h"
#include "slus.h"

/* Call the action for the selected row and return its completion result. */
CachedPagedActionResult dispatch_paged_menu_action(CachedPagedMenu *menu)
{
    return cached_paged_menu_actions[menu->entry_ids[menu->selected_row]](menu);
}

/* Close the paged menu when the selected action completes. */
void run_paged_menu_action(CachedPagedMenu *menu)
{
    if (dispatch_paged_menu_action(menu) != 0) {
        release_paged_menu(menu);
    }
}

/* Restore the base text color and horizontal positions of the visible rows. */
void style_paged_rows(CachedPagedMenu *menu)
{
    s32 index;

    index = 0;
    if (menu->entry_count > 0) {
        do {
            menu->rows->text[index]->data->x = 52;
            menu->rows->text[index]->data->red = 0x68;
            menu->rows->text[index]->data->green = 0x68;
            menu->rows->text[index]->data->blue = 0x60;
            menu->rows->left[index]->data->x = 9;
            menu->rows->middle[index]->data->x = 97;
            menu->rows->right[index]->data->x = 143;
            index++;
        } while (index < menu->entry_count);
    }
}

/* Release row objects and display resources, then flag the menu for removal. */
void release_paged_menu(CachedPagedMenu *menu)
{
    if (menu != 0) {
        remove_item_menu_entry_objects((ItemMenuPart **)menu->rows, menu->entry_count);
        release_null_terminated_entries(menu->resources);
        NODE_HEADER(menu)->flags |= OBJECT_REMOVE_PENDING;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* The creator selects one of three owner workflows before enabling the menu. */
typedef void (*CachedPagedOwnerAction)(ObjectNodeHeader *owner);
typedef ObjectNodeHeader *(*CachedPagedOwnerRelease)(ObjectNodeHeader *owner);

static CachedPagedOwnerAction close_paged_owner[3] = {
    finish_menu_pair_cleanup,
    schedule_familiar_prompt_cleanup,
    finish_menu_pair_cleanup,
};
static CachedPagedOwnerAction resume_paged_owner[3] = {
    resume_menu_pair_panel,
    enable_familiar_prompt_flow_input,
    resume_menu_pair_panel,
};
static CachedPagedOwnerRelease release_paged_owner[3] = {
    release_menu_pair_node,
    release_familiar_prompt_owner,
    release_action_node,
};

void dispatch_paged_owner_resume(CachedPagedMenu *menu)
{
    CachedPagedOwnerAction callbacks[3] = {
        resume_menu_pair_for_familiar,
        enable_familiar_prompt_flow_input,
        resume_menu_pair_for_familiar,
    };

    callbacks[menu->owner_action](menu->owner);
}

void close_paged_menu_owner(CachedPagedMenu *menu)
{
    close_paged_owner[menu->owner_action](menu->owner);
}

void resume_paged_menu_owner(CachedPagedMenu *menu)
{
    resume_paged_owner[menu->owner_action](menu->owner);
}

ObjectNodeHeader *release_paged_menu_owner(CachedPagedMenu *menu)
{
    return release_paged_owner[menu->owner_action](menu->owner);
}

CachedPagedActionResult confirm_paged_owner_close(CachedPagedMenu *menu)
{
    close_paged_menu_owner(menu);
    return (ObjectNodeHeader *)1;
}

enum CachedItemRequest {
    EQUIP_SELECTED_ITEM = 1,
    UNEQUIP_SELECTED_ITEM = 2,
    USE_SELECTED_ITEM = 3,
    HOLD_SELECTED_ITEM = 5,
    CHANGE_FIRST_FAMILIAR_SLOT = 6,
    CHANGE_SECOND_FAMILIAR_SLOT = 7,
    DEPLOY_SELECTED_FAMILIAR = 8,
    DEPLOY_SELECTED_FAMILIAR_ALTERNATE = 9,
    USE_SELECTED_TARGET_ITEM = 16,
    REGISTER_SELECTED_ITEM_MODE_TWO = 17,
    REGISTER_SELECTED_ITEM_MODE_ONE = 18,
    USE_MARKED_SELECTED_ITEM = 20,
    SELECT_TARGET_WITH_FAMILIAR = 21
};

/* Publish the item and player-action code before closing the menu. */
CachedPagedActionResult request_item_equip(CachedPagedMenu *menu)
{
    DungeonMenuItemSelection *selection = &selected_item_record_alias;
    DungeonItemEntry *item = menu->item;
    selection->request = EQUIP_SELECTED_ITEM;
    selection->item = item;
    close_paged_menu_owner(menu);
    return (ObjectNodeHeader *)1;
}

/* Publish the item and player-action code before closing the menu. */
CachedPagedActionResult request_item_unequip(CachedPagedMenu *menu)
{
    DungeonMenuItemSelection *selection = &selected_item_record_alias;
    DungeonItemEntry *item = menu->item;
    selection->request = UNEQUIP_SELECTED_ITEM;
    selection->item = item;
    close_paged_menu_owner(menu);
    return (ObjectNodeHeader *)1;
}

/* Publish the item and player-action code before closing the menu. */
CachedPagedActionResult request_item_use(CachedPagedMenu *menu)
{
    DungeonMenuItemSelection *selection = &selected_item_record_alias;
    DungeonItemEntry *item = menu->item;
    selection->request = USE_SELECTED_ITEM;
    selection->item = item;
    close_paged_menu_owner(menu);
    return (ObjectNodeHeader *)1;
}

/* Publish the item and player-action code before closing the menu. */
CachedPagedActionResult request_item_hold(CachedPagedMenu *menu)
{
    DungeonMenuItemSelection *selection = &selected_item_record_alias;
    DungeonItemEntry *item = menu->item;
    selection->request = HOLD_SELECTED_ITEM;
    selection->item = item;
    close_paged_menu_owner(menu);
    return (ObjectNodeHeader *)1;
}

/* Publish the item and player-action code before closing the menu. */
CachedPagedActionResult request_familiar_deployment(CachedPagedMenu *menu)
{
    DungeonMenuItemSelection *selection = &selected_item_record_alias;
    DungeonItemEntry *item = menu->item;
    selection->request = DEPLOY_SELECTED_FAMILIAR;
    selection->item = item;
    close_paged_menu_owner(menu);
    return (ObjectNodeHeader *)1;
}

/* Publish the item and player-action code before closing the menu. */
CachedPagedActionResult request_familiar_alternate_deployment(CachedPagedMenu *menu)
{
    DungeonMenuItemSelection *selection = &selected_item_record_alias;
    DungeonItemEntry *item = menu->item;
    selection->request = DEPLOY_SELECTED_FAMILIAR_ALTERNATE;
    selection->item = item;
    close_paged_menu_owner(menu);
    return (ObjectNodeHeader *)1;
}

/* Publish the item and player-action code before closing the menu. */
CachedPagedActionResult request_target_item_use(CachedPagedMenu *menu)
{
    DungeonMenuItemSelection *selection = &selected_item_record_alias;
    DungeonItemEntry *item = menu->item;
    selection->request = USE_SELECTED_TARGET_ITEM;
    selection->item = item;
    close_paged_menu_owner(menu);
    return (ObjectNodeHeader *)1;
}

/* Publish the item and player-action code before closing the menu. */
CachedPagedActionResult request_item_registration_mode_two(CachedPagedMenu *menu)
{
    DungeonMenuItemSelection *selection = &selected_item_record_alias;
    DungeonItemEntry *item = menu->item;
    selection->request = REGISTER_SELECTED_ITEM_MODE_TWO;
    selection->item = item;
    close_paged_menu_owner(menu);
    return (ObjectNodeHeader *)1;
}

/* Publish the item and player-action code before closing the menu. */
CachedPagedActionResult request_item_registration_mode_one(CachedPagedMenu *menu)
{
    DungeonMenuItemSelection *selection = &selected_item_record_alias;
    DungeonItemEntry *item = menu->item;
    selection->request = REGISTER_SELECTED_ITEM_MODE_ONE;
    selection->item = item;
    close_paged_menu_owner(menu);
    return (ObjectNodeHeader *)1;
}

/* Publish the item and player-action code before closing the menu. */
CachedPagedActionResult request_familiar_target(CachedPagedMenu *menu)
{
    DungeonMenuItemSelection *selection = &selected_item_record_alias;
    DungeonItemEntry *item = menu->item;
    selection->request = SELECT_TARGET_WITH_FAMILIAR;
    selection->item = item;
    close_paged_menu_owner(menu);
    return (ObjectNodeHeader *)1;
}


CachedPagedActionResult request_familiar_slot_change(CachedPagedMenu *menu)
{
    s32 request = CHANGE_SECOND_FAMILIAR_SLOT;

    selected_item_record_alias.item = menu->item;
    if (menu->familiar_slot == 0) {
        request = CHANGE_FIRST_FAMILIAR_SLOT;
    }
    selected_item_record_alias.request = request;
    close_paged_menu_owner(menu);
    return (ObjectNodeHeader *)1;
}

CachedPagedActionResult request_marked_item_use(CachedPagedMenu *menu)
{
    DungeonItemEntry *item;
    DungeonMenuItemSelection *selection;

    menu->item->unk_03 |= 0x40;
    selection = &selected_item_record_alias;
    item = menu->item;
    selection->request = USE_MARKED_SELECTED_ITEM;
    selection->item = item;
    dispatch_paged_owner_resume(menu);
    return (ObjectNodeHeader *)1;
}

/* Release the current owner once and retry opening the follow-up menu if allocation fails. */
CachedPagedActionResult open_paged_fusion_menu(CachedPagedMenu *menu)
{
    if (menu->owner_released == 0) {
        menu->owner_released = 1;
        menu->owner = release_paged_menu_owner(menu);
    }
    return (ObjectNodeHeader *)(long)(create_cached_fusion_menu(menu->owner, menu->item_index) != 0);
}

/* Release the current owner once and retry opening the follow-up menu if allocation fails. */
CachedPagedActionResult open_paged_party_menu(CachedPagedMenu *menu)
{
    if (menu->owner_released == 0) {
        menu->owner_released = 1;
        menu->owner = release_paged_menu_owner(menu);
    }
    return (ObjectNodeHeader *)(long)(open_party_menu(menu->owner, menu->actor_index) != 0);
}

/* Release the current owner once and retry opening the follow-up menu if allocation fails. */
CachedPagedActionResult open_paged_linked_actor_menu(CachedPagedMenu *menu)
{
    if (menu->owner_released == 0) {
        menu->owner_released = 1;
        menu->owner = release_paged_menu_owner(menu);
    }
    return (ObjectNodeHeader *)(long)(open_linked_actor_menu(menu->owner, menu->actor_index) != 0);
}

/* Release the current owner once and retry opening the follow-up menu if allocation fails. */
CachedPagedActionResult open_paged_familiar_prompt(CachedPagedMenu *menu)
{
    if (menu->owner_released == 0) {
        menu->owner_released = 1;
        menu->owner = release_paged_menu_owner(menu);
    }
    return (ObjectNodeHeader *)(long)(create_cached_familiar_prompt_flow(menu->owner, menu->item_index) != 0);
}



/* The item list uses these callback indices in the same order as the display labels. */
CachedPagedMenuAction cached_paged_menu_actions[19] = {
    confirm_paged_owner_close,
    request_item_use,
    request_item_hold,
    view_paged_item,
    request_familiar_slot_change,
    request_familiar_deployment,
    request_familiar_alternate_deployment,
    open_paged_fusion_menu,
    open_paged_party_menu,
    open_paged_linked_actor_menu,
    request_item_equip,
    request_item_unequip,
    request_target_item_use,
    open_paged_familiar_prompt,
    request_item_registration_mode_two,
    request_item_registration_mode_one,
    request_marked_item_use,
    request_familiar_target,
    request_item_use,
};

/* Poll cancel, confirm and directional repeat before advancing the row motion. */
void poll_paged_menu_input(CachedPagedMenu *menu)
{
    GameWork *input = &g_game_work;

    if (input->buttons != 0) {
        if (input->pressed_buttons & 0x20) {
            SD_Call(AUDIO_CANCEL);
            release_paged_menu(menu);
            resume_paged_menu_owner(menu);
        } else if (input->pressed_buttons & 0x40) {
            SD_Call(AUDIO_MENU_CONFIRM);
            if (!dispatch_paged_menu_action(menu)) {
                NODE_HEADER(menu)->update_callback = run_paged_menu_action;
            }
            release_paged_menu(menu);
        } else if (input->buttons & 0x5000) {
            s32 direction = 0;

            if (input->pressed_buttons & 0x4000) {
                direction = 1;
                menu->repeat_ticks = 0;
                menu->row_transition_duration = 3;
            } else if (input->pressed_buttons & 0x1000) {
                direction = -1;
                menu->repeat_ticks = 0;
                menu->row_transition_duration = 3;
            } else if (menu->repeat_ticks >= 3) {
                menu->repeat_ticks--;
                if (input->buttons & 0x4000) {
                    direction = 1;
                    menu->row_transition_duration = 2;
                } else if (input->buttons & 0x1000) {
                    direction = -1;
                    menu->row_transition_duration = 2;
                }
            } else {
                menu->repeat_ticks++;
            }
            if (direction != 0) {
                SD_Call(AUDIO_CURSOR_MOVE);
                menu->row_transition_progress = 0;
                menu->previous_row = menu->selected_row;
                menu->selected_row = advance_index_with_single_wrap(menu->selected_row,
                                                                   direction, menu->entry_count);
            }
        }
    }
    update_cached_paged_row_motion(menu);
}

void run_paged_menu_input(CachedPagedMenu *menu)
{
    poll_paged_menu_input(menu);
}

void advance_paged_menu_opening(CachedPagedMenu *menu, struct ObjectPosition *position,
                                       ItemMenuDisplayLinks *display)
{
    display->display->x = menu->initial_x + (menu->distance_x * menu->opening_ticks) / 4;
    display->display->y = menu->initial_y + (menu->distance_y * menu->opening_ticks) / 4;
    display->display->depth = menu->initial_depth + (menu->distance_depth * menu->opening_ticks) / 4;
    display->position->position.rotation_y = menu->opening_ticks * 256 - 1024;
    if (++menu->opening_ticks >= 5) {
        menu->motion_callback = run_paged_menu_input;
    }
    poll_paged_menu_input(menu);
}

void start_paged_menu_opening(CachedPagedMenu *menu, struct ObjectPosition *position,
                                     ItemMenuDisplayLinks *display)
{
    menu->opening_ticks++;
    display->position->position.rotation_y = 1024 - menu->opening_ticks * 256;
    menu->motion_callback = advance_paged_menu_opening;
}

void cancel_paged_menu(CachedPagedMenu *menu)
{
    resume_paged_menu_owner(menu);
    release_paged_menu(menu);
}

void update_cached_paged_row_motion(CachedPagedMenu *menu)
{
    s32 cursor_row;
    s32 delta_y;
    s32 index;

    cursor_row = menu->previous_row;
    delta_y = ((menu->selected_row - cursor_row) * (menu->row_transition_progress << 4)) /
              menu->row_transition_duration + 10;
    menu->rows->cursor->data->y = cursor_row * 16 + delta_y;
    index = 0;
    if (index < menu->entry_count) {
        do {
            s32 highlight = menu->row_highlight[index];
            s32 next_highlight;
            /* BYTES: shade slot row_highlight[index] as byte address + row + member offset 0x5C; indexing the member, or adding the offset before the row, grows the function by a word. */
            u8 *highlight_slot = (u8 *)menu + index + 0x5C;
            ItemMenuRowDisplay *text_row;
            s32 display_shade;

            if (index == menu->selected_row) {
                next_highlight = brighten_cached_menu_highlight(highlight, menu->row_transition_duration,
                                                            menu->row_transition_progress);
            } else {
                next_highlight = fade_cached_menu_highlight(highlight);
            }
            *highlight_slot = next_highlight;
            text_row = menu->rows->text[index];
            display_shade = menu->row_highlight[index];
            text_row->data->x = display_shade + 52;
            menu->rows->right[index]->data->x = display_shade + 143;
            menu->rows->left[index]->data->x = display_shade + 9;
            menu->rows->middle[index]->data->x = display_shade + 97;
            menu->rows->text[index]->data->red = menu->row_highlight[index] * 3 + 104;
            menu->rows->text[index]->data->green = menu->row_highlight[index] * 3 + 104;
            menu->rows->text[index]->data->blue = menu->row_highlight[index] * 4 + 96;
            index++;
        } while (index < menu->entry_count);
    }
    if (menu->row_transition_progress < menu->row_transition_duration) {
        menu->row_transition_progress++;
    }
}

void initialize_paged_rows(CachedPagedMenu *menu)
{
    s32 slot = 14;

    if (slot < menu->entry_count + 14) {
        s32 label_y = 10;

        do {
            /* The indexed offset is the first operand of the address addition. */
            ((ItemMenuRowDisplay **)((slot - 14) * sizeof(*menu->rows->text) +
                                     (unsigned long)menu->rows->text))[0]->data->y = label_y;
            /* The indexed offset is the first operand of the address addition. */
            ((ItemMenuRowDisplay **)((slot - 14) * sizeof(*menu->rows->text) +
                                     (unsigned long)menu->rows->text))[0]->handler = menu->panel_packets;
            slot++;
            label_y += 16;
        } while (slot < menu->entry_count + 14);
    }
    menu->rows->cursor->handler = menu_leaf_template_6;
    menu->rows->count_display->handler = get_menu_count_template(menu->entry_count);
    menu->rows->count_display->data->y = menu->entry_count * 8 + 2;
    slot = 0;
    if (slot < menu->entry_count) {
        u8 *left_template = cached_selection_row_left_template;
        u8 *middle_template = cached_selection_row_middle_template;
        s32 marker_y = 10;

        do {
            menu->rows->left[slot]->data->y = marker_y;
            menu->rows->left[slot]->handler = left_template;
            menu->rows->middle[slot]->data->y = marker_y;
            menu->rows->middle[slot]->handler = middle_template;
            slot++;
            marker_y += 16;
        } while (slot < menu->entry_count);
    }
    slot = 20;
    if (slot < menu->entry_count + 20) {
        s32 action_y = 130;

        do {
            const char *text = get_paged_item_action_label(menu->entry_ids[slot - 20]);
            void *label = create_label_glyph_entries((char *)text, 1);

            /* The indexed offset is the first operand of the address addition. */
            ((ItemMenuRowDisplay **)((slot - 20) * sizeof(*menu->rows->right) +
                                     (unsigned long)menu->rows->right))[0]->handler = label;
            /* The indexed offset is the first operand of the address addition. */
            ((ItemMenuRowDisplay **)((slot - 20) * sizeof(*menu->rows->right) +
                                     (unsigned long)menu->rows->right))[0]->data->y = action_y;
            slot++;
            action_y += 16;
        } while (slot < menu->entry_count + 20);
    }
    menu->row_transition_duration = 1;
    menu->row_transition_progress = 1;
    style_paged_rows(menu);
}

void initialize_paged_request(CachedPagedMenu *menu, s32 item_index, s32 selected_row,
                                     ObjectNodeHeader *owner, DungeonItemEntry *item,
                                     s32 owner_action, s32 source_mode)
{
    menu->owner = owner;
    menu->selected_row = selected_row;
    menu->item_index = item_index;
    menu->owner_action = owner_action;
    menu->source_mode = source_mode;
    menu->item = item;
    if (item->kind == ITEM_KIND_FAMILIAR) {
        menu->actor_index = get_menu_actor_index((ActorRecord *)(unsigned long)(u32)resolve_item_record_slot_value(item));
    }
    build_item_action_options(menu);
    initialize_paged_panel_packets(menu->panel_packets);
    menu->motion_callback = start_paged_menu_opening;
    if (menu->entry_count == 0) {
        SD_Call(0x506);
        NODE_HEADER(menu)->update_callback = cancel_paged_menu;
    }
}

void setup_paged_menu(CachedPagedMenu *menu, s32 item_index, s32 selected_row,
                             ObjectNodeHeader *owner, s32 x, s32 y, struct DungeonItemEntry *item,
                             s32 owner_action, s32 source_mode)
{
    initialize_paged_request(menu, item_index, selected_row, owner, item, owner_action, source_mode);
    init_item_menu_list_position((ItemMenuTransition *)menu, &menu->links, menu->position_words, menu->background_words, x, y);
    initialize_paged_rows(menu);
}

s32 prepare_paged_parts(CachedPagedMenu *menu, s32 count)
{
    s32 ready = 0;
    u16 **resources = menu->resources;

    menu->rows = (ItemMenuRows *)rebuild_pointer_pool((s32 *)resources, count, 8);
    if (menu->rows != 0) {
        menu->panel_packets = (void *)(unsigned long)(u32)append_allocated_node_body((s32 *)resources, 8);
        if (menu->panel_packets != 0) {
            menu->part_vectors.unk0 = display_vector_defaults.unk0;
            menu->part_vectors.unk4 = display_vector_defaults.unk4;
            menu->part_vectors.unk8 = display_vector_defaults.unk8;
            set_menu_part_vectors((ItemMenuPart **)menu->rows, &menu->part_vectors, 26);
            ready = 1;
        }
    }
    return ready;
}

ObjectNodeHeader *open_paged_item_menu(ObjectNodeHeader *owner, s32 item_index,
                                             s32 selected_row, s32 x, s32 y,
                                             struct DungeonItemEntry *item)
{
    return create_paged_menu_node(owner, item_index, selected_row, x, y, item, 0, 0);
}

ObjectNodeHeader *open_paged_action_item_menu(ObjectNodeHeader *owner, s32 item_index,
                                                    s32 selected_row, s32 x, s32 y,
                                                    struct DungeonItemEntry *item, s32 source_mode)
{
    return create_paged_menu_node(owner, item_index, selected_row, x, y, item, 2, source_mode);
}

ObjectNodeHeader *open_paged_item_menu_with_source(ObjectNodeHeader *owner, s32 item_index,
                                                         s32 selected_row, s32 x, s32 y,
                                                         struct DungeonItemEntry *item, s32 source_mode)
{
    return create_paged_menu_node(owner, item_index, selected_row, x, y, item, 0, source_mode);
}

ObjectNodeHeader *create_familiar_assignment_menu(ObjectNodeHeader *owner, s32 item_index,
                                                         s32 selected_row, s32 x, s32 y,
                                                         struct DungeonItemEntry *item, s32 slot)
{
    ObjectNodeHeader *node = create_paged_menu_node(owner, item_index, selected_row, x, y, item, 1, 0);

    if (node != 0) {
        CachedPagedMenu *menu = NODE_BODY(node);

        menu->familiar_slot = slot;
    }
    return node;
}

/* The reverse draw order ends when the chain builder sees the count as an index. */
u8 cached_paged_draw_order[28] = {
    0, 1, 14, 15, 16, 17, 18, 19, 2, 3, 4, 5, 6, 7,
    8, 9, 10, 11, 12, 13, 20, 21, 22, 23, 24, 25, 26, 0
};
RECT cached_paged_panel_rectangle = {-44, -8, 88, 16};

ObjectNodeHeader *create_paged_menu_node(ObjectNodeHeader *owner, s32 item_index,
                                               s32 selected_row, s32 x, s32 y, DungeonItemEntry *item,
                                               s32 owner_action, s32 source_mode)
{
    ObjectNodeHeader *node = allocate_list_node(0, &owner->next);

    if (node != 0) {
        CachedPagedMenu *menu = NODE_BODY(node);

        if (prepare_paged_parts(menu, 26) != 0) {
            node->sprite = (SpriteFrameState *)&menu->links;
            menu->draw_chain = link_item_menu_display_entries(menu->rows);
            node->update_callback = invoke_menu_motion_handler;
            setup_paged_menu(menu, item_index, selected_row, owner, x, y, item, owner_action, source_mode);
            register_node(node, draw_tinted_node_sprites_scratch);
            return node;
        }
        release_null_terminated_entries(menu->resources);
        node->flags |= OBJECT_REMOVE_PENDING;
        node = 0;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    return node;
}

ObjectNodeHeader *open_paged_item_view(CachedPagedMenu *menu)
{
    ObjectNodeHeader *owner = release_paged_menu_owner(menu);

    if (menu->owner_action == 0) {
        DungeonItemEntry *item = menu->item;

        if (item->kind == ITEM_KIND_FAMILIAR) {
            return open_view_default(owner, menu->item_index, item);
        }
        return open_view_primary(owner, menu->item_index, item);
    }
    {
        ObjectNodeHeader *view;
        if (menu->owner_action == 2) {
            view = open_view_secondary(owner, menu->item_index, menu->item);
        } else {
            view = open_view_alternate(owner, menu->item_index, menu->item);
        }
        return view;
    }
}

CachedPagedActionResult view_paged_item(CachedPagedMenu *menu)
{
    if (menu->item->kind == ITEM_KIND_FAMILIAR) {
        resolve_item_record_slot_value(menu->item);
    }
    return open_paged_item_view(menu);
}

void initialize_paged_panel_packets(void *packets)
{
    init_packet_pair_and_gradient(packets, &cached_paged_panel_rectangle);
}
