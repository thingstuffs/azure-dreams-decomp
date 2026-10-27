#include "dungeon/level/floor_flags.h"
#include "common.h"

extern s16 dungeon_floor_marker_entries[8];
extern void submit_activation_command(void);
extern void * create_transformed_render_object(s32 x, s32 y, s32 initial_value, s32 update_param, s32 mode);

/* Create green markers for up to four leading type-2 entries. */
void draw_green_type_two_markers(void) {
    s16 *record;
    s32 entry_count;
    s32 color;

    submit_activation_command();
    for (entry_count = 0; entry_count < 4; entry_count++) {
        record = &dungeon_floor_marker_entries[entry_count * 4];
        if (record[0] != 2) {
            break;
        }
        color = 0x208020;
        create_transformed_render_object(record[1], record[2], color, FLOOR_ELEVATOR_VISIBLE, 0);
    }

}
