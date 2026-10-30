#include "common.h"
#include "records/Rec_func_80021E88_arg1.h"
#include "town/menu.h"
#include "town/minigame/object.h"


typedef struct S_80021E88_1 {
    u8 pad_00[0x18];
    s16 unk_18;
    u8 pad_1A[0x6];
    u16 unk_20;
    s16 unk_22;
} S_80021E88_1;   /* object in update_minigame_transition */

typedef struct S_80021E88_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
} S_80021E88_2;   /* arg2 in update_minigame_transition */


typedef struct S_80021E88_4 {
    u8 pad_00[0x22];
    s16 unk_22;
} S_80021E88_4;   /* ((S_80021E88_0 *)arg0)->unk_04 in update_minigame_transition */

extern u32 town_money;
extern u8 D_800243F0[];
extern s32 D_80024438[];
extern s32 D_80024444[];

/* Updates the object transition state, height, and display values. */
void update_minigame_transition(MinigameTransitionObject *controller, Rec_func_80021E88_arg1 *position, S_80021E88_2 *display) {
    s16 state;
    s16 transition_pending;
    s32 transition;
    u16 flags;
    S_80021E88_1 *object;

    object = controller->object;
    transition = 0;
    if (object->unk_18 == 0) {
        controller->state = 0;
    }
    if (town_money >= 100U) {
        if (test_three_axis_box_overlap(D_800243F0, position) != 0) {
            transition = 1;
        } else {
            display->unk_08 = D_80024438[controller->mode.s];
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
        display->unk_0C = 0x808080;
        controller->state = 1;
        return;

    case 1:
        transition_pending = transition;
        if (transition_pending) {
            if (((S_80021E88_4 *)(controller->object))->unk_22 == 3) {
                object->unk_20 |= 1;
                display->unk_08 = D_80024444[controller->mode.s];
                object->unk_22 = controller->mode.u;
            }
        }
        if (object->unk_22 == 3) {
            return;
        }
        if (((S_80021E88_4 *)(controller->object))->unk_22 == controller->mode.s) {
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
        flags = object->unk_20;
        if (flags & 1) {
            object->unk_20 = flags | 1;
            display->unk_08 = D_80024444[controller->mode.s];
        }
        return;
    default:
        return;
    }
}
