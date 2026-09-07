#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern u8 D_80045C34[];
extern u8 D_80172874[];
extern u8 D_80174ABC[];

void func_80172A14(void *arg0, void *arg1) {
    void *temp_a0;
    register void *temp_a0_2 ASM_REG("$4");
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v1;

    temp_v0 = func_8003FD64(0x12, (u8 *)arg0 - 0x20);
    if (temp_v0 != 0) {
        FIELD(arg0, void *, 0xAC) = temp_v0;
        FIELD(temp_v0, void *, 0x10) = D_80172874;
        func_8004491C(temp_v0, D_80045C34);
        temp_v0_2 = (u8 *)temp_v0 + 0x20;
        FIELD(temp_v0_2, s16, 0x18) = 5;
        FIELD(temp_v0_2, void *, 0x20) = arg0;
        FIELD(temp_v0_2, void *, 0x24) = arg1;
        temp_a0 = FIELD(temp_v0, void *, 0xC);
        FIELD(temp_a0, s16, 0x10) = 0x40;
        FIELD(temp_a0, u16, 0x14) |= 0xC;
        temp_v1 = FIELD(temp_v0, void *, 8);
        FIELD(temp_v1, u16, 2) = FIELD(arg1, u16, 2);
        FIELD(temp_v1, u16, 6) = FIELD(arg1, u16, 6);
        FIELD(temp_v1, u16, 0xA) = FIELD(arg1, u16, 0xA);
        temp_a0_2 = FIELD(temp_v0, void *, 0xC);
        FIELD(temp_a0_2, s16, 0x1E) = 0xA00;
        FIELD(temp_a0_2, s16, 0x1C) = 0xA00;
        FIELD(temp_a0_2, s8, 0xE) = 0;
        FIELD(temp_a0_2, s8, 0xD) = 0;
        FIELD(temp_a0_2, s8, 0xC) = 0;
        FIELD(temp_a0_2, void *, 8) = D_80174ABC;
    }
}
