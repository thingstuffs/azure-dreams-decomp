#include "common.h"

extern s32 D_80013718;
extern u16 D_80083460[];
extern s16 *D_800F8A44[];
extern s32 D_800814A0[];

/* Update both state targets and set flags when the mode is 3. */
void func_800F6544(void *data)
{
    s16 **state_slot;
    s16 **state_table;
    s16 *state_ptr;
    s16 state;
    s32 slot_index;
    u16 *flags;
    u32 flags_page;

    if (*(s32 *)0x80013718 == 3) {
        flags_page = 0x80080000;
        ASM_KEEP(flags_page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        slot_index = 1;
        flags = (u16 *)(flags_page + 0x3460);
        state_table = D_800F8A44;
        state_slot = state_table + 1;
        do {
            state_ptr = *state_slot;
            if (state_ptr != 0) {
                state = 4;
                if (flags[1] & 0x80) {
                    state = 0x14;
                }
                *state_ptr = state;
            }
            slot_index -= 1;
            state_slot -= 1;
        } while (slot_index >= 0);
        ((u16 *)data)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}

/* MECHANISM: Frameless leaf; an absolute scalar lvalue makes the assembler reuse $v1
   for the D_80013718 lui/lw pair instead of gcc's separate symbolic page register.
   A held 0x80080000 page splits the flags address around count initialization as
   retail's lui / li / addiu while preserving both pointer inductions and the exact CFG. */
