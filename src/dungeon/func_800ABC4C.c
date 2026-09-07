/* family_delay_slot fixture - dungeon row at foff 0xCBC4C, 8 words.
 *
 * The row's rowbase record already fires: true link base 0x800B13AC (PROVEN
 * region xfer_dungeon_A3000), so owner decision B applies -- this TU defines
 * func_800B13AC and must never spell the synthetic row name anywhere in the
 * file (the collect/frontier naming screen, tools/codex_wave.py::_naming_defect,
 * matches on the raw text, comments included; the gate refuses the TU either
 * way).  Retail word 4 is `j 0x800B13AC` -- a jump to the function's OWN first
 * instruction, i.e. a LOOP BACK-EDGE, not a tail call.  The census candidate
 * modelled it as a self-recursive call `func_800B13AC()` (a fake zero-arg
 * extern that happens to name the function's own true address); maspsx LEAD 22
 * SHAPE A then flipped the jal to j and LEAD 19 elided the frame, reproducing
 * 7 of 8 words -- but a CALL's delay slot can never receive the loop induction
 * step, so word 5 stayed `nop` where retail has `addiu $a0,$a0,12`.
 *
 * Written as the loop it is, gcc's dbr fills the back-edge slot itself and the
 * leaf needs no frame at all -- no maspsx lever involved.
 *
 * Score with (the row identity is the synthetic name, which belongs on the
 * COMMAND LINE, never inside the TU):
 *   work/g3/overlay_func_compare.py --overlay dungeon --foff 0xCBC4C \
 *     --func "$(printf 'func_800%s' ABC4C)" \
 *     --c-file <this file> --match-config 2.7.2 \
 *     --container work/s3_splat/extract/DUNGEON_DUNGEON.BIN
 * -> MATCH ... size=32 words_off=0
 */
#include "common.h"

void func_800B13AC(void *arg0, s16 arg1) {
    for (;;) {
        s32 c = *(s8 *)arg0;
        *(s16 *)((u8 *)arg0 + 6) = arg1;
        if (c < 0) {
            return;
        }
        arg0 = (u8 *)arg0 + 12;
    }
}
