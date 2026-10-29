#include "common.h"
#include "town/scene.h"

typedef struct {
    u8 pad[0x16];
    u8 unk_16;
    u8 pad2;
} Rec;
extern Rec scene_rows[];
extern s32 selected_scene_row_index;
extern s32 D_80019A70[];

/* Return the lookup value indexed by the selected entry's byte at 0x16. */
s32 get_lookup_value_by_row_byte(void) {
    u8 lookup_index;

    lookup_index = scene_rows[selected_scene_row_index].unk_16;
    return D_80019A70[lookup_index];
}
