#include "common.h"
#include "records/Rec_func_80021E88_arg1.h"

typedef struct S_80021E88_0 {
    s16 unk_00;
    u8 pad_02[0x2];
    void * unk_04;
    u8 pad_08[0x4C];
    union { s16 s; u16 u; } unk_54;   /* accessed as both */
} S_80021E88_0;   /* arg0 in func_80021E88 */

typedef struct S_80021E88_1 {
    u8 pad_00[0x18];
    s16 unk_18;
    u8 pad_1A[0x6];
    u16 unk_20;
    s16 unk_22;
} S_80021E88_1;   /* object in func_80021E88 */

typedef struct S_80021E88_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
} S_80021E88_2;   /* arg2 in func_80021E88 */


typedef struct S_80021E88_4 {
    u8 pad_00[0x22];
    s16 unk_22;
} S_80021E88_4;   /* ((S_80021E88_0 *)arg0)->unk_04 in func_80021E88 */


extern s32 func_800A2A18(void *, void *);
extern u32 D_80012D5C;
extern u8 D_800243F0[];
extern s32 D_80024438[];
extern s32 D_80024444[];

/* Updates the object transition state, height, and display values. */
void func_80021E88(S_80021E88_0 *controller, Rec_func_80021E88_arg1 *position, S_80021E88_2 *display) {
    s16 state;
    s16 transition_pending;
    s32 transition;
    u16 flags;
    S_80021E88_1 *object;

    object = controller->unk_04;
    transition = 0;
    if (object->unk_18 == 0) {
        controller->unk_00 = 0;
    }
    if (D_80012D5C >= 100U) {
        if (func_800A2A18(D_800243F0, position) != 0) {
            transition = 1;
        } else {
            display->unk_08 = D_80024438[controller->unk_54.s];
        }
    }

    state = controller->unk_00;
    switch (state) {
    case 0:
        position->unk_08 += 0xFFF80000;
        if (position->unk_08 > 0) {
            return;
        }
        position->unk_08 = 0;
        display->unk_0C = 0x808080;
        controller->unk_00 = 1;
        return;

    case 1:
        transition_pending = transition;
        if (transition_pending) {
            if (((S_80021E88_4 *)(controller->unk_04))->unk_22 == 3) {
                object->unk_20 |= 1;
                display->unk_08 = D_80024444[controller->unk_54.s];
                object->unk_22 = controller->unk_54.u;
            }
        }
        if (object->unk_22 == 3) {
            return;
        }
        if (((S_80021E88_4 *)(controller->unk_04))->unk_22 == controller->unk_54.s) {
            controller->unk_00 = 3;
            return;
        }
        controller->unk_00 = 2;
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
            display->unk_08 = D_80024444[controller->unk_54.s];
        }
        return;
    default:
        return;
    }
}
