#include "common.h"

typedef void (*Callback)(s32);

extern void func_80700B64(void) __attribute__((noreturn));
extern s32 func_80700D74(u16 value);
extern u8 D_80700000[];

void func_8088134C(void) {
    register s32 index ASM_REG("$17") = 0;
    register s32 offset ASM_REG("$16") = 0;
    s32 result;

    ASM_KEEP(index);
    ASM_KEEP(offset);
    result = func_80700D74(*(u16 *)(D_80700000 + offset + 0x650));
    ASM_SCHED_BARRIER();
    offset += 4;
    if (result != 0) {
        index++;
        ASM_TAILSLOT_PIN_TIED(index);
        func_80700B64();
        ASM_KEEP(index);
        return;
    }
    ASM_KEEP(offset);
    ((Callback *)(D_80700000 + 0x6DC))
        [((s8 *)(D_80700000 + 0x6E4))[index]](index);
}
