#include "common.h"

extern void func_8008BF0C(void **);

void func_8008C004(void **arg0) {
    register void *record ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    {
        register void *first_record ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
        u16 value;

        first_record = *arg0;
        value = *(u16 *)((u8 *)first_record + 8);
        value -= 0x200;
        *(u16 *)((u8 *)first_record + 8) = value;
    }
    record = *arg0;
    if (*(s16 *)((u8 *)record + 8) < -0x800) {
        *(s16 *)((u8 *)record + 8) = -0x800;
        func_8008BF0C(arg0);
    }
}
