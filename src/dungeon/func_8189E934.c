#include "common.h"



#ifndef NULL
#define NULL 0
#endif

typedef struct Input6 {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
    s32 w4;
    s32 w5;
} Input6;

typedef struct Tail {
    s16 pad0;
    s16 arg2;
    s32 copy;
    s32 arg0;
} Tail;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern u8 D_80045340[];
extern u8 D_80024020[];
extern u8 D_80024C78[];


void *func_8003FC64(u32);
void func_8004491C(void *, u8 *);
s32 rand(void);

typedef struct S_80024134_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s16 unk_20;
} S_80024134_0;   /* temp_v0 in func_80024134 */

typedef struct S_80024134_1 {
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
} S_80024134_1;   /* temp_s0 in func_80024134 */

/* Allocates an object, initializes its display data, and copies the input state. */
s32 func_80024134(s32 stored_value, void *input, s16 stored_tag) {
    s32 random_or_w2;
    s32 rounded_random;
    void *object;
    Tail *state;
    S_80024134_1 *display;
    void *input_copy;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        state = (Tail *)((s8 *)object + 0x20);
        ((S_80024134_0 *)object)->unk_10 = D_80024020;
        state->arg0 = stored_value;
        ((S_80024134_0 *)object)->unk_20 = 0;
        state->arg2 = stored_tag;
        display = ((S_80024134_0 *)object)->unk_0C;
        display->unk_0E = 0x80;
        display->unk_0D = 0x80;
        display->unk_0C = 0x80;
        display->unk_08 = D_80024C78;
        display->unk_12 = 0x7E02;
        display->unk_14 = (u16) (display->unk_14 | 0x100);
        rounded_random = rand();
        random_or_w2 = rounded_random;
        if (random_or_w2 < 0) {
            rounded_random = random_or_w2 + 0xFFF;
        }
        display->unk_1A = (s16) (random_or_w2 - ((rounded_random >> 0xC) << 0xC));
        display->unk_1E = 0x800;
        display->unk_1C = 0x800;
        func_8004491C(object, D_80045340);
        input_copy = ((S_80024134_0 *)object)->unk_08;
        *(Input6 *)input_copy = *(Input6 *)input;
        random_or_w2 = *(volatile s32 *)((s8 *)input_copy + 8);
        state->copy = random_or_w2;
        return (s32)object;
    }
    return 0;
}
