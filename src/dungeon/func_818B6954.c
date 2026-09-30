#include "common.h"
#include "shared/slus_callbacks.h"

#ifndef NULL
#define NULL 0
#endif


typedef struct {
    s32 w[6];
} Copy24;

typedef struct S_818B6954_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_818B6954_0;   /* temp_v0 in func_818B6954 */

typedef struct S_818B6954_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
} S_818B6954_1;   /* temp_v0_2 in func_818B6954 */

typedef struct S_818B6954_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_818B6954_2;   /* temp_s0_2 in func_818B6954 */


extern s32 func_8003DB94();
extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 func_800644B8();
extern s32 func_80064584();
extern s32 rand();

extern u8 D_800240B8[];
extern u8 D_800DEC70[];

/* Create an object with randomized rotation and a radial position offset. */
s32 func_818B6954(s32 context_value, void *source_state, s32 render_param) {
    s16 offset_angle;
    S_818B6954_2 *render_state;
    s32 *object_state;
    void *object;
    S_818B6954_1 *object_data;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        ((S_818B6954_0 *)object)->unk_10 = D_800240B8;
        object_data = (S_818B6954_1 *)((u8 *)object + 0x20);
        ((S_818B6954_0 *)object)->unk_20 = context_value;
        object_data->unk_04 = 0;
        object_data->unk_06 = 0;
        render_state = ((S_818B6954_0 *)object)->unk_0C;
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
        object_state = ((S_818B6954_0 *)object)->unk_08;
        *(Copy24 *)object_state = *(Copy24 *)source_state;
        offset_angle = rand() % 0x1000;
        object_state[0] += (func_80064584(offset_angle) >> 4) * 0x1200;
        object_state[1] += (func_800644B8(offset_angle) >> 4) * 0x1200;
        return (s32)object;
    }
    return 0;
}
