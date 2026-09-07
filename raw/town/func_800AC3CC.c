#include "common.h"

#define FIELD_U8(p, off) (*(u8 *)((u8 *)(p) + (off)))

extern s32 func_80033B2C();
extern s32 func_800A9878();
extern s32 func_800A99D8();
extern s32 func_800A9A38();
extern s32 func_800A9ADC();
extern s32 func_800A9BC0();
extern s32 func_800A9BFC();

extern u8 D_8006BC7A;
extern s32 *D_800D1038[];

s32 func_800A9B2C(s32 arg0, void *arg1) {
    register s32 temp_v0 ASM_REG("$16");
    register s32 **temp_addr ASM_REG("$4");
    register s32 **temp_base ASM_REG("$3");
    s32 temp_v1;
    s32 temp_a1;

    temp_v0 = func_800A9878();
    ASM_KEEP(temp_v0);
    if ((temp_v0 != -1) && (func_800A9ADC(arg0, arg1) != 0)) {
        if ((FIELD_U8(arg1, 1) == 13) && (arg0 == 9)) {
            if (FIELD_U8(arg1, 0) == 3) {
                if (func_80033B2C(0x12CB) != 0) {
                    u8 *dispatch_result;

                    dispatch_result = (u8 *)0x80070000;
                    ASM_KEEP(dispatch_result);
                    dispatch_result -= 0x4386;
                    ASM_TAILSLOT_PIN(dispatch_result);
                    return func_800A9BFC();
                }
                return 0;
            } else {
                ASM_SCHED_BARRIER();
                arg1 = (void *)3;
                ASM_TAILSLOT_PIN(arg1);
                return func_800A9BC0();
            }
        }
        arg1 = (void *)func_800A9A38(arg1);
        temp_v1 = func_800A99D8(temp_v0);
        temp_base = D_800D1038;
        ASM_KEEP(temp_base);
        temp_addr = (s32 **)((temp_v0 * 4) + (s32)temp_base);
        ASM_KEEP(temp_addr);
        temp_a1 = (temp_addr[0] + (temp_v1 * 4))[(s32)arg1];
        ASM_KEEP(temp_a1);
        return func_800A9BFC();
    }
    return 0;
}
