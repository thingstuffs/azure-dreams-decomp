#include "dungeon/menu_cache_actor_choice.h"
#include "dungeon/menu_cache_party_menu.h"
#include "dungeon/menu_cache_close.h"
#include "dungeon/menu/state.h"
#include "dungeon/system/submit_control_and_reset_status.h"
#include "engine/cd.h"
#include "engine/node/allocation.h"
#include "dungeon/menu_cache_selection.h"
#include "script_symbols.h"
#include "engine/object.h"
#include "slus.h"


enum {
    CACHED_PARTY_PREVIEW_CLOSED,
    CACHED_PARTY_PREVIEW_BEHAVIOR,
    CACHED_PARTY_PREVIEW_DIRECTION
};

void show_party_menu_notice(void)
{
    set_message_mode(1);
    call_message_mode_handler();
    build_object_registration_script(cached_no_linked_actor_notice);
}

ObjectNodeHeader *create_party_menu(ObjectNodeHeader *owner, s32 actor_index, s32 preserve_owner)
{
    ObjectNodeHeader *node = allocate_list_node(0, &owner->next);

    if (node != 0) {
        CachedPartyMenu *menu;

        clear_win_sw0_resident_bit();
        set_message_mode(2);
        menu = NODE_BODY(node);
        menu->owner = owner;
        clear_dungeon_menu_flag();
        if (get_menu_actor_mask() != 0) {
            menu->preserve_owner = preserve_owner;
            menu->actor_choice = create_party_actor_choice(node, actor_index);
            menu->command_panel = create_party_command_panel(node);
            menu->command_state = create_party_command_state(node);
            if (menu->actor_choice != 0 && menu->command_panel != 0 && menu->command_state != 0) {
                return node;
            }
            release_party_menu_children(menu);
            node->flags |= OBJECT_REMOVE_PENDING;
            node = 0;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        } else {
            node->update_callback = check_party_menu_close_signal;
            show_party_menu_notice();
        }
    }
    return node;
}

ObjectNodeHeader *open_party_menu(ObjectNodeHeader *owner, s32 actor_index)
{
    return create_party_menu(owner, actor_index, 0);
}

ObjectNodeHeader *open_party_submenu(ObjectNodeHeader *owner, s32 actor_index)
{
    return create_party_menu(owner, actor_index, 1);
}

void release_party_menu_children(CachedPartyMenu *menu)
{
    set_dungeon_menu_flag_if_idle();
    release_party_actor_choice(menu->actor_choice);
    release_selection_panel(menu->command_panel);
    release_party_command_state(menu->command_state);
    enqueue_script_message_command();
}

