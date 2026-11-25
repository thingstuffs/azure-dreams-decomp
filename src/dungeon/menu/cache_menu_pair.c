#include "dungeon/actor/ability_eligibility.h"
#include "dungeon/item/actor_target.h"
#include "dungeon/menu_cache_close.h"
#include "dungeon/menu_cache_selection.h"
#include "dungeon/player/held_item_kind_data.h"
#include "engine/node/allocation.h"
#include "shared/game_state.h"
#include "shared/item_ids.h"
#include "slus.h"

typedef ObjectNodeHeader *(*CachedMenuPanelRelease)(ObjectNodeHeader *node);
static const CachedMenuPanelRelease release_panel[2] = {
    release_item_display,
    release_storage_display,
};

typedef void (*CachedMenuPanelResume)(ObjectNodeHeader *node);
static const CachedMenuPanelResume resume_panel[2] = {
    resume_item_display,
    resume_storage_display,
};

/* Release the active item or storage panel through its matching callback. */
void release_menu_pair_active_panel(ObjectNodeHeader *node)
{
    CachedItemList *menu = NODE_BODY(node);
    ObjectNodeHeader *panel = menu->panels[menu->active_panel];

    if (panel != 0) {
        menu->panels[menu->active_panel] = release_panel[menu->active_panel](panel);
    }
}

/* Release the active panel before queuing the close message. */
void release_menu_pair_and_queue_message(void *body)
{
    release_menu_pair_active_panel(NODE_HEADER(body));
    enqueue_script_message_command();
}

ObjectNodeHeader *release_menu_pair_node(ObjectNodeHeader *node)
{
    CachedItemList *list = NODE_BODY(node);
    ObjectNodeHeader *owner;
    s32 global_flags;
    u16 flags;

    release_menu_pair_and_queue_message(list);
    flags = node->flags;
    global_flags = object_flag_block.flags;
    node->flags = flags | OBJECT_REMOVE_PENDING;
    owner = list->owner;
    object_flag_block.flags = global_flags | OBJECT_REMOVE_PENDING;
    return owner;
}

void start_menu_pair_close(CachedItemList *list)
{
    release_menu_pair_and_queue_message(list);
    if (ensure_menu_pair_close(list) == 0) {
        NODE_HEADER(list)->update_callback = ensure_menu_pair_close;
    }
}

void finish_menu_pair_cleanup(ObjectNodeHeader *node)
{
    CachedItemList *list = NODE_BODY(node);

    release_menu_pair_node(node);
    destroy_selection_menu_and_release_owner(list->owner);
}

