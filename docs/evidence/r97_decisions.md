# Round 97 decisions (pickup 2026-10-06 evening; owner: "go with your recommendations, act on them")

Numbering continues docs/evidence/r96_decisions.md (items 1-15). The owner reviewed the round-96 SECOND LOOK list
and the pickup recommendations and agreed with all of them (2026-10-06).

16. **Round-96 second looks 1, 9, 11, 14 ACCEPTED as decided** (800A56D0 sibling clamp, rodata_owners for
    non-module rows, 819613A8 `&= 0xFFFF` before u16 stores, w_8005947C empty stub takes the status byte).
    Item 10 (load-bearing one-trips): ACCEPTED as statement-macro bodies - the 85 rows in
    ledger/onetrip_loadbearing.jsonl are no longer counted in STATUS's `do{}while(0)` scaffolding row (status.py
    reads both one-trip ledgers); the ledger stays visible and a row re-opens only with a new mechanism idea.
17. **Item 6 RESOLVED: func_80018A70 takes the three arguments its caller passes.** `main` has no rows in
    0x80018000-0x80019500, so 0x80018A70 is overlay-loaded code; its definer (src/dungeon/func_80285A70.c) sits in
    the same dungeon window block as the caller (func_802831D8). Retail's caller loads $a0-$a2 before the jal (the
    arity-0 call is total 6), so the call is byte truth. The definition was `void (void)`; it is now
    `void func_80018A70(void *caller_state, u32 block_extent, u32 color_command)` - unused parameters, byte-neutral
    (verify exact, total 0; the gate is not needed for that row: true_name + rowbase proven) and the caller's extern
    now agrees with the definition. Same direction as item 14 (the caller's bytes are the evidence for a callee whose
    body never reads its parameters).
18. **Item 8 stays REFUSED (pad-word struct cast at re-read sites).** Evidence found: main/func_8001B7F8 declares
    `PadState { s32 held; s32 unk_04; s32 pressed; }` at D_801379A8, so 0x801379B0 is `.pressed`. Reading EVERY
    access through that struct in the two main rows is NOT exact (8001EFC4 total 31 li-expansion, 8001FDA0 total 21
    code-motion), so the original did not spell these rows as plain struct reads; the held candidate's pun at
    selected sites only is still compiler imitation. Volatiles kept. No C row writes these words (all accesses are
    reads), so whether `volatile` is the original's (a pad/VSync callback writer) is open. Type phase 14: one
    declaration (PadState) for the six spellings, volatile where exactness needs it (OPEN_ITEMS 26).
19. **Hard basket +2: dungeon/func_819112CC, slus/w_800463EC (OPAQUE-BASE/LOOP).** Both were served by Opus and
    astra at their current texts and worked by the Fable OPAQUE-BASE lane (r95_fable_opaque) and r95_opus_A; they
    are the loop.c-invariance siblings of 81910A9C. Normal lanes skip them (basket 31 -> 33 rows).
20. **Held candidates need more work (owner 10-06)**: r96_sonnet_pr3/held (false 2-arg prototype, OPEN_ITEMS 23),
    main/func_8000F774 fake dependency (OPEN_ITEMS 25).
21. **slus/w_8004CAA0 register globals: surfaced, not yet counted as pins.** `$sp` is real machine state (stack
    switch to scratchpad 0x1F8003FC); keeping only `$sp` bound is not exact (total 16, length drift), so the
    `$3`/`$8`/`$5` bindings are doing pin work. pin_census.hidden_asm now reports file-scope global register
    variables as `reg-global` (4, this row only) and STATUS prints them in the hidden-scaffolding line. Provenance
    call pending (OPEN_ITEMS 24).
