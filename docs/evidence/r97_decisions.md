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
26. **(r98) Per-row compiler evidence for two stock town rows** (r98_sol61_cell1 EVIDENCE.md; owner reminder that the
    epilogue pattern was studied before - the brief separated the step-1b production-compiler epilogue oddity, which
    constrains game code only, from the 2.6.3 reorg needed-set signature). town/func_808B2B04 stays 2.6.3-G0
    (supported: faithful 2.6.3/2.7.2 reorg traces reproduce the 2.6.3-only rule; the census module merges two index
    groups). town/func_806D30B4 stays 2.6.3-G0 (provisional: exact at 2.6.3, 6 off at 2.7.2, /20 expansion matches
    2.6.3; neighbours non-discriminating). Recorded in ledger/recipe_evidence.jsonl (row-scoped; the module census is
    not widened); STATUS's wrong-compiler tracker skips them while they stay at that cfg. main/func_8001C4D8 is the
    opposite case: its card-UI object is stock code, so its cdk recipe is a fit (best text total 5 at stock 2.7.2,
    open). **Revised (owner 10-07: decide compilers on the evidence; where it does not decide, leave UNCONFIRMED and name
    what would confirm):** 808B2B04 = supported (exempt); 806D30B4 = UNCONFIRMED - stays in the tracker, and
    ledger/recipe_evidence.jsonl `to_confirm` lists the measurements (a discriminating construct elsewhere in the same
    object, the object boundary near 0x653018-0x653434, or a 2.7.2-exact text). SECOND LOOK: no.
27. **(r98) The main_seg3 object (806D2898..806D35DC, 21 contiguous rows) is stock 2.6.3 - CONFIRMED** (r98_sol61_seg3
    VERDICT.md). The only 2.7.2-only signal (806D2C3C) was text: computing the loop-invariant control word before
    the loop makes it exact at both stock compilers (landed). The two rows that did not build at 2.6.3 had `//`
    comments (landed as C89 comments; exact at both). 806D30B4's /20 expansion is 2.6.3-only under every natural
    spelling (expmed highpart: 2.6.3 `=d` mfhi into $a2 vs 2.7.2 `=h` + reload via $t1). 806D30B4 -> confirmed in
    ledger/recipe_evidence.jsonl. The census module main_seg3.c also holds 7 non-contiguous rows (8094D004..80950CC0)
    that are a different grouping; the census still names stock 2.7.2 for the module (most rows are exact at both).
    Next (CPU, no lane): re-run the module recipe census with the contiguous object split from the 7 outliers.
28. **(r98) sn_main index 77 (808B2B04..808B3620, 13 rows) is stock 2.6.3 - CONFIRMED** (r98_sol61_snmain VERDICT.md).
    The only counter-signals were text: 808B2B98 / 808B2CB0's `addu` operand order comes from `p = base + q` (2.6.3
    expand_binop puts the REG ahead of the MEM operand); `p = base; p += q` is exact at both stock compilers (landed).
    808B34B0 did not build at 2.6.3 because of a `//` comment and a typedef-level `__attribute__((packed))` (C89
    comment + packed on the u32 member: exact at both, lwl/lwr kept; landed). 808B2B04's 2.6.3-only reorg needed-set
    witness then decides the object; 808B2B04 -> confirmed in ledger/recipe_evidence.jsonl.
29. **(r99) Composite rows are CARVE DEBT, not accepted source** (owner question 10-07: does keeping them make sense?). The
    `asm("func_X")` prefix of a composite row is another function's jump table or overlay data (e.g. dungeon/func_80283000:
    a table of code addresses 0x8001D4FC..0x8001E944 before func_8001607C's code; elsewhere Shift-JIS message text) that
    retail's overlay linker placed before this row's code; the original source had it in its owning module's .rodata/.data.
    r95 item 8 kept the spelling because it reproduces the bytes honestly, and named a re-carve as the long-term fix. So:
    STATUS lists them on their own "carve debt" line (112 rows) - not in the generic inline-asm row, and not as accepted;
    levels.py keeps them as L5 `inline_asm` residue (L5_EXCLUDE_COMPOSITE_ASM stays False). Resolution = module placement:
    a module built as one TU emits its switch tables / data in its own sections and the prefix arrays and `.size` stamps go
    (r99_astra_mod2 "complete function + data accounting"). Also r99: town/func_808BB138's r98 tail-lane text turned a
    tail_jump into two LABEL_AS_CALL fidelity sites (func_800009FC / func_80000A24) - in r99_sol61_fid*. Lander: equal-pin
    prototype / typing lanes land via READABLE_LANES=<lanes>; tools/land_admit.py admits live fidelity-site reductions.
