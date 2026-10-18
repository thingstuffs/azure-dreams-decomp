r121w_proto1a: prototypes and types

This is a partial delivery against the private B13 snapshot `ddc07bc5949684593cdc45a67e378a1f18324318`. The patch changes **406 queued C files**: 363 overlay files and 43 SLUS files. It changes no other C file, shared header, compiler recipe, link list, or ledger. Shared headers added or changed: **none**. No binary or retail payload is part of the delivery.

The complete queue has **437 per-file results** in [results.tsv](results.tsv). Its M2C token count falls from **1,121 to 243**, removing **878 tokens (78.32%)**. Home sources fall from 1,090 to 212 tokens; the six excluded copies retain their original 31 tokens. Of the 406 edited files, 403 reduce tokens; three retain their token counts with compatibility-include or typedef-spacing housekeeping, and their data declarations remain held.

| Per-item status | Files | Meaning |
|---|---:|---|
| DONE | 265 | No M2C token or identified home-signature follow-up remains |
| PARTIAL | 131 | Verified edits delivered; unresolved data declarations remain |
| PARTIAL_HOME_PROTOTYPE | 10 | Caller ABI is byte exact; exact placed-callee signatures are supplied in the separately checked follow-up patch |
| HOLD_DATA_EVIDENCE | 25 | Original source retained because its data type or extent remains unproved |
| SKIP_NON_HOME_COPY | 6 | Explicit relink copies left untouched for LL4, as BRIEF requires |

All M2C function-declaration tokens in the home queue files have been removed. There are 273 files with zero M2C tokens, including eight that still have an exact-home-signature follow-up. The remaining 212 home tokens are **211 data declarations and one necessary local compatibility typedef**. The data holds span 158 home files. Each unresolved declaration has its own [holds.tsv](holds.tsv) entry with a use-site witness and a continuation step. Eleven home-signature refinements and the six excluded copies also have hold entries.

**What was delivered**

Function declarations use identified home C definitions, with compatibility integer aliases normalized to their actual signed width. Local tagged records use matching forward declarations; small anonymous records needed by an interface are declared with the definition's fields. Existing applicable concept declarations and actual caller expressions establish the other argument categories and return uses. [declaration_evidence.tsv](declaration_evidence.tsv) records 436 current declaration replacements. Exact-home refinements found after the primary source freeze are explicitly held below rather than counted as completed interfaces.

A late link-list audit followed `source_row` through the source-layout resolver and found 11 further exact-home refinements across ten files. All ten follow-up candidates pass their row checks. [prototype_followup.patch](prototype_followup.patch) applies **after** the primary patch; [prototype_followup.json](prototype_followup.json) records the home, exact declaration, both source hashes, and check receipts. These refinements are outside the frozen primary gate. I started that gate before completing this placement audit, so the follow-up has an explicit scoped-gate hold rather than an unearned full-window claim. Its four-window scope is [prototype_followup_windows.txt](prototype_followup_windows.txt).

Data declarations use an applicable concept record/declaration or an actual function declaration when the symbol is a code address. Callback resolution checks the load address and bank, not just a synthetic row number. A false `D_800D1658` callback match was rejected because `town/func_800D1658` actually loads at `0x800CEDB8`. Three town data declarations were also restored to holds because a dungeon header at the same numerical address does not establish their type. These rejected interpretations are preserved in the evidence, not in the patch.

Local integer aliases preserve the original signed width and pointer stride. Fully specified callback typedefs received ordinary names. Unused FIELD/BREAK/SYNC macro definitions were deleted, and the direct MEMCPY alias became `memcpy`. No live trap or synchronization behavior was approximated. No cast, pin, asm, volatile qualifier, NON_MATCHING arm, pragma, goto, or mask was added to force a match.

**Signature mismatches found: original-prototype evidence**

Six caller rows, involving five C-defined functions, reject the identified definition's signature. Their original B13 rows verify exact; their current caller-supported declarations also verify exact. The rejected exact signature either fails to compile the call or changes the generated words. [signature_mismatches.json](signature_mismatches.json) retains the defining source, failed check, original exact check, current declaration, and caller-expression evidence.

