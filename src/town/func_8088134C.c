#include "common.h"

typedef void (*Callback)(s32);

extern void func_80700B64(void) __attribute__((noreturn));
extern s32 func_80700D74(u16 value);
extern u8 D_80700000[];

void func_8088134C(void) {
    s32 index = 0;
    s32 offset = 0;
    s32 result;

    ASM_KEEP(index);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    ASM_KEEP(offset);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    result = func_80700D74(*(u16 *)(D_80700000 + offset + 0x650));
    ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot contents depend on it */
    offset += 4;
    if (result != 0) {
        index++;
        ASM_TAILSLOT_PIN_TIED(index);   /* MATCH pin: retail delay-slot contents depend on it */
        func_80700B64();
        return;
    }
    ASM_KEEP(offset);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    ((Callback *)(D_80700000 + 0x6DC))
        [((s8 *)(D_80700000 + 0x6E4))[index]](index);
}
