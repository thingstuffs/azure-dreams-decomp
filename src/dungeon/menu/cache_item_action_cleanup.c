#include "dungeon/menu_cache_close.h"
#include "dungeon/menu_cache_selection.h"
#include "shared/audio_commands.h"
#include "shared/game_work.h"
#include "slus.h"

void queue_action_cleanup_message(CachedItemActionMenu *menu)
{
    enqueue_script_message_command();
}

ObjectNodeHeader *release_action_node(ObjectNodeHeader *node)
{
    CachedItemActionMenu *menu = NODE_BODY(node);
    ObjectNodeHeader *owner;
    s32 global_flags;
    u16 flags;

    queue_action_cleanup_message(menu);
    flags = node->flags;
    global_flags = object_flag_block.flags;
    node->flags = flags | OBJECT_REMOVE_PENDING;
    owner = menu->owner;
    object_flag_block.flags = global_flags | OBJECT_REMOVE_PENDING;
    return owner;
}

/* When the owner's selection menu is ready, mark this menu for removal. */
void *ensure_action_close(CachedItemActionMenu *menu)
{
    void *selection = ensure_selection_menu_and_register_draw(menu->owner);

    if (selection != 0) {
        NODE_HEADER(menu)->flags |= OBJECT_REMOVE_PENDING;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    return selection;
}

void start_action_close(CachedItemActionMenu *menu)
{
    queue_action_cleanup_message(menu);
    if (ensure_action_close(menu) == 0) {
        NODE_HEADER(menu)->update_callback = ensure_action_close;
    }
}


void finish_action_cleanup(ObjectNodeHeader *node)
{
    CachedItemActionMenu *menu = NODE_BODY(node);

    release_action_node(node);
    destroy_selection_menu_and_release_owner(menu->owner);
}

void poll_action_notice_cancel(void *body)
{
    if (g_game_work.buttons != 0 && (g_game_work.pressed_buttons & 0x20) != 0) {
        SD_Call(AUDIO_CANCEL);
        enqueue_script_message_command();
        NODE_HEADER(body)->flags |= OBJECT_REMOVE_PENDING;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

void schedule_action_menu_close(ObjectNodeHeader *node)
{
    node->update_callback = start_action_close;
}
