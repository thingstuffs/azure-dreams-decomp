#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef struct {
    s32 word[6];
} Copy24;

extern void func_800248A0(void) __attribute__((noreturn));
extern void *func_8003FC64();
extern s32 func_8004491C();
extern u8 D_80024088[];
extern u8 D_800241CC[];

s32 func_818BCFB0(s32 *arg0, void *arg1, s16 arg2)
{
    s32 var_a2;
    void *temp_a3;
    void *obj;
    void *state;

    obj = func_8003FC64(0x212);
    if (obj != 0) {
        FIELD(obj, void *, 0x10) = D_80024088;
        func_8004491C(obj, D_800241CC);

        {
            register void *init_state ASM_REG("$2");
            register s32 init_value ASM_REG("$3");

            init_value = 0x7DCF;
            FIELD(obj, s32, 0x20) = *arg0;
            ASM_SCHED_BARRIER();
            init_state = (u8 *)obj + 0x20;
            FIELD(init_state, s16, 4) = 0;
            FIELD(init_state, s16, 6) = 0;
            FIELD(init_state, s16, 8) = 0;
            FIELD(init_state, s16, 0xA) = arg2;
            FIELD(init_state, s16, 0xC) = init_value;
            FIELD(init_state, s8, 0xE) = 0;
            ASM_KEEP(init_state);
            ASM_KEEP(init_value);
        }

        state = FIELD(obj, void *, 0xC);
        FIELD(state, s16, 0x1E) = 0x1000;
        FIELD(state, s16, 0x1C) = 0x1000;

        temp_a3 = FIELD(obj, void *, 8);
        var_a2 = arg2 * 3;
        *(Copy24 *)temp_a3 = *(Copy24 *)arg1;

        if (var_a2 < 0) {
            var_a2 += 3;
        }
        {
            register s32 result ASM_REG("$2");
            register s32 field ASM_REG("$3");
            register s32 scaled ASM_REG("$4");

            result = (s32)obj;
            ASM_KEEP(result);
            field = FIELD(temp_a3, u16, 0xA);
            scaled = var_a2 >> 2;
            field += scaled;
            ASM_KEEP(field);
            ASM_KEEP(scaled);
            FIELD(temp_a3, u16, 0xA) = field;
            func_800248A0();
        }
    }
    return 0;
}
