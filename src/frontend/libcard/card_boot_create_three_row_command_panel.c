#include "common.h"
#include "shared/object_node.h"
#include "engine/node.h"
#include "engine/scene.h"
#include "main/data.h"
#include "sdk/libc.h"
#include "slus.h"

typedef struct S_800238D4_1 {
    u8 pad_00[0x19C];
    s32 unk_19C;
} S_800238D4_1;   /* work in card_boot_create_three_row_command_panel */

extern void process_nonzero(void *record);
extern void func_800237EC(void *state, s32 value);
extern s32 card_boot_link_three_row_panel_entries(void *input);
extern void card_boot_initialize_three_row_command_panel(void *state, s32 init_value);
extern void card_boot_animate_three_row_selection(void *state);

extern u8 menu_backdrop_tag[];

/* Creates or resets the object, initializes its state, and runs its update callback. */
void *card_boot_create_three_row_command_panel(s32 init_value)
{
    ObjectNodeHeader *object;
    u8 *state;

    object = D_800291D0;
    state = D_800291D0 + 0x20;
    if (find_active_list_node(object) == 0) {
        object = initialize_scene_object_in_buffer(0, object, 0x112);
        register_node(object, menu_backdrop_tag);
    } else {
        process_nonzero(object);
        object->flags &= 0x7FFF;
        bzero(state, 0x428);
    }

    func_800237EC(state, 0x12);
    object->sprite = state + 0x190;
    ((S_800238D4_1 *)state)->unk_19C = card_boot_link_three_row_panel_entries(state + 0x1A0);
    card_boot_initialize_three_row_command_panel(state, init_value);
    object->unk_10 = card_boot_animate_three_row_selection;
    card_boot_animate_three_row_selection(state);
    return object;
}
