#include "common.h"
#include "m2c_compat.h"

typedef struct Copy24 {
    s32 word0;
    s32 word4;
    s32 word8;
    s32 wordC;
    s32 word10;
    s32 word14;
} Copy24;

extern s32 D_800DEB70;
extern u8 D_80045340[];

void *func_8003FD64();
M2C_UNK func_8004491C();
s32 rand();
extern M2C_UNK D_80025094;

typedef struct S_80025270_0 {
    u8 pad_00[0x8];
    Copy24 * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80025270_0;   /* temp_v0 in func_80025270 */

typedef struct S_80025270_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    u8 pad_0E[0x12];
    s32 unk_20;
    s32 unk_24;
    s32 unk_28;
} S_80025270_1;   /* temp_a0_2 in func_80025270 */

typedef struct S_80025270_2 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80025270_2;   /* arg0 in func_80025270 */

typedef struct S_80025270_3 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
} S_80025270_3;   /* temp_v1 in func_80025270 */

/* Creates an attached effect with copied transform data and a randomized angle. */
s32 func_80025270(void *object, Copy24 *src_transform, s16 effect_index) {
    s32 first_word;
    s32 second_word;
    s32 random_value;
    s32 adjusted_random;
    S_80025270_1 *state;
    Copy24 *transform;
    void *effect;
    s16 saved_index;
    effect = func_8003FD64(0x212, (u8 *)object - 0x20);
    if (effect != NULL) {
        saved_index = effect_index;
        state = effect + 0x20;
        ((S_80025270_0 *)effect)->unk_10 = &D_80025094;
        ((S_80025270_0 *)effect)->unk_20 = (s32)object;
        state->unk_08 = (s16) (saved_index * 7);
        state->unk_04 = 0;
        state->unk_06 = 0;
        state->unk_0A = 0;
        state->unk_0C = (s16) (saved_index * 0x600);
        state->unk_20 = src_transform->wordC;
        state->unk_24 = src_transform->word10;
        state->unk_28 = src_transform->word14;
        object = ((S_80025270_0 *)effect)->unk_0C;
        ((S_80025270_2 *)object)->unk_0E = 0x20;
        ((S_80025270_2 *)object)->unk_0D = 0x20;
        ((S_80025270_2 *)object)->unk_0C = 0x20;
        ((S_80025270_2 *)object)->unk_12 = 0x7DCF;
        ((S_80025270_2 *)object)->unk_14 = (u16) (((S_80025270_2 *)object)->unk_14 | 0xC);
        ((S_80025270_2 *)object)->unk_10 = (u16) (((S_80025270_2 *)object)->unk_10 | 0x20);
        ((S_80025270_2 *)object)->unk_14 = (u16) (((S_80025270_2 *)object)->unk_14 | 0x100);
        func_8003DB94(object, &D_800DEB70, 0);
        adjusted_random = rand();
        random_value = adjusted_random;
        if (random_value < 0) {
            adjusted_random = random_value + 0xFFF;
        }
        ((S_80025270_2 *)object)->unk_1A = (s16) (random_value - ((adjusted_random >> 0xC) << 0xC));
        ((S_80025270_2 *)object)->unk_1E = 0x400;
        ((S_80025270_2 *)object)->unk_1C = 0x400;
        func_8004491C(effect, D_80045340);
        transform = ((S_80025270_0 *)effect)->unk_08;
        *transform = *src_transform;
        first_word = ((S_80025270_3 *)transform)->unk_00;
        second_word = ((S_80025270_3 *)transform)->unk_04;
        ((S_80025270_3 *)transform)->unk_0C = first_word;
        ((S_80025270_3 *)transform)->unk_10 = second_word;
        return (s32)effect;
    }
    return 0;
}
