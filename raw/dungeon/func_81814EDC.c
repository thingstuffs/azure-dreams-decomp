#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

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
    void *temp_a0_3;
    void *temp_a1;
    void *temp_s0_2;
    void *temp_s1_2;
    void *temp_s1_4;
    void *temp_s3;
    void *temp_v0;

    if (M2C_FIELD(arg0, s16 *, 0) == 0) {
        if (!(M2C_FIELD(arg0, u16 *, 0xA) & 1)) {
            temp_s1 = func_80069EF8() & 7;
            temp_s0 = (func_80069EF8() & 0xFF) | 0x80;
            func_800245BC(arg0 - 0x20, temp_s1, 0xF0, temp_s0, 0, 0, (s32) (s16) (-0x20 - (func_80069EF8() & 0x1F)));
        }
        temp_v0 = func_8003FC64(0x212);
        if (temp_v0 != NULL) {
            void **arg1_addr = &arg1;

            M2C_FIELD(temp_v0, s16 *, 0x22) = 9;
            M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80024280;
            func_8004491C(temp_v0, D_80045340);
            temp_s0_2 = M2C_FIELD(temp_v0, void **, 0xC);
            M2C_FIELD(temp_s0_2, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0_2, u16 *, 0x14) | 0xC);
            temp_s1_2 = M2C_FIELD(temp_v0, void **, 8);
            {
                s32 random_offset = func_80069EF8() & 0x1F;
                register void *source ASM_REG("$8") = *arg1_addr;
                s32 coordinate = M2C_FIELD(source, u16 *, 2);

                coordinate -= 0x10;
                coordinate += random_offset;
                ASM_KEEP(source);
                M2C_FIELD(temp_s1_2, s16 *, 2) = (s16) coordinate;
            }
            {
                s32 random_offset = func_80069EF8() & 0x1F;
                register void *source ASM_REG("$8") = *arg1_addr;
                s32 coordinate = M2C_FIELD(source, u16 *, 6);

                coordinate -= 0x10;
                coordinate += random_offset;
                ASM_KEEP(source);
                M2C_FIELD(temp_s1_2, s16 *, 6) = (s16) coordinate;
            }
            {
                s32 random_offset = func_80069EF8() & 7;
                register void *source ASM_REG("$8") = *arg1_addr;
                s32 coordinate = M2C_FIELD(source, u16 *, 0xA);

                coordinate -= 4;
                coordinate += random_offset;
                ASM_KEEP_NV(source);
                M2C_FIELD(temp_s1_2, s16 *, 0xA) = (s16) coordinate;
            }
            temp_s0_2 = M2C_FIELD(temp_v0, void **, 0xC);
            M2C_FIELD(temp_s0_2, s16 *, 0x1C) = 0x2000;
            M2C_FIELD(temp_s0_2, s16 *, 0x1E) = 0x1000;
            M2C_FIELD(temp_s0_2, u8 *, 0xE) = 0x80;
            M2C_FIELD(temp_s0_2, u8 *, 0xD) = 0x80;
            M2C_FIELD(temp_s0_2, u8 *, 0xC) = 0x80;
            func_8003DB94(temp_s0_2, D_800DE938, 0);
            func_800478B8(temp_s0_2);
            func_800478B8(temp_s0_2);
        }
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 2) - 1;
        M2C_FIELD(arg0, u16 *, 2) = temp_v0_2;
        if ((temp_v0_2 << 0x10) <= 0) {
            var_s4 = 0;
            if (M2C_FIELD(arg0, s16 *, 8) != 0) {
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

                        M2C_FIELD(temp_s1_4, s16 *, 2) = 0xD;
                        temp_s3 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x30), void **, -0x18);
                        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80024280;
                        func_8004491C(temp_v0, D_80045340);
                        temp_s0_2 = M2C_FIELD(temp_v0, void **, 0xC);
                        M2C_FIELD(temp_s0_2, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0_2, u16 *, 0x14) | 0xC);
                        M2C_FIELD(temp_s1_4, s32 *, 0x58) = (s32) (((func_80069EF8() & 0x7FFF) << 5) + 0xFFF80000);
                        M2C_FIELD(temp_s1_4, s32 *, 0x5C) = (s32) (((func_80069EF8() & 0x7FFF) << 5) + 0xFFF80000);
                        M2C_FIELD(temp_s1_4, s32 *, 0x60) = (s32) (((func_80069EF8() & 0x3FFF) << 5) + 0xFFF80000);
                        temp_s1_4 = M2C_FIELD(temp_v0, void **, 8);
                        random_offset = func_80069EF8() & 0xF;
                        coordinate = M2C_FIELD(temp_s3, u16 *, 2);
                        coordinate -= 8;
                        coordinate += random_offset;
                        M2C_FIELD(temp_s1_4, s16 *, 2) = (s16) coordinate;
                        random_offset = func_80069EF8() & 1;
                        coordinate = M2C_FIELD(temp_s3, u16 *, 6);
                        coordinate -= 1;
                        coordinate += random_offset;
                        M2C_FIELD(temp_s1_4, s16 *, 6) = (s16) coordinate;
                        M2C_FIELD(temp_s1_4, s16 *, 0xA) = (s16) (M2C_FIELD(temp_s3, u16 *, 0xA) - 0x20);
                        temp_s0_2 = M2C_FIELD(temp_v0, void **, 0xC);
                        M2C_FIELD(temp_s0_2, s16 *, 0x1E) = 0x1000;
                        M2C_FIELD(temp_s0_2, s16 *, 0x1C) = 0x1000;
                        M2C_FIELD(temp_s0_2, u8 *, 0xE) = 0x80;
                        M2C_FIELD(temp_s0_2, u8 *, 0xD) = 0x80;
                        M2C_FIELD(temp_s0_2, u8 *, 0xC) = 0x80;
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
                    register s32 callback_type ASM_REG("$2") = 0xB;
                    register void *task ASM_REG("$4") = temp_v0;

                    ASM_KEEP(callback_type);
                    {
                        void *source_owner;
                        register u8 *handler ASM_REG("$5") = (u8 *) 0x80040000;

                        ASM_KEEP(handler);
                        M2C_FIELD(temp_v0, s16 *, 0x22) = callback_type;
                        source_owner = M2C_FIELD(arg0, void **, 0x30);
                        ASM_KEEP(source_owner);
                        handler += 0x5340;
                        temp_s3 = M2C_FIELD(source_owner, void **, -0x18);
                        ASM_SCHED_BARRIER();
                        {
                            register M2C_UNK *callback ASM_REG("$8") = &D_80024280;

                            M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = callback;
                        }
                        func_8004491C(task, handler);
                    }
                    temp_s0_2 = M2C_FIELD(temp_v0, void **, 0xC);
                    M2C_FIELD(temp_s0_2, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0_2, u16 *, 0x14) | 0xC);
                    temp_s1_2 = M2C_FIELD(temp_v0, void **, 8);
                    random_offset = func_80069EF8() & 0xF;
                    coordinate = M2C_FIELD(temp_s3, u16 *, 2);
                    coordinate -= 8;
                    coordinate += random_offset;
                    M2C_FIELD(temp_s1_2, s16 *, 2) = (s16) coordinate;
                    random_offset = func_80069EF8() & 1;
                    coordinate = M2C_FIELD(temp_s3, u16 *, 6);
                    coordinate -= 1;
                    coordinate += random_offset;
                    M2C_FIELD(temp_s1_2, s16 *, 6) = (s16) coordinate;
                    M2C_FIELD(temp_s1_2, u16 *, 0xA) = (u16) M2C_FIELD(temp_s3, u16 *, 0xA);
                    temp_s0_2 = M2C_FIELD(temp_v0, void **, 0xC);
                    M2C_FIELD(temp_s0_2, s8 *, 0xE) = temp_s6;
                    M2C_FIELD(temp_s0_2, s8 *, 0xD) = temp_s6;
                    M2C_FIELD(temp_s0_2, s8 *, 0xC) = temp_s6;
                    M2C_FIELD(temp_s0_2, s16 *, 6) = 7;
                    if (var_s4 == 0) {
                        M2C_FIELD(temp_s0_2, s16 *, 0x1C) = temp_s8;
                        M2C_FIELD(temp_s0_2, s16 *, 0x1E) = temp_s7;
                        M2C_FIELD(temp_s1_2, u16 *, 0xA) -= 0x14;
                        func_80024B08();
                        return;
                    }
                    M2C_FIELD(temp_s0_2, s16 *, 0x1C) = temp_s7;
                    M2C_FIELD(temp_s0_2, s16 *, 0x1E) = temp_s8;
                    ASM_SCHED_BARRIER();
                    func_8003DB94(temp_s0_2, D_800DE938, 0);
                    goto block_18;
                }
