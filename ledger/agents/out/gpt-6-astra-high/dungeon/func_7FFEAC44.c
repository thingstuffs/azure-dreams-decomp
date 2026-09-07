#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

typedef struct S_7FFEAC44_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0x18];
    s32 unk_2C;
    u8 pad_30[0xE];
    s16 unk_3E;
    u8 pad_40[0x4];
    void * unk_44;
} S_7FFEAC44_0;   /* temp_v0 in func_7FFEAC44 */

typedef struct S_7FFEAC44_1 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_7FFEAC44_1;   /* temp_a0 in func_7FFEAC44 */

typedef struct S_7FFEAC44_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_7FFEAC44_2;   /* temp_v1 in func_7FFEAC44 */

typedef struct S_7FFEAC44_3 {
    u8 pad_00[0x8];
    void * unk_08;
} S_7FFEAC44_3;   /* arg0 in func_7FFEAC44 */

typedef struct S_7FFEAC44_4 {
    u8 pad_00[0xC];
    union { struct { u8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    u8 pad_10[0x2];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_7FFEAC44_4;   /* temp_a0_2 in func_7FFEAC44 */

typedef struct S_7FFEAC44_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_7FFEAC44_5;   /* ((S_7FFEAC44_3 *)arg0)->unk_08 in func_7FFEAC44 */


#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_8003A7C4();
void *func_8003CF18();
extern u16 D_80094422[5];
extern M2C_UNK D_800E2BB8;
extern M2C_UNK D_8010CB64;

/* Create an effect at the source position with the specified color. */
void func_7FFEAC44(S_7FFEAC44_3 *source, s32 color) {
    s32 saved_color;
    S_7FFEAC44_1 *render_state;
    S_7FFEAC44_4 *sprite;
    S_7FFEAC44_0 *effect;
    S_7FFEAC44_2 *position;

    effect = func_8003CF18(0x12);
    if (effect != NULL) {
        render_state = effect->unk_0C;
        effect->unk_10 = &D_8010CB64;
        effect->unk_44 = source;
        effect->unk_3E = 0x46;
        render_state->unk_10 = 0x20;
        render_state->unk_14 =
            (u16)(render_state->unk_14 | 0xC);
        position = effect->unk_08;
        position->unk_02 =
            (u16)((S_7FFEAC44_5 *)(source->unk_08))->unk_02;
        position->unk_06 =
            (u16)((S_7FFEAC44_5 *)(source->unk_08))->unk_06;
        position->unk_0A =
            (u16)((S_7FFEAC44_5 *)(source->unk_08))->unk_0A;
        sprite = effect->unk_0C;
        sprite->unk_0C.at02.v = 0x80;
        sprite->unk_0C.at01.v = 0x80;
        sprite->unk_0C.at00.v = 0x80;
        saved_color = *(volatile s32 *)&color;
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        sprite->unk_0C.at00u.v = saved_color;
        effect->unk_2C = saved_color;
        sprite->unk_12 = 0x7DCE;
        sprite->unk_14 =
            (u16)(sprite->unk_14 | 0x100);
        func_8003A7C4(sprite, &D_800E2BB8, 0);
        D_80094422[0] += 1;
    }
}
