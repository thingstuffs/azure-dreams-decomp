#include "common.h"
#include "town/scene/state_data.h"
#include "town/scene.h"

typedef struct {
    u8 pad[0x16];
    u8 lookup_index;
    u8 pad2;
} Rec;
extern Rec scene_rows[];

/* Check whether the selected record byte at offset 0x16 is at least two. */
s32 is_selected_row_byte_at_least_2(void) {
    return scene_rows[selected_scene_row_index].lookup_index >= 2;
}