| Caller(s) | Tree definition | Delivered caller ABI / evidence |
|---|---|---|
| main/func_80010194, main/func_8001442C | `func_8004E994`: `void(void)` | `void(s32)`; caller passes a dereferenced word |
| town/func_8009A5F4 | `func_800352FC`: `void(void)` | `s32(Rec_func_80097D54_arg0 *, s32, s32, s32)`; four arguments and tested return |
| town/func_80098218 | `select_lowest_corrected_probe`: parameter 5 is `u16` | Parameter 5 remains `s32`; the exact definition changes 10 aligned words (7 substitutions, 3 indels), while retaining this signed width restores the exact row |
| town/func_800AA878 | `update_linked_part_position`: two pointer parameters | `void(void *, s32, void *)`; this caller supplies three arguments |
| town/func_806C90F8 | Same-bank placement resolves to `get_linked_record_field_2_d_60`: `s32(void)` | `s32(s32, s32)`; caller supplies two words and tests the result; the exact home signature fails with too many arguments |

Two additional rows disagree with an available header (`func_80017724` and `func_8001A418`). No home C definition was established there, so those are header disagreements rather than additional C-definition mismatch claims. The same-identifier definition for `query_referenced_flag_for_table_entry` belongs to another bank and is not counted as original-prototype evidence. A numerical `func_800B39E4` match was likewise rejected: the dungeon row loads at `0x800B9144`; the town placement actually shares `clear_item_menu_entry_groups(s32)`, whose exact signature passes in the follow-up. `save_and_clear_entity_flag_ten` has two differing tree definitions; this caller matches the no-argument definition. The two formerly `D_...` callback declarations now use their home signatures; their fields preserve the observed three-argument indirect-call ABI, while the targets have two parameters and return void. Those callback ABI differences are recorded in `evidence/prototype_finish.json`.

**Validation and scope**

All **406 delivered files pass** their final source-hash-bound checks, indexed by [row_proofs.tsv](row_proofs.tsv). Overlay checks compare the complete registered row with retail at its recorded recipe. SLUS checks compare every allocated section, defined symbol, and relocation of the physical TU with the B13 object; all 43 affected SLUS rows are standalone physical units. The affected certified overlay module, `town_minigame_dispatch_44b44`, also compiles as a combined TU with the staged changes. The row database and link-list checks report `row database OK`.

The single fresh scoped gate finished **MATCH**: {'MATCH': 109}, 109 requested windows, four workers, process exit 0. The scope is [touched_windows.txt](touched_windows.txt): 106 town windows and three main windows. It includes 457 affected registered rows, including 51 linked placements sharing the edited homes. [gate.log](gate.log) is the sanitized process log. The gate uses a lane-local journal and no cached-window skips.

The patch passes `git apply --check` against the saved B13 files and reverse-checks against the staged source tree. [staged_sources.tsv](staged_sources.tsv) records every B13 and delivered source SHA-256. The declaration search index was reduced from 2,723,986 bytes to the relevant symbols; `evidence/index_summary.json` preserves its original SHA-256 and census. Every delivered receipt is below 2 MB. `attempt_evidence.tsv` and the JSON plans include rejected trials; the final patch, accepted declaration table, and source-hash-bound final checks are authoritative.

**Deliveries**

- [delivery.patch](delivery.patch): source changes only, relative to B13; lane files are excluded.
- [results.tsv](results.tsv): one line for each of the 437 queue files.
- [holds.tsv](holds.tsv): 211 unresolved data declarations, 11 exact-home refinements awaiting a follow-up gate, and six non-home-copy holds.
- [touched_windows.txt](touched_windows.txt), [gate.log](gate.log), and this report.
- [prototype_followup.patch](prototype_followup.patch), its JSON row proofs, and its four-window scope: complete and row-verified, held outside the primary gate.
- Supporting source hashes, accepted declarations, signature mismatch evidence, and per-row proofs are linked above.

**HOW TO CONTINUE**

1. Apply `delivery.patch` to B13 after `git apply --check`; keep `results.tsv`, `holds.tsv`, and the evidence with the handoff.
2. Apply the separately row-verified `prototype_followup.patch` in a follow-up batch and run its one fresh scoped gate using `prototype_followup_windows.txt`. Follow callee placements through `ledger/rows.jsonl:source_row` and the source-layout resolver; a synthetic number alone does not identify the home function.
3. Work the 211 `data-definition-type-or-extent` entries in `holds.tsv`. Recover the defining object or a concrete type/extent declaration in its home image. An adjacent symbol or an identically addressed symbol in another bank does not establish its allocation size. The retained typedef in `town/func_800C41C0.c` disappears after its last unresolved data declaration is resolved. Route the five C-definition discrepancies to the appropriate home owners; the caller evidence constrains the original prototype and must not be replaced with a coercing cast.
4. Leave the six copy files to LL4. They are intentionally absent from the patch.
5. For a follow-up batch, verify each changed row/physical TU at its existing recipe, include every affected linked placement, then run one fresh scoped gate with four workers and a new journal. The guarded `run_gate.py` belongs to this completed invocation and must not be reused for a second gate.
