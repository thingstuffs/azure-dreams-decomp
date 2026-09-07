#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct {
    s32 words[6];
} Copy24;

void *func_8003FC64(s32);
void func_8004491C(void *, void *);
void func_80047784(void *, u8, s32);
extern u8 D_80045340;
extern s16 D_80083228;
extern u8 D_8017573C;
extern u8 D_80176498[];

void *func_80175858(void *arg0, Copy24 *arg1, void *arg2) {
    void *temp_a0;
    register void *temp_a2 ASM_REG("$6");
    void *temp_v0;
    register void *temp_v1 ASM_REG("$3");
    register void *result ASM_REG("$2");
    register u16 temp_a1 ASM_REG("$5");
    register void *arg0_hold ASM_REG("$17") = arg0;
    register Copy24 *arg1_hold ASM_REG("$19") = arg1;
    register void *arg2_hold ASM_REG("$18") = arg2;

    ASM_KEEP_NV(arg0_hold);
    ASM_KEEP_NV(arg1_hold);
    ASM_KEEP_NV(arg2_hold);
    temp_v0 = func_8003FC64(0x312);
    if (temp_v0 != NULL) {
        goto allocated;
    }
    result = NULL;
    goto done;
allocated:
    M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_8017573C;
    func_8004491C(temp_v0, &D_80045340);
    temp_a2 = temp_v0 + 0x20;
    ASM_KEEP_NV(temp_a2);
    M2C_FIELD(temp_a2, u16 *, 4) =
        (u16)M2C_FIELD(arg0_hold, u16 *, 0x2A);
    temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
    M2C_FIELD(temp_a0, s32 *, 0x28) =
        M2C_FIELD(arg2_hold, s32 *, 0x28);
    temp_a1 = M2C_FIELD(arg2_hold, u16 *, 0x12);
    ASM_KEEP_NV(temp_a1);
    M2C_FIELD(temp_a0, s16 *, 0x1E) = 0x800;
    M2C_FIELD(temp_a0, s16 *, 0x1C) = 0x800;
    M2C_FIELD(temp_a0, s32 *, 0xC) = 0x808080;
    M2C_FIELD(temp_a0, u16 *, 0x12) = temp_a1;
    func_80047784(
        temp_a0,
        D_80176498[
            ((D_80083228 + M2C_FIELD(temp_a2, s16 *, 4) + 0x100) >> 9) &
            7],
        0);
    temp_v1 = M2C_FIELD(temp_v0, void **, 8);
    ASM_KEEP_NV(temp_v1);
    result = temp_v0;
    ASM_KEEP_NV(result);
    *(Copy24 *)temp_v1 = *arg1_hold;
done:
    return result;
}

/* MECHANISM: True-space CFG plus one v0 result carrier preserves bnez/local-j/zero-delay.
   Guarded s1/s3/s2 argument holds reproduce the 0x28 frame and exact save scatter.
   Byte-table typing and an early a1 halfword lifetime remove scaling and load-delay drift.
   Holding the copy destination in v1 before v0 yields retail's packed 24-byte copy order. */
