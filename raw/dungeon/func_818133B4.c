#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern s32 func_80027454();
extern s32 func_80027FA4();
extern s32 func_80027FF4();
extern s32 func_80028534();
extern s32 func_80028648();
extern s32 D_80027D7C;

void func_800283B4(s32 arg0) {
    void *temp_s0;

    temp_s0 = arg0 + 0x20;
    FIELD(temp_s0, s32, 0x14) = 1;
    FIELD(FIELD(temp_s0, void *, 0x80), s16, 2) = 0;
    FIELD(temp_s0, s32, 8) = 0;
    FIELD(temp_s0, s32, 0x28) = FIELD(FIELD(temp_s0, void *, 0x48), s32, 0x1C);
    FIELD(temp_s0, s32, 0x38) = FIELD(temp_s0, s32, 0x18);
    func_80027454(arg0 + 0x58, FIELD(temp_s0, s32, 0x14), 0, FIELD(temp_s0, s32, 0x28));
    func_80027FF4(FIELD(temp_s0, s32, 0x4C), FIELD(temp_s0, s32, 0x14));
    FIELD(temp_s0, s32, 0x84) = func_80027FA4(FIELD(temp_s0, s32, 0x88));
    func_80028534(FIELD(temp_s0, s32, 0x88));
    func_80028648(arg0);
    FIELD(temp_s0, s32 *, -0x10) = &D_80027D7C;
}
