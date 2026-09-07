#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((s8 *)(expr) + (offset)))
#define UNALIGNED32(expr) (expr)

typedef struct {
    u8 bytes[12];
} Block12;

extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 D_80045340;
extern s32 D_800D4954;
extern Block12 D_800E233C;

void func_800D4AB0(void *arg0) {
    void *temp_a0;
    register void *temp_a3 ASM_REG("$7");
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_2;

    temp_v0 = func_8003FC64(0x12);
    temp_v1 = temp_v0 + 0x20;
    if (temp_v0 != 0) {
        FIELD(temp_v1, s16, 0x5A) = 0x78;
        FIELD(temp_v1, s16, 0x5C) = 0x78;
        FIELD(temp_v1, void *, 0x88) = FIELD(arg0, void *, 0x88);
        FIELD(temp_v0, s32 *, 0x10) = &D_800D4954;
        func_8004491C(temp_v0, &D_80045340);
        temp_a3 = FIELD(temp_v0, void *, 0xC);
        FIELD(temp_a3, s16, 0x10) = 0x60;
        FIELD(temp_a3, s16, 0x6) = 0;
        FIELD(temp_a3, u16, 0x14) = FIELD(temp_a3, u16, 0x14) | 0xC;
        temp_v1_2 = FIELD(FIELD(arg0, void *, 0x88), void *, -0x18);
        temp_a0 = FIELD(temp_v0, void *, 0x8);
        FIELD(temp_a0, u16, 0x2) = FIELD(temp_v1_2, u16, 0x2);
        FIELD(temp_a0, u16, 0x6) = FIELD(temp_v1_2, u16, 0x6);
        FIELD(temp_a0, s16, 0xA) = FIELD(temp_v1_2, u16, 0xA) - 0x32;
        temp_a3 = FIELD(temp_v0, void *, 0xC);
        FIELD(temp_a3, u8, 0xE) = 0x80;
        FIELD(temp_a3, u8, 0xD) = 0x80;
        FIELD(temp_a3, u8, 0xC) = 0x80;
        FIELD(temp_a3, s16, 0x1E) = 0;
        FIELD(temp_a3, s16, 0x1C) = 0;
        FIELD(temp_v0, Block12, 0x96) = D_800E233C;
        FIELD(temp_a3, void *, 8) = temp_v0 + 0x96;
    }
}
