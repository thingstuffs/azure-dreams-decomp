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
    s32 field_04_value,
    s32 field_00_value,
    s16 paired_value,
    s16 x_offset,
    s16 y_offset,
    s32 z_offset)
{
    S_func_8187B8B0_0 *source_obj = source;
    s16 saved_field_04 = field_04_value;
    u32 saved_field_00 = field_00_value;
    s16 saved_pair ;
    s32 saved_z_offset = z_offset;
    S_func_8187B8B0_0 *spawned_obj;
    S_func_8187B8B0_3 *actor_data;
    s32 y_jitter;
    s32 z_jitter;
    s16 x_bias;
    s16 y_bias;
    s32 z_bias;
    s16 x_pos;
    s16 y_pos;
    s32 z_pos;
    void *init_obj;
    void *init_data;
    S_func_8187B8B0_2 *x_dest;
    S_func_8187B8B0_2 *y_dest;
    S_func_8187B8B0_2 *z_dest;

    spawned_obj = func_8003FD64(0x211, source_obj);
    if (spawned_obj != NULL) {
        saved_pair = paired_value;
        spawned_obj->unk_10 = (s32)&D_80024FF0;
        z_offset = rand() & 0x1F;
        x_pos = ((S_func_8187B8B0_1 *)source_obj->unk_08)->unk_02;
        x_dest = spawned_obj->unk_08;
        x_pos += z_offset;
        x_bias = x_offset - 0x10;
        x_pos += x_bias;
        x_dest->unk_02 = (s16)x_pos;

        y_jitter = rand() & 0x1F;
        y_pos = ((S_func_8187B8B0_1 *)source_obj->unk_08)->unk_06;
        y_dest = spawned_obj->unk_08;
        y_pos += y_jitter;
        y_bias = y_offset - 0x10;
        y_pos += y_bias;
        y_dest->unk_06 = (s16)y_pos;

        z_jitter = rand();
        init_obj = spawned_obj;
        init_data = &D_80024DA0;
        z_jitter &= 0x1F;
        z_pos = ((S_func_8187B8B0_1 *)source_obj->unk_08)->unk_0A;
        actor_data = (S_func_8187B8B0_3 *)((u8 *)spawned_obj + 0x20);
        z_dest = spawned_obj->unk_08;
        z_pos += z_jitter;
        z_bias = saved_z_offset - 0x10;
        z_pos += z_bias;
        z_dest->unk_0A = (s16)z_pos;
        actor_data->unk_04 = saved_field_04;
        actor_data->unk_10 = saved_pair;
        actor_data->unk_12 = saved_pair;
        func_8004491C(init_obj, init_data, z_dest);
        actor_data->unk_B4 = rand() + 0x10000;
        spawned_obj->unk_20 = saved_field_00;
    }
}

