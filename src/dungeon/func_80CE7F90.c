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

void func_80171790(void *arg0, void *arg1) {
    S_80171790_5 *saved_arg0;
    S_80171790_4 *saved_arg1;
    s32 saved_obj_angle;
    s32 saved_data_scale;
    S_80171790_0 *saved_tail;
    register void *init_obj ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
    S_80171790_3 *copy_dst;
    u8 byte1;
    u8 byte2;

    saved_arg0 = arg0;
    saved_arg1 = arg1;
    saved_obj_angle = (s32) func_8003FC64(0x212);
    if (saved_obj_angle != 0) {
        init_obj = (void *) saved_obj_angle;
        saved_tail = (void *) saved_obj_angle + 0x20;
        ASM_KEEP(saved_tail);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        saved_tail->unk_18 = 6;
        saved_tail->unk_1A = 6;
        ((S_80171790_1 *)((void *) saved_obj_angle))->unk_10 = &D_80170E2C;
        func_8004491C(init_obj, &D_80170CEC);
        saved_data_scale = (s32) ((S_80171790_1 *)((void *) saved_obj_angle))->unk_0C;
        ((S_80171790_2 *)((void *) saved_data_scale))->unk_10 = 0x60;
        ((S_80171790_2 *)((void *) saved_data_scale))->unk_14 =
            (u16) (((S_80171790_2 *)((void *) saved_data_scale))->unk_14 | 0xC);
        copy_dst = ((S_80171790_1 *)((void *) saved_obj_angle))->unk_08;
        copy_dst->unk_02 = saved_arg1->unk_02;
        copy_dst->unk_06 = saved_arg1->unk_06;
        copy_dst->unk_0A =
            (s16) (saved_arg1->unk_0A - 0x50);
        saved_data_scale = (s32) ((S_80171790_1 *)((void *) saved_obj_angle))->unk_0C;
        ((S_80171790_2 *)((void *) saved_data_scale))->unk_1E = 0x1000;
        ((S_80171790_2 *)((void *) saved_data_scale))->unk_1C = 0x1000;
        ((S_80171790_2 *)((void *) saved_data_scale))->unk_0C = rand();
        ((S_80171790_2 *)((void *) saved_data_scale))->unk_0D = rand();
        ((S_80171790_2 *)((void *) saved_data_scale))->unk_0E = rand();
        ((S_80171790_1 *)((void *) saved_obj_angle))->unk_20 =
            ((S_80171790_2 *)((void *) saved_data_scale))->unk_0C;
        byte1 = ((S_80171790_2 *)((void *) saved_data_scale))->unk_0D;
        saved_tail->unk_01 = byte1;
        byte2 = ((S_80171790_2 *)((void *) saved_data_scale))->unk_0E;
        saved_tail->unk_60 = 0;
        saved_tail->unk_5C = 0;
        saved_tail->unk_58 = 0;
        saved_tail->unk_02 = byte2;
        saved_obj_angle = rand() & 0xFFF;
        saved_data_scale =
            (saved_arg0->unk_AE * func_80064584(saved_obj_angle)) >> 0xC;
        saved_tail->unk_62 =
            (saved_arg0->unk_AE * func_800644B8(saved_obj_angle)) >> 0xC;
        saved_obj_angle = rand() & 0xFFF;
        saved_tail->unk_5A =
            (saved_data_scale * func_80064584(saved_obj_angle)) >> 0xC;
        saved_tail->unk_5E =
            (saved_data_scale * func_800644B8(saved_obj_angle)) >> 0xC;
    }
}

/* MECHANISM: The fixed s0/s1/s2 object roles leave natural argument holds to allocate as s4/s3,
   reproducing the 0x28 frame and prologue schedule; s0 holds object+0x20 across the body.
   Two scheduler seams retain the byte1 load-delay nop, while a split byte2 live range hoists its lbu. */
