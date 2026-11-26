#include "engine/cd.h"
#include "engine/node/allocation.h"
#include "dungeon/actor/state.h"
#include "dungeon/menu_cache_fusion.h"
#include "dungeon/system/submit_control_and_reset_status.h"
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

/* Prepare the preview and open its confirmation panel when both familiars can fuse. */
ObjectNodeHeader *create_cached_fusion_menu(ObjectNodeHeader *owner, s32 index)
{
    ObjectNodeHeader *node = allocate_list_node(0, &owner->next);
    CachedFusionMenu *menu;
    u16 flags;
    s32 pending;

    do {
        if (node == 0) {
            break;
        }
        menu = NODE_BODY(node);
        clear_win_sw0_resident_bit();
        menu->owner = owner;
        clear_dungeon_menu_flag();
        if (get_menu_actor_mask() == 3) {
            menu->actor_choice = create_fusion_actor_selector(node, index, -24);
            if (menu->actor_choice != 0) {
                submit_control_command_six();
                drain_cd_command_queue();
                if (merge_creature_abilities_and_state(primary_actor_record->unk_AC.address,
                                                       primary_actor_record->unk_B0.address,
                                                       menu->actor_preview) == 0) {
                    node->update_callback = check_fusion_close_signal;
                    show_fusion_invalid_pair();
                    break;
                }
                /* BYTES: Passing the merge result keeps it live across the panel call and changes the saved node temporaries. */
                menu->confirmation_panel = allocate_menu_entry_object((ActorRecord *)menu->actor_preview,
                                                                       3, 82, -116, 512);
                if (menu->confirmation_panel != 0) {
                    node->update_callback = poll_fusion_confirmation;
                    menu->result_node = create_fusion_result();
                    if (menu->result_node != 0) {
                        show_fusion_confirmation();
                        break;
                    }
                }
            }
        } else {
            node->update_callback = check_fusion_close_signal;
            show_fusion_need_two();
            break;
        }
        release_fusion_children(menu);
        flags = node->flags;
        pending = object_flag_block.flags;
        node->flags = flags | OBJECT_REMOVE_PENDING;
        object_flag_block.flags = pending | OBJECT_REMOVE_PENDING;
        return 0;
    } while (0);
    return node;
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
