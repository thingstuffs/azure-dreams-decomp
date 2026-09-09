#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_func_8187B8B0_0 {
    u8 pad_00[0x08];
    void *unk_08;
    u8 pad_0C[0x04];
    s32 unk_10;
    u8 pad_14[0x0C];
    s32 unk_20;
} S_func_8187B8B0_0;

typedef struct S_func_8187B8B0_1 {
    u8 pad_00[0x02];
    u16 unk_02;
    u8 pad_04[0x02];
    u16 unk_06;
    u8 pad_08[0x02];
    u16 unk_0A;
} S_func_8187B8B0_1;

typedef struct S_func_8187B8B0_2 {
    u8 pad_00[0x02];
    s16 unk_02;
    u8 pad_04[0x02];
    s16 unk_06;
    u8 pad_08[0x02];
    s16 unk_0A;
} S_func_8187B8B0_2;

typedef struct S_func_8187B8B0_3 {
    u8 pad_00[0x04];
    s16 unk_04;
    u8 pad_06[0x0A];
    s16 unk_10;
    s16 unk_12;
    u8 pad_14[0xA0];
    s32 unk_B4;
} S_func_8187B8B0_3;

extern void *func_8003FD64();
extern s32 func_8004491C();
extern s32 rand();
extern s32 D_80024DA0;
extern s32 D_80024FF0;

/* Creates an object at a randomized offset from the source and initializes its actor data. */
void func_8187B8B0(
    void *source,
    s16 field_04_value,
    s32 field_00_value,
    s16 paired_value,
    s32 x_offset,
    s32 y_offset,
    s32 z_offset)
{
    s32 saved_x_offset = x_offset;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    S_func_8187B8B0_0 *source_obj = source;
    register s16 saved_field_04 ASM_REG("$22") = field_04_value;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 saved_field_00 ASM_REG("$23") = field_00_value;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s16 saved_pair ASM_REG("$20") = paired_value;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s32 saved_y_offset = y_offset;
    s32 saved_z_offset = z_offset;
    S_func_8187B8B0_0 *spawned_obj;
    S_func_8187B8B0_3 *actor_data;
    s32 x_jitter;
    s32 y_jitter;
    s32 z_jitter;
    s32 x_bias;
    s32 y_bias;
    s32 z_bias;
    s32 x_pos;
    s32 y_pos;
    s32 z_pos;
    register void *init_obj ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *init_data;
    S_func_8187B8B0_2 *x_dest;
    S_func_8187B8B0_2 *y_dest;
    S_func_8187B8B0_2 *z_dest;

    spawned_obj = func_8003FD64(0x211, source_obj);
    if (spawned_obj != NULL) {
        spawned_obj->unk_10 = (s32)&D_80024FF0;
        x_jitter = rand() & 0x1F;
        x_pos = ((S_func_8187B8B0_1 *)source_obj->unk_08)->unk_02;
        x_dest = spawned_obj->unk_08;
        x_pos += x_jitter;
        x_bias = saved_x_offset - 0x10;
        x_pos += x_bias;
        x_dest->unk_02 = (s16)x_pos;

        y_jitter = rand() & 0x1F;
        y_pos = ((S_func_8187B8B0_1 *)source_obj->unk_08)->unk_06;
        y_dest = spawned_obj->unk_08;
        y_pos += y_jitter;
        y_bias = saved_y_offset - 0x10;
        y_pos += y_bias;
        y_dest->unk_06 = (s16)y_pos;

        z_jitter = rand();
        init_obj = spawned_obj;
        init_data = &D_80024DA0;
        ASM_USE2(init_obj, init_data);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        z_jitter &= 0x1F;
        z_pos = ((S_func_8187B8B0_1 *)source_obj->unk_08)->unk_0A;
        actor_data = (S_func_8187B8B0_3 *)((u8 *)spawned_obj + 0x20);
        z_dest = spawned_obj->unk_08;
        z_pos += z_jitter;
        z_bias = saved_z_offset - 0x10;
        z_pos += z_bias;
        z_dest->unk_0A = (s16)z_pos;
        ASM_KEEP(saved_x_offset);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(saved_y_offset);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(saved_z_offset);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        actor_data->unk_04 = saved_field_04;
        ASM_KEEP(saved_field_04);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        actor_data->unk_10 = saved_pair;
        actor_data->unk_12 = saved_pair;
        func_8004491C(init_obj, init_data, z_dest);
        ASM_KEEP(saved_pair);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        actor_data->unk_B4 = rand() + 0x10000;
        spawned_obj->unk_20 = saved_field_00;
        ASM_KEEP(saved_field_00);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    }
}

