#include "common.h"
#include "town/scene.h"

typedef struct {
    u8 pad[0x16];
    u8 unk_16;
    u8 pad2;
} Rec;
extern Rec scene_rows[];
extern s32 selected_scene_row_index[3];

/* Check whether the selected record byte at offset 0x16 is at least two. */
s32 is_selected_row_byte_at_least_2(void) {
    return scene_rows[selected_scene_row_index[0]].unk_16 >= 2;
}
