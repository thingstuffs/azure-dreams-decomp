# Round 95 decisions (orchestrator, owner-delegated 2026-10-06: "make the decision on the best path, document anything that may need a second look")

Each line: decision - evidence - SECOND LOOK? (yes = owner may want to revisit).

## Taken
1. t122/t142 sweep output (14 pin-free rows: 12 goto->loop, 2 unwraps) was autocommitted ungated in 12be81432 (23:41Z) by the
   autocommit loop. KEEP if the isolated gate_all + SLUS build MATCH (gate log work/native_lane/_r95/gate_sweeps.log); revert those
   14 files if not. Each was byte-verified per row by sweep.py.
2. Arity (func_80094984 family): LAND the 3-arg chain (r95_sonnet_ar1 out/, 28 texts) after harmonising the prototype to
   `void (void *, void *, void *)` and renaming the definition's `s32 handler_param` -> `void *ptr2`. Evidence:
   work/native_lane/r95_arity_check/FINDINGS.md (dispatcher func_80097DE8 saves/restores $a2 around a call before jalr into the
   0x800D0510/0x800D0560 handler tables; direct callers set $a2). SECOND LOOK: no.
3. 800971DC `register s32 zero ASM_REG("$0")` -> `s32 zero = 0;` + `+ zero` (r95_opus_C): REFUSE - an add of a known-zero
   variable is the fake-dependency family (owner: refuse fake deps). Pin stays; recorded in ledger/refused_trades.jsonl.
4. 8184AF90 3 -> 0 at `2.7.2-cdk-G0 -fno-cse-skip-blocks` (r95_opus_C): ACCEPT as a pin-for-flag trade (owner ruling 09-18: trades
   positive; pinned text exact at the target cell = rule 2). Land via land_coherence.sh; record in recipe_trades.jsonl. SECOND
   LOOK: yes - it adds a crutch flag in a plain cdk module (flag census will want it reconciled later).
5. 800C5028 1 -> 0 via a shared `fail:` label (row already had a goto): ACCEPT (shared exit reached by 3+ jumps = plausibly original).
6. Dead copy/load rows 800A3D40, 8105A724, 81339F68 (DEAD-INSN): HARD BASKET. A pure-C dead copy is deleted by flow; every candidate needs a
   fake consumer (81339F68's adds a store retail lacks). Same for the pending r93_opus_fp1 items: (a) no-op RMW `&= 0xF7FFFFFF` on a u16
   field - REFUSE (fake no-op operation; keep the volatile); (b) type-pun `y = *(s32 *)&x` to keep a stack slot - REFUSE (shapes the frame,
   not the source; keep the volatile). Never-accessed 8-byte frames: stay HELD. SECOND LOOK: yes if you'd accept a dead-copy spelling.
7. main/func_800219C4: SDK object (PsyQ LIBCARD PATCH.OBJ, 416 bytes, matches retail per r91c_astra_al2) - route to the stock-object
   path (link the stock object as library code, provenance noted), out of the C pin campaign. Implementation: a later lane.
8. Composite rows (`asm("func_X")` data prefix + `.size` stamp, ~114 rows): KEEP the spelling (it encodes retail's data-in-.text
   layout faithfully); FIX tools/levels.py so it no longer counts them as `tail_call` (112 phantom rows). A row re-carve (data words
   as their own rows, as accepted for 8195281C) is the cleaner long-term option. SECOND LOOK: yes (re-carve is a row-identity call).
9. L5 predicate (r95_pt CENSUS.md section 4): ADOPT - drop sites keyed to functions the row does not define (SLUS merged defs),
   PASSTHRU only when the call is arity-short vs its definition, INDIRECT only for empty-arg slot calls, JT only while `goto *`
   remains, declared noreturn tails counted once (tail_call). Implemented by a tooling lane with tests; levels before/after recorded.
10. HARD BASKET (was "park"; renamed on the owner's request 10-06) list (r95_opus_dossier FIRST_LANES.md section 7, 20 rows / 43 pins): not abandoned: ledger/hard_basket.jsonl holds each row's class, why it is hard and the next
    measurement; normal row lanes skip it, mechanism lanes pick it up (r95_opus_B already refuted 81888810/8188E3A0 -> added to the hard basket).
11. Type phase 12: ALREADY APPLIED (a83e8dbf6, round 91; apply12.sh --dry-run 10-06: 135 done, 66 already landed/stale, 0 to land) -
    r95_wa2's "never applied" was wrong. Next type work = phase 13 (r91_types_p12/DESIGN.md HOW TO CONTINUE).
12. Cleanup approvals (CPU / tool, no model judgement needed): NON_MATCHING host-shim/stale strip (~22 rows; superseded - host shims serve the port build, only alt-C arms were promoted: r95_sonnet_nm1, 7 rows); the 23 pin-free
    crutch-flag / off-module rows retired at the module recipe via the equal-pins route (NARROWED by item 16: not laned); maspsx selfinc guard for the 10
    `_fold_selfinc_la` rows; the r91_luna_offby1 STATUS one-line fix (shape table excludes parked ovmovie).
13. Volatiles: the 50 SPU-band sites (15 rows) and 9 extern-volatile polled flags (7 rows) are probably real hardware/interrupt
    state - verify writers (Sonnet check) before adding to ledger/real_volatiles.jsonl; until then unchanged. SECOND LOOK: no.
14. Into-block gotos: r95_sonnet_ib1/ib2 measured 13 of 16 rows' into-block gotos as load-bearing (retail loop notes, shared tails,
   jump-table order). Do not serve more into-block lanes; record them as plausibly original.
15. Volatile verification (r95_sonnet_vol, VERDICTS.tsv): 26 sites / 11 slus rows REAL (SPU/DMA registers, polled SPUCNT/SPUSTAT,
    busy-wait delay locals) -> appended to ledger/real_volatiles.jsonl. All 9 extern-volatile sites (7 rows) are SCAFFOLDING (no poll
    loop, no callback writer, siblings use the globals plainly) - removal work, but load-bearing (dist 2-85 when removed), so it needs
    restructuring lanes. 13 libspu RAM-shadow sites UNSURE (SDK code; left as is). The lane's claimed free win (konami_runtime_w_800345B8 l.154
    volatile store) is NOT byte-exact: verify.py 585 vs 586 words, length-drift (the lane read lab listing dist 0 as exact) - dropped. SECOND LOOK: the UNSURE libspu shadow set.
