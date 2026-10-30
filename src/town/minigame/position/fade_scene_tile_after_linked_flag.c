#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_links.h"
#include "town/minigame/position.h"

   /* the 0x2 bytes before arg0 in fade_scene_tile_after_linked_flag, addressed as arg0[-1] */


typedef struct S_80026C54_1 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_80026C54_1;


/* Waits for the linked object flag, then fades the stored value and marks completion. */
void fade_scene_tile_after_linked_flag(SceneTileObject *effect) {
    S_80026C54_1 *linked_object;
    s16 state;
    s32 fade_value;

    linked_object = effect->linked;
    state = effect->state.s;

    switch (state) {
    case 0:
        if (linked_object->unk_1A & 8) {
            effect->state.u++;
        }
        break;

    case 1:
        fade_value = effect->color + 0xFFF7F7F8U;
        effect->color = fade_value;
        if (fade_value <= 0x80808) {
            ((ObjectStatusPrefix16 *)effect)[-1].flags |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    }

}
