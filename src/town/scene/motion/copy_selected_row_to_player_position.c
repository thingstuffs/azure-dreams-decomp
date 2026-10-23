#include "common.h"

typedef struct {
    u8 pad[0x14];
    s16 val;
    u8 pad2[2];
} Entry;

extern struct { void *ptr; s32 pad[2]; } town_scene_root;
extern Entry scene_rows[3];
extern s32 selected_scene_row_index[3];

/* Copy the selected entry value to the current object's destination field. */
void copy_selected_row_to_player_position(void) {
    s32 *value_ptr = *(s32 **) ((u8 *) town_scene_root.ptr + 0x1C);
    *value_ptr = scene_rows[selected_scene_row_index[0]].val;
}
