# Round 96 decisions (orchestrator, under the owner's 10-06 delegation: decide on best evidence, flag SECOND LOOK)

1. **town/func_800A56D0 fake dependency -> sibling two-sided clamp (ACCEPTED).** r96_opus_fd replaced
   `packet + depth_or_page - depth_or_page` (a refused fake dependency since r93_opus_fd1) with the two-sided otz clamp the
   row's siblings carry verbatim (`if (otz >= 0x1E0) otz = 0x1DF; if (otz < 0) otz = 0;` - func_800A3BF4:160-163,
   func_800AC9AC:149-152, func_800A5398:82-87). The `otz = 0` arm is dead (flow deletes its store); its compare keeps the
   first clamp's `otz = 479` live, which is what retail emits. Admissible because it is a copied block a human wrote in three
   sibling functions (owner 09-29: copied blocks OK), not cancelling arithmetic, volatile or a dead memory access.
   Evidence: work/native_lane/r96_opus_fd/MECHANISM.md. SECOND LOOK: yes (resolved 2026-10-06: see docs/evidence/r97_decisions.md items 16-18) (dead source code kept for its compiler effect,
   though copied from siblings). If refused: revert the row to the fake and record it in ledger/oddities.jsonl review.
2. **kitlib fake-dependency detector extended** (`x = x;`, `d += h; d -= h;`): tree scan finds exactly the census's sites
   plus slus/w_80043568 `slot = slot;` (new, in r96_sonnet_ot4). SECOND LOOK: no.
3. **dungeon/func_807B08F0 parameters s32 -> s16** (r96_sonnet_ot3, removes a one-trip): no in-tree caller; the third
   parameter was already s16 and the body sign-extends both. SECOND LOOK: no.
4. **81329AC4 is not an oddity candidate:** the empty-fence test is negative (hard basket `next` updated). SECOND LOOK: no.
5. **dungeon/func_8196012C `rand(primitive_word)` stays** (r96_opus_ca flagged a phantom argument): dropping it is not exact
   (total 7) - retail loads $a0 before `jal rand`, so the original call passed a value to an unprototyped rand (K&R-legal).
   Byte truth, not a defect. SECOND LOOK: no.
6. **dungeon/func_802831D8 arity** (r96_opus_ca): callee func_80018A70 is defined `void(void)` and this row is its only
   caller; the arity-0 text is total 9 (allocation row, r91). Left as is; route next as an allocation row with the
   arity-0 text as base. CPU check (r96): the PINNED text at arity 0 is total 6, not exact - retail loads $a1/$a2 before the jal, so
   the 3-argument call is byte truth; the `void(void)` definition in src/dungeon/func_80285A70.c may be a different overlay's
   function at the same address (overlay address overlap). SECOND LOOK: yes (resolved 2026-10-06: see docs/evidence/r97_decisions.md items 16-18) (which function really sits at 0x80018A70 for this caller).
7. **CALL-ARG class -> hard basket** (800C7F80, w_80042560, 8096C508, 800AE09C): r96_opus_ca MECHANISM.md is a sourced
   negative in this cdk cc1. SECOND LOOK: no.
8. **HELD: one-field struct cast at re-read sites only** (r96_sonnet_vb3: main/func_8001EFC4, main/func_8001FDA0,
   town/func_8080EEC4 - `((PadWord *)&D_801379B0)->value` replaces a volatile so cse does not forward a global re-read
   across a struct store). Reading ONE global through a struct pun at selected sites only, to steer cse's in_struct
   invalidation, reads as compiler imitation rather than recovered source (the same global is read plainly elsewhere).
   Kept the volatiles; candidates in the lane's held/. SECOND LOOK: yes (resolved 2026-10-06: see docs/evidence/r97_decisions.md items 16-18) (accept if the owner sees the pad word as a
   struct the original declared, e.g. a PadState overlay used at those sites).
