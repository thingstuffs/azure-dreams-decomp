# SLUS small-data repair: isolated measurements, 2026-09-24

Progress on `docs/GOAL_TOOLCHAIN_AND_MODULES.md`. The initial isolated measurements
below precede the production activation recorded in the next section. The primary
agent performed the assembler experiments; Sol inventoried ownership and prepared module candidates; Luna audited
the separate MAIN coverage gaps.

## Resumed private proofs

[49F68](gp_order_bytes.md) is genuine/retail-exact after an RTL-guided guard
ordering repair. Its [local-data guard](selfinc_local_guard.md) now gives the
full private image and all 50 words with every pass enabled; its 12 existing
pass consumers remain a separate retirement queue. The generic assembler
transition remains private.

## Latest ownership checkpoint

[8099C](gp_shared_8099c.md) now owns the cancellation word in an active two-row
module. Its full retail image passes. Direct genuine proof covers the setter;
the renderer's separately recorded genuine proof uses the already accepted
compiler epilogue model. Its remaining model dependency stays in the ledger.
Production: **198 dependency records, 30 GP rows, 18 ownership units,
873 physical / 884 logical rows**. The original runtime pilot is recertified.

Previous checkpoint: [Shared state at 81510](gp_shared_state_81510.md) adds two rows at their coherent
registered CDK recipe, after a byte-neutral 45340 recipe landing. All 573 words
match genuine ASPSX 2.79 and retail without masks; no compatibility pass fires.
The full image passes at 874 physical / 884 logical rows. There are now 199
dependency records and 32 remaining GP rows, with 17 active ownership units.

[Split small-data storage](gp_split_storage.md) adds a further row with three
initialized halfwords and one private uninitialized halfword in C. Production
now supports separately placed `.sdata` and zero-only `.sbss` sections. Full
image and all 53 function words pass, leaving 201 dependencies and 34 GP rows.
The existing pilot is recertified and all 87 focused tests pass.

[Runtime count and shared display slots](gp_count_and_slots.md) add seven real
C definitions for three more rows. The full image remains exact at 875 physical
and 884 logical inputs; genuine ASPSX 2.79 matches all 402 affected words with
zero masks. Dependency records fall from 205 to 202, and the GP cohort from 38
to 35. Existing pins remain. These two units have no L4 placement certificate;
the original runtime pilot is rechecked separately.

## Earlier ownership wave checkpoint

[The next integrated wave](gp_ownership_wave.md) repairs 18 more rows with 24 real
C data definitions. The full image is retail-exact at 876 physical / 884 logical
compiler rows; genuine ASPSX 2.79 matches all 781 affected function words with
zero masks and no compatibility passes firing. Dependency records: 223 -> 205;
GP cohort: 56 -> 38 remaining. This supersedes the two "next trials" below and the
old concern that explicit zero initializers necessarily require `.sbss` handling.
Twelve new ownership units have no L4 certificate; the original pilot is
recertified separately. Reproduce with `tools/fidelity/prove_slus_ownership.py`.

The generic assembler correction is still experimental. A newly precise blocker
is 47E78's address load: real C storage is already genuine/retail exact, but stock
GNU small-data optimization shrinks it; the experimental correction restores it.
The wave report preserves the corrected retail-anchor evidence and distinguishes
that assembler-owned issue from the earlier failing linked-layout comparison.

## Production module checkpoint

The three-function `runtime_directory` pilot is active with a shared header,
canonical per-row C fragments, a single ordinary C aggregator and a real signed
word definition for `D_80080A6C`. The complete image matches retail with 882
physical compiler inputs and unchanged 884 logical rows. See
[rationale and type review](runtime_directory_module.md),
[workflow](../SLUS_MODULES.md) and `ledger/modules/runtime_directory.json`.
The fresh certificate records genuine ASPSX 2.79 and retail equality for all
104 function words, zero masked relocations, and no compatibility passes fired.
Dependency entries fall from 226 to 223, with 56 of the original 59 GP rows
remaining. The earlier inventories below describe the initial 59-row state.
The unchanged ladder reports C634/C920 at L5 and C758 at L4; its existing
fidelity-site residue is retained. The global maspsx correction is still
experimental; no pass has been retired.

Lane diagnostics now compile candidates in their actual module context, reject
individual recipe changes and refuse results when sibling/header inputs change.
Module placement is certified against current sources, headers, review, pinned
recipe and verifier inputs; existing L4/L5 criteria still apply independently.
The old row inventory's C758 prototype-count artifact does not expand the pilot:
module validation checks actual bodies and genuine comparison uses the declared
member function, so external C6F8 remains outside its proof.

Remaining GP triage identifies 24 connected cohorts over 68 symbols. Eighteen
cohorts (21 rows) have a single exact recipe; six (35 rows) mix recipes. The next
clean complete-row trials are `w_800508F0` and `konami_runtime_w_80035888`, each
with two contiguous nonzero `s32` values and no other recorded users. The third
candidate `w_8004D614` is partial because two of four words are zero. The measured
shared-user graph and exact asset bytes are retained in
`work/native_lane/gp_next_cohorts/{REPORT.md,cohorts.json}`; graph components are
still investigation groups, not original translation-unit claims.

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
