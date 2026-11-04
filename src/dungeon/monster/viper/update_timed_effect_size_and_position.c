#include "common.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "shared/entity.h"
#include "dungeon/monster/viper/effect.h"
#include "shared/object_node.h"
#include "dungeon/monster/viper.h"

   /* the 0x2 bytes before arg0 in update_timed_effect_size_and_position, addressed as arg0[-1] */

typedef struct Page8008 {
    u8 pad[0x14A0];
    u32 flags;
} Page8008;

/*
 * Shrinks the sprite in staged steps, moves it vertically in state 2, and marks the effect for
 * removal in state 3.
 */
void update_timed_effect_size_and_position(ViperTimedEffectBody *effect, ObjectPosition *position, Rec_func_800AA258_arg2 *visual, void *unused_actor)
{
    s32 state;
    u16 size_or_state;
    Page8008 *flag_page;

    state = effect->state;
    effect->timer.s--;

    switch (state) {
    case 0:
        if (visual->unk_14 & 0x8000) {
            effect->state = 3;
            return;
        }
        effect->timer.s = 3;
        effect->state++;
                        /* fall through */
    case 1:
        size_or_state = visual->unk_1E - 0x50;
        visual->unk_1E = size_or_state;
        visual->unk_1C = size_or_state;
        if (effect->timer.u < 0) {
            state = 2;
            size_or_state = effect->state;
            effect->timer.s = state;
            size_or_state++;
            effect->state = size_or_state;
        }
        return;
    case 2:
        position->z.v += 0x28000;
        size_or_state = visual->unk_1E - 0x80;
        visual->unk_1E = size_or_state;
        visual->unk_1C = size_or_state;
        if (effect->timer.u < 0) {
            size_or_state = effect->state;
            size_or_state++;
            effect->state = size_or_state;
        }
        return;
    case 3:
        flag_page = (Page8008 *)0x80080000;
        NODE_HEADER(effect)->flags |= 0x8000;
        flag_page->flags |= 0x8000;
        return;
    default:
        return;
    }
}
