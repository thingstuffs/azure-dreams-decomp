#include "shared/dungeon_item_entries.h"
#include "common.h"
#include "m2c_compat.h"

void submit_activation_command(void);                            /* extern */
void *create_transformed_render_object(); /* extern */
extern u8 dungeon_ground_item_positions[];

typedef struct S_8009F020_0 {
    u8 unk_00;
    u8 unk_01;
} S_8009F020_0;

typedef struct S_8009F020_1 {
    u8 unk_00;
    u8 unk_01;
} S_8009F020_1;

/* Create blue markers at the positions of enabled entries. */
void draw_blue_enabled_entry_markers(s32 setup_arg_0, s32 setup_arg_1, s32 setup_arg_2, s32 setup_arg_3) {
    u8 *entry_state;
    u8 *entry_position;
    s32 entry_index;

    submit_activation_command();
    entry_index = 0;
    entry_position = dungeon_ground_item_positions;
    entry_state = ((u8 *)dungeon_ground_items);
    do {
        if ((((S_8009F020_0 *)entry_state)->unk_01 != 0) && (((S_8009F020_0 *)entry_state)->unk_00 != 0)) {
            create_transformed_render_object(((S_8009F020_1 *)entry_position)->unk_00, ((S_8009F020_1 *)entry_position)->unk_01, 0x802020,
                2, entry_index);
        }
        entry_position += 0xC;
        entry_index += 1;
        entry_state += 4;
    } while (entry_index < 0x40);
}
