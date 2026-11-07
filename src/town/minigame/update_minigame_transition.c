#include "common.h"
#include "records/Rec_func_80021E88_arg1.h"
#include "town/menu.h"
#include "town/minigame/object.h"
#include "town/minigame/effect.h"

typedef struct S_80021E88_4 {
    u8 pad_00[0x22];
    s16 unk_22;
} S_80021E88_4;   /* ((MinigameTransitionObject *)arg0)->unk_04 in update_minigame_transition */

extern u32 town_money;
extern u8 D_800243F0[];
extern s32 D_80024438[];
extern s32 D_80024444[];

/* Updates the object transition state, height, and display values. */
void update_minigame_transition(MinigameTransitionObject *controller, Rec_func_80021E88_arg1 *position, SpriteFrameState *display) {
    s16 state;
    s16 transition_pending;
    s32 transition;
    u16 flags;
    TownEffect *object;

    object = controller->object;
    transition = 0;
    if (object->state == 0) {
        controller->state = 0;
    }
    if (town_money >= 100U) {
        if (test_three_axis_box_overlap(D_800243F0, position) != 0) {
            transition = 1;
        } else {
            display->source = D_80024438[controller->mode];
        }
    }

    state = controller->state;
    switch (state) {
    case 0:
        position->unk_08 += 0xFFF80000;
        if (position->unk_08 > 0) {
            return;
        }
        position->unk_08 = 0;
        display->color.word = 0x808080;
        controller->state = 1;
        return;

    case 1:
        transition_pending = transition;
        if (transition_pending) {
            if (((S_80021E88_4 *)(controller->object))->unk_22 == 3) {
                object->flags |= 1;
                display->source = D_80024444[controller->mode];
                object->phase = (u16)controller->mode;
            }
        }
        if (object->phase == 3) {
            return;
        }
        if (((S_80021E88_4 *)(controller->object))->unk_22 == controller->mode) {
            controller->state = 3;
            return;
        }
        controller->state = 2;
        return;

    case 2:
        position->unk_08 += 0x80000;
        if (position->unk_08 > 0x3FFFFF) {
            position->unk_08 = 0x400000;
            return;
        }
        return;

    case 3:
        flags = object->flags;
        if (flags & 1) {
            object->flags = flags | 1;
            display->source = D_80024444[controller->mode];
        }
        return;
    default:
        return;
    }
}
