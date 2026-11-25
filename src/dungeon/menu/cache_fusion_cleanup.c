#include "engine/text.h"
#include "dungeon/menu_cache_actor_choice.h"
#include "dungeon/menu_cache_close.h"
#include "dungeon/menu_cache_selection.h"
#include "dungeon/menu/state.h"
#include "slus.h"

/* Release the selection, panel and result, then queue the menu message. */
void release_fusion_children(CachedFusionMenu *menu)
{
    release_actor_choice(menu->actor_choice);
    release_menu_entry_object(menu->confirmation_panel);
    set_object_and_global_removal_flag(menu->result_node);
    set_dungeon_menu_flag_if_idle();
    enqueue_script_message_command();
}

/* When the owner's selection menu is ready, mark this menu for removal. */
void *ensure_fusion_close(CachedFusionMenu *menu)
{
    void *selection = ensure_selection_menu_and_register_draw(menu->owner);

    if (selection != 0) {
        NODE_HEADER(menu)->flags |= OBJECT_REMOVE_PENDING;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    return selection;
}

void start_fusion_close(CachedFusionMenu *menu)
{
    release_fusion_children(menu);
    if (ensure_fusion_close(menu) == 0) {
        NODE_HEADER(menu)->update_callback = ensure_fusion_close;
    }
}


/* Finish the fusion and release the original selection owner. */
void finish_fusion_cleanup(CachedFusionMenu *menu)
{
    ObjectNodeHeader *owner;
    s32 flags;

    release_fusion_children(menu);
    NODE_HEADER(menu)->flags |= OBJECT_REMOVE_PENDING;
    flags = object_flag_block.flags;
    owner = menu->owner;
    object_flag_block.flags = flags | OBJECT_REMOVE_PENDING;
    destroy_selection_menu_and_release_owner(owner);
}

void schedule_fusion_close(ObjectNodeHeader *node)
{
    if (node != 0) {
        node->update_callback = start_fusion_close;
    }
}

void schedule_fusion_cleanup(ObjectNodeHeader *node)
{
    if (node != 0) {
        node->update_callback = finish_fusion_cleanup;
    }
}
