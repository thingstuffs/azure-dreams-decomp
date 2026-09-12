#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
s32 rand();                                 /* extern */
extern M2C_UNK D_80170CEC;
extern M2C_UNK D_80170E2C;

typedef struct S_80171790_0 {
    u8 pad_00[0x1];
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x15];
    s16 unk_18;
    s16 unk_1A;
    u8 pad_1C[0x3C];
    s16 unk_58;
    s16 unk_5A;
    s16 unk_5C;
    s16 unk_5E;
    s16 unk_60;
    s16 unk_62;
} S_80171790_0;   /* saved_tail in func_80171790 */

typedef struct S_80171790_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    u8 unk_20;
} S_80171790_1;   /* (void *) saved_obj_angle in func_80171790 */

typedef struct S_80171790_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80171790_2;   /* (void *) saved_data_scale in func_80171790 */

typedef struct S_80171790_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80171790_3;   /* copy_dst in func_80171790 */

typedef struct S_80171790_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80171790_4;   /* saved_arg1 in func_80171790 */

typedef struct S_80171790_5 {
    u8 pad_00[0xAE];
    s16 unk_AE;
} S_80171790_5;   /* saved_arg0 in func_80171790 */

/* Creates an effect at an offset position with randomized attributes and motion. */
void func_80171790(void *source, void *position) {
    S_80171790_5 *source_obj;
    S_80171790_4 *source_pos;
    s32 obj_or_angle;
    s32 data_or_speed;
    S_80171790_0 *effect_state;
    void *init_obj;
    S_80171790_3 *effect_pos;
    u8 random_byte_1;
    u8 random_byte_2;

    source_obj = source;
    source_pos = position;
    obj_or_angle = (s32) func_8003FC64(0x212);
    if (obj_or_angle != 0) {
        init_obj = (void *) obj_or_angle;
        effect_state = (void *) obj_or_angle + 0x20;
        effect_state->unk_18 = 6;
        effect_state->unk_1A = 6;
        ((S_80171790_1 *)((void *) obj_or_angle))->unk_10 = &D_80170E2C;
        func_8004491C(init_obj, &D_80170CEC);
        data_or_speed = (s32) ((S_80171790_1 *)((void *) obj_or_angle))->unk_0C;
        ((S_80171790_2 *)((void *) data_or_speed))->unk_10 = 0x60;
        ((S_80171790_2 *)((void *) data_or_speed))->unk_14 =
            (u16) (((S_80171790_2 *)((void *) data_or_speed))->unk_14 | 0xC);
        effect_pos = ((S_80171790_1 *)((void *) obj_or_angle))->unk_08;
        effect_pos->unk_02 = source_pos->unk_02;
        effect_pos->unk_06 = source_pos->unk_06;
        effect_pos->unk_0A =
            (s16) (source_pos->unk_0A - 0x50);
        data_or_speed = (s32) ((S_80171790_1 *)((void *) obj_or_angle))->unk_0C;
        ((S_80171790_2 *)((void *) data_or_speed))->unk_1E = 0x1000;
        ((S_80171790_2 *)((void *) data_or_speed))->unk_1C = 0x1000;
        ((S_80171790_2 *)((void *) data_or_speed))->unk_0C = rand();
        ((S_80171790_2 *)((void *) data_or_speed))->unk_0D = rand();
        ((S_80171790_2 *)((void *) data_or_speed))->unk_0E = rand();
        ((S_80171790_1 *)((void *) obj_or_angle))->unk_20 =
            ((S_80171790_2 *)((void *) data_or_speed))->unk_0C;
        random_byte_1 = ((S_80171790_2 *)((void *) data_or_speed))->unk_0D;
        effect_state->unk_01 = random_byte_1;
        random_byte_2 = ((S_80171790_2 *)((void *) data_or_speed))->unk_0E;
        effect_state->unk_60 = 0;
        effect_state->unk_5C = 0;
        effect_state->unk_58 = 0;
        effect_state->unk_02 = random_byte_2;
        obj_or_angle = rand() & 0xFFF;
        data_or_speed =
            (source_obj->unk_AE * func_80064584(obj_or_angle)) >> 0xC;
        effect_state->unk_62 =
            (source_obj->unk_AE * func_800644B8(obj_or_angle)) >> 0xC;
        obj_or_angle = rand() & 0xFFF;
        effect_state->unk_5A =
            (data_or_speed * func_80064584(obj_or_angle)) >> 0xC;
        effect_state->unk_5E =
            (data_or_speed * func_800644B8(obj_or_angle)) >> 0xC;
    }
}

/* MECHANISM: The fixed s0/s1/s2 object roles leave natural argument holds to allocate as s4/s3,
   reproducing the 0x28 frame and prologue schedule; s0 holds object+0x20 across the body.
   Two scheduler seams retain the random_byte_1 load-delay nop, while a split random_byte_2 live range hoists its lbu. */
