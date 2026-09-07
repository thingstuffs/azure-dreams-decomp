#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
extern M2C_UNK D_80024918;

typedef s32 UnalignedS32 __attribute__((aligned(1)));

typedef struct {
    UnalignedS32 word;
} Packed4;

typedef struct {
    s32 words[4];
} FourWords;

typedef struct {
    Packed4 part[2];
} Packed8;


typedef struct S_800249E4_0 {
    u8 pad_00[0x74];
    s16 unk_74;
    s16 unk_76;
} S_800249E4_0;   /* temp_a0 in func_800249E4 */

/* Allocate an object and initialize its endpoints, one-eighth movement steps, and parameters. */
void func_800249E4(s32 object_value, void *start_pos, void *end_pos, s16 setting, FourWords params_a, FourWords params_b, Packed8 packed_params) {
    s32 start_x;
    s32 start_y;
    s32 start_z;
    s32 word_0;
    s32 word_1;
    s32 word_2;
    s32 word_3;
    s32 packed_word_0;
    s32 packed_word_1;
    void *state;
    register void *object ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
    register u8 *stack_base ASM_REG("$29");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

    object = func_8003FC64(0x212);
    if (object != NULL) {
        state = object + 0x20;
        (*(M2C_UNK **)((u8 *)object + 0x10)) = &D_80024918;
        (*(s32 *)((u8 *)object + 0x20)) = object_value;
        ((S_800249E4_0 *)state)->unk_74 = 0;
        ((S_800249E4_0 *)state)->unk_76 = setting;
        start_x = (*(s32 *)((u8 *)start_pos + 0));
        (*(s32 *)((u8 *)state + 0x1C)) = start_x;
        (*(s32 *)((u8 *)state + 0x34)) = start_x;
        start_y = (*(s32 *)((u8 *)start_pos + 4));
        (*(s32 *)((u8 *)state + 0x20)) = start_y;
        (*(s32 *)((u8 *)state + 0x38)) = start_y;
        start_z = (*(s32 *)((u8 *)start_pos + 8));
        (*(s32 *)((u8 *)state + 0x24)) = start_z;
        (*(s32 *)((u8 *)state + 0x3C)) = start_z;
        (*(s32 *)((u8 *)state + 4)) = (s32) (*(s32 *)((u8 *)end_pos + 0));
        (*(s32 *)((u8 *)state + 8)) = (s32) (*(s32 *)((u8 *)end_pos + 4));
        (*(s32 *)((u8 *)state + 0xC)) = (s32) (*(s32 *)((u8 *)end_pos + 8));
        (*(s32 *)((u8 *)state + 0x40)) = (s32) ((s32) ((*(s32 *)((u8 *)end_pos + 0)) - (*(s32 *)((u8 *)start_pos + 0))) >> 3);
        (*(s32 *)((u8 *)state + 0x44)) = (s32) ((s32) ((*(s32 *)((u8 *)end_pos + 4)) - (*(s32 *)((u8 *)start_pos + 4))) >> 3);
        (*(s32 *)((u8 *)state + 0x48)) = (s32) ((s32) ((*(s32 *)((u8 *)end_pos + 8)) - (*(s32 *)((u8 *)start_pos + 8))) >> 3);
        word_0 = params_a.words[0];
        word_1 = params_a.words[1];
        word_2 = params_a.words[2];
        word_3 = params_a.words[3];
        (*(s32 *)((u8 *)object + 0x6C)) = word_0;
        (*(s32 *)((u8 *)object + 0x70)) = word_1;
        (*(s32 *)((u8 *)object + 0x74)) = word_2;
        (*(s32 *)((u8 *)object + 0x78)) = word_3;
        word_0 = params_b.words[0];
        word_1 = params_b.words[1];
        word_2 = params_b.words[2];
        word_3 = params_b.words[3];
        (*(s32 *)((u8 *)object + 0x7C)) = word_0;
        (*(s32 *)((u8 *)object + 0x80)) = word_1;
        (*(s32 *)((u8 *)object + 0x84)) = word_2;
        (*(s32 *)((u8 *)object + 0x88)) = word_3;
        stack_base = (u8 *)&packed_params - 0x58;
        packed_word_0 = (*(Packed4 *)((u8 *)stack_base + 0x58)).word;
        packed_word_1 = (*(Packed4 *)((u8 *)stack_base + 0x5C)).word;
        (*(Packed4 *)((u8 *)object + 0x8C)).word = packed_word_0;
        (*(Packed4 *)((u8 *)object + 0x90)).word = packed_word_1;
    }
}

/* MECHANISM: Two 16-byte plus one packed 8-byte by-value args preserve the 0x28/s0-s3 hold set.
   Scalarized copy bursts color through v0,v1,a0,a1 while the allocation result is held in a2.
   A derived sp base with ASM_KEEP prevents packed tail loads folding from lwl/lwr pairs into lw;
   the paired tail source reads then also eliminate both downstream branch-displacement drifts. */
