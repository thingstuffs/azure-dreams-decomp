#include "common.h"
#include "m2c_compat.h"

typedef struct S_81814EDC_0_pre {
    u16 unk_00;
} S_81814EDC_0_pre;   /* the 0x2 bytes before arg0 in func_81814EDC, addressed as arg0[-1] */

typedef struct S_81814EDC_0 {
    s16 unk_00;
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x4];
    s16 unk_08;
    u16 unk_0A;
    u8 pad_0C[0x9];
    u8 unk_15;
    u16 unk_16;
    u8 pad_18[0x14];
    s32 unk_2C;
    void * unk_30;
    u8 pad_34[0x24];
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
} S_81814EDC_0;   /* arg0 in func_81814EDC */

typedef struct S_81814EDC_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xE];
    s16 unk_22;
} S_81814EDC_1;   /* temp_v0 in func_81814EDC */

typedef struct S_81814EDC_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    union { u8 s; s8 u; } unk_0C;   /* accessed as both */
    union { u8 s; s8 u; } unk_0D;   /* accessed as both */
    union { u8 s; s8 u; } unk_0E;   /* accessed as both */
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_81814EDC_2;   /* temp_s0_2 in func_81814EDC */

typedef struct S_81814EDC_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81814EDC_3;   /* source in func_81814EDC */

typedef struct S_81814EDC_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
} S_81814EDC_4;   /* temp_s1_2 in func_81814EDC */

typedef struct S_81814EDC_5 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x4C];
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
} S_81814EDC_5;   /* temp_s1_4 in func_81814EDC */

typedef struct S_81814EDC_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81814EDC_6;   /* temp_s3 in func_81814EDC */

typedef struct S_81814EDC_7_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_81814EDC_7_pre;   /* the 0x18 bytes before source_owner in func_81814EDC, addressed as source_owner[-1] */

typedef struct S_81814EDC_8_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_81814EDC_8_pre;   /* the 0x14 bytes before temp_a0 in func_81814EDC, addressed as temp_a0[-1] */

typedef struct S_81814EDC_8 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_81814EDC_8;   /* temp_a0 in func_81814EDC */

typedef struct S_81814EDC_9 {
    u8 pad_00[0xC];
    union { s8 s; u8 u; } unk_0C;   /* accessed as both */
    union { s8 s; u8 u; } unk_0D;   /* accessed as both */
    union { s8 s; u8 u; } unk_0E;   /* accessed as both */
} S_81814EDC_9;   /* temp_a1 in func_81814EDC */

typedef struct S_81814EDC_10 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_81814EDC_10;   /* arg1_value in func_81814EDC */

typedef struct S_81814EDC_11 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_81814EDC_11;   /* temp_a0_3 in func_81814EDC */

typedef struct S_81814EDC_12_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_81814EDC_12_pre;   /* the 0x18 bytes before ((S_81814EDC_0 *)arg0)->unk_30 in func_81814EDC, addressed as ((S_81814EDC_0 *)arg0)->unk_30[-1] */


extern u8 D_80045340[];
extern u8 D_800DE938[];
extern u8 D_800DE870[9];
extern s32 D_800814A0[3];
M2C_UNK func_800245BC();
void func_80024B08() __attribute__((noreturn));
void func_80024BB8() __attribute__((noreturn));
void *func_8003FC64();
M2C_UNK func_8004491C();
s32 func_80069EF8();
M2C_UNK func_8009CE1C();
s32 func_800A4778();
extern M2C_UNK D_80024280;

