#include "common.h"
#include "shared/object_node.h"

extern void * func_8003FD64();
extern s32 func_8004491C();
struct State;
struct Output;
struct Interp;
extern void update_orbiting_color_particle(struct State *state, struct Output *output, struct Interp *interp);
extern s32 draw_shaded_quad_chain(void *initial_state, void *context, void *data);

typedef struct S_800BC0A8_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_800BC0A8_0;

typedef struct S_800BC0A8_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800BC0A8_1;

typedef struct S_800BC0A8_2 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    u8 pad_0A[0x3E];
    s16 unk_48;
    u8 pad_4A[0x2];
    s16 unk_4C;
    s16 unk_4E;
    s16 unk_50;
    u8 pad_52[0x6];
    s16 unk_58;
} S_800BC0A8_2;

typedef struct S_800BC0A8_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
} S_800BC0A8_3;

/* Creates an object and initializes its position, angle, and state. */
void *create_orbiting_color_particle(s16 x, s16 y, s16 z, s16 angle, s16 value_50, s16 value_58, s32 state_word, s16 value_48) {
    s16 saved_value_50 = value_50;
    s16 saved_value_58 = value_58;
    s16 saved_value_48 = value_48;
    S_800BC0A8_3 *transform;
    S_800BC0A8_2 *state;
    void *object;
    S_800BC0A8_1 *position;

    object = func_8003FD64(0x202, ((s32 *)&D_80083498.next));
    if (object != 0) {
        ((S_800BC0A8_0 *)object)->unk_10 = update_orbiting_color_particle;
        func_8004491C(object, draw_shaded_quad_chain);
        position = ((S_800BC0A8_0 *)object)->unk_08;
        state = object + 0x20;
        position->unk_02 = x;
        state->unk_04 = x;
        position->unk_06 = y;
        state->unk_06 = y;
        position->unk_0A = z;
        state->unk_08 = z;
        transform = ((S_800BC0A8_0 *)object)->unk_0C;
        transform->unk_1A = (s16) (angle + 0x400);
        transform->unk_14 = (u16) (transform->unk_14 | 0xC);
        state->unk_4E = angle;
        state->unk_4C = 4;
        state->unk_50 = (s16) saved_value_50;
        ((S_800BC0A8_0 *)object)->unk_20 = state_word;
        state->unk_58 = (s16) saved_value_58;
        state->unk_48 = (s16) saved_value_48;
    }
    return object;
}
