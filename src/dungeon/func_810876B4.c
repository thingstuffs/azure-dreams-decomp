#include "common.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80174EB4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80174EB4_0;   /* obj in func_80174EB4 */

typedef struct S_80174EB4_1 {
    u8 pad_00[0x4];
    void * unk_04;
    void * unk_08;
} S_80174EB4_1;   /* slot in func_80174EB4 */

typedef struct S_80174EB4_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
} S_80174EB4_2;   /* prim in func_80174EB4 */



typedef struct S_80174EB4_5 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80174EB4_5;   /* dst in func_80174EB4 */

typedef struct S_80174EB4_6 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80174EB4_6;   /* query_arg in func_80174EB4 */



extern void *func_8003FD64(s32, s32);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 func_8003DE58(s32, void *, u16 *, s32);

extern u8 D_80045340[9];
extern u8 D_80174D24[9];

/* Create a render object, copy its source state, and apply queried position offsets. */
s32 func_80174EB4(s32 priority, Rec_D_800E3D7C *source_state, Rec_func_800AA258_arg2 *render_data) {
    u16 offsets[3];
    void *object;
    S_80174EB4_5 *state;
    S_80174EB4_2 *primitive;
    S_80174EB4_1 *context;

    object = func_8003FD64(0x312, priority - 0x20);
    if (object != 0) {
        ((S_80174EB4_0 *)object)->unk_10 = D_80174D24;
        func_8004491C(object, D_80045340);

        context = (u8 *)object + 0x20;
        context->unk_04 = source_state;
        context->unk_08 = render_data;

        primitive = ((S_80174EB4_0 *)object)->unk_0C;
        primitive->unk_28 = render_data->unk_28;
        primitive->unk_0E = 0x80;
        primitive->unk_0D = 0x80;
        primitive->unk_0C = 0x80;
        primitive->unk_1E = 0x1000;
        primitive->unk_1C = 0x1000;
        primitive->unk_14 |= 0xC;
        primitive->unk_10 |= 0x20;
        func_80047784(primitive, 0x38, 0);

        {
            S_80174EB4_6 *query_data = render_data;
            u16 *offset_out;
            s32 copy_word_0;
            register s32 copy_word_1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            s32 copy_word_2;
            s32 copy_word_3;

            ASM_KEEP(query_data);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            state = ((S_80174EB4_0 *)object)->unk_08;
            ASM_KEEP(state);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            offset_out = offsets;
            ASM_KEEP(offset_out);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            copy_word_0 = source_state->unk_00.at00_s32.v;
            copy_word_1 = source_state->unk_04.at00_s32.v;
            copy_word_2 = source_state->unk_08.at00_s32.v;
            copy_word_3 = source_state->unk_0C.as_s32;
            state->unk_00.at00.v = copy_word_0;
            state->unk_04.at00.v = copy_word_1;
            state->unk_08.at00.v = copy_word_2;
            state->unk_0C = copy_word_3;
            copy_word_1 = source_state->unk_14.as_s32;
            state->unk_10 = source_state->unk_10.at00_s32.v;
            state->unk_14 = copy_word_1;

            offsets[2] = 0;
            offsets[1] = 0;
            offsets[0] = 0;
            if (func_8003DE58(query_data->unk_08, query_data,
                              offset_out, 0) != 0) {
                state->unk_00.at02.v += offsets[0];
                state->unk_04.at02.v += offsets[1];
                state->unk_08.at02.v += offsets[2];
            }
        }
        return (s32)object;
    }
    return 0;
}
