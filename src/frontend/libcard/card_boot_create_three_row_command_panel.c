#include "common.h"
#include "frontend/libcard.h"
#include "shared/object_node.h"
#include "engine/node.h"
#include "engine/scene.h"
#include "main/data.h"
#include "sdk/libc.h"
#include "slus.h"

typedef struct CardCommandPanelState {
    u8 pad_00[0x190];
    u8 sprite[0xC];
    struct S_800491F4 *chain;
    struct S_800491F4 *nodes[18];
} CardCommandPanelState;   /* work in card_boot_create_three_row_command_panel */

extern void func_800237EC(void *state, s32 value);
#include "frontend/libcard/interfaces.h"

extern u8 menu_backdrop_tag[];

/* Creates or resets the object, initializes its state, and runs its update callback. */
void *card_boot_create_three_row_command_panel(void *init_value)
{
    ObjectNodeHeader *object;
    CardCommandPanelState *state;
    void *body;

    object = card_command_panel_object;
    state = (CardCommandPanelState *)(card_command_panel_object + 0x20);
    if (find_active_list_node(object) == 0) {
        object = initialize_scene_object_in_buffer(0, object, 0x112);
        register_node(object, menu_backdrop_tag);
    } else {
        process_nonzero(object);
        object->flags &= 0x7FFF;
        bzero(state, 0x428);
    }

    func_800237EC(state, 0x12);
    object->sprite = state->sprite;
    state->chain = card_boot_link_three_row_panel_entries(state->nodes);
    card_boot_initialize_three_row_command_panel(state, init_value);
    object->update_callback = card_boot_animate_three_row_selection;
    body = state;
    card_boot_animate_three_row_selection(body);
    return object;
}
