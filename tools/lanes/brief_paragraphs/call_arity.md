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
