# r121_twins: 278 exact C rows / 85,380 bytes

Base: `9fe78bff5269271682eeb182c738bdb15d4d8203` (`SCRATCH_HEAD` of the supplied external root). Work and outputs are confined to this lane and `private_root/`; the supplied root was never mutated and no commits were made. The separate Opus6 package is not installed or included.

| item | status | delivery / reason |
|---|---|---|
| 1. 28 queued pieces / 1,372 bytes | 7 leads; 21 refused as relocation-only twins | No queued piece admitted. Two complete 36-byte bodies have relocation-shaped twins but lack placement/low-address object provenance; five full switch bodies have fragment leads. The other 21 fail the exact twin rule or lack a complete containing extent. Per-piece table below. |
| 2. Seven stale monster banks | exact | 278 new C rows / 85,380 bytes; 7/7 full production windows byte-identical. Only the seven 40-byte floor wrappers from Opus6 remain raw code; they were explicitly excluded. Five banks also retain 56-byte raw header fragments, which are not relabelled. |
| 3. Remaining raw code / window-gap sweep | complete census; hits are leads | 1297 unique spans across all configured overlay windows; 1174 have at least one whole-body-shaped hit. All overlay MATCH code rows and 1,153 SLUS definition units were included; see `twin_census.tsv`, with word counts and full compressed hit details. |

## Bank deliveries

| bank file start | true base | new exact rows | new C bytes | gate |
|---|---|---:|---:|---|
| 0x129B060 | 0x8016F860 | 36 | 7,328 | MATCH |
| 0x12A1060 | 0x80169860 | 41 | 13,772 | MATCH |
| 0x12A7060 | 0x80163860 | 41 | 13,772 | MATCH |
| 0x12AD060 | 0x8015D860 | 37 | 9,192 | MATCH |
| 0x12B3060 | 0x80157860 | 41 | 13,772 | MATCH |
| 0x12B9060 | 0x80151860 | 41 | 13,772 | MATCH |
| 0x12BF060 | 0x8014B860 | 41 | 13,772 | MATCH |

Each admitted body is a whole-body twin at the instruction/register level. Every differing word is a `j`/`jal` target or a paired absolute-address relocation. The ordinary C template is renamed and its imports/data are mapped from retail pairs. Source declarations inherited from shared headers are renamed before preprocessing. Two callback families use signatures taken directly from matched resident bodies (`func_800AC82C`, `func_800AC7EC`, `func_800AD9B4`), rather than taking another wrapper's apparent contract. `import_contracts.tsv` binds all 983 direct call sites to matched callee bodies. The 21 indirect callback calls preserve the matched template's existing Callback declaration and four-argument call expressions (`indirect_contracts.tsv`); no new dynamic target or runtime contract is asserted. Short empty functions have separate complete `jr ra`/delay-slot extents following the prior body's complete return; no containing-function tail is split off.

The existing rowbase records for five banks were `solved`. The normal `tools/rowbase.py promote` path recompiled a proof candidate and checked every registered member before changing them to `proven`. Their extents and deltas are unchanged. This lets the normal window gate place and check compiler-generated switch tables. No compiler, assembler, flag registry or gate was changed. Every admitted src row has zero pins, asm and volatile; relocation masks were used only to find candidates, never to admit them. The full window compare checks all linked calls, absolute jumps and table contents without relocation masking. Static link placement is claimed; runtime reachability is not.

## Queue pieces

`refused` below means refused as a relocation-only twin/admission in this pass, not a compiler impossibility or a permanent park. Full prior continuation notes remain in `next.tsv`.

