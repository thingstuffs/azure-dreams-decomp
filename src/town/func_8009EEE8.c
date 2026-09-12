#include "common.h"
#include "m2c_compat.h"

typedef struct S_8009C648_6 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_8009C648_6;   /* temp_v0 in func_8009C648 */

typedef struct S_8009C648_7 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8009C648_7;   /* ((S_8009C648_6 *)temp_v0)->unk_0C in func_8009C648 */




extern s32 rand(void);
extern void *func_8009C390(void *, M2C_UNK, s32, s32);
extern void func_8009C46C(void *, void *, void *);
extern u8 D_80088D78[8];
extern M2C_UNK D_800D06C8[3];

typedef struct S_8009C648_0 {
    s32 unk_00;
    s32 unk_04;
} S_8009C648_0;   /* var_s4 in func_8009C648 */

typedef struct S_8009C648_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_8009C648_1;   /* temp_v0 in func_8009C648 */

typedef struct S_8009C648_2 {
    u8 pad_00[0x80];
    s32 unk_80;
} S_8009C648_2;   /* held_arg0 in func_8009C648 */

typedef struct S_8009C648_3 {
    u8 pad_00[0x60];
    s32 unk_60;
} S_8009C648_3;   /* temp_s1 in func_8009C648 */

typedef struct S_8009C648_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_8009C648_4;   /* temp_s0 in func_8009C648 */

typedef struct S_8009C648_5 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8009C648_5;   /* tail_s0 in func_8009C648 */

/* Spawns up to six parts with source-selected data and randomized motion. */
void func_8009C648(u8 *source_data, M2C_UNK spawn_arg) {
    s8 part_indices[6];
    s32 velocity_bias;
    M2C_UNK *part_params;
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
    ASM_KEEP(velocity_bias);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    part_params = D_800D06C8;
    source_object = (u8 *)source_data - 0x20;
spawn_part:
    part_object = func_8009C390(source_object, spawn_arg, ((S_8009C648_0 *)part_params)->unk_00, ((S_8009C648_0 *)part_params)->unk_04);
    if (part_object != NULL) {
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
        source_object = (u8 *)source_data - 0x20;
        if (part_index < 6) {
            goto spawn_part;
        }
    }
}
