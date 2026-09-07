#include "common.h"

typedef s32 M2C_UNK;

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_80024488(void) __attribute__((noreturn));
extern M2C_UNK func_8003DB94();
extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern M2C_UNK D_80024374;
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DE870;

void *func_800243E0(void *arg0) {
    void *temp_s0;
    void *temp_v0;
    void *temp_v1;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 == 0) {
        register void *zero ASM_REG("$2") = 0;

        ASM_TAILSLOT_PIN(zero);
        func_80024488();
    }
    FIELD(temp_v0, M2C_UNK *, 0x10) = &D_80024374;
    temp_s0 = FIELD(temp_v0, void *, 0xC);
    FIELD(temp_s0, u8, 0xE) = 0x80;
    FIELD(temp_s0, u8, 0xD) = 0x80;
    FIELD(temp_s0, u8, 0xC) = 0x80;
    func_8003DB94(temp_s0, &D_800DE870, 0);
    FIELD(temp_s0, s16, 0x1E) = 0x2000;
    FIELD(temp_s0, s16, 0x1C) = 0x2000;
    func_8004491C(temp_v0, &D_80045340);
    temp_v1 = FIELD(temp_v0, void *, 8);
    FIELD(temp_v1, u16, 2) = FIELD(arg0, u16, 2);
    FIELD(temp_v1, u16, 6) = FIELD(arg0, u16, 6);
    FIELD(temp_v1, u16, 0xA) = FIELD(arg0, u16, 0xA);
    return temp_v0;
}
