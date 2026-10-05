## Calls at the callee's REAL arity (round 85; r85_opus_par2 81332D28 and 8132530C to 0)
A pinned row's own `extern` prototype often has the wrong argument count for the callee's DEFINITION (m2c guessed).
Before the first call clobbers $a0-$a3, passing an incoming parameter through costs no instruction but COUNTS as a
register reference, and changes which entry moves combine merges - global.c order and the sched1 entry prefix flip,
which is what the pins were faking. Rule: compare every call's argument count with the callee's definition (find the
definition in the SAME container/overlay - func_ names are VRAM-named and overlays reuse addresses; check true_name /
src/<container>/INDEX.md), use the real count (pass the incoming parameters where the definition takes them; nothing
for a (void) callee), then re-run alloc_need. Never add arguments a callee does not take (PASSTHRU ruling).
Calibration (r85_sonnet_ar3): a call with MORE arguments than the callee definition is usually retail-real (the extra
register/stack args are in the retail bytes - the definition is the artifact); test by dropping and scoring first.
The paying case is a MISSING argument the callee takes (e.g. func_800C7930 -> 800C77D0 takes 4: passing the incoming
parameter through replaced an ASM_CLOBBER("$7")). A text census over-reports.

Return types too (r85_opus_m4): if every callee is declared void, a final `return <const>` can be scheduled after the last store, because its `(set v0 K)` is single-set and gets the birthing boost. Give library callees their real return type: RotMatrix/TransMatrix (func_80065820/func_80064BC0) return a MATRIX*. The value is then live in $v0 and the order changes. Check the callee's own row or the PsyQ prototype before you change a declaration.

**Parameter WIDTHS too (r93_opus_p26, dungeon/func_80CC085C 3 -> 0):** take the callee's parameter TYPES from its
definition, not only the count. An m2c prototype `s32 f(s32, s32, ...)` for a callee defined with s16 parameters makes the
caller stage the narrowing by hand (`(x << 16) >> 16`, REG pins on the converted value); with the definition's s16
prototype the call emits retail's `sll 16; sra 16` itself and those pins fall. Generator t143_protowidth does this
mechanically (and tries the row's pins erased jointly).
