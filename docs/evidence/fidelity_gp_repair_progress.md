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

The measurement discrepancy found before refreshing the global dependency census was:
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

Next: activate the validated module build/verification path after completing
source-metric and lane integration, then extend the proven data-recovery approach.
Finish the CD-control integration alongside it.
Preserve production defaults until the coordinated repair passes required gates
and any remaining owner sign-off.

### Build-helper checkpoint

`tools/build/slus_modules.py` now provides optional manifest validation, expansion
of physical module edges into stable logical row records, verified raw-asset
carving, ordered linker-slot replacement, and removal of the corresponding
absolute symbol assignments. Configure, row-database, candidate compilation,
whole-image verification and recipe-lander consumers now support it; no production
module manifest is active. All 13 contract tests in
`tools/tests/test_slus_modules.py` pass, including negative cases for mismatched
row IDs, ambiguous linker slots, changed assets and invalid ownership records.
A read-only check against the actual SLUS asset verifies the four-byte initializer,
EXE address mapping, prefix/data/suffix boundaries (0..44, 44..48, 48..179648),
and removal of exactly one absolute assignment.

The integration keeps canonical per-row source fragments and stable row
IDs; a standard C aggregator includes the members and shared header and owns the
data definition. Only the aggregator is compiled. The three-row pilot therefore
has 882 physical SLUS compilation edges but still 884 logical rows. These counts
are now proved in the isolated build; production still has 884 physical TUs.

Reproduce the complete configured build and candidate checks with:

```sh
python3 tools/fidelity/probe_slus_module_build.py
```

The [build receipt](slus_module_build_receipt.json) proves retail equality with
the **stock assembler and generated Ninja build**, real `.sdata` ownership at
0x80080A6C, unchanged function addresses/sizes, and logical edges identical to the
registered split table. Member/header edits rebuild the whole module; data edits
rebuild carved inputs and the linker script. The candidate gate accepts unchanged
text, rejects a one-word function change, rejects conflicting or partial-cohort
recipe changes, and restores the exact image. It also rejects a candidate whose
own function stays exact but whose macro changes a later sibling's compiled body.
The same staged source through
`compilation_source` and `compile_slus` matches genuine ASPSX 2.79 for all 104 words
(18/32/54), with zero differing or masked retail relocations. Initialized-data
relocations now resolve from agreeing named symbols in the gated linked ELF;
missing or conflicting anchors remain masked.

The name-table discrepancy is repaired: standalone compilation and both assembler
legs now use production's canonical names. The fresh [stock 59-row measurement](slus_canonical_measure_receipt.json)
has 59/59 selfchecks and direct maspsx-to-retail matches, no missing functions or
errors, and 0/59 genuine matches, agreeing with the prior stock journal. This is
the expected unrepaired external-data model; the earlier **49/59** result used
the experimental corrected assembler and is a different treatment. The production
SLUS SHA-1 gate also passes with all 884 TUs and the identical pinned recipe.

All **64 focused tests** pass across module helpers, configuration, candidate
context, canonical names, genuine comparison, recipe landing and rebaselining.
The row database check passes. The old inactive verifier patch in
`work/native_lane/slus_module_integration/` is superseded by the current tools.

Before production activation, finish module-aware lane diagnostics and status/L4
evidence, then install the reviewed manifest, shared header and sources together
with the regenerated pinned physical build. Re-run whole-image and genuine gates
and refresh only the dependency records justified by that activated source.
No global assembler default, dependency-ledger entry or L4/L5 claim changed here.
