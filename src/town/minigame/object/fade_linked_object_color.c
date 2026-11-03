#include "shared/object_node.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_links.h"
#include "town/minigame/object.h"
#include "town/minigame/position.h"


typedef struct S_800203D8_1 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800203D8_1;


/* Waits for the linked object flag, then dims the color and sets completion flags. */
void fade_linked_object_color(SceneTileObject *fade) {
    S_800203D8_1 *linked_obj;
    s16 state;
    s32 color;

    linked_obj = fade->linked;
    state = fade->state.s;

    switch (state) {
    case 0:
        if (linked_obj->unk_04 & -32768) {
            fade->state.u++;
        }
        break;

    case 1:
        color = fade->color + 0xFFF7F7F8U;
        fade->color = color;
        if (color <= 0x80808) {
            NODE_HEADER(fade)->flags |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    }

}