/* Release the storage parts and clear the selected panel slot. */
ObjectNodeHeader *release_storage_display(ObjectNodeHeader *node)
{
    CachedStoragePanel *panel = NODE_BODY(node);

    if (node != 0) {
        release_null_terminated_entries(panel->resources);
        release_storage_components(panel);
        node->flags |= OBJECT_REMOVE_PENDING;
        node = 0;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    return node;
}

/* Refresh the active panel through its item or storage handler. */
void resume_menu_pair_panel(ObjectNodeHeader *node)
{
    CachedItemList *list = NODE_BODY(node);
    s32 index = list->active_panel;
    ObjectNodeHeader *panel = list->panels[index];

    if (panel != 0) {
        resume_panel[index](panel);
    }
}

void resume_menu_pair_for_familiar(ObjectNodeHeader *node)
{
    CachedItemList *list = NODE_BODY(node);

    list->script_pending = 1;
    resume_menu_pair_panel(node);
    submit_script_with_registered_context(cached_familiar_action_context);
}

s32 is_familiar_item(const DungeonItemEntry *item)
{
    return item->kind == ITEM_KIND_FAMILIAR;
}

void refresh_storage_panel(CachedStoragePanel *panel)
{
    refresh_storage_header(panel);
    populate_storage_panel_rows(panel);
}

void resume_storage_display(ObjectNodeHeader *node)
{
    CachedStoragePanel *panel = NODE_BODY(node);

    panel->enabled = 1;
    refresh_storage_panel(panel);
    populate_storage_panel_rows(panel);
}

/* Select the item or storage panel from the current inventory index. */
s32 create_cached_pair_panel(CachedItemList *list)
{
    s32 ready = 1;
    s32 extra_count;
    ObjectNodeHeader *window;

    extra_count = list->extra_entries[0] != 0;
    if (list->extra_entries[1] != 0) {
        extra_count++;
    }
    if ((list->position < list->count - extra_count) || list->count == 0) {
        CachedItemDisplayNode *panel;

        list->active_panel = 0;
        panel = create_item_display(NODE_HEADER(list));
        window = panel ? &panel->header : 0;
        list->panels[0] = window;
    } else {
        list->active_panel = ready;
        window = create_storage_display_node(NODE_HEADER(list));
        list->panels[1] = window;
    }
    if (window == 0) {
        ready = 0;
    }
    return ready;
}

/* Select the item or storage panel from the current inventory index. */
s32 reopen_cached_pair_panel(CachedItemList *list)
{
    s32 ready = 1;
    s32 extra_count;
    ObjectNodeHeader *window;

    extra_count = list->extra_entries[0] != 0;
    if (list->extra_entries[1] != 0) {
        extra_count++;
    }
    if ((list->position + extra_count < list->count) || list->count == 0) {
        CachedItemDisplayNode *panel;

        list->active_panel = 0;
        panel = create_open_item_display(NODE_HEADER(list));
        window = panel ? &panel->header : 0;
        list->panels[0] = window;
    } else {
        list->active_panel = ready;
        window = create_storage_display_node(NODE_HEADER(list));
        list->panels[1] = window;
    }
    if (window == 0) {
        ready = 0;
    }
    return ready;
}


/* Select the initial page and include the two optional item entries. */
void initialize_menu_pair(CachedItemList *list, s32 position,
                                       ObjectNodeHeader *owner, s32 mode)
{
    DungeonItemEntry *selected;

    selected = get_selected_item_data();
    list->owner = owner;
    list->entries = GAME_STATE->item_list;
    list->count = count_pointer_list_entries((void **)GAME_STATE->item_list);
    list->position = position;
    list->mode = mode;
    if (list->count != 0) {
        list->last_page = (list->count - 1) / 10;
    }
    {
        s32 initial_position = list->position;
        s32 count = list->count;
        s32 page;
        if (initial_position < count) {
            page = initial_position / 10;
        } else {
            page = (count - 1) / 10;
        }
        list->page = page;
    }
    if (held_item_record.kind != ITEM_KIND_NONE) {
        list->extra_entries[1] = &held_item_record;
    }
    if (selected->kind != ITEM_KIND_NONE && selected->kind != ITEM_KIND_ELEVATOR) {
        list->extra_entries[0] = selected;
    }
    /* BUG: With both extra entries empty, retail reads the kind through the
     * null second pointer. Address 1 holds zero on the console. */
    if (list->extra_entries[0] != 0 || list->extra_entries[1]->kind != ITEM_KIND_NONE) {
        list->last_page++;
        if (list->extra_entries[0] != 0) {
            list->count++;
            list->excluded_count++;
        }
        if (list->extra_entries[1] != 0) {
            list->count++;
            list->excluded_count++;
        }
    }
}

/* Create the menu node, release its child if initialization fails and retire the node. */
ObjectNodeHeader *allocate_menu_pair(ObjectNodeHeader *owner, s32 position, s32 mode)
{
    ObjectNodeHeader *node = allocate_list_node(0, &owner->next);

    if (node != 0) {
        CachedItemList *list = NODE_BODY(node);

        set_message_mode(1);
        call_message_mode_handler();
        initialize_menu_pair(list, position, owner, mode);
        if (create_cached_pair_panel(list) != 0) {
            return node;
        }
        release_menu_pair_and_queue_message(list);
        NODE_HEADER(list)->flags |= OBJECT_REMOVE_PENDING;
        node = 0;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    return node;
}

s32 reopen_menu_pair(ObjectNodeHeader *node)
{
    CachedItemList *list = NODE_BODY(node);

    return reopen_cached_pair_panel(list);
}

ObjectNodeHeader *open_cached_inventory_or_dialog(ObjectNodeHeader *owner, s32 index)
{
    s32 dialog_index = index;
    DungeonItemEntry *selected = get_selected_item_data();

    if (held_item_record.kind == ITEM_KIND_NONE) {
        if (selected->kind == ITEM_KIND_NONE || selected->kind == ITEM_KIND_ELEVATOR) {
            return create_item_action_dialog(owner, dialog_index);
        }
    }
    return allocate_menu_pair(owner, count_pointer_list_entries((void **)GAME_STATE->item_list), 1);
}

void schedule_menu_pair_close(ObjectNodeHeader *node)
{
    node->update_callback = start_menu_pair_close;
}
