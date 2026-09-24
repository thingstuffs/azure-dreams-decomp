# SLUS function partitions: foundation and private build proof

Status: **build generation and full-image partition gates integrated; activation pending genuine/placement records**.
The existing whole-row module model remains active. There is no production
`config/slus_partitions.json`. Configure, row projection and full-image candidate
gating now support an optional partition plan. Genuine comparison and placement
certification still need per-owner records before a plan can be activated.
Do not activate a partition solely from the private build proof below.

## Purpose and identity

The [E0 list-cursor pilot](evidence/gp_e0_partition.md) needs one function from
`slus/code`, one from `slus/code2`, and the whole `slus/w_80041134` row. The new
`tools/build/slus_partitions.py` records each collector's immutable raw hash,
original recipe, complete canonical definition set, and disjoint subsets sent
to named modules. It retains both original row IDs and canonical editable C
files. Generated source views hold each collector remainder and its moved
function bodies. A remainder retains declarations for the moved functions.

The actual frozen and current definitions are 156 for `code` and 24 for `code2`;
these sets equal their emitted ELF function sets. The registry's 221/32 `defs`
counts also include prototypes and must not be used as physical function counts.
The [example plan](evidence/slus_partitions/example_plan.json) preserves all 180
collector functions. The E0 destination has its ordinary one-function member
41134 plus two explicit incoming function parts. No function is falsely assigned
to 41134's original logical identity, and its frozen whole-member check is kept.

## Contracts

- `load_plan` validates identities, canonical functions, unique ownership and a
  nonempty remainder. Retiring a fully distributed collector requires a separate
  explicit migration; it is not silently allowed here.
- `validate_context` checks the frozen raw hash and exact definition set, original
  recipe, known destinations, and conflicts with whole module membership or
  aggregator sources. A graph edge alone is not a historical TU assertion.
- `render_parent` accepts ordinary top-level C definitions, respecting comments,
  strings and braces. Conditional definitions, directives inside selected bodies,
  macro-defined functions and nested C includes fail closed when coverage cannot
  be established. This is a conservative source-view tool, not a general C parser.
- `expected_units` and `check_emitted` require exact physical function sets and
  reject missing or duplicate ownership. Build consumers must run the emitted
  check; source extraction by itself is not the emitted-code proof.
- `connected_context`, `row_units` and `fingerprint` describe every connected
  parent/owner and the separate physical recipes/function scopes. Fingerprints
  require all declared source/header inputs and include the alias map and tool
  code. Build consumers must supply the complete connected closure.
- `output_paths`, `render_files` and `project_edges` retain original logical
  source/object identities while using explicit generated compiler inputs.
  Projection rejects bypassed/missing remainders and recipe or object drift.
  The original logical recipe is provenance; it does **not** claim every moved
  function still uses that recipe. Per-owner recipes must remain in proofs.

The renderer writes only beneath the build directory, refuses escaping output
symlinks, and preserves unchanged output mtimes. Its CLI is:

```sh
python3 tools/slus_partitions.py render --plan config/slus_partitions.json \
  --output-dir build/partition_sources --names config/names.tsv
```

That command is shown relative to an exported build root. The optional plan
loader accepts an absent plan; the explicitly requested render command does not.

## Measured private build

The [normal-Ninja receipt](evidence/slus_partitions/build_receipt.json) and
[configure candidate diff](evidence/slus_partitions/configure.diff) prove the
build mechanics in isolation. A multi-output render edge takes the original C
files as inputs, and its `restat = 1` rule avoids rebuilding unchanged views.
The generated remainder files compile at the original collector recipes, while
the E0 module uses 2.8.1. No hand patch to the final Ninja file is needed.

The private build retains all 19 active modules, adds the E0 owner, and has
873 physical inputs projecting to the exact existing 884-row ledger. All **181
functions** in the two remainders plus destination occur exactly once. All **44
E0 words** match fresh stock, actual linked and genuine ASPSX 2.79 objects with
zero masks; this does not claim genuine equality for all collector functions.
The whole 524288-byte image matches retail SHA-256
`ae19d8d4bdd2db9a933b1e44d70dd61be670781e441d7cb37da85250a7aed31f`.
Primary review confirms actual four-byte `.sdata` ownership and non-absolute
linkage at `800814E0`, with the old absolute assignment removed, while canonical
collector files remain unchanged.

Normal source edits test both paths. Changing 41110 in canonical `code.c`
rebuilds only its destination object; changing an unmoved function rebuilds only
`code.o`. Both images fail retail equality. Restoring each source rebuilds only
the corresponding object and returns the exact retail image. `code2.o` remains
untouched in both cases. Thirteen [unit tests](../tools/tests/test_slus_partitions.py)
cover the schema, frozen provenance, missing/duplicate functions, unsupported
source forms, transitive owner closure, per-owner recipes, fingerprint freshness,
projection and filesystem output boundaries. See the
[primary review](evidence/slus_partitions/primary_review.json).

