#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern s32 func_8003DB94();
extern void *func_8003FD64();
extern s32 func_8004491C();

extern s32 D_8002548C;
extern s32 D_80045340;
extern s32 D_80083498;
extern s32 D_800DDC40;
extern s32 D_800DEB70;

void func_81977D08(void *arg0, void *arg1)
{
    void *temp_a2;
    void *temp_s0;
    void *temp_v0;

    temp_v0 = func_8003FD64(0x212, &D_80083498);
    if (temp_v0 != NULL) {
        register void *call_a1 ASM_REG("$5") = &D_800DEB70;

        ASM_KEEP_NV(call_a1);
        FIELD(temp_v0, s32 *, 0x10) = &D_8002548C;
        ASM_SCHED_BARRIER();
        {
            register s32 color ASM_REG("$2") = 0x80;

            temp_s0 = FIELD(temp_v0, void *, 0xC);
            {
                register s32 zero ASM_REG("$6") = 0;

                FIELD(temp_v0, void *, 0x20) = arg0;
                FIELD(temp_s0, u8, 0xE) = color;
                FIELD(temp_s0, u8, 0xD) = color;
                FIELD(temp_s0, u8, 0xC) = color;
                func_8003DB94(temp_s0, call_a1, zero);
            }
        }
        FIELD(temp_s0, s16, 0x1E) = 0x1800;
        FIELD(temp_s0, s16, 0x1C) = 0x1800;
        FIELD(temp_s0, u16, 0x14) = FIELD(temp_s0, u16, 0x14) | 0xC;
        FIELD(temp_s0, u16, 0x10) = FIELD(temp_s0, u16, 0x10) | 0x20;
        temp_a2 = FIELD(temp_v0, void *, 8);
        FIELD(temp_a2, s32, 0) = FIELD(arg1, s32, 0);
        FIELD(temp_a2, s32, 4) = FIELD(arg1, s32, 4);
        FIELD(temp_a2, s32, 8) = FIELD(arg1, s32, 8) -
            (((u8 *)&D_800DDC40)[FIELD(FIELD(arg0, void *, 0x14), u8, 0x13)] >> 1 << 16);
        func_8004491C(temp_v0, &D_80045340, temp_a2);
    }
}
