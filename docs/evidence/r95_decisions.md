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
6. Dead copy/load rows 800A3D40, 8105A724, 81339F68 (DEAD-INSN): PARK. A pure-C dead copy is deleted by flow; every candidate needs a
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
10. Park list (r95_opus_dossier FIRST_LANES.md section 7, 20 rows / 43 pins): ACCEPT as tie-class residue; a mechanism lane may
    reopen a row with new evidence (r95_opus_B already refuted 81888810/8188E3A0 -> added to park).
11. Type phase 12 (work/native_lane/r91_types_p12/apply12.sh, 201 rows, verify-exact, never applied): APPLY after the r95 landing
    batch (dry-run, sample, gate), per the owner's type-consolidation ruling (09-28).
12. Cleanup approvals (CPU / tool, no model judgement needed): NON_MATCHING host-shim/stale strip (~22 rows); the 23 pin-free
    crutch-flag / off-module rows retired at the module recipe via the equal-pins route; maspsx selfinc guard for the 10
    `_fold_selfinc_la` rows; the r91_luna_offby1 STATUS one-line fix (shape table excludes parked ovmovie).
13. Volatiles: the 50 SPU-band sites (15 rows) and 9 extern-volatile polled flags (7 rows) are probably real hardware/interrupt
    state - verify writers (Sonnet check) before adding to ledger/real_volatiles.jsonl; until then unchanged. SECOND LOOK: no.
14. Into-block gotos: r95_sonnet_ib1/ib2 measured 13 of 16 rows' into-block gotos as load-bearing (retail loop notes, shared tails,
   jump-table order). Do not serve more into-block lanes; record them as plausibly original.
15. Volatile verification (r95_sonnet_vol, VERDICTS.tsv): 26 sites / 11 slus rows REAL (SPU/DMA registers, polled SPUCNT/SPUSTAT,
    busy-wait delay locals) -> appended to ledger/real_volatiles.jsonl. All 9 extern-volatile sites (7 rows) are SCAFFOLDING (no poll
    loop, no callback writer, siblings use the globals plainly) - removal work, but load-bearing (dist 2-85 when removed), so it needs
    restructuring lanes. 13 libspu RAM-shadow sites UNSURE (SDK code; left as is). Free win: konami_runtime_w_800345B8 l.154 volatile
    store removal is byte-exact (land after r95_sol61_s12, which holds that row). SECOND LOOK: the UNSURE libspu shadow set.