30. **(r99) LOCAL-GLOBAL class (r99_opus_lg):** 81888810 / 8188E3A0 1 -> 0 landed - the address assignment folded into its
    first use as the last term of the x-sum (`... + (lower_right = &vertices[...])->x) >> 2`; an assignment inside an
    expression = uglier but pure C, owner ruling). The column was never global in retail: a longer local-alloc life
    (lreg_explain GEOMETRY "live past uid U") is the lever. REFUSED: 818B6AFC's always-false `if ((u32)tick >> 16) abort();`
    (byte-exact pin-free, but the check exists only to give flow a block boundary - same class r98 declined); recorded in
    ledger/refused_trades.jsonl with the lead. Hard basket 32 -> 30 rows. SECOND LOOK: no.
31. **(r101) Carve-debt re-carve representation (orchestrator, delegated):** for the 61 b-route prefixes whose table
    consumers have clone templates (r100_sol61_unreg PREFIXES.tsv), each unregistered physical consumer becomes its OWN
    row (split record + rowbase record + C file copied from the template with its bank's own addresses) - `instances` in
    ledger/splits is a count only and no c_path serves two records, so this is the existing representation, not a new
    one. The composite prefix splits into owner-specific data rows (r95 item 8 / 116005735 precedent): each jump table
    owned by its consumer and written as `func + offset` against that consumer's symbol; entry/vector/numeric words as
    their own data rows with census-evidenced owners (unknown owner = own address-named data row, recorded as
    owner-unresolved); the `asm("func_X")` alias + `.size` stamp leave the composite row. Native table emission by the
    consumer's own switch stays the later module-placement step. Lanes r101_sol61_rc1-rc7 (rc1 pilot), the 2 GAP
    functions in r101_sol61_gap, module-gate native .rodata in r101_astra_gate. SECOND LOOK: yes (row identity).
32. **(r105) A prefix that crosses a bank boundary is split AT the boundary (orchestrator, delegated).** town/func_806D23A4
    (packed CD pairs [0x651000,0x652800) / [0x652800,0x654000), both to 0x80016000) and town/func_80950CC0 (candidate
    0x8D1000 boundary) hold bytes of TWO load images. Representation: one rowbase record PER load image, each with its
    own placement receipt (loader call / packed record / descriptor consumer) and its own delta, never one record or one
    uniform delta across the boundary; the prefix becomes per-image data rows (decision 31 shapes: owner by explicit use,
    else owner-unresolved) that partition the original extent exactly; the registered body keeps its row id. An image
    whose receipt is not found stays HELD for that side only - the other side may land if its window proves alone.
    SECOND LOOK: no (follows decision 31 + the r103 brief's "no overlapping/spanning region without a load receipt").
33. **(r105) An orphan code fragment is stale-image residue DATA, not code (orchestrator, delegated).** town/func_802F100C's
    trailing 372 B at file [0x271220,0x271394) equal the tail of MAIN's func_804081AC [0x2711AC,0x271394) (same file
    offsets); TOWN zeroes the parent's first 116 B incl. the prologue, so no callable TOWN entry exists (r103_sol61_own3).
    Representation: the 488 B at the parent's exact extent [0x2711AC,0x271394) become ONE data row (bytes as `.word`
    data in a C initializer, zero head kept as zeros) named for its address, `ownership_status: owner-unresolved`,
    `residue: stale-image` with the MAIN parent id and the byte-equality receipt in its evidence; the rest of the prefix
    (104 B u16 table, remaining zero pad) are ordinary data rows. Never a rebuilt prologue, an invented entry, or C that
    claims to be TOWN code. Levels/STATUS count it as data (no fidelity site). SECOND LOOK: yes (a new residue class).
34. **(r105) Bank loader receipts before tool changes (orchestrator, delegated).** own3's static receipt (DUNGEON loader
    func_800A982C, selector s -> LBA 0x607F + (s-1)*12, 12 sectors to 0x80024000; DUNGEON extent LBA 0x3016) puts every
    normal-selector bank on a 0x6000 grid from file 0x1834800. All three held modules and both GAP functions sit on it
    (arithmetically consistent - only selector 49 has a receipt so far; per-selector receipts pending r105_sol61_bank: 1870800 = selector 11 incl. its callback at +0x7DC; 197281c = 54, assets to +0x9A8; 7e6a5800 = 56, grid to
    +0x35B8; GAP A = 44 at +0x1408 -> base 0x80025408; GAP B = 65 at +0x58C -> 0x8002458C). Where a receipt proves ONE
    load covering both of 1870800's adjacent intervals, one region record spanning them is the r103 brief's permitted
    representation and the r103 adjacent-regions gate patch is NOT landed (it voids every certificate for no consumer);
    it lands only if a module is found that genuinely needs two loads. SECOND LOOK: no.
