#include "common.h"


extern void func_80025370() __attribute__((noreturn));
extern s32 func_8003DB94();
extern void *func_8003FC64();
extern void func_8004491C();
extern s32 func_80069EF8();

extern u8 D_80025098[9];
extern u8 D_80025AF0[9];
extern u8 D_80045C34[9];


typedef struct S_818C3A3C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_818C3A3C_0;   /* temp_v0 in func_818C3A3C */

typedef struct S_818C3A3C_1 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    s16 unk_14;
} S_818C3A3C_1;   /* temp_s2 in func_818C3A3C */

typedef struct S_818C3A3C_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818C3A3C_2;   /* arg0 in func_818C3A3C */

typedef struct S_818C3A3C_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_818C3A3C_3;   /* temp_s0 in func_818C3A3C */

typedef struct S_818C3A3C_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818C3A3C_4;   /* arg1 in func_818C3A3C */

typedef struct S_818C3A3C_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818C3A3C_5;   /* temp_v1_ptr in func_818C3A3C */

/* Creates an effect with randomized rotation, owner-dependent scale, and copied instance data. */
s32 func_818C3A3C(S_818C3A3C_2 *owner, S_818C3A3C_4 *initial_data) {
    s32 copy_word_0;
    s32 copy_word_1;
    s32 copy_word_2;
    s32 copy_word_3;
    s32 palette_flags;
    s32 call_zero;
    s32 setup_value;
    void *handler;
    s32 scale;
    s32 random_value;
    s32 biased_random;
    s16 result;
    S_818C3A3C_3 *sprite;
    void *effect_state;
    void *effect;
    S_818C3A3C_5 *effect_data;
    void *effect_name;

    effect = func_8003FC64(0x212);
    if (effect != 0) {
        effect_state = (u8 *)effect + 0x20;
        effect_name = D_80025AF0;
        handler = D_80025098;
        ASM_KEEP_NV(handler);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_CLOBBER("$3");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        palette_flags = 0x7DCF;
        ((S_818C3A3C_0 *)effect)->unk_10 = handler;
        ((S_818C3A3C_0 *)effect)->unk_20 = owner;
        ((S_818C3A3C_1 *)effect_state)->unk_10 = 0;
        setup_value = owner->unk_14;
        call_zero = 0;
        *(volatile u16 *)((u8 *)effect_state + 0x14) = setup_value;

        sprite = ((S_818C3A3C_0 *)effect)->unk_0C;
        setup_value = 0x80;
        sprite->unk_0E = setup_value;
        sprite->unk_0D = setup_value;
        sprite->unk_0C = setup_value;
        setup_value = sprite->unk_14;
        sprite->unk_12 = palette_flags;
        setup_value |= 0xC;
        sprite->unk_14 = setup_value;
        setup_value = sprite->unk_10;
        palette_flags = sprite->unk_14;
        setup_value |= 0x20;
        palette_flags |= 0x100;
        sprite->unk_10 = setup_value;
        sprite->unk_14 = palette_flags;
        func_8003DB94(sprite, effect_name, call_zero);

        biased_random = func_80069EF8();
        random_value = biased_random;
        if (random_value < 0) {
            biased_random = random_value + 0xFFF;
        }
        sprite->unk_1A = random_value - ((biased_random >> 12) << 12);

        scale = 0x1400 / ((S_818C3A3C_1 *)effect_state)->unk_14;
        sprite->unk_1E = scale;
        sprite->unk_1C = scale;
        func_8004491C(effect, D_80045C34);

        effect_data = ((S_818C3A3C_0 *)effect)->unk_08;
        ASM_KEEP(effect_data);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        result = (u32)effect;
        ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        copy_word_0 = initial_data->unk_00;
        copy_word_1 = initial_data->unk_04;
        copy_word_2 = initial_data->unk_08;
        copy_word_3 = initial_data->unk_0C;
        effect_data->unk_00 = copy_word_0;
        effect_data->unk_04 = copy_word_1;
        effect_data->unk_08 = copy_word_2;
        effect_data->unk_0C = copy_word_3;
        copy_word_0 = initial_data->unk_10;
        copy_word_1 = initial_data->unk_14;
        effect_data->unk_10 = copy_word_0;
        effect_data->unk_14 = copy_word_1;
        func_80025370(copy_word_0, copy_word_1, copy_word_2, copy_word_3);
    }
    return 0;
}
