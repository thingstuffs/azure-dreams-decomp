#include "common.h"
#include "shared/object_node.h"
#include "m2c_compat.h"

#include "modules/main_server_ship_interfaces.h"
#include "engine/menu.h"
#include "frontend/libcard.h"
#include "main/data.h"
#include "engine/scene.h"

struct S_8003FE78;    /* extern */

/* Creates an object and initializes its state. */
void *card_boot_create_slot_selection_menu(void *init_value, s32 unused) {
    CardSlotMenuState *state;
    ObjectNodeHeader *object;

    object = initialize_scene_object_in_buffer(0, (struct S_8003FE78 *)(&D_8002B7E0), 0x1C);
    state = (CardSlotMenuState *)(object + 1);
    card_boot_initialize_slot_menu_request(state, init_value);
    card_boot_erase_temporary_file();
    card_boot_refresh_directory_summary();
    state->unk_48 = 1;
    state->backdrop = create_or_reset_seven_entry_menu_backdrop(object, ((void *)object) + 0x68);
    state->command_panel = card_boot_create_three_row_command_panel(object);
    state->slot_details = render_rotated_grid_surface(object, state->unk_28, 0);
    state->mode = 0;
    object->update_callback = &update_inventory_menu;
    return object;
}