Reproduce with `python3 work/native_lane/slus_partition_build/probe.py` for the
isolated normal build and `python3 -m unittest discover -s tools/tests -p
test_slus_partitions.py -v` for the library. The private configure candidate is
saved for review; the production configure file is unchanged.

## Plural candidate compilation

`slus_module_context.compilation_sources` now returns each physical source view,
its own compiler recipe, the original row's function subset, and the complete
expected function set of that object. A collector edit renders all connected
source views privately; a whole member keeps incoming collector functions in its
actual owner context. Canonical sources and original row IDs are preserved.
Connected fingerprints include all participating parents, aggregators, whole
members, declared headers, aliases, recipes, and both rendering/adapter tools.
Existing unpartitioned module fingerprints retain their previous contract.

`verify.compile_slus_units` compiles each stream and requires exact ELF function
coverage, with no missing, additional or duplicated ownership. It refuses stale
inputs and partial compile failures. This is an input/coverage API, not a linked
retail or genuine-ASPSX verdict. `verify_slus` now dispatches partition-connected live inputs to the complete
image gate described below. Other singular compilation consumers still refuse
them until they can account for every physical stream.
Historical frozen-raw compilation remains independent.

The [compile receipt](evidence/slus_partitions/plural_receipt.json) checks all
three E0 logical inputs through this API. Both remainder objects (155 and 23
functions) and the three-function destination have identical allocated sections,
relocations and symbols to the already retail-linked private build objects.
The [negative receipt](evidence/slus_partitions/plural_negative_receipt.json)
changes a moved body and a remainder body: only the expected object changes.
A macro-generated extra function, invisible to the conservative source scanner,
is rejected by the compiled coverage check. This illustrates why source parsing
alone is not a coverage proof. Likewise, edge projection must still be followed
by exact whole-ledger equality. Malformed paths and ambiguous or invalid alias
targets fail closed.

Six context tests cover multiple destinations, incoming sibling parents, distinct
recipes, host-compiled candidate behavior, fingerprints, legacy refusals and raw
exceptions. Five compiler-boundary tests check per-owner recipes, complete emission,
header selection, source/fingerprint drift and failure without partial success.
That checkpoint passed 85 SLUS tests; the expanded suite below now passes 99.
`row_db.py check` passes. The existing runtime-directory
pilot has been recertified against
the changed verifier: full production image MATCH and genuine ASPSX 2.79 exact
with zero masks. See [review hashes](evidence/slus_partitions/plural_review.json).
Reproduce the actual MIPS routing/coverage probe with
`python3 work/native_lane/slus_plural_context/negative_probe.py`.

## Full-image gate and normal build integration

The [integration receipt](evidence/slus_partitions/integration_receipt.json)
proves the final configure/export/row-database implementation. With no plan,
configure generates the exact current pinned Ninja file. With the private E0
plan, it emits generated-source dependencies and a pre-link `partition_coverage`
stamp. That check reads every defined ELF `STT_FUNC`, including local functions,
from each remainder and destination object. Its exact-set check rejects extra,
missing and duplicated ownership. A macro-generated extra function is rejected
by ordinary Ninja before linking, even though source extraction accepted it.
All 181 functions, 884 logical rows and the 44-word unmasked genuine E0 proof
remain intact in the retail-exact private image.

`row_db.slus_edges` projects the active physical graph before expanding whole
modules. `row_db check` also projects the pinned graph and validates frozen raw
provenance; an active plan cannot silently keep the old original-source compiler
inputs. The exporter exposes frozen `raw/slus` and removes an obsolete optional
plan link when the canonical plan is removed. No production plan is present.

The [gate receipt](evidence/slus_partitions/gate_receipt.json) exercises the full
`SlusView` implementation and the row verifier. A collector candidate is written
to its original logical path in the isolated view; normal Ninja renders its
remainder and moved parts and compiles each owner at its own recipe. Implicit
logical-row recipe changes are refused because a collector can span recipes.
The gate checks the whole partition's emitted functions before comparison. It
restores original files or symlinks, recipes, generated inputs, affected objects
and the exact retail image after each trial; a failed restoration cannot return
a successful result.

Six actual MIPS scenarios cover unchanged input, edits to moved/remainder/whole
member bodies, invalid C and a hidden macro function. Only unchanged input passes;
every trial restores the original canonical inputs and exact retail image. The
row verifier independently reports a whole-collector MATCH for unchanged input
and a mismatch for a changed moved body. It checks that the isolated build uses
the current canonical sources, headers and declared partition context, then
rejects source/fingerprint drift. Historical raw verification stays standalone.

