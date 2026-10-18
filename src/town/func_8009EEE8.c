#include "common.h"
#include "m2c_compat.h"

typedef struct S_8009C648_6 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_8009C648_6;

typedef struct S_8009C648_7 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8009C648_7;


extern s32 rand(void);
typedef struct S_8009C390_3 S_8009C390_3;
void * create_town_effect_object(s32 parent, S_8009C390_3 *position, s32 object_value, s32 state_value);
extern void func_8009C46C(void *, void *, void *);
extern u8 D_80088D78[8];
extern M2C_UNK D_800D06C8[3];

typedef struct S_8009C648_0 {
    s32 unk_00;
    s32 unk_04;
} S_8009C648_0;

typedef struct S_8009C648_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_8009C648_1;

typedef struct S_8009C648_2 {
    u8 pad_00[0x80];
    s32 unk_80;
} S_8009C648_2;   /* held_arg0 in spawn_randomized_effect_parts */

typedef struct S_8009C648_3 {
    u8 pad_00[0x60];
    s32 unk_60;
} S_8009C648_3;

typedef struct S_8009C648_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_8009C648_4;

typedef struct S_8009C648_5 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8009C648_5;   /* tail_s0 in spawn_randomized_effect_parts */

/* Spawns up to six parts with source-selected data and randomized motion. */
void spawn_randomized_effect_parts(u8 *source_data, s32 spawn_arg) {
    s8 part_indices[6];
    s32 velocity_bias;
    s32 *part_params;
    s32 part_index;
    S_8009C648_4 *velocity;
    S_8009C648_3 *part_data;
    void *part_object;
    void *source_object;
    s32 random_z;
    S_8009C648_5 *motion;

    memcpy(part_indices, D_80088D78, 6);
    part_index = 0;
    velocity_bias = 0xFFFC0000;
    part_params = D_800D06C8;
    do {
        source_object = (u8 *)source_data - 0x20;
        part_object = create_town_effect_object(source_object, spawn_arg, ((S_8009C648_0 *)part_params)->unk_00,
            ((S_8009C648_0 *)part_params)->unk_04);
        if (part_object == NULL) {
            break;
        }
        velocity = ((S_8009C648_1 *)part_object)->unk_08;
        part_data = (u8 *)part_object + 0x20;
        ((S_8009C648_7 *)(((S_8009C648_6 *)part_object)->unk_0C))->unk_08 =
            ((s32 *)((S_8009C648_2 *)source_data)->unk_80)[part_indices[part_index]];
        part_data->unk_60 = part_index;
        velocity->unk_0C = (s32)((rand() * 0x10) + velocity_bias);
        velocity->unk_10 = (s32)((rand() * 0x10) + velocity_bias);
        random_z = rand();
        motion = velocity;
        part_params += 2;
        motion->unk_14 = (s32)(0xFFF00000 - (random_z * 0x10));
        motion->unk_00 =
            (s32)(motion->unk_00 + (motion->unk_0C * 8));
        motion->unk_04 =
            (s32)(motion->unk_04 + (motion->unk_10 * 8));
        func_8009C46C(part_data, motion, ((S_8009C648_1 *)part_object)->unk_0C);
        part_index += 1;
    } while (part_index < 6);
}
