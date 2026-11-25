#include "dungeon/actor/ability_eligibility.h"
#include "dungeon/item/actor_target.h"
#include "dungeon/menu_cache_close.h"
#include "dungeon/menu_cache_paged.h"
#include "dungeon/menu_cache_selection.h"
#include "dungeon/player/held_item_kind_data.h"
#include "engine/item.h"
#include "engine/node/allocation.h"
#include "engine/runtime.h"
#include "shared/item_ids.h"
#include "slus.h"

/* The elevator category uses the short item text records. */
typedef struct CachedElevatorDescription {
    u16 flags;
    s16 display_index;
    const char *name;
    char *script;
} CachedElevatorDescription;

/* Show the notice for an item action with no matching target. */
void show_cached_action_unavailable(void)
{
    build_object_registration_script(item_action_nothing_found_notice);
}

void poll_item_action_confirmation(CachedItemActionMenu *menu)
{
    s32 result = poll_window_switch_flags();

    if (result != 0) {
        if (result == 1) {
            finish_action_cleanup(NODE_HEADER(menu));
            enqueue_script_message_command();
            selected_item_record_alias.item = 0;
            selected_item_record_alias.request = ITEM_KIND_FAMILIAR;
        } else {
            schedule_action_menu_close(NODE_HEADER(menu));
            enqueue_script_message_command();
        }
    } else {
        poll_cached_action_owner_cancel(menu);
    }
}

void initialize_item_action(CachedItemActionMenu *menu, ObjectNodeHeader *owner)
{
    DungeonItemEntry *selected = get_selected_item_data();

    menu->owner = owner;
    if (held_item_record.kind != 0) {
        menu->held_item = &held_item_record;
    }
    if (selected->kind != 0) {
        menu->selected_item = selected;
    }
    if (menu->held_item != 0) {
        menu->selected_slot = 0;
    } else {
        menu->selected_slot = 1;
    }
}

ObjectNodeHeader *create_item_action_dialog(ObjectNodeHeader *owner, s32 unused_item_index)
{
    ObjectNodeHeader *node = allocate_list_node(0, &owner->next);

    if (node != 0) {
        CachedItemActionMenu *menu = NODE_BODY(node);
        void *callback;

        clear_win_sw0_resident_bit();
        initialize_item_action(menu, owner);
        if (menu->selected_item != 0 && menu->selected_slot == 1 &&
            menu->selected_item->kind == ITEM_KIND_ELEVATOR) {
            const CachedElevatorDescription *records;

            set_message_mode(0);
            call_message_mode_handler();
            records = itemCategoryTable[ITEM_KIND_ELEVATOR].records;
            dispatch_control_string_with_suffix(records[menu->selected_item->unk_00].script);
            callback = poll_item_action_confirmation;
        } else {
            set_message_mode(1);
            call_message_mode_handler();
            show_cached_action_unavailable();
            callback = check_action_close_signal;
        }
        node->update_callback = callback;
    }
    return node;
}

void poll_item_action_notice(CachedItemActionMenu *menu)
{
    s32 result = poll_window_switch_flags();

    if (result != 0) {
        if (result == 1) {
            enqueue_script_message_command();
            selected_item_record_alias.item = 0;
            selected_item_record_alias.request = ITEM_KIND_FAMILIAR;
        } else {
            enqueue_script_message_command();
        }
        NODE_HEADER(menu)->flags |= OBJECT_REMOVE_PENDING;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    } else {
        poll_action_notice_cancel(menu);
    }
}

ObjectNodeHeader *create_cached_elevator_notice(void)
{
    DungeonItemEntry *item = get_selected_item_data();
    ObjectNodeHeader *node = allocate_flagged_object_node(0);

    if (node != 0) {
        const CachedElevatorDescription *records;

        clear_win_sw0_resident_bit();
        set_message_mode(0);
        call_message_mode_handler();
        records = itemCategoryTable[ITEM_KIND_ELEVATOR].records;
        dispatch_control_string_with_suffix(records[item->unk_00].script);
        node->update_callback = poll_item_action_notice;
    }
    return node;
}