Ten gate tests cover routing, per-owner recipes, complete emitted coverage and
restoration after match/mismatch/compile/link/coverage failures. Three actual ELF
coverage tests check local functions, missing objects and protected stamp paths;
an additional registry test rejects original-source bypass and frozen-raw drift.
The full **99-test SLUS suite** and row database check pass. The production SLUS
SHA-1 gate still matches the pinned recipe and retail image, and the runtime pilot
has fresh unmasked genuine/retail certification. Verifier fingerprints now include
the partition, isolated-gate, export and projection tools.

See [review hashes](evidence/slus_partitions/gate_review.json) and the
[configure](evidence/slus_partitions/configure_integration.diff),
[export](evidence/slus_partitions/mk_root_integration.diff) and
[row-database](evidence/slus_partitions/row_db_integration.diff) changes. Reproduce
with `python3 work/native_lane/slus_partition_integration/probe.py` for the normal
build and `python3 work/native_lane/slus_partition_gate/probe.py` for candidate
routing/restoration. These remain E0 fixtures, not a global ownership rollout.

## Per-owner genuine-ASPSX measurement

The [genuine receipt](evidence/slus_partitions/genuine_receipt.json) measures each
logical row at its actual physical recipes, after the full-image partition gate
and emitted-function coverage checks. Every traced object must reproduce its
pipeline object. A row record retains disjoint function scopes, actual recipes,
whole-unit pass traces, GP externs and attribution for every physical stream.
Source, connected-context and tool fingerprints must remain stable throughout.

The top-level row keeps its original recipe as provenance. Genuine exact versions
are the intersection across all row subsets, with complete comparison coverage.
Owners exact at different versions form a separate reporting category rather than
being labelled maspsx-dependent. Owner ablations stay owner-only: their union is
not a measured intervention on the complete row. Reports retain one logical-row
denominator and emit separate physical-owner detail. The single-recipe cell trial
CLI and worker refuse connected rows before measurement or output; a per-owner
trial requires an explicit future interface. Frozen raw measurement remains
standalone.

The E0 fixture accounts for all 181 functions. Its destination's three functions
are a direct 44-word genuine ASPSX 2.79 match with zero masked relocations. Each
physical result includes a separate complete-TU comparison in the same genuine
mode; a certificate must use that result, not combine subset proofs from different
modes. The [code](evidence/slus_partitions/genuine_code.json) collector still has
156 functions and genuine difference 47; its seven unrelated GP symbols remain.
The [code2](evidence/slus_partitions/genuine_code2.json) collector still has 24
functions and genuine difference 33, with its three unrelated GP symbols retained.
Those differences are token-comparator results; their resolved positional retail
differences are 97 and 42 respectively. The
[whole member](evidence/slus_partitions/genuine_w_80041134.json) matches at 30 words.
All three logical scopes remain stock-retail-exact. None of these subset results
clears a collector's outstanding dependencies or grants it module placement.

Eighteen new tests cover complete/disjoint aggregation, missing comparison
coverage, disjoint owner versions, report consistency, owner-only ablations,
cell-trial refusal and live/raw dispatch. The **117-test SLUS suite**, 25 related
comparator/cell/configuration tests and row database check pass. The existing
runtime-directory measurement is identical except for timing; its certificate
has been refreshed against the integrated tools and full retail image. The
production SHA-1 gate also remains MATCH with the unchanged pinned recipe.
See [review hashes](evidence/slus_partitions/genuine_review.json). Reproduce the
private MIPS measurement with
`python3 work/native_lane/slus_partition_genuine/probe.py`.

The next [certificate handoff](evidence/slus_partitions/certificate_next.md)
identifies current whole-member assumptions. It is a proposal, not a placement
certificate. Data ownership and L4/L5 placement remain separate claims.

## Remaining integration, in order

1. **Implemented:** plural physical contexts, connected fingerprints and candidate
   compilation with exact emitted-function coverage. Legacy singular entry points
   refuse partition-connected live rows; frozen raw remains standalone.
2. **Implemented:** optional build generation, logical projection, pre-link ELF
   coverage and the plural `SlusView` candidate gate with full restoration.
   Normal Ninja and row verification both enforce emitted coverage.
3. **Implemented:** genuine-ASPSX records across per-owner streams with exact
   disjoint function scopes and per-owner recipes/pass traces. One original
   logical row is retained, including unrelated GP/model dependencies.
4. Extend ownership/certificate evidence with incoming function parts and fresh
   connected fingerprints. A subset proof must not grant placement to a whole
   collector. Preserve existing L4/L5 pin and fidelity requirements.
5. After negative/regression gates pass, activate E0 with the reviewed source
   and data binding, rerun the full retail/genuine gates and runtime pilot, and
   remove only dependencies proved eliminated. Then use the same mechanism for
   the remaining actual function groups.

The [consumer inventory](evidence/slus_partitions/consumers.md) identifies exact
callsites. Production remains **197 dependencies, 29 GP rows, 19 ownership
units, 873 physical / 884 logical rows**. The separate generic assembler
correction and pass retirement are still pending; this layer changes neither.
