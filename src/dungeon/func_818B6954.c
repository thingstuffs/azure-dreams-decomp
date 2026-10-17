#include "shared/object_node.h"
#include "modules/dungeon_ovl_18d6800.h"
#include "common.h"
#include "shared/slus_callbacks.h"

#ifndef NULL
#define NULL 0
#endif











extern s32 rand();

extern u8 D_800DEC70[];

/* Create an object with randomized rotation and a radial position offset. */
s32 func_80024154(s32 context_value, void *source_state, s32 render_param, s32 ignored_context) {
    s16 offset_angle;
    B28_818B6954_S_818B6954_2 *render_state;
    s32 *object_state;
    void *object;
    B28_818B6954_S_818B6954_1 *object_data;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        ((B28_818B6954_S_818B6954_0 *)object)->unk_10 = func_800240B8;
        object_data = (B28_818B6954_S_818B6954_1 *)((u8 *)object + 0x20);
        ((B28_818B6954_S_818B6954_0 *)object)->unk_20 = context_value;
        object_data->unk_04 = 0;
        object_data->unk_06 = 0;
        render_state = ((B28_818B6954_S_818B6954_0 *)object)->unk_0C;
        render_state->unk_0C = render_param;
        render_state->unk_12 = 0x7DCF;
        render_state->unk_14 |= 0xC;
        render_state->unk_10 |= 0x20;
        render_state->unk_14 |= 0x100;
        func_8003DB94(render_state, D_800DEC70, 0);
        render_state->unk_1A = rand() % 0x1000;
        render_state->unk_1E = 0xC00;
        render_state->unk_1C = 0xC00;
        func_8004491C(object, func_80045340);
        object_state = ((B28_818B6954_S_818B6954_0 *)object)->unk_08;
        *(B28_818B6954_Copy24 *)object_state = *(B28_818B6954_Copy24 *)source_state;
        offset_angle = rand() % 0x1000;
        object_state[0] += (func_80064584(offset_angle) >> 4) * 0x1200;
        object_state[1] += (func_800644B8(offset_angle) >> 4) * 0x1200;
        return (s32)object;
    }
    return 0;
}