35. **(r105) Placement-independent data rows may be gated without a proven rowbase region (orchestrator, delegated).**
    The window gate links a rodata-owner row at its proven true vram (overlay_local_gate.py:1660) because relocated
    words (pointers) only come out right at the right address. r105_sol61_own4's three town/func_802F100C rows (104 B
    u16 table, 312 B zero pad, 488 B stale-image residue) compile to objects with ZERO relocations, no undefined
    symbols, no text (evidence/D_802F*.object.txt, data_object_accounting.json): their bytes cannot depend on the link
    address, so the region requirement protects nothing there and only keeps decision 33's representation out.
    Ruling: a rodata-owner segment with no proven region links at the window's own linear vram IF its object has zero
    relocations, zero undefined symbols and an empty .text (asserted by the gate, fail-closed otherwise); the window's
    full byte compare is unchanged; such rows are recorded `placement: unproven` (no L4 module placement, no rowbase
    claim). Any row with a relocation still needs a proven region. Tool lane with tests + gate --all + a real
    certification run; then 802F100C lands as decision 33 drafted it. SECOND LOOK: yes (gate tool change).
36. **(r106) An identical-arm test on a field retail really loads is accepted, its unknown bit commented (orchestrator,
    delegated).** GAP B dungeon/func_81994D8C (r106_opus_gapB): retail loads `lhu actor+0x98` at five sites and then
    discards it. `fl = pl->unk_98; fl &= BIT; if (fl) S; else S;` keeps exactly that load (the and-insn writes its own
    pseudo, no REG_DEAD note, jump2 deletes branch + and but stops before the load). The read itself is retail-evidenced
    - the original source read the field there and its two outcomes compiled identically (e.g. equal constants) -
    which is the owner's "same statement in both arms is likely original copy-paste" ruling, not a fake dependency.
    Unlike the refused 818B6AFC always-false check (it ADDED a test retail lacks), nothing is added that retail does not
    execute. The BIT is not encoded in any byte: the text must say so (`/* +0x98 bit unknown: retail reads the field,
    both arms compile identically */`), never imply evidence; prefer a bit the sibling census tests on the same actor.
    SECOND LOOK: yes.
37. **(r108) Weak groups inside one bank image merge when one whole-bank TU reproduces every section placement
    (orchestrator, delegated).** r108_sol61_big1-6 found existing L3 rows inside banks 19de800, 7ce800, 1960800, 18a0800,
    1924800, 19c6800, 1918800 assigned to OTHER weak ledger groups. No weak dungeon group spans two bank images (census
    10-09: 443 groups, 0 multi-bank), and the "other" groups are naming twins of the same image (e.g. ovl_7e67b800.c =
    delta 0x80024000 - 0x19A8800 = bank 63 = ovl_19a8800.c; r107 gap1 reassigned func_819892A4 on that basis). An image
    can still hold several TUs, so the deciding evidence is layout: if ONE TU over the whole bank is byte-exact (GNU +
    genuine ASPSX + retail) INCLUDING the placement of every compiler-emitted rodata/data section (jump tables,
    strings, records - separately compiled TUs would each place their own), the bank is one TU and its weak groups merge
    into the bank module (guarded reassignment records citing the selector receipt + the whole-bank proof). A bank with
    nothing to discriminate (no TU-owned rodata, both partitions admit the same relocations - 7e6a5800) stays HELD.
    SECOND LOOK: yes.