9. **rodata_owners records for rows that are not one whole PsyQ module** (r96_opus_cg: the 80EDF000 clone family x5 +
   81886800). Each row owns its module's whole .rodata incl. other functions' jump-table words (kept as raw data words,
   as the old .text prefix arrays had them); every rodata_first_link check passes (one read-only section, relocations
   inside the span, zero cut). Accepted so the computed gotos become real switches. SECOND LOOK: yes (resolved 2026-10-06: see docs/evidence/r97_decisions.md items 16-18) (convention
   stretch of overlay_local_gate.rodata_owner's docstring; re-carve with module placement later).
10. **Pin-free one-trip blocks that are load-bearing -> ledger/onetrip_loadbearing.jsonl (tracked, not re-served).**
    r96_sonnet_ot1..ot7 served every pin-free one-trip row (~100 rows): 25 cleared with natural shapes; the ~85 rows
    listed are load-bearing by measured mechanism (loop-weight register priority 35, sched region/tie 32, reorg delay-slot
    prediction 6, cse block end 5, cross-jump 1, 6 only screened). Plain unwrap was exact on 0 of them. A `do { } while (0)`
    is exactly what a statement macro body expands to (`#define X(...) do { ... } while (0)`), so these are consistent
    with original macros - the same pattern accepted for pinned rows (owner 10-06, item 19 / ledger/onetrip_barrier_rows.jsonl).
    Decision: stop serving them; keep them visible in the ledger. SECOND LOOK: yes (resolved 2026-10-06: see docs/evidence/r97_decisions.md items 16-18) (owner: accept as macro bodies, i.e.
    retire them from the scaffolding count, or keep them as removal targets for a future mechanism idea).
11. **dungeon/func_819613A8 `x &= 0xFFFF; y &= 0xFFFF;` before their halfword stores (ACCEPTED as a spelling trade;
    r96_opus_cont, 2 -> 1 pins).** Explicit truncation before a u16 store is ordinary C (combine deletes it, no
    instruction); its effect is flow-time refs that order x/y above `row` in local-alloc. Unlike the refused no-op masks
    (r96_sonnet_vb1 `(x & 0xFC) >> 2`) it does not invent a value transform. SECOND LOOK: yes (resolved 2026-10-06: see docs/evidence/r97_decisions.md items 16-18) (it exists for its
    allocation effect). **slus/w_80047054 skip_bytes reused for the bound** (two roles, codegen-neutral rename) -
    the accepted two-role temp class (r93/r94 trades). SECOND LOOK: no.
12. **REFUSED: dungeon/func_800CA184 double address mask** (r96_opus_big, exact at 2 pins): `& mask & mask` exists only
    for flow-time refs - the refused 81910A9C shape. The PsyQ bitfield getaddr/setaddr spelling was measured (48-96, not
    exact). Recorded in ledger/refused_trades.jsonl; the row stays at 3 pins. SECOND LOOK: no.
13. **OWNER 10-06: item 12 REVERSED - double address mask accepted as a macro.** The double mask sits exactly at the
    `setaddr(p, getaddr(ot))` half of each OT link (single mask on the `setaddr(ot, p)` half) in TWO independent rows
    (800CA184, 81910A9C - the r93-refused case), with the masks held in locals as retail's registers show: the expansion of
    a getaddr/setaddr/addPrim macro set, not a fake dependency. Spelled as include/shared/ot_link.h OT_GETADDR/OT_SETADDR
    (ties the rows together). Landed: 800CA184 3 -> 2, 81910A9C 2 -> 1 (r96_cpu_otlink, gated MATCH). Rule for lanes: an
    idempotent re-mask at an OT-link site is the macro shape - use the shared macros; a re-mask elsewhere is still refused.
14. **slus/w_8005947C: the empty stub func_80058E64 takes the status byte** (r96_opus_p3, 1 -> 0 pins). Definition in
    src/slus/code.c changed `(void)` -> `(u8 status)` (empty body: byte-neutral, gated); the row's only caller passes
    `event_byte`. Evidence: retail leaves the masked status in $a0 before the jal and prefs.py reproduces 8/8 allocations
    from that argument's copy preference. Opposite direction of the phantom-argument rule (an empty stub's parameter list
    is not recoverable from its own bytes; the caller's are the evidence). SECOND LOOK: yes (resolved 2026-10-06: see docs/evidence/r97_decisions.md items 16-18).
15. **slus/w_8003E758 switch landed on the SHA-1 image gate (r96_opus_cg patch applied).** configure.py now chains
    slus_rodata_trim.py + slus_data_pieces.py for a data_pieces module that also owns .rodata; slus_modules.data_piece_plan
    exempts .rodata records (unit test test_rodata_record_needs_no_data_piece). SHA-1 MATCH, recipe repinned (10-line
    diff: the chained step), split ledger unchanged, 199 SLUS tests OK (test_configure_slus_data_pieces fixture updated
    from the retired -G32 recipe - those 2 failures predated this round). FOLLOW-UP (kit): prove_slus_ownership's
    data-piece branch rejects the receipt because the per-function retail compare MASKS 2 words (the jump-table
    address relocations against the TU's owned .rodata; diff 0, physical exact len 1041/1041) and the branch demands
    masked 0 - extend check_data_piece_record to accept .rodata-relocation masks proven by the image gate. SECOND LOOK: no.
