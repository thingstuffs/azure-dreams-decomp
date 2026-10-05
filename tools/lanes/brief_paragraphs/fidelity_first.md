## Fidelity first: clean the row, THEN re-measure the pins (owner insight 2026-10-05, round 93 evidence)
Pins often compensate for decompiler debt rather than for a missing C shape, and fall TOGETHER with it. Round 93: Opus
lanes on rows whose gotos had just been replaced by real loops/switches removed 16 pins (r93_opus_p7/p9/p10: earlier
analyses at the m2c text were stale); typing a callee from its definition / the right call arity changed promotions
(r93_opus_p3 K&R u8, r93_opus_p9); a `volatile` on part bytes was what kept `lbu; sll; sra` (combine.py: no-recog
(volatile MEM)) on dungeon/func_800C9858. Order of work on a pinned row:
1. Fidelity: callee prototypes from the DEFINITION (rows are filed by file offset - look up by true_name;
   tools/lanes/proto_check.py), real call arity (call_arity paragraph), parameter widths (an s32 stack parameter
   tested as (p<<16)==0 is s16), D_ data externs with their agreed types, struct fields instead of raw offsets.
2. Structure: m2c goto loops -> real for/while (loop.c, loop-depth ref weighting), goto ladders -> switch (read the
   retail table), shared tails copied only where measured (brief_paragraphs/goto_recipes.md).
3. Scaffolding: try each `volatile` / one-trip `do {} while (0)` / fake dependency WITH the pins, not separately -
   erase.py --with-scaffold (when available) erases them as sites in pairs/all.
4. Only then re-run erase.py (singles, pairs, all) and map each surviving pin's deciding pass (why.py --deps-table,
   combine.py, prefs.py, alloc_need, dbr.py).
Each step must stay byte-exact on its own (stage it: fewer leftovers/gotos/scaffolding stages even with equal pins), so
the pin work starts from a clean, landed base.
