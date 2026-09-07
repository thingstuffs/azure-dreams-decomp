#include "common.h"

typedef struct Copy16 {
    s32 word[4];
} Copy16;

#define FIELD(ptr, type, off) (*(type *)((u8 *)(ptr) + (off)))

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, u8, s32);
extern void func_800BC26C(void *, s32, void *, void *);

extern s32 D_80045340;
extern u8 D_80083160[];
extern u8 D_80083498[];
extern u8 D_800D5594[];
extern s8 D_800DCECC[];
extern u8 D_800E23F0[];

void func_80D3B0B8(u8 *arg0, u8 *arg1, u8 *arg2) {
    register u8 *saved_arg0 ASM_REG("$20") = arg0;
    register u8 *saved_arg1 ASM_REG("$22") = arg1;
    register u8 *saved_arg2 ASM_REG("$21") = arg2;
    register u8 *temp_v0 ASM_REG("$18");
    register u8 *temp_s3 ASM_REG("$19");
    register u8 *temp_s1 ASM_REG("$17");
    register u8 *base_80083160 ASM_REG("$16");
    u8 *temp_v1;
    register Copy16 *var_a2 ASM_REG("$6");
    register Copy16 *var_a3 ASM_REG("$7");
    register Copy16 *var_t0 ASM_REG("$8");
    register u8 *table_800E23F0 ASM_REG("$5");

    temp_v0 = func_8003FD64(0x112, D_80083498);
    temp_s3 = temp_v0 + 0x20;
    if (temp_v0 != 0) {
        FIELD(temp_s3, s16, 0x96) = 0x78;
        FIELD(temp_v0, void *, 0x10) = D_800D5594;
        FIELD(temp_s3, u8 *, 0xAC) = saved_arg0 - 0x20;
        FIELD(temp_s3, u16, 0x94) = FIELD(saved_arg0, u16, 0x2A);
        var_a3 = (Copy16 *)saved_arg2;
        FIELD(temp_s3, u16, 0x2A) = FIELD(saved_arg0, u16, 0x2A);
        temp_s1 = FIELD(temp_v0, u8 *, 0xC);

        var_t0 = (Copy16 *)(saved_arg2 + 0x30);
        var_a2 = (Copy16 *)temp_s1;
        do {
            *var_a2 = *var_a3;
            var_a3++;
            var_a2++;
        } while (var_a3 != var_t0);
        ASM_KEEP(var_a2);
        ASM_KEEP(var_a3);
        ASM_KEEP(var_t0);

        func_8004491C(temp_v0, &D_80045340);
        table_800E23F0 = D_800E23F0;
        FIELD(temp_s1, u8 *, 0x2C) = table_800E23F0;
        base_80083160 = D_80083160;
        func_80047784(temp_s1,
            table_800E23F0[((FIELD(base_80083160, s16, 0xC8) +
                FIELD(saved_arg0, s16, 0x2A) + 0x100) >> 9) & 7], 0);

        temp_v1 = FIELD(temp_v0, u8 *, 8);
        FIELD(temp_v1, u16, 2) = FIELD(saved_arg1, u16, 2);
        FIELD(temp_v1, u16, 6) = FIELD(saved_arg1, u16, 6);
        FIELD(temp_v1, u16, 0xA) = FIELD(saved_arg1, u16, 0xA);
        {
            register u16 field_1c ASM_REG("$2");
            register u16 field_1e ASM_REG("$3");

            field_1c = FIELD(saved_arg2, u16, 0x1C);
            FIELD(temp_s1, u16, 0x1C) = field_1c;
            field_1e = FIELD(saved_arg2, u16, 0x1E);
            FIELD(temp_s1, u8, 0xE) = 0x80;
            FIELD(temp_s1, u8, 0xD) = 0x80;
            FIELD(temp_s1, u8, 0xC) = 0x80;
            FIELD(temp_s1, u16, 0x1E) = field_1e;
        }
        FIELD(temp_s1, s16, 6) =
            D_800DCECC[((FIELD(base_80083160, s16, 0xC8) +
                FIELD(saved_arg0, s16, 0x2A) + 0x100) >> 9) & 7] * 4;
        FIELD(saved_arg0, u8, 0xB0)++;
        func_800BC26C(temp_v0, 0, temp_s1 + 0x2C, temp_s3 + 0x2A);
        ASM_KEEP(temp_v0);
        ASM_KEEP(temp_s3);
        ASM_KEEP(temp_s1);
        ASM_KEEP(base_80083160);
        ASM_KEEP(saved_arg0);
        ASM_KEEP(saved_arg1);
        ASM_KEEP(saved_arg2);
    }
}
