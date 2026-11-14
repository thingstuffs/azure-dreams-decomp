#include "common.h"
#include "frontend/libcard.h"
#include "shared/object_node.h"
#include "engine/node.h"
#include "engine/scene.h"
#include "main/data.h"
#include "sdk/libc.h"
#include "slus.h"
#include "frontend/libcard/message.h"

typedef struct CardCommandPanelState {
    u8 pad_00[0x190];
    u8 sprite[0xC];
    struct S_800491F4 *chain;
    struct S_800491F4 *nodes[18];
} CardCommandPanelState;   /* work in card_boot_create_command_panel */

#include "frontend/libcard/interfaces.h"



/* Creates or resets the object, initializes its state, and runs its update callback. */
void *card_boot_create_command_panel(void *init_value)
{
    ObjectNodeHeader *object;
    CardCommandPanelState *state;
    void *body;

    object = card_command_panel_object;
    state = (CardCommandPanelState *)(card_command_panel_object + 0x20);
    if (find_active_list_node(object) == 0) {
        object = initialize_scene_object_in_buffer(0, object, 0x112);
        register_node(object, card_boot_render_panel_hierarchy);
    } else {
        card_boot_destroy_command_panel(object);
        object->flags &= 0x7FFF;
        bzero(state, 0x428);
    }

    init_card_continue_nodes(state, 0x12);
    object->sprite = state->sprite;
    state->chain = card_boot_link_command_panel_nodes(state->nodes);
    card_boot_init_command_panel(state, init_value);
    object->update_callback = card_boot_animate_command_panel_selection;
    body = state;
    card_boot_animate_command_panel_selection(body);
    return object;
}
