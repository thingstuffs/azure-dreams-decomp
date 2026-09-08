#include "common.h"

extern void func_8008BF0C(void **);

void func_8008BF5C(void **arg0) {
    register void *record ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    {
        register void *first_record ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
        u16 value;

        first_record = *arg0;
        value = *(u16 *)((u8 *)first_record + 0xA);
        value -= 0x100;
        *(u16 *)((u8 *)first_record + 0xA) = value;
    }
    record = *arg0;
    if (*(s16 *)((u8 *)record + 0xA) < -0x400) {
        *(s16 *)((u8 *)record + 0xA) = -0x400;
        func_8008BF0C(arg0);
    }
}
