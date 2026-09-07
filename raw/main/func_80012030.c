/* family_delay_slot fixture - row foff 0x262030 [main], true base 0x80025030.
 * The row's rowbase record already fires (true base 0x80025030), so retail word 24
 * `j 0x250a4` is the FUNCTION-LOCAL if/else join jump (base + 0x74 = word 29).
 * The wave candidate still modelled it as a fake noreturn extern func_800250A4();
 * maspsx LEAD 18 flips jal->j but a CALL's delay slot can never hold the join's
 * first insn, so word 25 stayed `nop` where retail has `addiu $s0,$s0,4` (gcc dbr
 * steal-from-thread + redirect-to-target+4).  Written as a real if/else, gcc emits
 * the jump itself and fills the slot.
 */
#include "common.h"

extern void func_80023A50(s32, s32);
extern void func_800241D4(s32, s32);
extern void func_80024274(s32);
extern void func_80024F3C(s32, s32, s32);

#define FIELD(base, off) (*(s32 *)((u8 *)(base) + (off)))

void func_80025030(void *arg0) {
    s32 flag;
    register s32 i ASM_REG("$17");
    register void *cur ASM_REG("$16");

    if (FIELD(arg0, 0x48) == 1) {
        flag = 1;
    } else {
        func_80023A50(FIELD(arg0, 0x18), FIELD(arg0, 0x44));
        flag = 0;
    }
    i = 0;
    cur = arg0;
loop:
    if (i == FIELD(arg0, 0x28)) {
        func_800241D4(FIELD(cur, 4), flag);
    } else {
        func_80024274(FIELD(cur, 4));
    }
    cur = (u8 *)cur + 4;
    i += 1;
    if (i >= 5) {
        func_80024F3C(FIELD(arg0, 0x1C), FIELD(arg0, 0x28), FIELD(arg0, 0x44));
        return;
    }
    goto loop;
}