void start_party_menu_close(CachedPartyMenu *menu)
{
    release_party_menu_children(menu);
    if (menu->preserve_owner == 0) {
        if (ensure_party_menu_close(menu) == 0) {
            NODE_HEADER(menu)->update_callback = ensure_party_menu_close;
        }
    } else {
        NODE_HEADER(menu)->flags |= OBJECT_REMOVE_PENDING;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

void finish_party_menu_cleanup(CachedPartyMenu *menu)
{
    s32 flags;
    s32 preserve_owner;

    release_party_menu_children(menu);
    NODE_HEADER(menu)->flags |= OBJECT_REMOVE_PENDING;
    flags = object_flag_block.flags;
    preserve_owner = menu->preserve_owner;
    object_flag_block.flags = flags | OBJECT_REMOVE_PENDING;
    if (preserve_owner == 0) {
        destroy_selection_menu_and_release_owner(menu->owner);
    }
}

ObjectNodeHeader *create_party_command_state(ObjectNodeHeader *owner)
{
    ObjectNodeHeader *node = allocate_flagged_object_node(0);

    if (node != 0) {
        CachedPartyCommandState *state = NODE_BODY(node);

        state->owner = owner;
        node->update_callback = idle_party_command_state;
    }
    return node;
}

void complete_party_command_state_release(CachedPartyCommandState *state)
{
    mark_cached_secondary_node_for_removal(state);
}

void release_party_command_state(ObjectNodeHeader *node)
{
    if (node != 0) {
        node->update_callback = complete_party_command_state_release;
    }
}

void set_party_command_marker(ObjectNodeHeader *node)
{
    if (node != 0) {
        CachedPartyCommandState *state = NODE_BODY(node);

        state->command_marker = 1;
    }
}

void resume_party_menu(CachedPartyMenu *menu)
{
    enable_selection_panel(menu->command_panel);
    enable_party_choice_input(menu->actor_choice);
    NODE_HEADER(menu)->update_callback = 0;
    menu->preview_mode = CACHED_PARTY_PREVIEW_CLOSED;
}

void finish_party_preview(CachedPartyMenu *menu)
{
    CachedSelectionPanelNode *panel;

    resume_party_menu(menu);
    start_party_choice_focus(menu->actor_choice, 1);
    panel = menu->command_panel;
    schedule_selection_panel_open(panel != 0 ? &panel->header : 0);
}

void wait_for_party_preview_close(CachedPartyMenu *menu)
{
    if (menu->preview_controller->flags & OBJECT_REMOVE_PENDING) {
        menu->preview_controller = 0;
        NODE_HEADER(menu)->update_callback = finish_party_preview;
    }
}

void open_party_preview(CachedPartyMenu *menu)
{
    menu->preview_controller = create_selection_menu_controller(get_party_choice_selection(menu->actor_choice));
    if (menu->preview_controller != 0) {
        wait_for_party_preview_close(menu);
        NODE_HEADER(menu)->update_callback = wait_for_party_preview_close;
    }
}

void prepare_party_preview(CachedPartyMenu *menu)
{
    submit_control_and_reset_status();
    drain_cd_command_queue();
    start_party_choice_focus(menu->actor_choice, 0);
    set_party_command_marker(menu->command_state);
    menu->preview_controller = create_selection_menu_controller(get_party_choice_selection(menu->actor_choice));
    if (menu->preview_controller == 0) {
        NODE_HEADER(menu)->update_callback = open_party_preview;
    } else {
        wait_for_party_preview_close(menu);
        NODE_HEADER(menu)->update_callback = wait_for_party_preview_close;
    }
}

void schedule_menu_preview(ObjectNodeHeader *node)
{
    if (node != 0) {
        CachedPartyMenu *menu = NODE_BODY(node);

        disable_party_choice_input(menu->actor_choice);
        node->update_callback = prepare_party_preview;
        menu->preview_mode = CACHED_PARTY_PREVIEW_DIRECTION;
    }
}

void update_party_preview_target(ObjectNodeHeader *node, s32 actor_index)
{
    CachedPartyMenu *menu = NODE_BODY(node);
    ObjectNodeHeader *preview = menu->preview_controller;

    if (preview != 0 && !(preview->flags & OBJECT_REMOVE_PENDING)) {
        switch_selected_preview(preview, (s16)actor_index);
    }
}

void open_party_behavior_panel(CachedPartyMenu *menu)
{
    ActorRecord *actor = get_party_choice_actor(menu->actor_choice);

    menu->behavior_panel = create_familiar_behavior_panel(NODE_HEADER(menu), actor);
    if (menu->behavior_panel != 0) {
        disable_party_choice_input(menu->actor_choice);
        menu->preview_mode = CACHED_PARTY_PREVIEW_BEHAVIOR;
        NODE_HEADER(menu)->update_callback = 0;
    }
}

void schedule_party_menu_resume(ObjectNodeHeader *node)
{
    if (node != 0) {
        node->update_callback = resume_party_menu;
    }
}

ObjectNodeHeader *refresh_party_choice_preview(ObjectNodeHeader *node)
{
    CachedPartyMenu *menu = NODE_BODY(node);

    if (menu->preview_mode == CACHED_PARTY_PREVIEW_BEHAVIOR) {
        ActorRecord *actor;

        queue_menu_message(menu->behavior_panel);
        actor = get_party_choice_actor(menu->actor_choice);
        node = create_familiar_behavior_panel(node, actor);
        menu->behavior_panel = node;
    }
    return node;
}

s32 get_party_preview_mode(ObjectNodeHeader *node)
{
    CachedPartyMenu *menu = NODE_BODY(node);

    return menu->preview_mode;
}

void schedule_party_menu_close(ObjectNodeHeader *node)
{
    if (node != 0) {
        node->update_callback = start_party_menu_close;
    }
}

void schedule_party_menu_cleanup(ObjectNodeHeader *node)
{
    if (node != 0) {
        node->update_callback = finish_party_menu_cleanup;
    }
}

void check_party_menu_close_signal(void *body)
{
    if (test_resident_bitmap_bit(sn_win_sw0) != 0) {
        clear_resident_bitmap_bit(sn_win_sw0);
        schedule_party_menu_close(NODE_HEADER(body));
    } else {
        poll_menu_owner_cancel(body);
    }
}
