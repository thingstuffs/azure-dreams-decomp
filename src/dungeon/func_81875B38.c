#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_func_81875B38_1 {
    u8 pad_00[0x8];
    void *unk_08;
} S_func_81875B38_1;

typedef struct S_func_81875B38_2 {
    u8 pad_00[0x8];
    void *unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_func_81875B38_2;

typedef struct S_func_81875B38_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_func_81875B38_3;

typedef struct S_func_81875B38_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_func_81875B38_4;

typedef struct S_func_81875B38_5 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    s16 unk_34;
    u8 pad_36[0x12];
    s32 unk_48;
} S_func_81875B38_5;

extern void *func_8003FD64();
extern s32 func_8004491C();
extern s32 rand();
extern s32 D_80025028;
extern s32 D_80025278;

static __inline__ S_func_81875B38_2 *effect_offset_32(void *p) {
    return (S_func_81875B38_2 *)((u8 *)p + 0x20);
}

/* Spawn and initialize an effect at a randomly offset position relative to the source. */
void func_81875B38(
    void *source,
    s32 property_34,
    s32 property_28,
    s16 property_52,
    s16 x_offset,
    s16 y_offset,
    s16 z_offset)
{
    S_func_81875B38_1 *source_obj = source;
    S_func_81875B38_2 *effect_ptr;
    S_func_81875B38_2 *effect_obj;
    u16 jitter;
    u16 effect_pos;

    effect_ptr = func_8003FD64(0x211, source_obj);
    if (effect_ptr != NULL) {
        effect_ptr->unk_10 = (s32)&D_80025278;
        jitter = rand() & 0x1F;
        effect_pos = ((S_func_81875B38_3 *)source_obj->unk_08)->unk_02 + jitter;
        effect_pos += x_offset - 0x10;
        ((S_func_81875B38_4 *)effect_ptr->unk_08)->unk_02 = effect_pos;

        jitter = rand() & 0x1F;
        effect_pos = ((S_func_81875B38_3 *)source_obj->unk_08)->unk_06 + jitter;
        effect_pos += y_offset - 0x10;
        ((S_func_81875B38_4 *)effect_ptr->unk_08)->unk_06 = effect_pos;

        jitter = rand() & 0x1F;
        effect_obj = effect_ptr;
        effect_ptr = effect_offset_32(effect_obj);
        effect_pos = ((S_func_81875B38_3 *)source_obj->unk_08)->unk_0A + jitter;
        effect_pos += z_offset - 0x10;
        ((S_func_81875B38_4 *)effect_obj->unk_08)->unk_0A = effect_pos;
        ((S_func_81875B38_5 *)effect_ptr)->unk_14 = property_34;
        ((S_func_81875B38_5 *)effect_ptr)->unk_32 = property_52;
        ((S_func_81875B38_5 *)effect_ptr)->unk_34 = property_52;
        func_8004491C(effect_obj, &D_80025028);
        ((S_func_81875B38_5 *)effect_ptr)->unk_48 = rand() + 0x10000;
        ((S_func_81875B38_5 *)effect_ptr)->unk_08 = property_28;
    }
}
