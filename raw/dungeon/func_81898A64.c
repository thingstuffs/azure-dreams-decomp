#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void *func_80024350() __attribute__((noreturn));
M2C_UNK func_8003DB94();
void *func_8003FC64();
M2C_UNK func_8004491C();
extern M2C_UNK D_800241D8;
extern M2C_UNK D_80024EF4;
extern M2C_UNK D_80045340;

void *func_80024264(s32 arg0, void *arg1)
{
    void *temp_a0;
    void *temp_s0;
    void *temp_v0;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 == NULL) {
        register void *dispatch_result ASM_REG("$2") = NULL;

        ASM_TAILSLOT_PIN(dispatch_result);
        func_80024350();
    }
    M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800241D8;
    temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
    M2C_FIELD(temp_v0, s32 *, 0x20) = arg0;
    M2C_FIELD(temp_v0, s16 *, 0x24) = 0;
    M2C_FIELD(temp_s0, u8 *, 0xE) = 0x80;
    M2C_FIELD(temp_s0, u8 *, 0xD) = 0x80;
    M2C_FIELD(temp_s0, u8 *, 0xC) = 0x80;
    func_8003DB94(temp_s0, &D_80024EF4, 0);
    M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x2000;
    M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x1000;
    M2C_FIELD(temp_s0, s16 *, 0x1A) = 0xC00;
    func_8004491C(temp_v0, &D_80045340);
    temp_a0 = M2C_FIELD(temp_v0, void **, 8);
    M2C_FIELD(temp_a0, s32 *, 0) = M2C_FIELD(arg1, s32 *, 0);
    M2C_FIELD(temp_a0, s32 *, 4) = M2C_FIELD(arg1, s32 *, 4);
    M2C_FIELD(temp_a0, s32 *, 8) = M2C_FIELD(arg1, s32 *, 8) + 0x500000;
    M2C_FIELD(temp_a0, s32 *, 0xC) = M2C_FIELD(arg1, s32 *, 0xC);
    M2C_FIELD(temp_a0, s32 *, 0x10) = M2C_FIELD(arg1, s32 *, 0x10);
    M2C_FIELD(temp_a0, s32 *, 0x14) = M2C_FIELD(arg1, s32 *, 0x14);
    return temp_v0;
}

/* MECHANISM: The aligned-2 seed already had the exact 0x28 frame, saved-register roles, and CFG.
   Unsigned byte fields materialize retail's +0x80; a guarded $v0 null carrier plus
   ASM_TAILSLOT_PIN sinks move v0,zero into the LEAD-18 noreturn-j delay slot. */
