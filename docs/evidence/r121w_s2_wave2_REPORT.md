## Wave 2 continuation addendum — 2026-10-17

**51 additional complete C rows / 21,936 additional bytes.** This is incremental to `delivery_wave1.patch` (SHA-256 `1fd97314bdaef083ae638d7899ebdda7ffa65c96ba2ec5d90d9f968ea82e4293`). Wave 1 was already applied: reverse-apply verification succeeded before any continuation edit. Its patch, results, holds and delivered evidence were retained. `delivery2.patch` uses the post-wave-1 tree as its preimage. No Git commits or external ref moves were made.

Production validation: **33 / 33 scoped windows MATCH**, including the final current-input audit.

### Per-item status

| Item | Status | New rows | New bytes |
|---|---|---:|---:|
| `dungeon/func_80E0D2E8` | goto-free home exact; six placements exact | 6 | 8,712 |
| `dungeon/func_809A3110` | symbolic palette home exact; 13 placements exact | 13 | 5,876 |
| `dungeon/func_80CE94C0` | structured switch home exact; five placements exact | 5 | 3,320 |
| `dungeon/func_81888068` | existing EffectColor layout exposed; home and placement exact | 1 | 260 |
| TOWN caller contracts | validated loader context and independent entries; exact placements | 26 | 3,768 |
| Largest 5,464-byte goto donor | held; action-block emission order remains unresolved | 0 | 0 |
| Grid donor | held; improved structured spelling has 3 substitutions / 0 indels | 0 | 0 |
| Two animation page donors | held; symbolic spelling has 2 substitutions / 0 indels each | 0 | 0 |

By original hold class: goto templates add 11 rows / 12,032 bytes; old twins2 scope holds add 14 rows / 6,136 bytes; bounded SDK holds add 26 rows / 3,768 bytes; pin/volatile templates add no rows. DUNGEON contributes 25 rows / 18,168 bytes; TOWN contributes 26 rows / 3,768 bytes. Every new row is a link-list placement of one existing TU. There are no new function definitions, copied clean C files, relink macros, pins, asm, volatile, NON_MATCHING, pragmas, gotos or comparison masks. Existing semantic bit operations remain intact. Four existing C homes and one existing module header change; these earn no coverage bytes. All five independently compiled home checks, including the EffectColor consumer and its original defining member, are byte-exact.

The actor cleanup is shared in the compiled output. Writing both structured cleanup arms initially gave seven register substitutions. The correction temporary had become a multiple-block variable. Giving the duplicated arm its own local correction restores the retail local allocation and lets the compiler share the exact tail. The path switch similarly repeats only its display statements within the existing function; the compiler emits the exact shared block. The palette body names `D_80175F70` directly, which preserves all 452 home bytes and emits the previously missing ELF low relocation. Its 13 targets no longer require literal-byte rebinding.

`EffectColor` already existed in `src/dungeon/func_81887570.c`. Its definition moves unchanged into `include/modules/dungeon_ovl_18a6800.h`, and the former definition is removed from that member. This makes the existing fade home independently compilable and leaves the aggregate with one consistent definition. The original 120-byte defining member and the 260-byte consumer both independently match; all header consumers are included in the scoped gate.

### TOWN load-context recovery

The conservative rowbase maps stopped before several callees. Their static load extent was already established separately in `docs/evidence/town_scene_loader_receipt.json` and `docs/evidence/town_script_modules.json`. The continuation revalidated the TOWN container hash, module-header words, descriptor words, destination, sector count and file offset directly from retail. It did not extend or rewrite a rowbase map. Both source and target callee lookup use only those validated load extents. Each accepted direct callee is backed by a complete matched definition or a complete relocation-only retail twin, with its full target-body proof retained in the compact receipt. Static placement makes no new runtime-residency claim.

That context supports 56 complete caller candidates. Only 27 also have a direct caller or adjacent-code-pointer authority inside the validated image. Of those, 26 match. One 84-byte caller still contains an unrelocatable literal table displacement and is held. Twenty other byte-exact candidates were removed from the staged link lists and split ledger because an independent entry reference was not established; nine further unreferenced candidates also failed source comparison. None of those 29 are delivered. Their prologue/preceding-return observations and complete-twin evidence remain available for continuation.

### Measurements and delivery

All 51 admitted comparisons have exact extent, zero substitutions and zero indels. Every changed twin word is checked against an ELF relocation of the required type. Standalone homes are checked before placements. The row database is valid, pre-existing registry records retain their values and byte order, and the generated view/module graph are updated. The final scope includes the edited sources, header consumers and the production link-list dependency closure: 19 changed link lists affect 66 placed rows, yielding 33 active windows in the combined scope. No full gate was run. The first launcher attempt rejected the stale generated source projection before certifying any window. The managed projection was refreshed with `tools/source_layout.py project build_ovl/layout_flat`, and the unchanged 33-window scope was submitted after a separate view preflight. The rejected launch is retained in `evidence2/gate_preflight_rejected.log`; it published no window receipts.

All raw first passes remain unedited genuine spimdisasm/m2c output. Their actual measurements are **0 exact, 35 compiling but different, 16 compiler failures**. These append to the baseline ledger without claiming L0 adoption. Exact source measurements append separately to promotions/reverify. Existing home edits get reverify facts. Integration level actions are listed in `levels_seed_needed2.tsv`.

