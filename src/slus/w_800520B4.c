#include "common.h"

#include "common.h"

typedef struct S_800520B4_Sub {
    void *field_0x00;
    s16 field_0x04;
    s16 field_0x06;
    u8 pad_0x08[2];
    s16 field_0x0A;
    s16 field_0x0C;
} S_800520B4_Sub;

typedef struct S_800520B4_Ptr {
    u8 pad_0x00[8];
    void *field_0x08;
    s32 field_0x0C;
    u8 pad_0x10[0xC];
    s16 field_0x1C;
    s16 field_0x1E;
} S_800520B4_Ptr;

typedef struct S_800520B4_Vec {
    s32 field_0x00;
    s32 field_0x04;
    s32 field_0x08;
} S_800520B4_Vec;

typedef struct S_800520B4 {
    u8 pad_0x00[8];
    S_800520B4_Vec *vec;
    S_800520B4_Ptr *ptr;
    void (*update_func)(void);
    u8 pad_0x14[0xC];
    S_800520B4_Sub sub;
} S_800520B4;

extern u8 D_80071FF0[0x10];
extern void func_80051F58(void);
extern void func_80044BB0(void);
extern void func_8004491C(S_800520B4 *a0, void (*a1)(void));

/* Initialize object state, callbacks, settings, and vector values. */
void func_800520B4(S_800520B4 *object, void *context)
{
    s16 *state_words;
    S_800520B4_Ptr *settings;
    S_800520B4_Vec *vector;

    object->update_func = func_80051F58;
    state_words = (s16 *)((u8 *)object + 0x20);
    object->sub.field_0x00 = context;
    state_words[2] = 0;
    state_words[3] = 0;
    state_words[5] = 0;
    state_words[6] = 0;

    settings = object->ptr;
    settings->field_0x08 = D_80071FF0;
    settings->field_0x0C = 0;
    settings->field_0x1E = 0x1000;
    settings->field_0x1C = 0x1000;

    func_8004491C(object, func_80044BB0);

    vector = object->vec;
    vector->field_0x00 = 0x980000;
    vector->field_0x04 = 0x800000;
    vector->field_0x08 = 0xA00000;
}