| container | queued file offset | queue bytes | status | reason |
|---|---|---:|---|---|
| town | 0x7f58ac | 88 | refused | Not a relocation-only twin: li-expansion opcode |
| town | 0x7f5858 | 76 | refused | Not a relocation-only twin: li-expansion opcode |
| dungeon | 0x8d1658 | 72 | refused | Complete containing function or data-accessor provenance remains unproven |
| dungeon | 0x1847144 | 72 | refused | Complete containing function or data-accessor provenance remains unproven |
| dungeon | 0x186c35c | 72 | lead | Fragment-only lead; complete function differs, so no source admission |
| dungeon | 0x18bf430 | 72 | lead | Fragment-only lead; complete function differs, so no source admission |
| dungeon | 0x18c59cc | 72 | lead | Fragment-only lead; complete function differs, so no source admission |
| dungeon | 0x18fb960 | 72 | refused | Complete containing function or data-accessor provenance remains unproven |
| dungeon | 0x190eb98 | 72 | lead | Fragment-only lead; complete function differs, so no source admission |
| dungeon | 0x1914128 | 72 | lead | Fragment-only lead; complete function differs, so no source admission |
| dungeon | 0x1967240 | 72 | refused | Complete containing function or data-accessor provenance remains unproven |
| town | 0x7f5808 | 72 | refused | Not a relocation-only twin: li-expansion opcode |
| town | 0x7f57c0 | 64 | refused | Complete containing function or data-accessor provenance remains unproven |
| town | 0x8385cc | 36 | lead | Whole-body shape agrees; placement/import or low-address object provenance still required |
| town | 0x844c8c | 36 | lead | Whole-body shape agrees; placement/import or low-address object provenance still required |
| town | 0x7f54f0 | 32 | refused | Not a relocation-only twin: literal immediate |
| town | 0x7f5778 | 32 | refused | Not a relocation-only twin: literal immediate |
| town | 0x832e4c | 32 | refused | Not a relocation-only twin: literal immediate |
| town | 0x8331f8 | 32 | refused | Not a relocation-only twin: literal immediate |
| town | 0x833468 | 32 | refused | Not a relocation-only twin: literal immediate |
| town | 0x2d3ecc | 24 | refused | Not a relocation-only twin: literal immediate |
| town | 0x2d3eec | 24 | refused | Not a relocation-only twin: literal immediate |
| town | 0x7fffd0 | 24 | refused | Not a relocation-only twin: literal immediate |
| town | 0x7ffff0 | 24 | refused | Not a relocation-only twin: literal immediate |
| town | 0x800010 | 24 | refused | Not a relocation-only twin: literal immediate |
| town | 0x800030 | 24 | refused | Not a relocation-only twin: literal immediate |
| town | 0x800050 | 24 | refused | Not a relocation-only twin: literal immediate |
| town | 0x800070 | 24 | refused | Not a relocation-only twin: literal immediate |

The `ori` versus `addiu` words in 0x7F5808/5858/58AC are opcode differences, not relocations. The wrappers at 0x7F54F0/5778 and 0x832E4C/331F8/33468 differ in literal arguments from their advertised matched twins. The six 0x7FFFD0..0x800070 wrappers and two 0x2D3E* stubs likewise differ in constants. Those differences are recorded, not masked away. The current reference row `func_80875124` also has a per-row `--aspsx-version=2.40` entry in `town.as_flags.jsonl`; its exact result is not evidence for inheriting that assembler flag at a new target. No assembler registry entry was added. The 0x8385CC/844C8C bodies have zero-HI address words; matching C shape does not prove whether these are linked runtime addresses or embedded unrelocated objects.

## Switch fragment leads

| complete diagnostic body | bytes | longest unchanged masked fragment | matched source | source file offset |
|---|---:|---:|---|---|
| 0x186b890 | 2836 | 104 B / 26 words | dungeon/func_818632E4 | 0x1883638 |
| 0x18becf0 | 1928 | 200 B / 50 words | dungeon/func_81893474 | 0x18b3670 |
| 0x18c4fd4 | 2624 | 96 B / 24 words | dungeon/func_818AAE60 | 0x18cb144 |
| 0x190ddb4 | 3628 | 132 B / 33 words | dungeon/func_818FA12C | 0x191a16c |
| 0x19137a4 | 2508 | 132 B / 33 words | dungeon/func_818FA12C | 0x191a16c |

Census spans can overlap between window views and include untyped gaps; their bytes are not a coverage sum.

`fragment_leads.tsv` retains up to twelve leads per full diagnostic body. Fragments do not establish a whole-function twin, callee contract or placement admission. Rebuilds, if pursued, should start with these matched idioms and the existing complete-body diagnostics.

## Verification and package

- Src: 278/278 exact at `2.7.2-cdk-G0`, aligned total/substitutions/indels = 0; all 7 complete window gates MATCH.
- Raw: 278 independently generated spimdisasm → m2c first passes, 76 exact. Baseline events contain their actual results, including differences/build failures; raw was never copied from matched src.
- Import audit: 983 body-backed calls, 0 unresolved. Registry and row database checks pass.
- Graph: 6,749 → 7,027 logical rows; source rows are singleton additions.
- Guarded installer: 13/13 checks passed.
- Private-root apply/recheck: live apply succeeded; immediate second plan empty; registry and row-db OK; graph regeneration unchanged; 278 src/raw hash pairs preserved.

`delivery_twins/` contains guarded `apply.py`, before/after SHA-256 inventories, append-only ledger transactions, sources/raw first passes, the graph, five rowbase promotions, receipts, census and continuation tables. The full before-images are retained for review. `--live --dry-run` is supported and dry-run wins. Protected/header/ledger drift and symlinks refuse before writes; installer failure rolls back. No live tree is changed by creating the package.

The package shares ledgers, physical graph, bank windows and rowbase inputs with other lanes. If Opus6 or another package lands first, rebuild against that combined base and rerun the normal proofs; do not bypass hash guards. Coverage events are supplied as integration records only, because this bank work is not the old 28-piece coverage queue.

