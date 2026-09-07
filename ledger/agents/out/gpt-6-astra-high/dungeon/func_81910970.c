#include "common.h"

typedef struct S_80024170_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_80024170_0;   /* temp_v0 in func_80024170 */

typedef struct S_80024170_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    u16 unk_08;
    u8 pad_0A[0x2];
    s32 unk_0C;
} S_80024170_1;   /* temp_s2 in func_80024170 */

typedef struct S_80024170_2 {
    u8 pad_00[0x12];
    u16 unk_12;
} S_80024170_2;   /* arg0 in func_80024170 */

typedef struct S_80024170_3 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x3];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80024170_3;   /* temp_s0 in func_80024170 */

typedef struct S_80024170_4 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80024170_4;   /* temp_v0_2 in func_80024170 */



typedef struct {
    s32 f0;
    s32 f1;
    s32 f2;
    s32 f3;
    s32 f4;
    s32 f5;
} Copy6;

extern void *func_8003FC64(s32);
extern s32 func_8004491C(void *, void *);
extern s32 rand(void);
extern u8 D_80024044[9];
extern u8 D_80045340[9];
extern u8 D_800DE720[9];

/* Creates an effect at the supplied position with a randomized sprite angle. */
s32 func_80024170(S_80024170_2 *owner, void *source_position)
{
    s32 random_value;
    s32 initial_z;
    s32 rounded_random;
    S_80024170_3 *sprite;
    S_80024170_1 *effect_state;
    void *effect;
    S_80024170_4 *position;

    effect = func_8003FC64(0x212);
    if (effect != 0) {
        effect_state = effect + 0x20;
        ((S_80024170_0 *)effect)->unk_10 = D_80024044;
        ((S_80024170_0 *)effect)->unk_20 = owner;
        effect_state->unk_06 = 0;
        effect_state->unk_08 = owner->unk_12;
        sprite = ((S_80024170_0 *)effect)->unk_0C;
        sprite->unk_0E = 0x80;
        sprite->unk_0D = 0x80;
        sprite->unk_0C = 0x80;
        sprite->unk_08 = D_800DE720;
        sprite->unk_12 = 0x7E00;
        sprite->unk_14 |= 0x100;
        rounded_random = rand();
        random_value = rounded_random;
        if (random_value < 0) {
            rounded_random = random_value + 0xFFF;
        }
        sprite->unk_1A = random_value - ((rounded_random >> 0xC) << 0xC);
        sprite->unk_1E = 0x400;
        sprite->unk_1C = 0x400;
        func_8004491C(effect, D_80045340);
        position = ((S_80024170_0 *)effect)->unk_08;
        *(Copy6 *)position = *(Copy6 *)source_position;
        initial_z = position->unk_08;
        effect_state->unk_0C = initial_z;
        return (s32)effect;
    }
    return 0;
}
