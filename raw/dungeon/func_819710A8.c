/* Selector 59, retail file [0x19910A8, 0x19911E0); complete callable clone. */
#include "common.h"
#include "modules/dungeon_native_abi.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_func_800248A8_1 {
    u8 pad_00[0x8];
    void *unk_08;
} S_func_800248A8_1;

typedef struct S_func_800248A8_2 {
    u8 pad_00[0x8];
    void *unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_func_800248A8_2;

typedef struct S_func_800248A8_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_func_800248A8_3;

typedef struct S_func_800248A8_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_func_800248A8_4;

typedef struct S_func_800248A8_5 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    s16 unk_34;
    u8 pad_36[0x12];
    s32 unk_48;
} S_func_800248A8_5;

extern s32 rand();
extern s32 func_80024598(u8 *, u8 *);
extern void func_800247E8(void *, s16 *);

static __inline__ S_func_800248A8_2 *effect_offset_32(void *p) {
    return (S_func_800248A8_2 *)((u8 *)p + 0x20);
}

/* Spawn and initialize an effect at a randomly offset position relative to the source. */
void func_800248A8(
    void *source,
    s32 property_34,
    s32 property_28,
    s16 property_52,
    s16 x_offset,
    s16 y_offset,
    s16 z_offset)
{
    S_func_800248A8_1 *source_obj = source;
    S_func_800248A8_2 *effect_ptr;
    S_func_800248A8_2 *effect_obj;
    u16 jitter;
    u16 effect_pos;

    effect_ptr = (S_func_800248A8_2 *)func_8003FD64(0x211, (ObjectNodeHeader **)source_obj);
    if (effect_ptr != NULL) {
        effect_ptr->unk_10 = (s32)func_800247E8;
        jitter = rand() & 0x1F;
        effect_pos = ((S_func_800248A8_3 *)source_obj->unk_08)->unk_02 + jitter;
        effect_pos += x_offset - 0x10;
        ((S_func_800248A8_4 *)effect_ptr->unk_08)->unk_02 = effect_pos;

        jitter = rand() & 0x1F;
        effect_pos = ((S_func_800248A8_3 *)source_obj->unk_08)->unk_06 + jitter;
        effect_pos += y_offset - 0x10;
        ((S_func_800248A8_4 *)effect_ptr->unk_08)->unk_06 = effect_pos;

        jitter = rand() & 0x1F;
        effect_obj = effect_ptr;
        effect_ptr = effect_offset_32(effect_obj);
        effect_pos = ((S_func_800248A8_3 *)source_obj->unk_08)->unk_0A + jitter;
        effect_pos += z_offset - 0x10;
        ((S_func_800248A8_4 *)effect_obj->unk_08)->unk_0A = effect_pos;
        ((S_func_800248A8_5 *)effect_ptr)->unk_14 = property_34;
        ((S_func_800248A8_5 *)effect_ptr)->unk_32 = property_52;
        ((S_func_800248A8_5 *)effect_ptr)->unk_34 = property_52;
        func_8004491C(effect_obj, (s32)func_80024598);
        ((S_func_800248A8_5 *)effect_ptr)->unk_48 = rand() + 0x10000;
        ((S_func_800248A8_5 *)effect_ptr)->unk_08 = property_28;
    }
}