38. **(r108, owner-approved 10-09) Grid banks are modelled as ONE TU; the TU boundary is not observable - amends 37.**
    Measured for dungeon_ovl_7e6a5800 (bank 56) and the family: SLUS TU starts are uniform mod 16 (221/205/217/231 over
    874 TUs, like in-TU functions) -> the linker does not pad objects; every evidenced owned data row in a grid bank sits
    in the head ahead of all text, none between code rows -> the linker groups sections across objects, so rodata
    placement cannot separate one TU from several (this corrects item 37's "layout" criterion); bank 56: one recipe
    (2.7.2-cdk-G0 x23), no byte-identical helpers, calls cross both ways, followers own no rodata (the one switch has 4
    cases -> compare chain), head = entry pointer + the entry's own 5-entry table. The only basis for its 1 + 22 split
    was census naming (delta-named ovl_7e6a5800 vs file-named ovl_197eb88). Ruling (owner: "go with the recommended
    approach"): every grid bank is ONE native TU; weak groups inside one bank image merge into it; membership evidence
    states `tu_boundary: "not observable (section-grouping link, no static duplicates, no recipe change)"` - the module
    certifies that this one-file source reproduces the image exactly, not how the original files were split. A bank
    that shows real multi-TU evidence (duplicated static helpers, data between text runs, a recipe change) is HELD as
    genuinely multi-TU. 7e6a5800 joins the next module lane. SECOND LOOK: no (owner-approved).
39. **(r109, owner-approved 10-10) A no-op read-modify-write that keeps a retail-evidenced read is accepted.** GAP B
    dungeon/func_81994D8C (r109_opus_gapB v52, byte-exact 873/873, promoted at 0x8002458C): retail performs `lhu
    actor+0x98` at five sites and discards it; at three of them retail's sched2 order needs the read to have NO in-block
    consumer at sched2, which the decision-36 identical-arm form cannot reach (MECHANISM.md section 4). The accepted
    spelling `p->unk_98 = p->unk_98;` gives the load a consumer through flow/combine/sched1; reload_cse_noop_set_p then
    deletes the same-value store, so the output holds retail's read and nothing retail lacks. Owner 10-10: accept "if it
    genuinely did the read" - plausibly a flag macro / define-driven update whose constants fold to a self-assignment in
    the retail build (a debug build may set a different value). Conditions: the read must be retail-evidenced at that
    site; the source comment says what is reconstructed (`/* +0x98 write-back: retail reads the field, the unchanged
    store compiles away */`); a self-assignment that keeps a load retail does NOT perform stays a refused fake
    dependency. Distinct from the refused `+ zero` (an added operation with no retail counterpart). SECOND LOOK: no.
40. **(r112) A re-carved row keeps its historical composite baseline record (rc1 precedent).** dungeon/func_81994800
    (GAP B prefix re-carve, decision 31): raw/dungeon/func_81994800.c is the frozen composite text (92 B data prefix +
    168 B body, 260 B); its ledger/baseline.jsonl record (65 words exact, 2026-09-07) measured that composite carve. The
    re-carve moves the 92 B into a data row; the fresh production window proves the 92 B data / 168 B code partition
    (r111_sol61_integ). Ruling: keep the historical record as the L0 fact about the frozen raw text, as for
    dungeon/func_80A1D000 (r101 rc1: 150-word composite record, row now 468 B); no invented 42-word raw measurement.
    The current partition is proven by the production window, not by the baseline. SECOND LOOK: yes (a data-row-aware
    re-baseline tool would let the record match the current carve; data-row baselining is an open tool gap, r105).
41. **(r112) DUNGEON bank 41 (file 0x1924800) is THREE TUs: a recipe change inside the bank (decision 38's criterion).**
    r112_sonnet_1924 (work/native_lane/r112_sonnet_1924/REPORT.md): func_819059A0 (runtime func_800251A0, 244 B) is exact
    only WITHOUT sched1 (`-fno-schedule-insns`, its registered row recipe); in the one-TU build at the bank recipe 3 words
    (1134/1138/1139) differ in ~370 pure-C compiles, all 315 dependency-legal orders of its 7 prologue statements included.
    Mechanism: sched1's birthing boost (single-set plain-register dest -> priority 0x7f000001) applies to the lui of
    D_800267B8 and the ticks load but not the status copy (SUBREG dest of the s8->s16 extension), giving 26,20,16; retail's
    16,20,26 is the unboosted / unscheduled order; the HIGH pseudo is always single-set (mips.md + cse), so no C lever.
    The whole bank at -fno-schedule-insns changes 7 other functions' lengths (10,228 vs 10,080 B); both neighbours need
    sched1. Layout cannot separate TUs (decision 38: section-grouping link; contiguous, no padding, no static callee).
    Ruling: model bank 41 as three consecutive native TUs in one load image - [head .. func_80025080], func_800251A0 alone at
    its row recipe (2.7.2-cdk-G0 -fno-schedule-insns), [func_80025294 ..] - not one TU with a per-function flag. The
    equally consistent alternative (one TU, a compiler-behaviour difference for one function) is not separable by any
    measured evidence; the split is the model that reproduces bytes with recorded recipes. SECOND LOOK: yes.
