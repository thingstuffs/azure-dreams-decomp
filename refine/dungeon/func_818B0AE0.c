#include "common.h"

typedef struct S_800242E0_0 {
    void * unk_00;
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
} S_800242E0_0;   /* arg0 in func_800242E0 */

typedef struct S_800242E0_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800242E0_1;   /* temp_v1 in func_800242E0 */

typedef struct S_800242E0_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800242E0_2;   /* arg1 in func_800242E0 */

typedef struct S_800242E0_3 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800242E0_3;   /* arg2 in func_800242E0 */



extern void func_8003DB94(void *, void *, s32);
extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 rand(void);
extern u8 D_800DEC70[];

/* Advances the height offset, randomizes lateral placement on wrap, and updates the object. */
void func_800242E0(S_800242E0_0 *state, S_800242E0_2 *position, S_800242E0_3 *object) {
    s32 angle;
    u16 height_offset;
    S_800242E0_1 *counter;

    counter = state->unk_00;
    counter->unk_14 = (u16)(counter->unk_14 + 1);
    height_offset = state->unk_04 + state->unk_06;
    state->unk_04 = height_offset;
    if ((s16)height_offset < -0x80) {
        angle = rand() % 0x1000;
        position->unk_02 = (s16)(state->unk_08 + ((func_800644B8(angle) * 2) >> 8));
        position->unk_06 = (s16)(state->unk_0A + ((func_80064584(angle) * 2) >> 8));
        state->unk_04 = (u16)(state->unk_04 + 0x80);
        state->unk_06 = (u16)(-6 - (rand() % 5));
    }
    position->unk_0A = (s16)(state->unk_0C + state->unk_04);
    func_800478B8(object);
    if (object->unk_14 & 0x6000) {
        func_8003DB94(object, D_800DEC70, 0);
    }
}