Deliveries are `delivery2.patch`, `results2.tsv`, `holds2.tsv`, `touched_windows2.txt`, `gate2.log`, and this addendum. `results2.tsv` contains all 169 starting hold outcomes and all 51 newly admitted rows. There are **26 input records closed, 11 partially reduced records and 143 remaining hold records**. Original records can overlap, so record counts and summed residual bytes are distinct from disjoint delivered coverage. Independently unioning the residual intervals confirms that uncovered bytes decrease from 197,460 to 175,524, exactly the 21,936-byte delivery. `docs/evidence/r121w_s2_wave2_receipts.json` and `docs/evidence/r121w_s2_wave2_gate.json` contain compact text proofs and hashes; no objects or other binary artifacts enter the patch. `preimage_manifest2.json` binds the wave-2 before/after files and patch SHA-256.

### Holds by reason

| Current reason | Input records |
|---|---:|
| donor goto-free spelling not yet byte-exact | 77 |
| bounded remainder needs new C or stronger complete-entry evidence | 24 |
| matched callee contracts unresolved | 13 |
| complete donor extent overlaps a live row or exceeds bounded gap | 6 |
| complete twin needs independent entry evidence | 5 |
| donor pin/volatile-free spelling not yet byte-exact | 5 |
| remaining complete donor still has goto | 5 |
| bounded remainder lacks a proven load region or complete body contract | 4 |
| donor address pieces lack ELF relocations | 2 |
| remaining complete donor still has pins/volatile | 1 |
| remaining donor address piece lacks ELF relocation | 1 |
| Total | 143 |

### HOW TO CONTINUE

1. Apply `delivery2.patch` only after `delivery_wave1.patch`; use `preimage_manifest2.json` to verify the baseline. Do not re-add either delivery's rows. After new row additions, refresh both `tools/row_db.py export build_ovl` and `tools/source_layout.py project build_ovl/layout_flat` before gating. The per-item outcomes and exact residual intervals are in `results2.tsv` / `holds2.tsv`.
2. Continue the largest donor, `dungeon/func_812A524C`, first. Its six held placements represent 32,784 bytes. The initial structured spelling from wave 1 remains better than the wave-2 common-cleanup rewrite (5,500 generated bytes, 131 substitutions / 293 indels). The unresolved feature is the three early action blocks and their later search exits; the unchanged home remains exact at its fingerprint-supported `2.7.2-cdk-G0` lineage. No compiler-wall claim is made.
3. Use `candidates/grid_role2.c` for the grid: reusing the point cursor prevents the unwanted invariant hoist and reduces the structured candidate to 3 substitutions / 0 indels, with frame and saved-register roles otherwise correct. The base currently uses s2 instead of retail's preserved s4; the later projection call rematerializes the address instead of copying s4. `grid_role_keep2.c` restores that last use but reintroduces the hoist (3 substitutions / 4 indels). Resolve those live ranges together. Do not land either near miss.
4. For `dungeon/func_809A1A8C` and `dungeon/func_812A85D4`, the `*_symbol_late2.c` candidates preserve extent with only 2 substitutions / 0 indels each. The entire residue is `lui v0; addiu a1,v0` versus retail's `lui a1; addiu a1,a1`. Local/direct-pointer spellings perturb the earlier allocation; preserve the scalar's earlier register role while resolving the address pseudo's basic-block lifetime. Keep genuine symbol relocations.
5. For bounded TOWN holds, reuse the validated loader contexts in `evidence2/town_load_contexts2.json` and the complete contracts in the wave-2 receipt. Investigate independent caller/pointer-table entry evidence for `evidence2/entry_context_absent2.json` before admitting any of those 29 candidates. `evidence2/held_missing_entry2.json` records the 20 exact but withheld cases. The remaining referenced 84-byte caller at file `0x3F2880` needs a symbolic table spelling; its current home `town/func_8028F414` leaves a literal displacement with no ELF relocation.
6. After the largest donor, prioritize the six 1,768-byte targets (10,608 bytes) and six 1,732-byte targets (10,392 bytes). `candidates/action_cleanup2.c` is a goto-free spelling of the latter at exact extent with 4 substitutions / 8 indels; its residue is switch-tail layout. Other goto/pin families retain their measured candidates under `candidates/` and `evidence/scores/*/w2_*`. The 1,504/1,464-byte cleanup siblings still duplicate code after their goto-free conversion; the 1,924-byte switch cleanup changes block layout. These remain source-shape problems, with no version-wall conclusion. Work from retail register roles and emission order, not masked comparisons.
7. Reuse `continue2.py`, `plan_cleaned2.py`, `contract_context2.py` and `admit2.py` only after refreshing live ownership. `admit2.py` excludes load-context candidates lacking independent entries. Keep one mutation runner. Once new source changes are complete, recompute the header/link-list dependency closure and run exactly one scoped gate with `--workers 4 --only-window ...`. Preserve all raw outcomes and capture fresh post-wave-2 preimages and deliver the next delta on top of wave 2 under new artifact names.
