#include "common.h"
#include "town/scene/state_data.h"
#include "town/scene.h"

typedef struct {
    u8 pad[0x16];
    u8 lookup_index;
    u8 pad2;
} Rec;
extern Rec scene_rows[];

extern s32 D_80019A70[];

/* Return the lookup value indexed by the selected entry's byte at 0x16. */
s32 get_row_lookup_value(void) {
    u8 lookup_index;

    lookup_index = scene_rows[selected_scene_row_index].lookup_index;
    return D_80019A70[lookup_index];
}