## HOW TO CONTINUE

1. Apply this package to a review root at the recorded base with `python3 delivery_twins/apply.py --root R --live --dry-run`, then `--live`; an immediate repeat dry-run must be empty. Run the registry, row-db check, graph regeneration and the seven production window gates listed in `manifest.json`.
2. Land the separate Opus6 floor wrappers with guards rebased to the combined tree. They are the only raw code left in these seven bank windows; do not count their 280 bytes as this delivery.
3. For queue item 1, use `queue_analysis.tsv` for exact differing words and `fragment_leads.tsv` for full-body source leads. Resolve zero-HI object provenance/placement and the listed literal or opcode differences before admission. Preserve the containing-function and mixed-data holds.
4. For a subsequent sweep, sort `twin_census.tsv` by `words`. Its hits include incidental tiny stubs and untyped window gaps: prove an entry/extent and imports, then compile and gate the complete body. Re-run `scripts/census_post.py` only in an isolated root after any new admissions.

Per-row deliveries follow; each has its separate generated raw first pass and measured src receipt.

| row | file offset | bytes | status | matched template |
|---|---|---:|---|---|
| func_8127B350 | 0x129B350 | 500 | exact | dungeon/func_81251350 |
| func_8127B544 | 0x129B544 | 212 | exact | dungeon/func_81251544 |
| func_8127B618 | 0x129B618 | 364 | exact | dungeon/func_81251618 |
| func_8127B784 | 0x129B784 | 424 | exact | dungeon/func_81251784 |
| func_8127B92C | 0x129B92C | 1000 | exact | dungeon/func_8125192C |
| func_8127C1C0 | 0x129C1C0 | 544 | exact | dungeon/func_812521C0 |
| func_8127CB28 | 0x129CB28 | 8 | exact | town/func_8032FD14 |
| func_8127CB30 | 0x129CB30 | 324 | exact | dungeon/func_80976E28 |
| func_8127CC74 | 0x129CC74 | 148 | exact | dungeon/func_81252C74 |
| func_8127CD08 | 0x129CD08 | 100 | exact | dungeon/func_80F88C30 |
| func_8127D34C | 0x129D34C | 724 | exact | dungeon/func_80977A94 |
| func_8127D620 | 0x129D620 | 32 | exact | dungeon/func_800D481C |
| func_8127D640 | 0x129D640 | 44 | exact | dungeon/func_80977D88 |
| func_8127D66C | 0x129D66C | 32 | exact | dungeon/func_80F89D24 |
| func_8127D68C | 0x129D68C | 56 | exact | dungeon/func_80F89D44 |
| func_8127DB64 | 0x129DB64 | 852 | exact | dungeon/func_809782AC |
| func_8127DEB8 | 0x129DEB8 | 100 | exact | dungeon/func_80F88C30 |
| func_8127DF1C | 0x129DF1C | 100 | exact | dungeon/func_80F8A600 |
| func_8127DF80 | 0x129DF80 | 56 | exact | dungeon/func_80F8A664 |
| func_8127DFB8 | 0x129DFB8 | 56 | exact | dungeon/func_80F8A69C |
| func_8127DFF0 | 0x129DFF0 | 56 | exact | dungeon/func_80F8A6D4 |
| func_8127E028 | 0x129E028 | 56 | exact | dungeon/func_800CF1BC |
| func_8127E060 | 0x129E060 | 88 | exact | dungeon/func_81254060 |
| func_8127E0B8 | 0x129E0B8 | 56 | exact | dungeon/func_80F89D44 |
| func_8127E0F0 | 0x129E0F0 | 8 | exact | town/func_80092860 |
| func_8127E0F8 | 0x129E0F8 | 60 | exact | dungeon/func_812540F8 |
| func_8127E134 | 0x129E134 | 24 | exact | dungeon/func_81254134 |
| func_8127E14C | 0x129E14C | 252 | exact | dungeon/func_8125414C |
| func_8127E248 | 0x129E248 | 156 | exact | dungeon/func_81254248 |
| func_8127E2E4 | 0x129E2E4 | 144 | exact | dungeon/func_812542E4 |
| func_8127E374 | 0x129E374 | 76 | exact | dungeon/func_81254374 |
| func_8127E3E8 | 0x129E3E8 | 8 | exact | town/func_80092860 |
| func_8127E3F0 | 0x129E3F0 | 64 | exact | dungeon/func_812543F0 |
| func_8127E430 | 0x129E430 | 48 | exact | dungeon/func_81254430 |
| func_8127E460 | 0x129E460 | 268 | exact | dungeon/func_81254460 |
| func_8127E56C | 0x129E56C | 288 | exact | dungeon/func_8125456C |
| func_81281098 | 0x12A1098 | 696 | exact | dungeon/func_81257000 |
| func_81281350 | 0x12A1350 | 500 | exact | dungeon/func_81251350 |
| func_81281544 | 0x12A1544 | 212 | exact | dungeon/func_81251544 |
| func_81281618 | 0x12A1618 | 364 | exact | dungeon/func_81251618 |
| func_81281784 | 0x12A1784 | 424 | exact | dungeon/func_81251784 |
| func_8128192C | 0x12A192C | 1000 | exact | dungeon/func_8125192C |
| func_81281D14 | 0x12A1D14 | 1196 | exact | dungeon/func_81257D14 |
| func_812821C0 | 0x12A21C0 | 544 | exact | dungeon/func_812521C0 |
| func_812823E0 | 0x12A23E0 | 1864 | exact | dungeon/func_8127C3E0 |
| func_81282B28 | 0x12A2B28 | 8 | exact | town/func_8032FD14 |
| func_81282B30 | 0x12A2B30 | 324 | exact | dungeon/func_80976E28 |
| func_81282C74 | 0x12A2C74 | 148 | exact | dungeon/func_81252C74 |
| func_81282D08 | 0x12A2D08 | 100 | exact | dungeon/func_80F88C30 |
| func_81282D6C | 0x12A2D6C | 1504 | exact | dungeon/func_81258D6C |
| func_8128334C | 0x12A334C | 724 | exact | dungeon/func_80977A94 |
| func_81283620 | 0x12A3620 | 32 | exact | dungeon/func_800D481C |
| func_81283640 | 0x12A3640 | 44 | exact | dungeon/func_80977D88 |
| func_8128366C | 0x12A366C | 32 | exact | dungeon/func_80F89D24 |
| func_8128368C | 0x12A368C | 56 | exact | dungeon/func_80F89D44 |
| func_812836C4 | 0x12A36C4 | 1184 | exact | dungeon/func_812596C4 |
| func_81283B64 | 0x12A3B64 | 852 | exact | dungeon/func_809782AC |
| func_81283EB8 | 0x12A3EB8 | 100 | exact | dungeon/func_80F88C30 |
| func_81283F1C | 0x12A3F1C | 100 | exact | dungeon/func_80F8A600 |
| func_81283F80 | 0x12A3F80 | 56 | exact | dungeon/func_80F8A664 |
| func_81283FB8 | 0x12A3FB8 | 56 | exact | dungeon/func_80F8A69C |
| func_81283FF0 | 0x12A3FF0 | 56 | exact | dungeon/func_80F8A6D4 |
| func_81284028 | 0x12A4028 | 56 | exact | dungeon/func_800CF1BC |
| func_81284060 | 0x12A4060 | 88 | exact | dungeon/func_81254060 |
| func_812840B8 | 0x12A40B8 | 56 | exact | dungeon/func_80F89D44 |
| func_812840F0 | 0x12A40F0 | 8 | exact | town/func_80092860 |
| func_812840F8 | 0x12A40F8 | 60 | exact | dungeon/func_812540F8 |
| func_81284134 | 0x12A4134 | 24 | exact | dungeon/func_81254134 |
| func_8128414C | 0x12A414C | 252 | exact | dungeon/func_8125414C |
| func_81284248 | 0x12A4248 | 156 | exact | dungeon/func_81254248 |
| func_812842E4 | 0x12A42E4 | 144 | exact | dungeon/func_812542E4 |
| func_81284374 | 0x12A4374 | 76 | exact | dungeon/func_81254374 |
| func_812843E8 | 0x12A43E8 | 8 | exact | town/func_80092860 |
| func_812843F0 | 0x12A43F0 | 64 | exact | dungeon/func_812543F0 |
| func_81284430 | 0x12A4430 | 48 | exact | dungeon/func_81254430 |
| func_81284460 | 0x12A4460 | 268 | exact | dungeon/func_81254460 |
| func_8128456C | 0x12A456C | 288 | exact | dungeon/func_8125456C |
| func_81287098 | 0x12A7098 | 696 | exact | dungeon/func_81251000 |
| func_81287350 | 0x12A7350 | 500 | exact | dungeon/func_81251350 |
| func_81287544 | 0x12A7544 | 212 | exact | dungeon/func_81251544 |
| func_81287618 | 0x12A7618 | 364 | exact | dungeon/func_81251618 |
| func_81287784 | 0x12A7784 | 424 | exact | dungeon/func_81251784 |
| func_8128792C | 0x12A792C | 1000 | exact | dungeon/func_8125192C |
| func_81287D14 | 0x12A7D14 | 1196 | exact | dungeon/func_81251D14 |
| func_812881C0 | 0x12A81C0 | 544 | exact | dungeon/func_812521C0 |
| func_812883E0 | 0x12A83E0 | 1864 | exact | dungeon/func_8127C3E0 |
| func_81288B28 | 0x12A8B28 | 8 | exact | town/func_8032FD14 |
| func_81288B30 | 0x12A8B30 | 324 | exact | dungeon/func_80976E28 |
| func_81288C74 | 0x12A8C74 | 148 | exact | dungeon/func_81252C74 |
| func_81288D08 | 0x12A8D08 | 100 | exact | dungeon/func_80F88C30 |
| func_81288D6C | 0x12A8D6C | 1504 | exact | dungeon/func_81252D6C |
| func_8128934C | 0x12A934C | 724 | exact | dungeon/func_80977A94 |
| func_81289620 | 0x12A9620 | 32 | exact | dungeon/func_800D481C |
| func_81289640 | 0x12A9640 | 44 | exact | dungeon/func_80977D88 |
| func_8128966C | 0x12A966C | 32 | exact | dungeon/func_80F89D24 |
| func_8128968C | 0x12A968C | 56 | exact | dungeon/func_80F89D44 |
| func_812896C4 | 0x12A96C4 | 1184 | exact | dungeon/func_80977E0C |
| func_81289B64 | 0x12A9B64 | 852 | exact | dungeon/func_809782AC |
| func_81289EB8 | 0x12A9EB8 | 100 | exact | dungeon/func_80F88C30 |
| func_81289F1C | 0x12A9F1C | 100 | exact | dungeon/func_80F8A600 |
| func_81289F80 | 0x12A9F80 | 56 | exact | dungeon/func_80F8A664 |
| func_81289FB8 | 0x12A9FB8 | 56 | exact | dungeon/func_80F8A69C |
| func_81289FF0 | 0x12A9FF0 | 56 | exact | dungeon/func_80F8A6D4 |
| func_8128A028 | 0x12AA028 | 56 | exact | dungeon/func_800CF1BC |
| func_8128A060 | 0x12AA060 | 88 | exact | dungeon/func_81254060 |
| func_8128A0B8 | 0x12AA0B8 | 56 | exact | dungeon/func_80F89D44 |
| func_8128A0F0 | 0x12AA0F0 | 8 | exact | town/func_80092860 |
| func_8128A0F8 | 0x12AA0F8 | 60 | exact | dungeon/func_812540F8 |
| func_8128A134 | 0x12AA134 | 24 | exact | dungeon/func_81254134 |
| func_8128A14C | 0x12AA14C | 252 | exact | dungeon/func_8125414C |
| func_8128A248 | 0x12AA248 | 156 | exact | dungeon/func_81254248 |
| func_8128A2E4 | 0x12AA2E4 | 144 | exact | dungeon/func_812542E4 |
| func_8128A374 | 0x12AA374 | 76 | exact | dungeon/func_81254374 |
| func_8128A3E8 | 0x12AA3E8 | 8 | exact | town/func_80092860 |
| func_8128A3F0 | 0x12AA3F0 | 64 | exact | dungeon/func_812543F0 |
| func_8128A430 | 0x12AA430 | 48 | exact | dungeon/func_81254430 |
| func_8128A460 | 0x12AA460 | 268 | exact | dungeon/func_81254460 |
| func_8128A56C | 0x12AA56C | 288 | exact | dungeon/func_8125456C |
| func_8128D350 | 0x12AD350 | 500 | exact | dungeon/func_81251350 |
| func_8128D544 | 0x12AD544 | 212 | exact | dungeon/func_81251544 |
| func_8128D618 | 0x12AD618 | 364 | exact | dungeon/func_81251618 |
| func_8128D784 | 0x12AD784 | 424 | exact | dungeon/func_81251784 |
| func_8128D92C | 0x12AD92C | 1000 | exact | dungeon/func_8125192C |
| func_8128E1C0 | 0x12AE1C0 | 544 | exact | dungeon/func_812521C0 |
| func_8128E3E0 | 0x12AE3E0 | 1864 | exact | dungeon/func_8127C3E0 |
| func_8128EB28 | 0x12AEB28 | 8 | exact | town/func_8032FD14 |
| func_8128EB30 | 0x12AEB30 | 324 | exact | dungeon/func_80976E28 |
| func_8128EC74 | 0x12AEC74 | 148 | exact | dungeon/func_81252C74 |
| func_8128ED08 | 0x12AED08 | 100 | exact | dungeon/func_80F88C30 |
| func_8128F34C | 0x12AF34C | 724 | exact | dungeon/func_80977A94 |
| func_8128F620 | 0x12AF620 | 32 | exact | dungeon/func_800D481C |
| func_8128F640 | 0x12AF640 | 44 | exact | dungeon/func_80977D88 |
| func_8128F66C | 0x12AF66C | 32 | exact | dungeon/func_80F89D24 |
| func_8128F68C | 0x12AF68C | 56 | exact | dungeon/func_80F89D44 |
| func_8128FB64 | 0x12AFB64 | 852 | exact | dungeon/func_809782AC |
| func_8128FEB8 | 0x12AFEB8 | 100 | exact | dungeon/func_80F88C30 |
| func_8128FF1C | 0x12AFF1C | 100 | exact | dungeon/func_80F8A600 |
| func_8128FF80 | 0x12AFF80 | 56 | exact | dungeon/func_80F8A664 |
| func_8128FFB8 | 0x12AFFB8 | 56 | exact | dungeon/func_80F8A69C |
| func_8128FFF0 | 0x12AFFF0 | 56 | exact | dungeon/func_80F8A6D4 |
| func_81290028 | 0x12B0028 | 56 | exact | dungeon/func_800CF1BC |
| func_81290060 | 0x12B0060 | 88 | exact | dungeon/func_81254060 |
| func_812900B8 | 0x12B00B8 | 56 | exact | dungeon/func_80F89D44 |
| func_812900F0 | 0x12B00F0 | 8 | exact | town/func_80092860 |
| func_812900F8 | 0x12B00F8 | 60 | exact | dungeon/func_812540F8 |
| func_81290134 | 0x12B0134 | 24 | exact | dungeon/func_81254134 |
| func_8129014C | 0x12B014C | 252 | exact | dungeon/func_8125414C |
| func_81290248 | 0x12B0248 | 156 | exact | dungeon/func_81254248 |
| func_812902E4 | 0x12B02E4 | 144 | exact | dungeon/func_812542E4 |
| func_81290374 | 0x12B0374 | 76 | exact | dungeon/func_81254374 |
| func_812903E8 | 0x12B03E8 | 8 | exact | town/func_80092860 |
| func_812903F0 | 0x12B03F0 | 64 | exact | dungeon/func_812543F0 |
| func_81290430 | 0x12B0430 | 48 | exact | dungeon/func_81254430 |
| func_81290460 | 0x12B0460 | 268 | exact | dungeon/func_81254460 |
| func_8129056C | 0x12B056C | 288 | exact | dungeon/func_8125456C |
| func_81293098 | 0x12B3098 | 696 | exact | dungeon/func_81269000 |
| func_81293350 | 0x12B3350 | 500 | exact | dungeon/func_81251350 |
| func_81293544 | 0x12B3544 | 212 | exact | dungeon/func_81251544 |
| func_81293618 | 0x12B3618 | 364 | exact | dungeon/func_81251618 |
| func_81293784 | 0x12B3784 | 424 | exact | dungeon/func_81251784 |
| func_8129392C | 0x12B392C | 1000 | exact | dungeon/func_8125192C |
| func_81293D14 | 0x12B3D14 | 1196 | exact | dungeon/func_81269D14 |
| func_812941C0 | 0x12B41C0 | 544 | exact | dungeon/func_812521C0 |
| func_812943E0 | 0x12B43E0 | 1864 | exact | dungeon/func_8127C3E0 |
| func_81294B28 | 0x12B4B28 | 8 | exact | town/func_8032FD14 |
| func_81294B30 | 0x12B4B30 | 324 | exact | dungeon/func_80976E28 |
| func_81294C74 | 0x12B4C74 | 148 | exact | dungeon/func_81252C74 |
| func_81294D08 | 0x12B4D08 | 100 | exact | dungeon/func_80F88C30 |
| func_81294D6C | 0x12B4D6C | 1504 | exact | dungeon/func_8126AD6C |
| func_8129534C | 0x12B534C | 724 | exact | dungeon/func_80977A94 |
| func_81295620 | 0x12B5620 | 32 | exact | dungeon/func_800D481C |
| func_81295640 | 0x12B5640 | 44 | exact | dungeon/func_80977D88 |
| func_8129566C | 0x12B566C | 32 | exact | dungeon/func_80F89D24 |
| func_8129568C | 0x12B568C | 56 | exact | dungeon/func_80F89D44 |
| func_812956C4 | 0x12B56C4 | 1184 | exact | dungeon/func_8126B6C4 |
| func_81295B64 | 0x12B5B64 | 852 | exact | dungeon/func_809782AC |
| func_81295EB8 | 0x12B5EB8 | 100 | exact | dungeon/func_80F88C30 |
| func_81295F1C | 0x12B5F1C | 100 | exact | dungeon/func_80F8A600 |
| func_81295F80 | 0x12B5F80 | 56 | exact | dungeon/func_80F8A664 |
| func_81295FB8 | 0x12B5FB8 | 56 | exact | dungeon/func_80F8A69C |
| func_81295FF0 | 0x12B5FF0 | 56 | exact | dungeon/func_80F8A6D4 |
| func_81296028 | 0x12B6028 | 56 | exact | dungeon/func_800CF1BC |
| func_81296060 | 0x12B6060 | 88 | exact | dungeon/func_81254060 |
| func_812960B8 | 0x12B60B8 | 56 | exact | dungeon/func_80F89D44 |
| func_812960F0 | 0x12B60F0 | 8 | exact | town/func_80092860 |
| func_812960F8 | 0x12B60F8 | 60 | exact | dungeon/func_812540F8 |
| func_81296134 | 0x12B6134 | 24 | exact | dungeon/func_81254134 |
| func_8129614C | 0x12B614C | 252 | exact | dungeon/func_8125414C |
| func_81296248 | 0x12B6248 | 156 | exact | dungeon/func_81254248 |
| func_812962E4 | 0x12B62E4 | 144 | exact | dungeon/func_812542E4 |
| func_81296374 | 0x12B6374 | 76 | exact | dungeon/func_81254374 |
| func_812963E8 | 0x12B63E8 | 8 | exact | town/func_80092860 |
| func_812963F0 | 0x12B63F0 | 64 | exact | dungeon/func_812543F0 |
| func_81296430 | 0x12B6430 | 48 | exact | dungeon/func_81254430 |
| func_81296460 | 0x12B6460 | 268 | exact | dungeon/func_81254460 |
| func_8129656C | 0x12B656C | 288 | exact | dungeon/func_8125456C |
| func_81299098 | 0x12B9098 | 696 | exact | dungeon/func_81251000 |
| func_81299350 | 0x12B9350 | 500 | exact | dungeon/func_81251350 |
| func_81299544 | 0x12B9544 | 212 | exact | dungeon/func_81251544 |
| func_81299618 | 0x12B9618 | 364 | exact | dungeon/func_81251618 |
| func_81299784 | 0x12B9784 | 424 | exact | dungeon/func_81251784 |
| func_8129992C | 0x12B992C | 1000 | exact | dungeon/func_8125192C |
| func_81299D14 | 0x12B9D14 | 1196 | exact | dungeon/func_81251D14 |
| func_8129A1C0 | 0x12BA1C0 | 544 | exact | dungeon/func_812521C0 |
| func_8129A3E0 | 0x12BA3E0 | 1864 | exact | dungeon/func_8127C3E0 |
| func_8129AB28 | 0x12BAB28 | 8 | exact | town/func_8032FD14 |
| func_8129AB30 | 0x12BAB30 | 324 | exact | dungeon/func_80976E28 |
| func_8129AC74 | 0x12BAC74 | 148 | exact | dungeon/func_81252C74 |
| func_8129AD08 | 0x12BAD08 | 100 | exact | dungeon/func_80F88C30 |
| func_8129AD6C | 0x12BAD6C | 1504 | exact | dungeon/func_81252D6C |
| func_8129B34C | 0x12BB34C | 724 | exact | dungeon/func_80977A94 |
| func_8129B620 | 0x12BB620 | 32 | exact | dungeon/func_800D481C |
| func_8129B640 | 0x12BB640 | 44 | exact | dungeon/func_80977D88 |
| func_8129B66C | 0x12BB66C | 32 | exact | dungeon/func_80F89D24 |
| func_8129B68C | 0x12BB68C | 56 | exact | dungeon/func_80F89D44 |
| func_8129B6C4 | 0x12BB6C4 | 1184 | exact | dungeon/func_80977E0C |
| func_8129BB64 | 0x12BBB64 | 852 | exact | dungeon/func_809782AC |
| func_8129BEB8 | 0x12BBEB8 | 100 | exact | dungeon/func_80F88C30 |
| func_8129BF1C | 0x12BBF1C | 100 | exact | dungeon/func_80F8A600 |
| func_8129BF80 | 0x12BBF80 | 56 | exact | dungeon/func_80F8A664 |
| func_8129BFB8 | 0x12BBFB8 | 56 | exact | dungeon/func_80F8A69C |
| func_8129BFF0 | 0x12BBFF0 | 56 | exact | dungeon/func_80F8A6D4 |
| func_8129C028 | 0x12BC028 | 56 | exact | dungeon/func_800CF1BC |
| func_8129C060 | 0x12BC060 | 88 | exact | dungeon/func_81254060 |
| func_8129C0B8 | 0x12BC0B8 | 56 | exact | dungeon/func_80F89D44 |
| func_8129C0F0 | 0x12BC0F0 | 8 | exact | town/func_80092860 |
| func_8129C0F8 | 0x12BC0F8 | 60 | exact | dungeon/func_812540F8 |
| func_8129C134 | 0x12BC134 | 24 | exact | dungeon/func_81254134 |
| func_8129C14C | 0x12BC14C | 252 | exact | dungeon/func_8125414C |
| func_8129C248 | 0x12BC248 | 156 | exact | dungeon/func_81254248 |
| func_8129C2E4 | 0x12BC2E4 | 144 | exact | dungeon/func_812542E4 |
| func_8129C374 | 0x12BC374 | 76 | exact | dungeon/func_81254374 |
| func_8129C3E8 | 0x12BC3E8 | 8 | exact | town/func_80092860 |
| func_8129C3F0 | 0x12BC3F0 | 64 | exact | dungeon/func_812543F0 |
| func_8129C430 | 0x12BC430 | 48 | exact | dungeon/func_81254430 |
| func_8129C460 | 0x12BC460 | 268 | exact | dungeon/func_81254460 |
| func_8129C56C | 0x12BC56C | 288 | exact | dungeon/func_8125456C |
| func_8129F098 | 0x12BF098 | 696 | exact | dungeon/func_81275000 |
| func_8129F350 | 0x12BF350 | 500 | exact | dungeon/func_81251350 |
| func_8129F544 | 0x12BF544 | 212 | exact | dungeon/func_81251544 |
| func_8129F618 | 0x12BF618 | 364 | exact | dungeon/func_81251618 |
| func_8129F784 | 0x12BF784 | 424 | exact | dungeon/func_81251784 |
| func_8129F92C | 0x12BF92C | 1000 | exact | dungeon/func_8125192C |
| func_8129FD14 | 0x12BFD14 | 1196 | exact | dungeon/func_81275D14 |
| func_812A01C0 | 0x12C01C0 | 544 | exact | dungeon/func_812521C0 |
| func_812A03E0 | 0x12C03E0 | 1864 | exact | dungeon/func_8127C3E0 |
| func_812A0B28 | 0x12C0B28 | 8 | exact | town/func_8032FD14 |
| func_812A0B30 | 0x12C0B30 | 324 | exact | dungeon/func_80976E28 |
| func_812A0C74 | 0x12C0C74 | 148 | exact | dungeon/func_81252C74 |
| func_812A0D08 | 0x12C0D08 | 100 | exact | dungeon/func_80F88C30 |
| func_812A0D6C | 0x12C0D6C | 1504 | exact | dungeon/func_81276D6C |
| func_812A134C | 0x12C134C | 724 | exact | dungeon/func_80977A94 |
| func_812A1620 | 0x12C1620 | 32 | exact | dungeon/func_800D481C |
| func_812A1640 | 0x12C1640 | 44 | exact | dungeon/func_80977D88 |
| func_812A166C | 0x12C166C | 32 | exact | dungeon/func_80F89D24 |
| func_812A168C | 0x12C168C | 56 | exact | dungeon/func_80F89D44 |
| func_812A16C4 | 0x12C16C4 | 1184 | exact | dungeon/func_812776C4 |
| func_812A1B64 | 0x12C1B64 | 852 | exact | dungeon/func_809782AC |
| func_812A1EB8 | 0x12C1EB8 | 100 | exact | dungeon/func_80F88C30 |
| func_812A1F1C | 0x12C1F1C | 100 | exact | dungeon/func_80F8A600 |
| func_812A1F80 | 0x12C1F80 | 56 | exact | dungeon/func_80F8A664 |
| func_812A1FB8 | 0x12C1FB8 | 56 | exact | dungeon/func_80F8A69C |
| func_812A1FF0 | 0x12C1FF0 | 56 | exact | dungeon/func_80F8A6D4 |
| func_812A2028 | 0x12C2028 | 56 | exact | dungeon/func_800CF1BC |
| func_812A2060 | 0x12C2060 | 88 | exact | dungeon/func_81254060 |
| func_812A20B8 | 0x12C20B8 | 56 | exact | dungeon/func_80F89D44 |
| func_812A20F0 | 0x12C20F0 | 8 | exact | town/func_80092860 |
| func_812A20F8 | 0x12C20F8 | 60 | exact | dungeon/func_812540F8 |
| func_812A2134 | 0x12C2134 | 24 | exact | dungeon/func_81254134 |
| func_812A214C | 0x12C214C | 252 | exact | dungeon/func_8125414C |
| func_812A2248 | 0x12C2248 | 156 | exact | dungeon/func_81254248 |
| func_812A22E4 | 0x12C22E4 | 144 | exact | dungeon/func_812542E4 |
| func_812A2374 | 0x12C2374 | 76 | exact | dungeon/func_81254374 |
| func_812A23E8 | 0x12C23E8 | 8 | exact | town/func_80092860 |
| func_812A23F0 | 0x12C23F0 | 64 | exact | dungeon/func_812543F0 |
| func_812A2430 | 0x12C2430 | 48 | exact | dungeon/func_81254430 |
| func_812A2460 | 0x12C2460 | 268 | exact | dungeon/func_81254460 |
| func_812A256C | 0x12C256C | 288 | exact | dungeon/func_8125456C |
