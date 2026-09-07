#include "common.h"

extern void func_8008BF0C(void);

void func_8008BFB0(void **arg0) {
    register void *record ASM_REG("$3");
    {
        register void *first_record ASM_REG("$2");
        u16 value;

        first_record = *arg0;
        value = *(u16 *)((u8 *)first_record + 0xA);
        value += 0x200;
        *(u16 *)((u8 *)first_record + 0xA) = value;
    }
    record = *arg0;
    if (*(s16 *)((u8 *)record + 0xA) >= 0x801) {
        *(u16 *)((u8 *)record + 0xA) = 0x800;
        func_8008BF0C();
    }
}

/* MECHANISM: A block-scoped first record is held in v0 while its explicit u16
   value occupies v1; the independent clamp reload is held in v1 across the
   signed test and call-delay-slot store. */
