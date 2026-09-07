#include "common.h"

extern void func_800B13D0(void);

void func_800B13CC(void *arg0, s32 arg1) {
    u16 *field = (u16 *)((u8 *)arg0 + 4);

    ASM_KEEP(field);
    *field = (u16)(*field | arg1);
    if (*(s8 *)arg0 >= 0) {
        field = (u16 *)((u8 *)field + 12);
        ASM_KEEP(field);
        arg0 = (u8 *)arg0 + 12;
        ASM_TAILSLOT_PIN_TIED(arg0);
        func_800B13D0();
    }
}
