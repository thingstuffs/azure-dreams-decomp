# r121w_s2 — partial delivery

Supplied private snapshot: `e72e2fcfb6bf315e58039ff464d1912986985ffb`. Work stayed in this lane and its private root. No Git commits or external ref moves were made.

**166 new complete C rows / 91,340 bytes.** These comprise 97 link-list placements of existing clean TUs and 69 new town callback functions. One existing donor home was edited to include its existing module header, making it independently compilable; its 1,452 bytes remain exact. Production validation: **65 / 65 scoped windows MATCH**, with a successful current-input audit.

| Input class | New rows | New bytes | Original records closed | Records still held |
|---|---:|---:|---:|---:|
| goto templates | 0 | 0 | 0 / 88 | 88 |
| pins/asm/volatile templates | 1 | 1,144 | 1 / 6 | 5 |
| old twins2 overlap scope | 90 | 73,476 | 90 / 113 | 23 |
| bounded SDK holds | 75 | 16,720 | 15 / 68 | 53 |
| Total | 166 | 91,340 | 106 / 275 | 169 |

Rows and hold records count different things: one bounded record can contain several functions, and supplied spans can overlap. Delivery bytes count disjoint new registered function extents once. The existing donor edit earns no new coverage bytes. `results.tsv` includes all 275 input outcomes followed by the 166 new rows. `holds.tsv` retains the unresolved input records, with their exact uncovered subspans and current reasons.

The dungeon delivery is 86 rows / 80,768 bytes. Town contributes 80 rows / 10,572 bytes. Main contributes no new rows.

## What was recovered

Ownership was rechecked against the live registered rows rather than the frozen twins2 exclusions. Partial occupancy was subtracted; it was never treated as complete coverage. No live row was deleted or shortened. Six complete 1,864-byte twins were recovered inside larger bounded spans. The other bounded recoveries are 57 constant-argument constructors and 12 entry-list callbacks in the town scene.

Each new town callback has an independently recorded entry in the scene callback tables, a complete prologue-to-return extent, an unedited genuine spimdisasm/m2c first pass, a snake_case definition, and a strict source comparison. Constructor selectors and record addresses were read from the original instructions. Callee declarations come from the existing matched constructors; entry-list handler declarations come from matched handler bodies. Constructor selectors differ semantically, so those functions cannot be shared by address rebinding.

The pin-class recovery uses the already clean complete donor `dungeon/func_80DE5258`, independently compiled before placement at `0xBBF13C`. It does not claim that the older volatile donor was cleaned.

Static placement does not infer runtime residency. All other copies are entries in `config/link/`; they introduce no copied clean C files or relocation `#define` text. Each home compiled independently. Placement scores compile the actual shared TU using its home's frozen bank evidence, invoke the production link-list rebinder, and mini-link with the production linker helpers. Every changed twin word is checked against an ELF relocation of the expected type. Switch-table contents are checked as well.

Five 1,304-byte switch functions needed additional raw-generator context. Their switch tables were bounded by consecutive aligned pointers into the complete function inside its existing proven load region. Those original bytes were passed to spimdisasm and m2c, with commands, bounds, targets and hashes recorded. Generated assembly and C were not edited.

The home edit is `src/dungeon/func_80F88C94.c`: add `modules/dungeon_ovl_fa7000.h`, the header already used by its aggregate module. This supplies the existing callback/data declarations. The standalone home and six placements match exactly.

## Validation and evidence

- Every admitted source comparison is exact: zero substitutions, zero indels, exact extent, no masked comparison.
- The row database and source aliases pass validation. Original registry records and their byte order are preserved; new rows append. Split views and the generated module graph are updated in place.
- New clean C has no pins, asm, volatile, NON_MATCHING, pragma, goto, or added masks. All 69 new definitions use snake_case names.
- All 166 raw first passes were separately measured: 20 exact, 82 compiling but different, 64 compiler failures. These actual outcomes append to the baseline ledger. No integration L0 adoption is inferred; see `levels_seed_needed.tsv`.
- Exact clean-source measurements append to promotions/reverify. Existing source and interface/gate tools are unchanged except the one donor include and new name bindings.
- The final gate is restricted to `touched_windows.txt` and uses four workers. The first proof-export attempt rejected the launcher's custom `PYTHONPATH`; no window receipts were published. The same 65-window scope passed with the canonical environment. The rejected invocation is preserved in `evidence/gate_environment_error.log`.