void func_81814EDC(void *arg0, void *arg1) {
    s16 temp_a0_2;
    s16 temp_s0_9;
    s32 temp_s0;
    s32 temp_s0_4;
    s32 temp_s1;
    s32 temp_s1_3;
    s32 var_s4;
    s32 temp_s6;
    s32 temp_s7;
    s32 temp_s8;
    u16 temp_v0_2;
    u16 temp_v0_5;
    void *temp_a0;
    S_81814EDC_11 *temp_a0_3;
    S_81814EDC_9 *temp_a1;
    S_81814EDC_2 *temp_s0_2;
    S_81814EDC_4 *temp_s1_2;
    S_81814EDC_5 *temp_s1_4;
    S_81814EDC_6 *temp_s3;
    void *temp_v0;

    if (((S_81814EDC_0 *)arg0)->unk_00 == 0) {
        if (!(((S_81814EDC_0 *)arg0)->unk_0A & 1)) {
            temp_s1 = func_80069EF8() & 7;
            temp_s0 = (func_80069EF8() & 0xFF) | 0x80;
            func_800245BC(arg0 - 0x20, temp_s1, 0xF0, temp_s0, 0, 0, (s32) (s16) (-0x20 - (func_80069EF8() & 0x1F)));
        }
        temp_v0 = func_8003FC64(0x212);
        if (temp_v0 != NULL) {
            void **arg1_addr = &arg1;

            ((S_81814EDC_1 *)temp_v0)->unk_22 = 9;
            ((S_81814EDC_1 *)temp_v0)->unk_10 = &D_80024280;
            func_8004491C(temp_v0, D_80045340);
            temp_s0_2 = ((S_81814EDC_1 *)temp_v0)->unk_0C;
            temp_s0_2->unk_14 = (u16) (temp_s0_2->unk_14 | 0xC);
            temp_s1_2 = ((S_81814EDC_1 *)temp_v0)->unk_08;
            {
                s32 random_offset = func_80069EF8() & 0x1F;
                register void *source ASM_REG("$8") = *arg1_addr;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                s32 coordinate = ((S_81814EDC_3 *)source)->unk_02;

                coordinate -= 0x10;
                coordinate += random_offset;
                temp_s1_2->unk_02 = (s16) coordinate;
            }
            {
                s32 random_offset = func_80069EF8() & 0x1F;
                register void *source ASM_REG("$8") = *arg1_addr;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                s32 coordinate = ((S_81814EDC_3 *)source)->unk_06;

                coordinate -= 0x10;
                coordinate += random_offset;
                temp_s1_2->unk_06 = (s16) coordinate;
            }
            {
                s32 random_offset = func_80069EF8() & 7;
                register void *source ASM_REG("$8") = *arg1_addr;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                s32 coordinate = ((S_81814EDC_3 *)source)->unk_0A;

                coordinate -= 4;
                coordinate += random_offset;
                temp_s1_2->unk_0A.s = (s16) coordinate;
            }
            temp_s0_2 = ((S_81814EDC_1 *)temp_v0)->unk_0C;
            temp_s0_2->unk_1C = 0x2000;
            temp_s0_2->unk_1E = 0x1000;
            temp_s0_2->unk_0E.s = 0x80;
            temp_s0_2->unk_0D.s = 0x80;
            temp_s0_2->unk_0C.s = 0x80;
            func_8003DB94(temp_s0_2, D_800DE938, 0);
            func_800478B8(temp_s0_2);
            func_800478B8(temp_s0_2);
        }
        temp_v0_2 = ((S_81814EDC_0 *)arg0)->unk_02.s - 1;
        ((S_81814EDC_0 *)arg0)->unk_02.s = temp_v0_2;
        if ((temp_v0_2 << 0x10) <= 0) {
            var_s4 = 0;
            if (((S_81814EDC_0 *)arg0)->unk_08 != 0) {
loop_effects:
                var_s4 += 1;
                temp_s1_3 = func_80069EF8() & 7;
                temp_s0_4 = (func_80069EF8() & 0xFF) | 0x80;
                func_800245BC(arg0 - 0x20, temp_s1_3, 0xF0, temp_s0_4, 0, 0, (s32) (s16) (-0x20 - (func_80069EF8() & 0x1F)));
                if (var_s4 < 4) {
                    goto loop_effects;
                }
                var_s4 = 0;
                do {
                    temp_v0 = func_8003FC64(0x212);
                    temp_s1_4 = temp_v0 + 0x20;
                    if (temp_v0 != NULL) {
                        s32 random_offset;
                        s32 coordinate;

                        temp_s1_4->unk_02 = 0xD;
                        temp_s3 = ((S_81814EDC_12_pre *)(((S_81814EDC_0 *)arg0)->unk_30))[-1].unk_00;
                        ((S_81814EDC_1 *)temp_v0)->unk_10 = &D_80024280;
                        func_8004491C(temp_v0, D_80045340);
                        temp_s0_2 = ((S_81814EDC_1 *)temp_v0)->unk_0C;
                        temp_s0_2->unk_14 = (u16) (temp_s0_2->unk_14 | 0xC);
                        temp_s1_4->unk_58 = (s32) (((func_80069EF8() & 0x7FFF) << 5) + 0xFFF80000);
                        temp_s1_4->unk_5C = (s32) (((func_80069EF8() & 0x7FFF) << 5) + 0xFFF80000);
                        temp_s1_4->unk_60 = (s32) (((func_80069EF8() & 0x3FFF) << 5) + 0xFFF80000);
                        temp_s1_4 = ((S_81814EDC_1 *)temp_v0)->unk_08;
                        random_offset = func_80069EF8() & 0xF;
                        coordinate = temp_s3->unk_02;
                        coordinate -= 8;
                        coordinate += random_offset;
                        temp_s1_4->unk_02 = (s16) coordinate;
                        random_offset = func_80069EF8() & 1;
                        coordinate = temp_s3->unk_06;
                        coordinate -= 1;
                        coordinate += random_offset;
                        temp_s1_4->unk_06 = (s16) coordinate;
                        temp_s1_4->unk_0A = (s16) (temp_s3->unk_0A - 0x20);
                        temp_s0_2 = ((S_81814EDC_1 *)temp_v0)->unk_0C;
                        temp_s0_2->unk_1E = 0x1000;
                        temp_s0_2->unk_1C = 0x1000;
                        temp_s0_2->unk_0E.s = 0x80;
                        temp_s0_2->unk_0D.s = 0x80;
                        temp_s0_2->unk_0C.s = 0x80;
                        func_8003DB94(temp_s0_2, D_800DE870, 0);
                    }
                    var_s4 += 1;
                } while (var_s4 < 2);
                temp_s8 = 0x1000;
                var_s4 = 0;
                temp_s6 = 0x80;
                temp_s7 = 0x2000;
loop_13:
                temp_v0 = func_8003FC64(0x212);
                if (temp_v0 != NULL) {
                    s32 random_offset;
                    s32 coordinate;
                    s32 callback_type = 0xB;
                    register void *task ASM_REG("$4") = temp_v0;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

                    ASM_KEEP(callback_type);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                    {
                        void *source_owner;
                        register u8 *handler ASM_REG("$5") = (u8 *) 0x80040000;   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */

                        ASM_KEEP(handler);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                        ((S_81814EDC_1 *)temp_v0)->unk_22 = callback_type;
                        source_owner = ((S_81814EDC_0 *)arg0)->unk_30;
                        handler += 0x5340;
                        temp_s3 = ((S_81814EDC_7_pre *)source_owner)[-1].unk_00;
                        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                        {
                            register M2C_UNK *callback ASM_REG("$8") = &D_80024280;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                            ((S_81814EDC_1 *)temp_v0)->unk_10 = callback;
                        }
                        func_8004491C(task, handler);
                    }
                    temp_s0_2 = ((S_81814EDC_1 *)temp_v0)->unk_0C;
                    temp_s0_2->unk_14 = (u16) (temp_s0_2->unk_14 | 0xC);
                    temp_s1_2 = ((S_81814EDC_1 *)temp_v0)->unk_08;
                    random_offset = func_80069EF8() & 0xF;
                    coordinate = temp_s3->unk_02;
                    coordinate -= 8;
                    coordinate += random_offset;
                    temp_s1_2->unk_02 = (s16) coordinate;
                    random_offset = func_80069EF8() & 1;
                    coordinate = temp_s3->unk_06;
                    coordinate -= 1;
                    coordinate += random_offset;
                    temp_s1_2->unk_06 = (s16) coordinate;
                    temp_s1_2->unk_0A.u = (u16) temp_s3->unk_0A;
                    temp_s0_2 = ((S_81814EDC_1 *)temp_v0)->unk_0C;
                    temp_s0_2->unk_0E.u = temp_s6;
                    temp_s0_2->unk_0D.u = temp_s6;
                    temp_s0_2->unk_0C.u = temp_s6;
                    temp_s0_2->unk_06 = 7;
                    if (var_s4 == 0) {
                        temp_s0_2->unk_1C = temp_s8;
                        temp_s0_2->unk_1E = temp_s7;
                        temp_s1_2->unk_0A.u -= 0x14;
                        func_80024B08();
                        return;
                    }
                    temp_s0_2->unk_1C = temp_s7;
                    temp_s0_2->unk_1E = temp_s8;
                    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                    func_8003DB94(temp_s0_2, D_800DE938, 0);
                    goto block_18;
                }
block_18:
                var_s4 += 1;
                if (var_s4 >= 2) {
                    temp_s0_9 = (s16) ((S_81814EDC_0 *)arg0)->unk_0A;
                    if (temp_s0_9 == 4) {
                        func_8009CE1C(((S_81814EDC_0 *)arg0)->unk_30, 0x10, ((S_81814EDC_0 *)arg0)->unk_15, 1, (s32) (s16) (((S_81814EDC_0 *)arg0)->unk_16 << 9), ((S_81814EDC_0 *)arg0)->unk_2C, 2);
                        if ((s16) ((S_81814EDC_0 *)arg0)->unk_0A == temp_s0_9) {
                            temp_a0 = ((S_81814EDC_0 *)arg0)->unk_30;
                            ((S_81814EDC_0 *)arg0)->unk_00 = 1;
                            temp_a1 = ((S_81814EDC_8_pre *)temp_a0)[-1].unk_00;
                            ((S_81814EDC_8 *)temp_a0)->unk_1C = (s32) (((S_81814EDC_8 *)temp_a0)->unk_1C | 0x10000000);
                            temp_a1->unk_0E.s = 0x30;
                            temp_a1->unk_0D.s = 0x30;
                            temp_a1->unk_0C.s = 0x30;
                            ((S_81814EDC_0 *)arg0)->unk_02.u = 0;
                            func_80024BB8(temp_a0, temp_a1);
                            return;
                        }
                    }
                    goto block_31;
                }
                goto loop_13;
            }
            ((S_81814EDC_0 *)arg0)->unk_00 = 1;
            goto block_24;
        }
block_24:
        {
            void **arg1_addr = &arg1;
            register S_81814EDC_10 *arg1_value ASM_REG("$8") = *arg1_addr;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            if ((func_800A4778(arg1_value->unk_00.at02.v, arg1_value->unk_04.at02.v, (s16) arg1_value->unk_08.at02.v, ((S_81814EDC_0 *)arg0)->unk_30) << 0x10) == 0) {
                arg1_value = *arg1_addr;

                arg1_value->unk_00.at00.v = (s32) (arg1_value->unk_00.at00.v + ((S_81814EDC_0 *)arg0)->unk_58);
                arg1_value->unk_04.at00.v = (s32) (arg1_value->unk_04.at00.v + ((S_81814EDC_0 *)arg0)->unk_5C);
                arg1_value->unk_08.at00.v = (s32) (arg1_value->unk_08.at00.v + ((S_81814EDC_0 *)arg0)->unk_60);
                goto block_26;
            }
            goto block_31;
        }
    }
block_26:
    temp_a0_2 = ((S_81814EDC_0 *)arg0)->unk_00;
    if (temp_a0_2 == 1) {
        temp_v0_5 = ((S_81814EDC_0 *)arg0)->unk_02.s + 1;
        ((S_81814EDC_0 *)arg0)->unk_02.s = temp_v0_5;
        if ((s16) temp_v0_5 >= 0x15) {
            if (((s16) ((S_81814EDC_0 *)arg0)->unk_0A == 4) && (((S_81814EDC_0 *)arg0)->unk_08 == temp_a0_2)) {
                temp_a0_3 = ((S_81814EDC_0 *)arg0)->unk_30;
                temp_a0_3->unk_1C = (s32) (temp_a0_3->unk_1C & 0xEFFFFFFF);
                temp_a1 = ((S_81814EDC_12_pre *)(((S_81814EDC_0 *)arg0)->unk_30))[-1].unk_04;
                temp_a1->unk_0E.u = 0x80;
                temp_a1->unk_0D.u = 0x80;
                temp_a1->unk_0C.u = 0x80;
            }
block_31:
            ((S_81814EDC_0_pre *)arg0)[-1].unk_00 = (u16) (((S_81814EDC_0_pre *)arg0)[-1].unk_00 | 0x8000);
            D_800814A0[0] |= 0x8000;
        }
    }
}
