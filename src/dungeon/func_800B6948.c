#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64();
M2C_UNK func_8004491C();
extern M2C_UNK D_80083498;
extern M2C_UNK D_800BBBE0;
extern M2C_UNK D_800BC054;

typedef struct S_800BC0A8_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_800BC0A8_0;   /* temp_v0 in func_800BC0A8 */

typedef struct S_800BC0A8_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800BC0A8_1;   /* temp_v0_2 in func_800BC0A8 */

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
} S_800BC0A8_2;   /* temp_a1 in func_800BC0A8 */

typedef struct S_800BC0A8_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
} S_800BC0A8_3;   /* temp_a0 in func_800BC0A8 */

/* Creates an object and initializes its position, angle, and state. */
void *func_800BC0A8(s16 x, s16 y, s16 z, s16 angle, s32 value_50, s32 value_58, s32 state_word, s32 value_48) {
    register s32 saved_value_50 ASM_REG("$21") = value_50;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 saved_value_58 ASM_REG("$23") = value_58;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 saved_value_48 ASM_REG("$22") = value_48;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    S_800BC0A8_3 *transform;
    S_800BC0A8_2 *state;
    void *object;
    S_800BC0A8_1 *position;

    object = func_8003FD64(0x202, &D_80083498);
    if (object != NULL) {
        ((S_800BC0A8_0 *)object)->unk_10 = &D_800BBBE0;
        func_8004491C(object, &D_800BC054);
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
