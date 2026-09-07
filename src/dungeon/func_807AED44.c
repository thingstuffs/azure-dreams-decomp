#include "common.h"

extern s32 D_80013718;
extern u16 D_80083460[];
extern s16 *D_800F8A44[];
extern s32 D_800814A0[];

void func_800F6544(void *arg0)
{
    s16 **entry;
    s16 **entry_base;
    s16 *value;
    s16 state;
    s32 count;
    u16 *flags;
    u32 page;

    if (*(s32 *)0x80013718 == 3) {
        page = 0x80080000;
        ASM_KEEP(page);   /* MATCH pin: retail immediate-load split depends on it */
        count = 1;
        flags = (u16 *)(page + 0x3460);
        entry_base = D_800F8A44;
        entry = entry_base + 1;
        do {
            value = *entry;
            if (value != 0) {
                state = 4;
                if (flags[1] & 0x80) {
                    state = 0x14;
                }
                *value = state;
            }
            count -= 1;
            entry -= 1;
        } while (count >= 0);
        ((u16 *)arg0)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}

/* MECHANISM: Frameless leaf; an absolute scalar lvalue makes the assembler reuse $v1
   for the D_80013718 lui/lw pair instead of gcc's separate symbolic page register.
   A held 0x80080000 page splits the flags address around count initialization as
   retail's lui / li / addiu while preserving both pointer inductions and the exact CFG. */
