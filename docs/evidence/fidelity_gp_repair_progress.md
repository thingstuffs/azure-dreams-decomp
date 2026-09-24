# SLUS small-data repair: isolated measurements, 2026-09-24

Progress on `docs/GOAL_TOOLCHAIN_AND_MODULES.md`. No production assembler, source,
recipe, counter, or gate has changed. The primary agent performed the assembler
experiments; Sol inventoried ownership and prepared module candidates; Luna audited
the separate MAIN coverage gaps.

## Data ownership is the implementation problem

The current 59-row dependency set contains 69 distinct globals and 111 row/symbol
pairs. None of those 69 names is defined by a built SLUS input object. The linked
ELF resolves all of them as absolute symbols through
`build_slus/config/generated/slus_006.14.undefined_syms.txt`. Their bytes live in
raw assets: three in `build/assets/3E018.o`, 66 in `build/assets/54240.o`.
Byte locations do not establish original TU ownership.

Twenty-two symbols are shared by multiple affected rows. The shared-symbol graph
has 25 components; its largest has 20 rows and seven current recipes. These are
investigation groups, not recovered original TUs. Recover real typed definitions,
initial bytes, grouping, and link placement together; do not duplicate tentative
definitions simply to recover `$gp` instructions.

Durable inventories: [rows](fidelity_gp_rows.tsv), [symbols](fidelity_gp_symbols.tsv),
and [prepared candidates](fidelity_gp_step4_candidates.tsv). Detailed report and
reproducer: `work/native_lane/gp_ownership_inventory/{REPORT.md,inventory.py}`.
Regenerate after source/data changes; the script reads the existing build.

## Assembler experiment

`tools/fidelity/probe_small_data.py` creates a private maspsx copy and tests a
generic correction against genuine ASPSX. It suppresses emitted `.extern` hints,
removes extern-size-based `$gp` hazard handling, forces downstream GNU `as -G0`
so maspsx alone selects small-data expansions, and honors `-G0` for local data.
It retains extern-size metadata internally for existing compatibility passes.

**70/70 cases match genuine ASPSX 2.79**, the pinned version. Fixtures cover loads,
stores, offsets, addresses, and hazards across small/large/unknown externs, commons,
local commons, and initialized small data, at `-G0` and `-G8`. They deliberately
omit epilogues to isolate macro/addressing behavior. Game functions test scheduling
separately. The wider 2.67/2.79/2.81 run matches 207/210: three 2.81 local-data
address loads still differ. No general version-coverage claim is made.

```sh
python3 tools/fidelity/probe_small_data.py --out work/fidelity/gp_probe279
```

The command exits nonzero on any candidate mismatch. Add
`--versions 2.67,2.79,2.81` for the wider experiment (three known failures).
The generated assembler is experimental, not an approved production switch.

## Full-build impact and natural-C candidates

An isolated SLUS view first calibrated **MATCH**, then rebuilt all 884 C objects
using the experiment. Function code/relocation comparison identifies **exactly
59 changed TUs**, the expected set; 825 are unchanged. The full image is **NO
MATCH** without source/data repair. Image differences include resulting layout
and relocation shifts, not just independently changed functions.

Fresh genuine-ASPSX 2.79 comparison gives **49/59 exact** experimental objects.
Nine residual rows already have combined helper dependencies. The tenth,
`slus/code`, has 30 normalized differing words including return/address scheduling.
Eliminating `$gp` differences alone does not establish full assembler fidelity.

Before refreshing the global dependency census, fix this measurement discrepancy:
`aspsx_diff.prepare_slus` invokes `tools/build/ccproc.py`, whose relative name-table
lookup misses `config/names.tsv`. The real exported `build_slus/tools/ccproc.py`
does load it. The new experiment applies that real canonical-name mapping to the
genuine input. Without it the result was 39/59; with it, 49/59. Also, stripping all
`.extern` lines removes metadata used by scheduling passes, so an `extern-abs`
attribution is not automatically proof of a pure `$gp` difference.

