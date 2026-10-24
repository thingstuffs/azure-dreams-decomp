#include "shared/object_node.h"
#include "common.h"
#include "frontend/libcard/interfaces.h"

#ifndef NULL
#define NULL 0
#endif

#include "modules/main_server_ship_interfaces.h"
#include "engine/menu.h"
#include "frontend/card.h"
#include "frontend/libcard.h"
#include "main/data.h"

typedef struct CardSaveMenuState {
    s32 backdrop;
    s32 surface;
    s32 heading;
    u8 pad_0C[0x14];
    void *request;
    s32 mode;
    s32 state;
    s32 selection;
} CardSaveMenuState;

/* Allocate an object and initialize its state and dispatch table. */
void *card_boot_create_save_slot_menu(void *init_value, s32 state_value)
{
    ObjectNodeHeader *object;
    CardSaveMenuState *state;

    object = allocate_flagged_object_node(0);
    if (object != NULL) {
        state = (void *)((u8 *)object + 0x20);
        state->mode = state_value;
        card_boot_initialize_save_menu_request(state, init_value);
        card_boot_erase_temporary_file();
        card_boot_refresh_directory_summary();
        state->backdrop = create_or_reset_seven_entry_menu_backdrop(object, 0);
        state->surface = render_rotated_grid_surface(object, state->selection, 3);
        state->heading = create_save_heading(object);
        state->state = 0;
        object->update_callback = D_800267C0;
    }
    return object;
}
