#include "common.h"

typedef struct S_800238D4_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_800238D4_0;   /* base in card_boot_create_three_row_command_panel */

typedef struct S_800238D4_1 {
    u8 pad_00[0x19C];
    s32 unk_19C;
} S_800238D4_1;   /* work in card_boot_create_three_row_command_panel */


extern s32 find_active_list_node(void *object);
extern void *initialize_scene_object_in_buffer(s32 value0, void *object, s32 value1);
extern void register_node(void *object, void *callback);
extern void process_nonzero(void *record);
extern void bzero(void *ptr, s32 size);
extern void func_800237EC(void *state, s32 value);
extern s32 card_boot_link_three_row_panel_entries(void *input);
extern void card_boot_initialize_three_row_command_panel(void *state, s32 init_value);
extern void card_boot_animate_three_row_selection(void *state);

extern u8 D_80027DD0[];
extern u8 D_800291D0[];

/* Creates or resets the object, initializes its state, and runs its update callback. */
void *card_boot_create_three_row_command_panel(s32 init_value)
{
    u8 *object;
    u8 *state;

    object = D_800291D0;
    state = D_800291D0 + 0x20;
    if (find_active_list_node(object) == 0) {
        object = initialize_scene_object_in_buffer(0, object, 0x112);
        register_node(object, D_80027DD0);
    } else {
        process_nonzero(object);
        ((S_800238D4_0 *)object)->unk_1E &= 0x7FFF;
        bzero(state, 0x428);
    }

    func_800237EC(state, 0x12);
    ((S_800238D4_0 *)object)->unk_0C = state + 0x190;
    ((S_800238D4_1 *)state)->unk_19C = card_boot_link_three_row_panel_entries(state + 0x1A0);
    card_boot_initialize_three_row_command_panel(state, init_value);
    *(void (**)(void *))(object + 0x10) = card_boot_animate_three_row_selection;
    card_boot_animate_three_row_selection(state);
    return object;
}
