#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_80173DD4_arg0.h"

typedef struct S_80175060_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80175060_0;   /* temp_v0 in func_80175060 */

typedef struct S_80175060_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x2];
    s16 unk_08;
    u8 pad_0A[0x2];
    s32 unk_0C;
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80175060_1;   /* temp_s0 in func_80175060 */


typedef struct S_80175060_3 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80175060_3;   /* temp_v1_2 in func_80175060 */



void func_8003DB94(void *, void *, s32);  /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_800478B8();                      /* extern */
s32 rand();                                /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DEA68;
extern M2C_UNK D_80174F64;

/* Creates an object with randomized phase and rotation and copies its initial state. */
s32 func_80175060(Rec_func_80173DD4_arg0 *owner, Rec_D_800E3D7C *initial_state) {
    s32 color;
    s32 four;
    s32 phase_rand;
    s32 rotation_rand;
    s32 biased_phase;
    s32 biased_rotation;
    S_80175060_1 *part;
    void *object;
    S_80175060_3 *state;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        ((S_80175060_0 *)object)->unk_10 = &D_80174F64;
        biased_phase = rand();
        phase_rand = biased_phase;
        part = object + 0x20;
        if (phase_rand < 0) {
            biased_phase = phase_rand + 0xFFF;
        }
        color = 0x606060;
        part->unk_04 = (s16) (phase_rand - ((biased_phase >> 0xC) << 0xC));
        four = 4;
        ASM_KEEP(four);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        part->unk_08 = (s16) four;
        part = ((S_80175060_0 *)object)->unk_0C;
        part->unk_0C = color;
        part->unk_14 = (u16) (part->unk_14 | 0xC);
        part->unk_10 = (u16) (part->unk_10 | 0x20);
        func_8003DB94(part, &D_800DEA68, 0);
        func_800478B8(part);
        biased_rotation = rand();
        rotation_rand = biased_rotation;
        if (rotation_rand < 0) {
            biased_rotation = rotation_rand + 0xFFF;
        }
        part->unk_1A = (s16) (rotation_rand - ((biased_rotation >> 0xC) << 0xC));
        part->unk_1E = 0x1000;
        part->unk_1C = 0x1000;
        func_8004491C(object, &D_80045340);
        {
            s32 copy_word_0;
            s32 copy_word_1;
            register s32 copy_word_2 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            register s32 copy_word_3 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

            state = ((S_80175060_0 *)object)->unk_08;
            ASM_KEEP(state);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            copy_word_0 = initial_state->unk_00.at00_s32.v;
            copy_word_1 = initial_state->unk_04.at00_s32.v;
            copy_word_2 = initial_state->unk_08.at00_s32.v;
            copy_word_3 = initial_state->unk_0C.as_s32;
            state->unk_00 = copy_word_0;
            state->unk_04 = copy_word_1;
            state->unk_08.at00.v = copy_word_2;
            state->unk_0C = copy_word_3;
            copy_word_0 = initial_state->unk_10.at00_s32.v;
            copy_word_1 = initial_state->unk_14.as_s32;
            state->unk_10 = copy_word_0;
            state->unk_14 = copy_word_1;
            ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            copy_word_0 = state->unk_00;
            copy_word_1 = state->unk_04;
            state->unk_0C = copy_word_0;
            state->unk_10 = copy_word_1;
        }
        state->unk_08.at02.v = owner->unk_88;
        return (s32) object;
    }
    return 0;
}
