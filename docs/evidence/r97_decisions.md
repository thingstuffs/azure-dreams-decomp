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
    (work/native_lane/r97_trunk_opaque) - result recorded below when it lands.
