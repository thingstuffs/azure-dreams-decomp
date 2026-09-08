#include "common.h"



#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_800256A0() __attribute__((noreturn));
extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern s32 rand();
extern M2C_UNK D_800254E0;
extern M2C_UNK D_80025DF8;
extern M2C_UNK D_80045340;

typedef struct S_818BDD8C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_818BDD8C_0;   /* temp_v0 in func_818BDD8C */

typedef struct S_818BDD8C_1 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_818BDD8C_1;   /* temp_v1 in func_818BDD8C */

typedef struct S_818BDD8C_2 {
    u8 pad_00[0x12];
    u16 unk_12;
} S_818BDD8C_2;   /* arg0 in func_818BDD8C */

typedef struct S_818BDD8C_3 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
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
} S_818BDD8C_3;   /* temp_s0 in func_818BDD8C */

typedef struct S_818BDD8C_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818BDD8C_4;   /* arg1 in func_818BDD8C */

typedef struct S_818BDD8C_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818BDD8C_5;   /* temp_v1_4 in func_818BDD8C */

/* Creates an object with its owner, rendering parameters, and supplied data. */
void *func_818BDD8C(S_818BDD8C_2 *owner, S_818BDD8C_4 *initial_data)
{
    s32 copy_word_0;
    s32 copy_word_1;
    s32 copy_word_2;
    s32 copy_word_3;
    s32 draw_flags;
    register s32 render_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    S_818BDD8C_3 *render;
    void *object;
    S_818BDD8C_1 *state;
    S_818BDD8C_5 *object_data;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        state = object + 0x20;
        ((S_818BDD8C_0 *)object)->unk_10 = &D_800254E0;
        ((S_818BDD8C_0 *)object)->unk_20 = owner;
        state->unk_10 = 0;
        state->unk_14 = (u16)owner->unk_12;
        render = ((S_818BDD8C_0 *)object)->unk_0C;
        render->unk_0E = 0x80;
        render->unk_0D = 0x80;
        render->unk_0C = 0x80;
        render->unk_12 = 0x7E01;
        render->unk_08 = &D_80025DF8;
        render_flags = render->unk_14 | 0xC;
        draw_flags = render->unk_10 | 0x20;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        render->unk_14 = render_flags;
        render_flags |= 0x100;
        render->unk_10 = draw_flags;
        render->unk_14 = render_flags;
        {
            register void *call_obj ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 scale;

            render->unk_1A = (s16)(rand() % 0x1000);
            call_obj = object;
            scale = 0x400;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            render->unk_1E = scale;
            render->unk_1C = scale;
            func_8004491C(call_obj, &D_80045340);
        }
        object_data = ((S_818BDD8C_0 *)object)->unk_08;
        ASM_KEEP(object_data);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        {
            register void *pinned_object ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
            pinned_object = object;
            ASM_KEEP(pinned_object);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        }
        copy_word_0 = initial_data->unk_00;
        copy_word_1 = initial_data->unk_04;
        copy_word_2 = initial_data->unk_08;
        copy_word_3 = initial_data->unk_0C;
        object_data->unk_00 = copy_word_0;
        object_data->unk_04 = copy_word_1;
        object_data->unk_08 = copy_word_2;
        object_data->unk_0C = copy_word_3;
        copy_word_0 = initial_data->unk_10;
        copy_word_1 = initial_data->unk_14;
        object_data->unk_10 = copy_word_0;
        object_data->unk_14 = copy_word_1;
        func_800256A0(copy_word_0, copy_word_1, copy_word_2, copy_word_3);
    }
    return 0;
}

/* MECHANISM: The natural 0x20 frame holds owner/object/initial_data in s0/s1/s2.
   A v1 flags accumulator plus a separate v0 flags word prevents OR fusion;
   pinned a0/v0 lifetimes and a fence place li before the callback la pair,
   while the kept destination and v0 result preserve the retail tail ABI. */