block_18:
                var_s4 += 1;
                if (var_s4 >= 2) {
                    temp_s0_9 = (s16) M2C_FIELD(arg0, u16 *, 0xA);
                    if (temp_s0_9 == 4) {
                        func_8009CE1C(M2C_FIELD(arg0, void **, 0x30), 0x10, M2C_FIELD(arg0, u8 *, 0x15), 1, (s32) (s16) (M2C_FIELD(arg0, u16 *, 0x16) << 9), M2C_FIELD(arg0, s32 *, 0x2C), 2);
                        if ((s16) M2C_FIELD(arg0, u16 *, 0xA) == temp_s0_9) {
                            temp_a0 = M2C_FIELD(arg0, void **, 0x30);
                            M2C_FIELD(arg0, s16 *, 0) = 1;
                            temp_a1 = M2C_FIELD(temp_a0, void **, -0x14);
                            M2C_FIELD(temp_a0, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_a0, s32 *, 0x1C) | 0x10000000);
                            M2C_FIELD(temp_a1, s8 *, 0xE) = 0x30;
                            M2C_FIELD(temp_a1, s8 *, 0xD) = 0x30;
                            M2C_FIELD(temp_a1, s8 *, 0xC) = 0x30;
                            M2C_FIELD(arg0, s16 *, 2) = 0;
                            func_80024BB8(temp_a0, temp_a1);
                            return;
                        }
                    }
                    goto block_31;
                }
                goto loop_13;
            }
            M2C_FIELD(arg0, s16 *, 0) = 1;
            goto block_24;
        }
