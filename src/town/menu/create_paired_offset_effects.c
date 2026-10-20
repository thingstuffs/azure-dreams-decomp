#include "common.h"
#include "m2c_compat.h"
#include "shared/object_payload.h"
#include "shared/vector.h"


typedef struct S_800A6F48_14 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800A6F48_14;

typedef struct S_800A6F48_15 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800A6F48_15;


void *create_preset_sprite_object();                         /* extern */
void spawn_person_radial_effects();               /* extern */
extern M2C_UNK D_800A70EC;
extern M2C_UNK D_800D0DD8;

typedef struct S_800A6F48_0 {
    u8 pad_00[0xC];
    s32 * unk_0C;
} S_800A6F48_0;   /* arg1 in create_paired_offset_effects */

typedef struct S_800A6F48_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_800A6F48_1;   /* &D_800D0DD8 in create_paired_offset_effects */

   /* arg2 in create_paired_offset_effects */

typedef struct S_800A6F48_3 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_800A6F48_3;

typedef struct S_800A6F48_4 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0xA4];
    s16 unk_B0;
} S_800A6F48_4;

typedef struct S_800A6F48_5 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800A6F48_5;

typedef struct S_800A6F48_6 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800A6F48_6;

typedef struct S_800A6F48_7 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_800A6F48_7;

typedef struct S_800A6F48_8 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0xA4];
    s16 unk_B0;
} S_800A6F48_8;

typedef struct S_800A6F48_9 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800A6F48_9;

typedef struct S_800A6F48_10 {
    u8 pad_00[0x50];
    s32 * unk_50;
    u8 pad_54[0x18];
    s16 unk_6C;
} S_800A6F48_10;   /* arg0 in create_paired_offset_effects */

typedef struct S_800A6F48_11 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_800A6F48_11;   /* arg3 in create_paired_offset_effects */

/* Creates two offset objects, adjusts their components, and initializes the owner and color. */
void create_paired_offset_effects(S_800A6F48_10 *owner, S_800A6F48_0 *spawn_state, IntVector3 *origin, S_800A6F48_11 *color) {
    s32 position[5];
    s32 *offset_data;
    s32 *second_offset_data;
    s32 y_component;
    s32 z_component;
    u32 offset_sum;
    S_800A6F48_4 *first_object;
    S_800A6F48_5 *first_y_data;
    S_800A6F48_6 *first_z_data;
    S_800A6F48_9 *second_y_data;

    spawn_state->unk_0C = &D_800D0DD8;
    offset_sum = ((S_800A6F48_1 *)(&D_800D0DD8))->unk_04 + ((S_800A6F48_1 *)(&D_800D0DD8))->unk_10;
    position[0] = origin->x + ((s32) (offset_sum + (offset_sum >> 0x1F)) >> 1);
    offset_data = spawn_state->unk_0C;
    position[1] = origin->y + ((S_800A6F48_3 *)offset_data)->unk_04 + ((S_800A6F48_3 *)offset_data)->unk_10;
    position[2] = origin->z;
    first_object = create_preset_sprite_object(position);
    ((S_800A6F48_14 *)(((ObjectPayloadView *)first_object)->unk_08))->unk_0C = 0x10000;
    first_y_data = first_object->unk_08;
    y_component = first_y_data->unk_10;
    first_y_data->unk_10 = (s32) (y_component / 4);
    first_z_data = first_object->unk_08;
    z_component = first_z_data->unk_14;
    first_z_data->unk_14 = (s32) (z_component / 4);
    first_object->unk_B0 = 0;
    spawn_person_radial_effects(position);
    second_offset_data = spawn_state->unk_0C;
    position[0] = origin->x - ((((S_800A6F48_7 *)second_offset_data)->unk_04
        + ((S_800A6F48_7 *)second_offset_data)->unk_10) / 3);
    first_object = create_preset_sprite_object(position);
    ((S_800A6F48_15 *)(((ObjectPayloadView *)first_object)->unk_08))->unk_0C = -0x8000;
    second_y_data = first_object->unk_08;
    second_y_data->unk_10 = (s32) (second_y_data->unk_10 / 3);
    first_object->unk_B0 = 0;
    spawn_person_radial_effects(position);
    owner->unk_50 = &D_800A70EC;
    owner->unk_6C = 0xA;
    color->unk_0E = 0x80;
    color->unk_0D = 0x80;
    color->unk_0C = 0x80;
}

/* MECHANISM: A five-word position array exposes all three initialized siblings and supplies the retail
   0x40 frame; the four arguments naturally occupy s3/s0/s1/s2. */
