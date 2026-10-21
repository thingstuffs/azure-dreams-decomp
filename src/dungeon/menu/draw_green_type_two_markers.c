#include "common.h"

extern s16 dungeon_floor_marker_entries[8];
extern void submit_activation_command(void);
extern void create_transformed_render_object(s16 x, s16 y, s32 color, s32 size, s32 count);

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
        create_transformed_render_object(record[1], record[2], color, 1, 0);
    }

}