Five prepared CDK candidates have no pinned `$gp` dependency on disputed data:
`w_8003FAD4`, `w_80041588`, `w_80041AB0`, `w_80043CD0`, `w_8004AB7C`. All source
hashes still match their preparation. Each matches genuine ASPSX 2.79 with the
experiment, and all five together yield **full-image MATCH** in an otherwise
stock isolated SLUS. This diagnostic mixed-object build does not authorize a
global switch. The sixth, `w_8003D92C`, needs ownership of `D_80080ABC/ABE`.

Reproducers/receipts in `work/native_lane/gp_semantics/`: `slus_impact.py`,
`slus_impact.json`, `slus_object_impact.json`, `compare_game.py`,
`game_genuine.json`, `check_prepared.py`, `prepared_results.json`. Compact durable
receipt: [fidelity_gp_repair_receipt.json](fidelity_gp_repair_receipt.json).
No dependency-ledger entries have been removed.

## Module preparation and next actions

`work/native_lane/cd_control_module_pilot/cd_control.{c,h}` combines dungeon rows
800B79C4/800B79F8/800B7A24, using actual symbols BD124/BD158/BD184 at CDK-G0.
Original baselines and each symbol from the combined source score exact (13, 11,
16 words). One module build edge, linked-overlay proof, shared `Control_CD`
prototype reconciliation, and row-identity integration remain. No L4 claim.

The first owned-data pilot now passes a **full SLUS link**. Three CDK runtime
functions (8003C634, 8003C758, 8003C920) share one ordinary definition,
`s32 D_80080A6C = 4;`, whose initializer is the four retail bytes at file 0x5426C.
GCC emits `.sdata`; all three function sections match stock bytes and relocations,
and genuine ASPSX 2.79 matches their 18, 32, and 54 words. The private link carves
those four bytes from asset 54240, inserts the module's `.sdata`, and removes the
absolute symbol assignment. The resulting 524,288-byte image equals retail:
SHA-1 `e6bfbb95ff6676899e077481221d73ddd4d3bf52`. The symbol is section-defined
at 0x80080A6C; all function addresses and sizes remain unchanged.

Candidate C/header and object/genuine/link receipts are retained in
[`gp_data_module_pilot/`](gp_data_module_pilot/). After running the small-data
probe above, reproduce the linked proof with:

```sh
python3 tools/fidelity/probe_gp_module.py
```

This uses a private build and stock link flags. Its one combined defining TU and
two empty former TUs are diagnostic staging, not a production module-registration
scheme. Original TU ownership remains an inference; exact reconstruction and
current C data ownership are proved by the candidate and link.

Next: integrate module build edges, row identities, data placement, and source
metrics coherently, then extend the proven data-recovery approach. Repair the
measurement-path discrepancy and finish the CD-control integration in parallel.
Preserve production defaults until the coordinated repair passes required gates
and any remaining owner sign-off.

### Build-helper checkpoint

`tools/build/slus_modules.py` now provides optional manifest validation, expansion
of physical module edges into stable logical row records, verified raw-asset
carving, ordered linker-slot replacement, and removal of the corresponding
absolute symbol assignments. The helper is not wired into production yet; no
module manifest is active. All 13 contract tests in
`tools/tests/test_slus_modules.py` pass, including negative cases for mismatched
row IDs, ambiguous linker slots, changed assets and invalid ownership records.
A read-only check against the actual SLUS asset verifies the four-byte initializer,
EXE address mapping, prefix/data/suffix boundaries (0..44, 44..48, 48..179648),
and removal of exactly one absolute assignment.

The proposed integration keeps canonical per-row source fragments and stable row
IDs; a standard C aggregator includes the members and shared header and owns the
data definition. Only the aggregator is compiled. The three-row pilot therefore
has 882 physical SLUS compilation edges but still 884 logical rows. These are
integration targets, not current production counts.

Unfinished verifier/context edits are retained as an inactive draft under
`work/native_lane/slus_module_integration/`; production verification remains
unchanged. Before activation, finish configure/exported-config support, logical
ledger expansion, recipe-lander safeguards, context-aware ASPSX measurement and
receipt invalidation. Prove that edits rebuild the entire module, a sibling
regression fails the full-image gate, and conflicting member recipes are refused.
The consumer audit is recorded under `work/native_lane/slus_module_consumers/`.
