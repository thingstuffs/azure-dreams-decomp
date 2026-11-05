#include "dungeon/level/floor_flags.h"
#include "shared/dungeon_item_entries.h"
#include "common.h"
#include "m2c_compat.h"
#include "dungeon/menu.h"

void *create_transformed_render_object(s32 x, s32 y, s32 initial_value, s32 update_param, s32 mode); /* extern */
extern DungeonItemPosition dungeon_ground_item_positions[64];

/* Create blue markers at the positions of enabled entries. */
void draw_blue_enabled_entry_markers(void) {
    DungeonItemEntry *entry_state;
    DungeonItemPosition *entry_position;
    s32 entry_index;

    submit_activation_command();
    entry_index = 0;
    entry_position = dungeon_ground_item_positions;
    entry_state = dungeon_ground_items;
    do {
        if ((entry_state->kind != 0) && (entry_state->unk_00 != 0)) {
            create_transformed_render_object(entry_position->x, entry_position->y, 0x802020,
                FLOOR_ITEMS_VISIBLE, entry_index);
        }
        entry_position++;
        entry_index += 1;
        entry_state++;
    } while (entry_index < 0x40);
}
