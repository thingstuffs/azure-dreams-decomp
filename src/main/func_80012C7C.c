#include "common.h"
#include "m2c_compat.h"

void card_boot_refresh_directory_summary();                            /* extern */
void card_boot_erase_temporary_file();                            /* extern */
s32 card_boot_create_three_row_command_panel();                          /* extern */
s32 render_rotated_grid_surface();            /* extern */
void card_boot_initialize_slot_menu_request();                 /* extern */
void *initialize_scene_object_in_buffer();   /* extern */
s32 create_or_reset_seven_entry_menu_backdrop();                  /* extern */
extern M2C_UNK D_80025BD4;
extern M2C_UNK D_8002B7E0;

typedef struct S_80025C7C_0 {
    u8 pad_00[0x18];
    s32 unk_18;
    s32 unk_1C;
    u8 pad_20[0x4];
    s32 unk_24;
    s32 unk_28;
    u8 pad_2C[0x1C];
    s32 unk_48;
} S_80025C7C_0;

typedef struct S_80025C7C_1 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80025C7C_1;

/* Creates an object and initializes its state. */
void *card_boot_create_slot_selection_menu(s32 init_value) {
    S_80025C7C_0 *state;
    void *object;

    object = initialize_scene_object_in_buffer(0, &D_8002B7E0, 0x1C);
    state = object + 0x20;
    card_boot_initialize_slot_menu_request(state, init_value);
    card_boot_erase_temporary_file();
    card_boot_refresh_directory_summary();
    state->unk_48 = 1;
    ((S_80025C7C_1 *)object)->unk_20 = create_or_reset_seven_entry_menu_backdrop(object, object + 0x68);
    state->unk_18 = card_boot_create_three_row_command_panel(object);
    state->unk_1C = render_rotated_grid_surface(object, state->unk_28, 0);
    state->unk_24 = 0;
    ((S_80025C7C_1 *)object)->unk_10 = &D_80025BD4;
    return object;
}
