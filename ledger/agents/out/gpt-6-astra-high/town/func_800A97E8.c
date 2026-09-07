#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A6F48_12 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800A6F48_12;   /* temp_v0_2 in func_800A6F48 */

typedef struct S_800A6F48_13 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800A6F48_13;   /* temp_v0_3 in func_800A6F48 */

typedef struct S_800A6F48_14 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800A6F48_14;   /* ((S_800A6F48_12 *)temp_v0_2)->unk_08 in func_800A6F48 */

typedef struct S_800A6F48_15 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800A6F48_15;   /* ((S_800A6F48_13 *)temp_v0_3)->unk_08 in func_800A6F48 */




void *func_800A75B8();                         /* extern */
M2C_UNK func_800ABD74();               /* extern */
extern M2C_UNK D_800A70EC;
extern M2C_UNK D_800D0DD8;

typedef struct S_800A6F48_0 {
    u8 pad_00[0xC];
    M2C_UNK * unk_0C;
} S_800A6F48_0;   /* arg1 in func_800A6F48 */

typedef struct S_800A6F48_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_800A6F48_1;   /* &D_800D0DD8 in func_800A6F48 */

typedef struct S_800A6F48_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800A6F48_2;   /* arg2 in func_800A6F48 */

typedef struct S_800A6F48_3 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_800A6F48_3;   /* temp_v1 in func_800A6F48 */

typedef struct S_800A6F48_4 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0xA4];
    s16 unk_B0;
} S_800A6F48_4;   /* temp_v0_2 in func_800A6F48 */

typedef struct S_800A6F48_5 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800A6F48_5;   /* temp_v1_2 in func_800A6F48 */

typedef struct S_800A6F48_6 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800A6F48_6;   /* temp_v1_3 in func_800A6F48 */

typedef struct S_800A6F48_7 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_800A6F48_7;   /* temp_v1_4 in func_800A6F48 */

typedef struct S_800A6F48_8 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0xA4];
    s16 unk_B0;
} S_800A6F48_8;   /* temp_v0_3 in func_800A6F48 */

typedef struct S_800A6F48_9 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800A6F48_9;   /* temp_v1_5 in func_800A6F48 */

typedef struct S_800A6F48_10 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x18];
    s16 unk_6C;
} S_800A6F48_10;   /* arg0 in func_800A6F48 */

typedef struct S_800A6F48_11 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_800A6F48_11;   /* arg3 in func_800A6F48 */

/* Creates two offset objects, adjusts their components, and initializes the owner and color. */
void func_800A6F48(S_800A6F48_10 *owner, S_800A6F48_0 *spawn_state, S_800A6F48_2 *origin, S_800A6F48_11 *color) {
    s32 position[5];
    M2C_UNK *offset_data;
    M2C_UNK *second_offset_data;
    s32 y_component;
    s32 z_component;
    u32 offset_sum;
    S_800A6F48_4 *first_object;
    register S_800A6F48_8 *second_object ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
    S_800A6F48_5 *first_y_data;
    S_800A6F48_6 *first_z_data;
    S_800A6F48_9 *second_y_data;

    spawn_state->unk_0C = &D_800D0DD8;
    offset_sum = ((S_800A6F48_1 *)(&D_800D0DD8))->unk_04 + ((S_800A6F48_1 *)(&D_800D0DD8))->unk_10;
    position[0] = origin->unk_00 + ((s32) (offset_sum + (offset_sum >> 0x1F)) >> 1);
    offset_data = spawn_state->unk_0C;
    position[1] = origin->unk_04 + ((S_800A6F48_3 *)offset_data)->unk_04 + ((S_800A6F48_3 *)offset_data)->unk_10;
    position[2] = origin->unk_08;
    first_object = func_800A75B8(position);
    ((S_800A6F48_14 *)(((S_800A6F48_12 *)first_object)->unk_08))->unk_0C = 0x10000;
    first_y_data = first_object->unk_08;
    y_component = first_y_data->unk_10;
    if (y_component < 0) {
        y_component += 3;
    }
    first_y_data->unk_10 = (s32) (y_component >> 2);
    first_z_data = first_object->unk_08;
    z_component = first_z_data->unk_14;
    if (z_component < 0) {
        z_component += 3;
    }
    first_z_data->unk_14 = (s32) (z_component >> 2);
    first_object->unk_B0 = 0;
    func_800ABD74(position, first_object);
    second_offset_data = spawn_state->unk_0C;
    position[0] = origin->unk_00 - ((((S_800A6F48_7 *)second_offset_data)->unk_04 + ((S_800A6F48_7 *)second_offset_data)->unk_10) / 3);
    second_object = func_800A75B8(position);
    ((S_800A6F48_15 *)(((S_800A6F48_13 *)second_object)->unk_08))->unk_0C = -0x8000;
    second_y_data = second_object->unk_08;
    second_y_data->unk_10 = (s32) (second_y_data->unk_10 / 3);
    second_object->unk_B0 = 0;
    func_800ABD74(position, second_object);
    owner->unk_50 = &D_800A70EC;
    owner->unk_6C = 0xA;
    color->unk_0E = 0x80;
    color->unk_0D = 0x80;
    color->unk_0C = 0x80;
}

/* MECHANISM: A five-word position array exposes all three initialized siblings and
   supplies the retail 0x40 frame; the four arguments naturally occupy s3/s0/s1/s2.
   A guarded $a1 pin holds the second factory result across its field updates, while
   unsigned byte lvalues preserve the retail li 0x80 before the final sb sequence. */
