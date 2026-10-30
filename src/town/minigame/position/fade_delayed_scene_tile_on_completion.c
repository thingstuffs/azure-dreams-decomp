#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/object_links.h"
#include "town/minigame/position.h"

   /* the 0x2 bytes before arg0 in fade_delayed_scene_tile_on_completion, addressed as arg0[-1] */


typedef struct S_8002017C_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_8002017C_1;   /* sub in fade_delayed_scene_tile_on_completion */


/* Advance a delayed fade after the linked object signals, then flag completion. */
void fade_delayed_scene_tile_on_completion(SceneTileObject *effect) {
    s16 state;
    s32 fade_rgb;
    u16 delay;
    S_8002017C_1 *linked_object;
    s16 next_state;
    u16 flags;

    linked_object = effect->linked;
    state = effect->state.s;
    switch (state) {
    case 0:
        delay = effect->delay - 1;
        effect->delay = delay;
        if ((delay << 0x10) <= 0) {
            flags = effect->flags;
            next_state = effect->state.s;
            flags &= 0xFFFD;
            next_state = (s16) (next_state + 1);
            effect->flags = flags;
            effect->state.s = next_state;
            return;
        }
        return;
    case 1:
        if (linked_object->unk_2A & 1) {
            effect->state.s++;
            return;
        }
        break;
    case 2:
        fade_rgb = effect->color + 0xFFF7F7F8;
        effect->color = fade_rgb;
        if (fade_rgb <= 0x80808) {
            (*(u16 *)((u8 *)effect + -2)) = (u16) (((ObjectStatusPrefix16 *)effect)[-1].flags | NODE_REMOVE);
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    }
}
