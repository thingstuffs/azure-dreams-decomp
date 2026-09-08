#include "common.h"

/* C-recipe probe (family_fold_detectors, 2026-07-29): the SAME idiom the LANDED
 * byte-exact func_8046958C (overlays/town/first_pass_matched/func_8046958C.c)
 * uses for the identical 68-byte shape — a register-pinned %hi PAGE BASE plus a
 * displacement, instead of a symbol reference. No `la` seed is emitted, so
 * maspsx's _fold_selfinc_la never fires and the retail split
 * (folded pre-loop access + preheader `addiu` completion) falls out of the C.
 * D_800CF85C == 0x800D0000 - 0x7A4 ; stride 4 (s32 scan).
 *
 * Named in TRUE space (2026-07-29 straggler pass): the town row at foff 0xDB84
 * sits in the PROVEN rowbase region xfer_town_B000, true link base 0x8008B2E4,
 * so owner decision B requires this TU to define func_8008B2E4 and never spell
 * the synthetic row name (tools/codex_wave.py::_naming_defect screens the raw
 * text; the gate refuses a synthetic-named TU in a proven region). The rename
 * moves no bytes — the body has no self-address or local-jump word — and the
 * production scorer still reports MATCH size=68 words_off=0.
 */
s32 func_8008B2E4(s32 arg0) {
    s32 *p = (s32 *)0x800D0000;

    ASM_KEEP(p);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    if (p[-0x1E9] != 0) {
        p += -0x1E9;
        do {
            if (arg0 == *p) {
                return 1;
            }
            p++;
        } while (*p != 0);
    }
    return 0;
}