16. Crutch retirement (item 12) narrowed after a closer look: of wa1's 20 pin-free recipe rows, the 5 non-SLUS ones were already served
    by alignment lanes and stayed open (8001C4D8 r93_sonnet_al3, 806D30B4/808B2B04 r92-r93, 80289BD4) or are owner-accepted
    (8028B994, r84); the 15 SLUS flag rows sit on 2.95.2 / 2.8.1 / stock 2.7.2 cells and may be SDK/library TUs, not game crutches,
    and lab.py cannot trial SLUS recipes. Not laned now; next step is a provenance census of those 15 SLUS TUs. SECOND LOOK: no.
17. Fable OPAQUE-BASE follow-up (r95_opus_E, nothing exact): HARD BASKET 800AED64, 81910A9C, 800A1020 with the mechanism recorded, not as
    impossible. 800AED64: allocator half SOLVED (q1: base set after func_80064D20 + join copy before func_80046884 = retail colours and
    memory order); remaining blocker = local-alloc update_equiv_regs substitutes a 2-ref constant base -> needs a third natural base ref
    before the copy (none found). 81910A9C: retail's loop DID have loop notes (flow loop-depth ref weighting decides the divide colours),
    so Fable's goto-loop route is refuted; multi-set carrier is a partial lever (295 -> 250). 800A1020: sched1 birthing boost beats a
    priority-1 store; combine decrements reg_n_sets when it folds a second set. Best texts: r95_opus_E/cand/. SECOND LOOK: no.
18. Terminology (owner 10-06): no row is "parked" in the pin campaign - stubborn rows go to the HARD BASKET (ledger/hard_basket.jsonl:
    id, pins, class, deciding pass, evidence lane, best text, why_hard, next). Builders/pools should skip basket rows for normal lanes;
    mechanism lanes and every round's dossier re-read the basket. (ovmovie stays owner-parked as a container - a different thing.)
19. One-trip `do { } while (0)` blocks as pin removers (r95_opus_H): HOLD. Finding: a loop note is a FULL sched1/sched2 barrier
    (sched_analyze_insn loop_notes branch: depends on every earlier reg use/set, flush_pending_lists), so a macro-style one-trip block
    around ONE statement reproduces retail on slus/w_80048B8C (either store) and town/func_8046C188 (staged text grows an existing
    one-trip block over five statements -> held in r95_opus_H/held/). Standing ruling: one-trip blocks are scaffolding (STATUS counts
    them; r19 keep_astra refused), so neither lands. SECOND LOOK: YES - if the owner accepts a single-statement `do{}while(0)` as a
    recovered macro body (e.g. a real #define with a name), these two rows (and w_80042560's 6-word diagnostic) become landable.
20. Owner rulings 10-06 on the second looks: item 19 ACCEPTED - a one-trip do{}while(0) barrier may land when it removes pins, TRACKED
    per row in ledger/onetrip_barrier_rows.jsonl (land_lanes.sh admits one-trip growth only for listed rows with fewer pins); item 4
    kept (compiler/flag alignment is next); autocommit loop STOPPED (it committed ungated sweep output); OPAQUE-BASE is NOT to be
    called impossible - keep attacking (a new mechanism lane), the in-EBB finding is "no route found yet in cdk", not a proof of absence.
21. ODDITIES (owner 2026-10-06): dungeon/func_8196096C's ASM_SCHED_BARRIER became ODDITY_SCHED_FENCE() (include/common.h, same
    zero-byte volatile-asm expansion; no runtime effect, compile-time ordering only). Evidence: exhaustive cdk audit (r95_fable_opaque2),
    30 flags/8 cells/-G, same-TU inline helper x2 + data defined in TU (12 = unchanged), one-trip blocks (best 4), asm nop (3) - only an
    empty volatile asm at that point is exact; one-off in the game -> most likely a header/debug macro that compiled to nothing.
    Tracked separately as a curiosity in ledger/oddities.jsonl and a STATUS line - NOT a pin, NOT a removal target. Guarded:
    kitlib.admissible refuses any new ODDITY_* in lane candidates; land_lanes.sh admits ODDITY_* growth only for ledgered rows.
    Pins 151 -> 150 / 81 -> 80 rows. 81329AC4 (REG pin on a page constant) is a different pin type: same test pending.
