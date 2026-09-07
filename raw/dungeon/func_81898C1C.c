#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void func_80024530(void) __attribute__((noreturn));
M2C_UNK func_8003DB94();
void *func_8003FC64();
M2C_UNK func_8004491C();
extern M2C_UNK D_80024370;
extern M2C_UNK D_80024E40;
extern M2C_UNK D_80045340;

void *func_8002441C(s32 arg0, void *arg1) {
    void *temp_s0;
    void *temp_v0;
    void *temp_v1;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 == 0) {
        register s32 tail_v0 ASM_REG("$2");

        tail_v0 = 0;
        ASM_TAILSLOT_PIN(tail_v0);
        func_80024530();
    }
    M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80024370;
    temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
    M2C_FIELD(temp_v0, s32 *, 0x20) = arg0;
    M2C_FIELD(temp_v0, s16 *, 0x24) = 0;
    M2C_FIELD(temp_s0, u8 *, 0xE) = 0x80;
    M2C_FIELD(temp_s0, u8 *, 0xD) = 0x80;
    M2C_FIELD(temp_s0, u8 *, 0xC) = 0x80;
    M2C_FIELD(temp_s0, u8 *, 0xE) = 0xC0;
    func_8003DB94(temp_s0, &D_80024E40, 0);
    M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x2000;
    M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x1000;
    M2C_FIELD(temp_s0, s16 *, 0x12) = 0x7DCF;
    M2C_FIELD(temp_s0, u16 *, 0x14) = (u16)(M2C_FIELD(temp_s0, u16 *, 0x14) | 0xC);
    M2C_FIELD(temp_s0, u16 *, 0x10) = (u16)(M2C_FIELD(temp_s0, u16 *, 0x10) | 0x20);
    M2C_FIELD(temp_s0, u16 *, 0x14) = (u16)(M2C_FIELD(temp_s0, u16 *, 0x14) | 0x100);
    func_8004491C(temp_v0, &D_80045340);
    temp_v1 = M2C_FIELD(temp_v0, void **, 8);
    M2C_FIELD(temp_v1, s32 *, 0) = M2C_FIELD(arg1, s32 *, 0);
    M2C_FIELD(temp_v1, s32 *, 4) = M2C_FIELD(arg1, s32 *, 4);
    M2C_FIELD(temp_v1, s32 *, 8) = M2C_FIELD(arg1, s32 *, 8);
    M2C_FIELD(temp_v1, s32 *, 0xC) = M2C_FIELD(arg1, s32 *, 0xC);
    M2C_FIELD(temp_v1, s32 *, 0x10) = M2C_FIELD(arg1, s32 *, 0x10);
    M2C_FIELD(temp_v1, s32 *, 0x14) = M2C_FIELD(arg1, s32 *, 0x14);
    return temp_v0;
}

/* MECHANISM: Unsigned byte fields preserve retail's positive 0x80/0xC0 immediates.
   A scoped $v0 zero plus ASM_TAILSLOT_PIN triggers LEAD 28b, sinking the
   live-for-compiler/dead-for-callee value into the noreturn tail-j delay slot. */
