## Fidelity first: clean the row, THEN re-measure the pins (owner insight 2026-10-05, round 93 evidence)
Pins often compensate for decompiler debt rather than for a missing C shape, and fall TOGETHER with it. Round 93: Opus
lanes on rows whose gotos had just been replaced by real loops/switches removed 16 pins (r93_opus_p7/p9/p10: earlier
analyses at the m2c text were stale); typing a callee from its definition / the right call arity changed promotions
(r93_opus_p3 K&R u8, r93_opus_p9); a `volatile` on part bytes was what kept `lbu; sll; sra` (combine.py: no-recog
(volatile MEM)) on dungeon/func_800C9858. Order of work on a pinned row:
1. Fidelity: callee prototypes from the DEFINITION (rows are filed by file offset - look up by true_name;
   tools/lanes/proto_check.py) - MEASURED one at a time: a definition prototype that makes the bytes WORSE means the
   original TU declared it K&R / implicit int (r94_fable_de48ec: two definition prototypes 13 -> 67; keep `extern s32 f();`), real call arity (call_arity paragraph), parameter widths (an s32 stack parameter
   tested as (p<<16)==0 is s16), D_ data externs with their agreed types, struct fields instead of raw offsets.
2. Structure: m2c goto loops -> real for/while (loop.c, loop-depth ref weighting), goto ladders -> switch (read the
   retail table), shared tails copied only where measured (brief_paragraphs/goto_recipes.md).
3. Scaffolding: try each `volatile` / one-trip `do {} while (0)` / fake dependency WITH the pins, not separately -
   erase.py --with-scaffold (when available) erases them as sites in pairs/all.
4. Only then re-run erase.py (singles, pairs, all) and map each surviving pin's deciding pass (why.py --deps-table,
   combine.py, prefs.py, alloc_need, dbr.py).
Each step must stay byte-exact on its own (stage it: fewer leftovers/gotos/scaffolding stages even with equal pins), so
the pin work starts from a clean, landed base.

**Round 93 correction (r93_opus_vb4, dungeon/func_800D1A48 4 pins + 12 volatiles + 2 one-trips + 2 gotos -> 0):**
a goto loop that measures 'retail-faithful' by `why.py --pass loop` loop count when structured may only look that way
because m2c's text keeps TWO lockstep walkers per object (`p` and `p2 = p + K`). Rewrite with ONE walker per pointer
(`quad[k+1]`, `packet + K` as expressions) before concluding: loop.c then combines every giv into retail's single
register (`addiu $18,$20,1`), substitutes single-use invariants into call arguments, and loop-depth ref weighting fixes
colours. Same lesson: r93_opus_p9 (800A02F0 one struct walker), r93_opus_p5.

**r93_opus_p25 (slus/w_8004B954 3 -> 0):** an m2c accumulator `a = i*k; ... a += k;` and a second pointer stepped in
lockstep with the first are both loop.c strength-reduction OUTPUT that m2c copied into the source: write `f(i*k)` at
each use and store everything off the ONE pointer (increments last) - loop.c rebuilds retail's registers itself
(same lesson as r93_opus_vb4/vb5/p19). A spilled argument reload that lands before a sched2 block head can be moved
INTO the block by putting its init at the top of the arm that uses it.