22. **Lost-compiler search, one more time (owner 10-06).** A low-IO `find /` (ionice -c3) for cc1/cc1psx/ccpsx/
    aspsx/cpppsx binaries and PsyQ/SDevTC/DTL archives found 235 cc1 files = 22 distinct binaries, every one already
    catalogued (fidelity_lostcc_A_sn_binaries.md, fidelity_step1c_compiler_inventory.md: SN32 0002/0004, SN16,
    DTL-S3040 2.7.2, 2.5.7/2.6.0/2.6.3, 2.8.1 SN 4.0.0010, 2.95.2 4.0.0030, egcs 2.91.66 and our rebuilds).
    Nothing new on disk. Targeted follow-up: the 39 gcc2 trunk snapshots hunt B left built
    (work/fidelity/lostcc/B/bin, 970403-970802 + 2.8.x variants) run on the pin-erased OPAQUE-BASE rows
    (work/native_lane/r97_trunk_opaque) - **RESULT: NEGATIVE.** Harness calibrated (pinned texts: identical bodies
    under cdk and r13838-noeh on all six rows; r13838-noeh = cdk on 58/58 erased rows). Over 41 cc1s (hunt-B set +
    r14477): no snapshot makes 81329AC4 (17), 800AED64 (39), 81910A9C (161), 8196096C fence-free (12), 819112CC (356)
    or w_800463EC (126) exact, and none changes the deciding order (81329AC4: the D_800E296C RMW still sinks below the
    lhu + three sh $0 page stores; 8196096C: the D_80027374 lui/addiu + lhu 4($4) still hoist above the scratch sw's),
    including r14536rev / r14639rev (hunt B's closest model of the lost production compiler). 58-row erased sweep
    (17 representative cc1s): no row exact anywhere; 52/58 erased bodies = cdk at every snapshot 04-03..07-10; only
    818B6AFC improves (62 -> 45, FSF 2.8 releases; not an OPAQUE-BASE row). Verdict: "a different 1997 gcc2 revision
    explains OPAQUE-BASE" is refuted for every compiler we hold; only an unpublished Cygnus-internal branch remains
    untested (no such cc1 exists locally). OPAQUE-BASE stays in the basket as a source question.
    Addendum (archives): the search's .zip/.img/.lzh/.7z hits are either already extracted hunt archives, game disc
    images (two Azure Dreams prototypes in ~/prototype, a non-toolchain bfm.img) or SDK archives whose cc1s are known -
    the one never-extracted SDK zip (toolchain/psyq/_archives/PSYQ_SDK.zip) holds CC1PSX 2.95.2 BUILD 4.0.0030 and
    2.6.3, both already catalogued (sha 0755e509f1.., d383902b6e..). Nothing left behind.
23. **dungeon/func_800A8714 (r97_opus_a2, 1 -> 0): the function-scope `idle_ally_range` also carries case 36's
    x_delta copy** (`idle_ally_range = x_delta; x_delta <<= 16; ... distance = idle_ally_range;`) - one variable
    in two roles in different switch cases: the accepted two-role temp class (r93/r94 trades, r96 decision 11's
    w_80047054). Mechanism (REPORT.md): a copy target whose last mention is this block never becomes the cse class
    head and shares $16 with distance; the in-place shift stops local-alloc optimize_reg_copy_1. SECOND LOOK: yes
    (the reuse exists for its allocation effect, the same reason item 11 was flagged; w_80047054's reuse was codegen-neutral).
    800995D0 (store reordered after an independent global read, roles split into locals) and 8028BAA4
    (`entry = &a[i]; entry--; x = *entry;`) are ordinary C. SECOND LOOK: no.
24. **dungeon/func_81989558 (r97_opus_a3, 1 -> 0): a static inline `grid_cell(grid, row, col)` accessor** (16 x 16
    grid of 4-byte points; `grid += row << 6; col <<= 2; return grid + col;`) replaces the open-coded case-1 address;
    ASM_KEEP_NV(ring) gone. Mechanism: the inlined `col` is set twice inside the loop, so loop.c
    consec_sets_invariant_p (loop.c:2951) refuses it as a movable and ring*4 is not hoisted / spilled (.cse/.loop
    dumps). An accessor function for a grid is ordinary C (same family as the OT_* macros, decision 13); it is used
    at ONE site (case 2 through the same helper scores 20), which is the weak point. SECOND LOOK: yes (single-use
    helper whose shape matters to loop.c; refuse -> revert to the KEEP and record in ledger/refused_trades.jsonl).
    Kit note: the lane's tools/loopsum.py (loop movables per candidate) found this - harvest into lanekit.
25. **REFUSED: slus/w_80054B08 negated-base subtraction (r97_astra_t2, exact at 1 pin, 3 -> 1).** The candidate
    writes `offset_base = -offset_base; status->field14 = second_offset - offset_base;` for `second_offset +
    offset_base`: cancelling arithmetic whose only job is a second set of offset_base through flow (combine erases the
    negation) - the refused fake-dependency class. The literal 0xFFFFFF masks in the same candidate are natural but
    alone give 1 pin at listing 2 / total 2. Candidate moved to the lane's held/; ledger/refused_trades.jsonl records
    what matched and the next lead (a real second set). SECOND LOOK: no (owner rule: still refuse fake deps).
