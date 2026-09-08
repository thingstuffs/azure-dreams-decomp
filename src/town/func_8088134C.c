#include "common.h"

typedef void (*Callback)(s32);

extern void func_80700B64(void) __attribute__((noreturn));
extern s32 func_80700D74(u16 value);
extern u8 D_80700000[];

void func_8088134C(void) {
    s32 index = 0;
    s32 offset = 0;
    s32 result;

    ASM_KEEP(index);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(offset);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    result = func_80700D74(*(u16 *)(D_80700000 + offset + 0x650));
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    offset += 4;
    if (result != 0) {
        index++;
        ASM_TAILSLOT_PIN_TIED(index);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_80700B64();
        return;
    }
    ASM_KEEP(offset);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    ((Callback *)(D_80700000 + 0x6DC))
        [((s8 *)(D_80700000 + 0x6E4))[index]](index);
}