block_24:
        {
            void **arg1_addr = &arg1;
            register void *arg1_value ASM_REG("$8") = *arg1_addr;

            if ((func_800A4778(M2C_FIELD(arg1_value, u16 *, 2), M2C_FIELD(arg1_value, u16 *, 6), (s16) M2C_FIELD(arg1_value, u16 *, 0xA), M2C_FIELD(arg0, void **, 0x30)) << 0x10) == 0) {
                arg1_value = *arg1_addr;

                M2C_FIELD(arg1_value, s32 *, 0) = (s32) (M2C_FIELD(arg1_value, s32 *, 0) + M2C_FIELD(arg0, s32 *, 0x58));
                M2C_FIELD(arg1_value, s32 *, 4) = (s32) (M2C_FIELD(arg1_value, s32 *, 4) + M2C_FIELD(arg0, s32 *, 0x5C));
                M2C_FIELD(arg1_value, s32 *, 8) = (s32) (M2C_FIELD(arg1_value, s32 *, 8) + M2C_FIELD(arg0, s32 *, 0x60));
                goto block_26;
            }
            goto block_31;
        }
    }
block_26:
    temp_a0_2 = M2C_FIELD(arg0, s16 *, 0);
    if (temp_a0_2 == 1) {
        temp_v0_5 = M2C_FIELD(arg0, u16 *, 2) + 1;
        M2C_FIELD(arg0, u16 *, 2) = temp_v0_5;
        if ((s16) temp_v0_5 >= 0x15) {
            if (((s16) M2C_FIELD(arg0, u16 *, 0xA) == 4) && (M2C_FIELD(arg0, s16 *, 8) == temp_a0_2)) {
                temp_a0_3 = M2C_FIELD(arg0, void **, 0x30);
                M2C_FIELD(temp_a0_3, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_a0_3, s32 *, 0x1C) & 0xEFFFFFFF);
                temp_a1 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x30), void **, -0x14);
                M2C_FIELD(temp_a1, u8 *, 0xE) = 0x80;
                M2C_FIELD(temp_a1, u8 *, 0xD) = 0x80;
                M2C_FIELD(temp_a1, u8 *, 0xC) = 0x80;
            }
block_31:
            M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
            D_800814A0[0] |= 0x8000;
        }
    }
}
