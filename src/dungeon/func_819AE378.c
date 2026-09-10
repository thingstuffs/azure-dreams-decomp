#include "common.h"



#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

typedef struct UnalignedWord {
    u32 value;
} __attribute__((packed)) UnalignedWord;

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_UNALIGNED32(expr) (expr)

extern void *func_8003FC64(s32);
extern s32 func_8004491C(void *, void *);
extern M2C_UNK D_80025A34;
extern M2C_UNK D_80025AAC;

typedef struct S_80025B78_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80025B78_0;   /* temp_v0 in func_80025B78 */

typedef struct S_80025B78_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80025B78_1;   /* temp_v1 in func_80025B78 */

typedef struct S_80025B78_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80025B78_2;   /* arg1 in func_80025B78 */

typedef struct S_80025B78_3 {
    s32 unk_00;
    u8 unk_04;
    u8 pad_05[0x3];
    s32 unk_08;
    s32 unk_0C;
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
} S_80025B78_3;   /* temp_v1_2 in func_80025B78 */

typedef struct S_80025B78_4 {
    s32 unk_00;
    u8 unk_04;
    u8 pad_05[0x3];
    s32 unk_08;
    s32 unk_0C;
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
} S_80025B78_4;   /* arg2 in func_80025B78 */

/* Creates an object and copies the supplied triplet, state fields, and 32-byte data block. */
void *func_80025B78(void *source_data, S_80025B78_2 *source_triplet, S_80025B78_4 *source_state)
{
    void *object;
    S_80025B78_1 *triplet;
    S_80025B78_3 *state;

    object = func_8003FC64(0x202);
    if (object != NULL) {
        ((S_80025B78_0 *)object)->unk_10 = &D_80025A34;
        func_8004491C(object, &D_80025AAC);
        triplet = ((S_80025B78_0 *)object)->unk_08;
        do {
            triplet->unk_02 = source_triplet->unk_02;
        } while (0);
        triplet->unk_06 = source_triplet->unk_06;
        triplet->unk_0A = source_triplet->unk_0A;
        state = ((S_80025B78_0 *)object)->unk_0C;
        state->unk_1C = source_state->unk_1C;
        state->unk_1E = source_state->unk_1E;
        state->unk_20 = source_state->unk_20;
        state->unk_16 = source_state->unk_16;
        state->unk_18 = source_state->unk_18;
        state->unk_1A = source_state->unk_1A;
        state->unk_0C = source_state->unk_0C;
        state->unk_14 = source_state->unk_14;
        state->unk_00 = source_state->unk_00;
        state->unk_08 = source_state->unk_08;
        state->unk_10 = source_state->unk_10;
        state->unk_04 = source_state->unk_04;
        {
            u32 word_0;
            u32 word_1;
            u32 word_2;
            register u32 word_3;

            word_0 = ((UnalignedWord *)source_data)[0].value;
            word_1 = ((UnalignedWord *)source_data)[1].value;
            word_2 = ((UnalignedWord *)source_data)[2].value;
            word_3 = ((UnalignedWord *)source_data)[3].value;
            ((UnalignedWord *)((u8 *)object + 0x20))[0].value = word_0;
            ((UnalignedWord *)((u8 *)object + 0x20))[1].value = word_1;
            ((UnalignedWord *)((u8 *)object + 0x20))[2].value = word_2;
            ((UnalignedWord *)((u8 *)object + 0x20))[3].value = word_3;
            word_0 = ((UnalignedWord *)source_data)[4].value;
            word_1 = ((UnalignedWord *)source_data)[5].value;
            word_2 = ((UnalignedWord *)source_data)[6].value;
            word_3 = ((UnalignedWord *)source_data)[7].value;
            ((UnalignedWord *)((u8 *)object + 0x20))[4].value = word_0;
            ((UnalignedWord *)((u8 *)object + 0x20))[5].value = word_1;
            ((UnalignedWord *)((u8 *)object + 0x20))[6].value = word_2;
            ((UnalignedWord *)((u8 *)object + 0x20))[7].value = word_3;
        }
    }
    return object;
}