`docs/evidence/r121w_s2_receipts.json` is a compact text receipt under 2 MB. It includes source/raw/retail/object hashes, entry and ABI authorities, address bindings, changed-word proofs and raw-generator provenance. Full working proofs remain in the lane's ignored evidence/state directories, bound by SHA-256. No objects or other binary artifacts are included in the delivery patch.

The private root has no Git repository. Patch preimages were captured before edits. The generated module graph preimage is reconstructed deterministically with the frozen original overlay registry and unchanged module definitions. `delivery.patch` is checked in reverse against the final private tree; the preimage manifest records hashes and this graph reconstruction.

## Holds by current reason

| Reason | Input records |
|---|---:|
| Donor goto-free spelling not yet byte-exact | 88 |
| Donor pin/volatile-free spelling not yet byte-exact | 5 |
| Donor address pieces lack ELF relocations | 15 |
| Donor requires aggregate type context | 1 |
| Complete donor overlaps a live row or exceeds the bounded gap | 6 |
| Remaining complete donor still has goto | 5 |
| Remaining complete donor still has pins/volatile | 1 |
| Matched callee contracts unresolved | 20 |
| Bounded remainder needs new C or stronger complete-entry evidence | 24 |
| Main remainder lacks a proven load region or complete body contract | 4 |
| Total | 169 |

Fifteen source failures involve split literal page/low-address spellings: a link-list rebinding cannot change an immediate with no ELF relocation. They remain held despite matching most words. No alternate symbolic donor was found in the saved complete-twin inventory. The separate aggregate-context hold needs `EffectColor`'s existing layout made available to its standalone home.

The largest goto donor is 5,464 bytes, with six held placements. Its unchanged home is exact at `2.7.2-cdk-G0`; byte fingerprints support that lineage. The first complete structured spelling generates 5,476 bytes, with 144 aligned substitutions and 67 indels. It is not admitted.

The 1,456-byte grid donor has a closer structured spelling: 1,456 generated bytes, 4 aligned substitutions and 4 indels. Its frame and register roles agree with retail. The remaining differences come from hoisting the frame-point base out of the structured inner loop, shifting the initial scheduling and subsequent base use. Disabling strength reduction did not remove those differences. The full retail listing, lineage evidence, candidates and scored receipts remain in the lane. No compiler-wall conclusion is asserted. The other measured cleanups likewise remain unlanded.

## HOW TO CONTINUE

1. Apply the text patch to the supplied snapshot, rebuild `build_ovl/`, and use the supplied scoped proof receipts and `gate.log` to review the 65 touched windows. Integrate levels/baselines under the owner's policy; raw failures have been retained rather than relabeled exact.
2. Work by donor family, biggest first. Start with `dungeon/func_812A524C` (5,464 bytes × six targets); preserve retail's action-block order and three search-loop exits in a structured spelling. Prove the donor home first, then add placements. The grid's next concrete problem is retaining retail's inner-loop point-base rematerialization without goto or pins.
3. For the 15 address-piece holds, replace the donor's literal page/low spellings with a byte-exact symbolic spelling that emits genuine relocations. Prove the home first; rerun the held placement score and require every changed word to bind to ELF relocation evidence. Do not edit immediate bytes or introduce relink macros.
4. For the one aggregate-context hold, expose the existing `EffectColor` layout to the standalone home without duplicating a function body. Recheck the aggregate module and the held placement after an independently exact home score.
5. Continue the bounded spans from the residual intervals in `holds.tsv`. Entry/caller and pointer-table evidence must identify complete uncovered functions. Leave live tails and partially overlapping complete donors in place. The current constructor and entry-list callback surveys are exhausted for their recognized forms; other shapes need new C and ABI evidence.
6. Keep one mutation runner. Existing code is shared through link-list placements. Use per-row scores during admission and one final production gate over only the newly touched windows, with `--workers 4 --only-window ...`. Keep generated first passes unedited, preserve failed measurements, and publish text receipts and hashes rather than binaries.

Continuation tools and candidates are in this lane: `survey.py`, `plan.py`, `row_score.py`, `admit*.py`, `raw_extra.py`, `new_wrappers.py`, `new_entry_wrappers.py`, and `candidates/`. They describe this completed run's frozen inputs; refresh ownership before reusing them on a different root. `admit.py` is the initial transaction, not a restart command for an already populated link-list tree.
