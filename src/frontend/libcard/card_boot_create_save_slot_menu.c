#include "shared/object_node.h"
#include "common.h"
#include "frontend/libcard/interfaces.h"

#ifndef NULL
#define NULL 0
#endif

extern s32 card_boot_initialize_save_menu_request(void *a0, s32 a1);
#include "modules/main_server_ship_interfaces.h"
extern s32 create_or_reset_seven_entry_menu_backdrop(void *a0, s32 a1);
extern s32 render_rotated_grid_surface(void *a0, s32 a1, s32 a2);
extern s32 create_save_heading(void *a0);
extern s32 D_800267C0[];

/* Allocate an object and initialize its state and dispatch table. */
void *card_boot_create_save_slot_menu(s32 init_value, s32 state_value)
{
    void *object;
    void *state;

    object = func_8003FC64(0);
    if (object != NULL) {
        state = (u8 *)object + 0x20;
        *(s32 *)((u8 *)state + 0x24) = state_value;
        card_boot_initialize_save_menu_request(state, init_value);
        card_boot_erase_temporary_file();
        card_boot_refresh_directory_summary();
        *(s32 *)((u8 *)object + 0x20) = create_or_reset_seven_entry_menu_backdrop(object, 0);
        *(s32 *)((u8 *)state + 4) = render_rotated_grid_surface(object, *(s32 *)((u8 *)state + 0x2C), 3);
        *(s32 *)((u8 *)state + 8) = create_save_heading(object);
        *(s32 *)((u8 *)state + 0x28) = 0;
        *(void **)((u8 *)object + 0x10) = D_800267C0;
    }
    return object;
}
