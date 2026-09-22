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

typedef struct S_80025030_0 {
    u8 pad_00[0x18];
    s32 unk_18;
    s32 unk_1C;
    u8 pad_20[0x8];
    s32 unk_28;
    u8 pad_2C[0x18];
    s32 unk_44;
    s32 unk_48;
} S_80025030_0;   /* state in func_80025030 */

/* Draw the party panel: five slots, the one at index unk_28 drawn with the highlight flag. */
void func_80025030(S_80025030_0 *state) {
    s32 highlight;
    s32 i;
    s32 *cur;

    if (state->unk_48 == 1) {
        highlight = 1;
    } else {
        func_80023A50(state->unk_18, state->unk_44);
        highlight = 0;
    }
    i = 0;
    cur = (s32 *)state;
loop:
    if (i == state->unk_28) {
        func_800241D4(cur[1], highlight);
    } else {
        func_80024274(cur[1]);
    }
    cur = cur + 1;
    i += 1;
    if (i >= 5) {
        func_80024F3C(state->unk_1C, state->unk_28, state->unk_44);
        return;
    }
    goto loop;
}
